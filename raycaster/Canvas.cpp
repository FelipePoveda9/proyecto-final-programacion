#include <cmath>
#include <string>
#include <iostream>
#include <algorithm>
#include "Canvas.h"
#include "Drawable.h"

Canvas::Canvas()
{
	screenWidth = 0;
	screenHeight = 0;
	windowWidth = 0;
	windowHeight = 0;
	halfWindowHeight = 0;
	halfWindowWidth = 0;
	FOV = 0;
	halfFOV = 0;
	screenDist = 0;
	scale = 0;
	rayCaster = RayCaster();
	backgroundOffset = 0;
	cellSize = 0;
}

Canvas::Canvas(int width, int height)
{
	screenWidth = width;
	screenHeight = height;
	windowWidth = screenWidth * 0.8;
	windowHeight = screenHeight * 0.8;
	halfWindowWidth = windowWidth / 2;
	halfWindowHeight = windowHeight / 2;

	FOV = PI / 3;
	halfFOV = FOV / 2;
	screenDist = halfWindowWidth / tan(halfFOV);
	
	int numRays = windowWidth/2;
	double deltaAngle = FOV / numRays;
	rayCaster = RayCaster(numRays, deltaAngle);
	scale = windowWidth / numRays;

	backgroundOffset = 0;

	cellSize = windowHeight / GRID_SIZE;
}

void Canvas::startWindow()
{
	InitWindow(windowWidth, windowHeight, "");
	SetWindowState(FLAG_VSYNC_HINT);
	SetTargetFPS(60);
	DisableCursor();
	textureManager.loadTexturesToVRAM();
}

void Canvas::draw(const Map& map, const Player& player) 
{
	BeginDrawing();
		ClearBackground(BLACK);
		draw3D(player, map);
	EndDrawing();
}

void Canvas::draw3D(const Player& player, const Map& map)
{	
	drawBackground();

	//add walls to queue
	double rayAngle = player.angle - (halfFOV) + 0.0001;
	auto rays = rayCaster.getAllRays(rayAngle, player, map);
	for (auto& ray : rays) {
		Drawable* castedPtr = &ray;
		drawQueue.push_back(castedPtr);
	}
	rayCaster.clearRays();

	//add objects to draw queue
	
	Object test;
	test.position = { 3.5 ,4.5 };
	test.depth = test.getDistanceFromPlayer(player);
	drawQueue.push_back(&test);
	//sort queue by depth from player
	std::sort(drawQueue.begin(), drawQueue.end(), [](const Drawable* a, const Drawable* b) { return a->depth > b->depth; });
	RayCastResult* rayPtr;
	Object* objPtr;
	for (auto& drawablePtr : drawQueue) {
		rayPtr = dynamic_cast<RayCastResult*>(drawablePtr);
		objPtr = dynamic_cast<Object*>(drawablePtr);
		if (rayPtr) {
			drawColumn(*rayPtr);
		}
		else if (objPtr) {
			drawObject(*objPtr, player);
		}
	}
	drawQueue.clear();

	drawWeapon();
}

void Canvas::drawObject(Object& object, const Player& player)
{
	//difference between player position and object position;
	Point2D d;
	d.x = object.position.x - player.position.x;
	d.y = object.position.y - player.position.y;
	double angleToSprite = atan2(d.y, d.x);

	//angle from player direction to sprite
	double delta = angleToSprite - player.angle;
	if ((d.x > 0 and player.angle > PI) or (d.x < 0 and d.y < 0)) {
		delta += PI * 2;
	}

	double deltaRays = delta / rayCaster.getDeltaAngle();
	auto halfNumRays = rayCaster.getNumRays() / 2;
	int screenPosX = (halfNumRays + deltaRays) * scale;

	double dist = object.getDistanceFromPlayer(player);

	Texture tex = textureManager.getTexture("sprites\\static\\imp.png");
	if ((-tex.width < screenPosX) and (screenPosX < (windowWidth + tex.width)) and dist > 0.5) {
		float spriteScale = 0.8f;
		double imgRatio = (float)tex.width / (float)tex.height;
		double proj = screenDist / dist * spriteScale;
		double projWidth = proj * imgRatio;
		double projHeight = proj;
		double halfWidth = projWidth / 2;
		double posX = screenPosX - halfWidth;
		double heightShift = projHeight * 0.27;
		double posY = halfWindowHeight - projHeight/2 + heightShift;
		object.textureArea = { 0,0, (float)tex.width, (float)tex.height };
		object.positionOnWindow = { (float)(posX), (float)(posY), (float)(projWidth), (float)(projHeight)};
		Color textureColor = WHITE;
		double darkness = 0.000009;
		textureColor.r = 225 / (1 + pow(object.depth, 5) * darkness);
		textureColor.g = 225 / (1 + pow(object.depth, 5) * darkness);
		textureColor.b = 225 / (1 + pow(object.depth, 5) * darkness);
		DrawTexturePro(tex, object.textureArea, object.positionOnWindow, { 0,0 }, 0, textureColor);
	}
}

