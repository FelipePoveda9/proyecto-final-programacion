#include "Weapon.h"
#include "TextureManager.h"
#include "Player.h"
#include "SoundManager.h"
#include <iostream>

Weapon::Weapon()
{
	auto texMgr = TextureManager::getInstance();
	sprite = new Animated();
	sprite->tex = texMgr->getTexture("");
	damage = 20;
	maxAmmo = 35;
	range = 10;
	ammoCount = maxAmmo;
	reloading = false;
}

void Weapon::shoot()
{
	if (ammoCount) {
		SoundManager* soundManager = SoundManager::getInstance();
		Sound shootSound = soundManager->getSound("shoot.mp3"); //sonido de disparo
		SetSoundVolume(shootSound, 0.5);
		PlaySound(shootSound);
		ammoCount--;
		reloading = true;
	}
}

bool Weapon::canShoot()
{
	return not reloading and (ammoCount > 0);
}

bool Weapon::refillAmmo(int refill)
{
	if (ammoCount < maxAmmo) {
		SoundManager* soundManager = SoundManager::getInstance();
		Sound AmmoSound = soundManager->getSound("ammo.mp3"); //sonido de recogida de municion
		PlaySound(AmmoSound);
		if (ammoCount + refill > maxAmmo) {
			ammoCount = maxAmmo;
		}
		else {
			ammoCount += refill;
		}
		return true;
	}
	return false;
}

int Weapon::getDamage()
{
	return damage;
}

int Weapon::getRange()
{
	return range;
}
