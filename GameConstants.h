#pragma once

#define DEBUG true 

// GameConstants
static float sPlayerShipAcceleration = 40.f;
static float sPlayerShipMaxVelocity = 300.f;
static float sPlayerShipAngularAcceleration = 0.5f;
static float sPlayerShipMaxAngularVelocity = 100.f;
static float sPlayerBulletSpeed = sPlayerShipMaxVelocity + 50.f;

// States
enum class GameState {
	LOADING,
	MAIN_MENU,
	MENU,
	PLAYING,
	PAUSE_MENU,
	GAME_OVER,
	UNLOADING
};