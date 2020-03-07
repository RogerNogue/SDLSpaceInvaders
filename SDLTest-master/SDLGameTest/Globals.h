#ifndef _GLOBALS_
#define _GLOBALS_
/*
Globals file
*/

enum update_status
{
	UPDATE_CONTINUE = 1,
	UPDATE_STOP,
	UPDATE_ERROR
};

#define SAFE_RELEASE(X) if(X != nullptr){delete X; X = nullptr;}

#define SCREEN_WIDTH 512
#define SCREEN_HEIGHT 512
//margins of 10 units
#define RIGHT_BORDER_POSITION 502
#define LEFT_BORDER_POSITION 10

//////////enemy definitions//////////
#define ENEMY_HEALTHPOINTS 2
#define NUM_ENEMIES 27
#define ENEMY_DIMENSIONS 25
#define ENEMIES_PER_ROW 9
#define X_SEPARATION_BETWEEN_ENEMIES 50
#define Y_SEPARATION_BETWEEN_ENEMIES 50
#define STARTING_ENEMIES_X 50
#define STARTING_ENEMIES_Y 50
//amount of times enemies go down once reached a corner
#define ENEMY_DOWN_STEPS 5
#define ENEMY_STARTING_SPEED 1

#define ENEMY_FIRE_CHANCE 997
#define ENEMY_FIRE_MAX_VAL 1000
#define SCORE_PER_KILL 5
//events are:
//1: enemies going down one level
//2: enemy dying
#define SPEED_INCREASE_PER_EVENT 1

//////////player definitions//////////
#define PLAYER_HEALTHPOINTS 5
#define PLAYER_DIMENSIONS 30
#define PLAYER_SPEED 5
//min game loops between player projectiles
#define PLAYER_FIRE_TIME 40

#define PROJECTILE_DIMENSIONS 10
#define PROJECTILE_SPEED 5

//////////obstacle definitions//////////
#define NUM_OBSTACLES 3
#define X_POSITION_LEFT_OBSTACLE 50
#define X_SEPARATION_BETWEEN_OBSTACLES 150
#define OBSTACLES_Y_POSITION 300
#define OBSTACLES_X_DIMENSIONS 100
#define OBSTACLES_Y_DIMENSIONS 100
#define OBSTACLES_HEALTHPOINTS 2


#endif
