#include <raylib.h>
#include <iostream>
#include <cmath>
#include "Player.h"
#include "TextureManager.h"
#include "SoundManager.h" 

void Player::act(Map& map)
{
	if (isAlive()) {
		move(map);
		attack();
	}
	hurtTimer += GetFrameTime();
}

void Player::move(Map& map)
{
	double cosAngle = cos(angle);
	double sinAngle = sin(angle);
	double speedPlayer = speed * GetFrameTime();
	Point2D d = { 0,0 };
	if (IsKeyDown(KEY_W)) {
		d.x += speedPlayer * cosAngle;
		d.y += speedPlayer * sinAngle;
	}
	if (IsKeyDown(KEY_S)) {
		d.x += -speedPlayer * cosAngle;
		d.y += -speedPlayer * sinAngle;
	}
	if (IsKeyDown(KEY_A)) {
		d.x += speedPlayer * sinAngle;
		d.y += -speedPlayer * cosAngle;
	}
	if (IsKeyDown(KEY_D)) {
		d.x += -speedPlayer * sinAngle;
		d.y += speedPlayer * cosAngle;
	}
	if (map.isPositionEmpty((int)(position.y + d.y), (int)position.x)) {
		position.y += d.y;
	}
	if (map.isPositionEmpty((int)position.y, (int)(position.x + d.x))) {
		position.x += d.x;
	}


	bool isNearDoorY = map.isDoor(int(position.y + d.y), int(position.x));
	bool isNearDoorX = map.isDoor(int(position.y), int(position.x + d.x));
	bool isNearDoor = isNearDoorX || isNearDoorY;

	if (isNearDoor && IsKeyPressed(KEY_SPACE) && !map.isDoor(int(position.y), int(position.x)) ) {
		if (isNearDoorX) {
			map.toggleDoor(int(position.y), int(position.x + d.x));
		}
		else {
			map.toggleDoor(int(position.y + d.y), int(position.x));
		}
	}

	SoundManager* soundManager = SoundManager::getInstance();
	Sound walkSound = soundManager->getSound("walk.mp3");
	if (IsKeyDown(KEY_W) || IsKeyDown(KEY_A) || IsKeyDown(KEY_S) || IsKeyDown(KEY_D)) {
		if (!IsSoundPlaying(walkSound)) {
			PlaySound(walkSound);
		}
	}
	else {
		if (IsSoundPlaying(walkSound)) {
			StopSound(walkSound);
		}
	}

	if (GetMouseDelta().x < 0) {
		angle -= sensibility * GetFrameTime() * -GetMouseDelta().x;
		if (angle < 0) {
			angle = 2 * PI;
		}
	}
	if (GetMouseDelta().x > 0) {
		angle += sensibility * GetFrameTime() * GetMouseDelta().x;
		if (angle > 2 * PI) {
			angle = 0;
		}
	}
}

void Player::takeDamage(int damage)
{
	std::cout << hurtTimer << "\n";
	if (hurtTimer > 0.3) {
		SoundManager* soundManager = SoundManager::getInstance();
		Sound hurtSound = soundManager->getSound("EnemyAttack.mp3"); //sonido de da�o
		PlaySound(hurtSound);
		health -= damage;
		hurtTimer = 0;
	}
}

void Player::attack()
{
	if (IsMouseButtonDown(MOUSE_BUTTON_LEFT) && weapon->canShoot()) {
		weapon->shoot();
		justShot = true;
	}
	else if (!weapon->canShoot() && IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
		SoundManager* soundManager = SoundManager::getInstance();
		Sound noAmmoSound = soundManager->getSound("reload.mp3"); //sonido cuando no hay balas
		PlaySound(noAmmoSound);
	}
}

bool Player::heal(int healthPoints)
{
	if (health < maxHealth) {
		SoundManager* soundManager = SoundManager::getInstance();
		Sound healSound = soundManager->getSound("heal.mp3"); //sonido de recogida de vida
		PlaySound(healSound);
		if (healthPoints + health > maxHealth) {
			health = maxHealth;
		}
		else {
			health += healthPoints;
		}
		return true;
	}
	return false;
}

void Player::reset()
{
	health = maxHealth;
	angle = PI/2;
	position = { 2, 2 };
	justShot = false;
	weapon->refillAmmo(10);
}

void Player::setSensibility(double sensibility)
{
	this->sensibility = sensibility;
}


double Player::getSensibility()
{
	return sensibility;
}

int Player::getMaxHealth()
{
	return maxHealth;
}

Player* Player::instance = nullptr;

Player* Player::getInstance()
{
	if (!instance) {
		instance = new Player();
	}
	return instance;
}

Player::Player()
{
	maxHealth = 100;
	hurtTimer = 0;
	health = maxHealth;
	speed = 5.0;
	sensibility = 0.1f;
	hurt = false;
	weapon = new Weapon();
	justShot = false;


	//initialize weapon texture
	auto texMgr = TextureManager::getInstance();
	weapon->sprite = new Animated();
	weapon->sprite->animationIndex = 0;
	Texture staticTex = texMgr->getTexture("sprites/static/shotgun.png");
	weapon->sprite->tex = staticTex;
	weapon->sprite->textureArea = { 0, 0, (float)staticTex.width, (float)staticTex.height };
	weapon->sprite->positionOnWindow.width = staticTex.width;
	weapon->sprite->positionOnWindow.height = staticTex.height;
	//shooting animation
	Animation shooting = {};
	shooting.texture = texMgr->getTexture("sprites/animated/gun.png");
	shooting.numFrames = 11;
	shooting.animationSpeed = 5.0;
	shooting.textureArea = { 0, 0, (float)shooting.texture.width, (float)shooting.texture.height };
	shooting.positionOnWindow.width = (float)(shooting.texture.width / shooting.numFrames);
	shooting.positionOnWindow.height = (float)(shooting.texture.height);
	weapon->sprite->animations.push_back(shooting);
}