void Canvas::drawColumn(RayCastResult ray)
{
	Color wallColor = WHITE;
	double darkness = 0.000009;
	wallColor.r = 225 / (1 + pow(ray.depth, 5) * darkness);
	wallColor.g = 225 / (1 + pow(ray.depth, 5) * darkness);
	wallColor.b = 225 / (1 + pow(ray.depth, 5) * darkness);

	double projectionHeight = screenDist / (ray.depth + 0.0001);

	Texture columnTexture;
	switch (ray.wall) {
		case brick:
			columnTexture = textureManager.getTexture("walls\\brick.png");
			break;
		case stone:
			columnTexture = textureManager.getTexture("walls\\stone.png");
			break;
		case mossyStone:
			columnTexture = textureManager.getTexture("walls\\mossy_stone.png");
			break;
		default:
			columnTexture = textureManager.getTexture("");
			break;
	}

	if (ray.horizontalTextureOffset > columnTexture.width) {
		ray.horizontalTextureOffset = 0;
	}
	Rectangle source = { ray.horizontalTextureOffset * (columnTexture.width - scale), 0, scale, columnTexture.height };
	Rectangle dest = { ray.index * scale, halfWindowHeight - (projectionHeight / 2), scale, projectionHeight };
	ray.textureArea = source;
	ray.positionOnWindow = dest;
	DrawTexturePro(columnTexture, ray.textureArea, ray.positionOnWindow, { 0,0 }, 0.f, wallColor);
}

void Canvas::drawWeapon()
{
	Texture2D shotgun = textureManager.getTexture("sprites\\static\\shotgun.png");
	double shotgunScale = 0.5;
	Vector2 position = { halfWindowWidth - (shotgun.width * shotgunScale) / 4, windowHeight - (shotgun.height * shotgunScale)};
	DrawTextureEx(shotgun, position, 0, shotgunScale, WHITE);
}

void Canvas::drawBackground()
{
	Texture background = textureManager.getTexture("backgrounds\\sunset.png");
	backgroundOffset += GetMouseDelta().x * 1.1;
	if (backgroundOffset > background.width) {
		 backgroundOffset = 0;
	}
	Rectangle source = { backgroundOffset, 0, background.width, background.height };
	Rectangle dest = { 0, 0, windowWidth, halfWindowHeight };
	DrawTexturePro(background, source, dest, { 0,0 }, 0, WHITE);
	Color light = { 30, 30, 20 ,255 };
	DrawRectangleGradientV(0, halfWindowHeight, windowWidth, halfWindowHeight, BLACK, light);
}


//TODO: usar funciones para dibujar minimapa

void Canvas::drawPlayer(Player player)
{
	int x = player.position.x * cellSize;
	int y = player.position.y * cellSize;
	double cosA = cos(player.angle);
	double sinA = sin(player.angle);
	DrawCircle(x, y, cellSize / 9, YELLOW);
	DrawLine(x, y, x + cosA * 20, y + sinA * 20, YELLOW);
}


void Canvas::drawMap(Map map)
{
	for (int row = 0; row < GRID_SIZE; row++) {
		for (int column = 0; column < GRID_SIZE; column++) {
			if (map.getElementAt(row, column) == 0) {
				DrawRectangle(column * cellSize, row * cellSize, cellSize, cellSize, BLACK);
			}
			else {
				DrawRectangle(column * cellSize, row * cellSize, cellSize, cellSize, WHITE);
			}
		}
	}
}

void Canvas::drawRay2D(Point2D end)
{
	int x = end.x * cellSize;
	int y = end.y * cellSize;
	DrawCircle(x, y, cellSize / 9, GREEN);
}

void Canvas::drawRay2D(Point2D start, Point2D end)
{
	Vector2 pos;
	Vector2 hit;
	pos.x = start.x * cellSize;
	pos.y = start.y * cellSize;
	hit.x = end.x * cellSize;
	hit.y = end.y * cellSize;
	DrawLineEx(pos, hit,  1.f, GREEN);
}