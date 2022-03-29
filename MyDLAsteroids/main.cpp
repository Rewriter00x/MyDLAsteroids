#include "MyDLAsteroidsFramework.h"
#include "MyFramework.h"
#include <iostream>

static int ScreenWidth = 1024;
static int ScreenHeight = 768;
static int MapWidth = ScreenWidth * 2;
static int MapHeight = ScreenHeight * 2;
static int EnemyNumber = 100;
static int Ammo = 3;
static float AbilityChance = 0.2;

int main(int argc, char *argv[])
{
    srand((unsigned int)time(0));
    return run(new MyDLAsteroidsFramework(ScreenWidth, ScreenHeight, MapWidth, MapHeight, EnemyNumber, Ammo, AbilityChance));
    //return run(new MyFramework);
}
