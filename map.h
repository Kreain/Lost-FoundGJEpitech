#ifndef MAP
#define MAP

#include "libs.h"

int sizeY = 10; int sizeX = 20;
int sizeD = 32; //32 pixels dessin
int nbDitems = 10; //10 items max dans le tileset par ligne
int maxMapFinJeu = 0;

sfTexture* texture_map;
sfSprite* sprite_map;

int map[10][20];

int entryX = 0; int entryY = 0;
int exitX = 0; int exitY = 0;
int entree = 998; int sortit = 999;

int map1[10][20] = {
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,1,2,3,0,0,0,5,0,4,0,1,2,3,0,2,0,0,7,4},
	{0,1,2,3,0,2,0,0,0,4,0,1,2,3,0,2,3,0,0,999},
	{0,1,2,3,0,2,0,5,7,4,0,1,2,3,0,2,3,5,7,4},
	{0,1,2,3,0,2,0,5,0,0,0,1,2,3,0,2,3,5,7,4},
	{0,1,0,0,0,2,0,0,0,4,0,1,2,3,0,2,3,5,7,4},
	{0,1,2,0,0,0,3,5,7,4,0,1,2,3,0,2,3,5,7,4},
	{0,1,2,3,0,0,3,5,7,4,0,0,0,0,0,2,3,5,7,4},
	{0,1,2,0,0,0,3,5,7,4,0,1,2,3,0,2,3,5,7,4},
	{998,0,0,0,0,2,3,5,7,4,0,1,2,3,0,2,3,5,7,4}
};

/*const int map2[5][10] = {
	{0,1,2,3,0,2,3,5,4,4},
	{0,1,2,3,0,2,3,5,4,1000},
	{0,1,2,3,0,2,3,5,4,4},
	{999,1,2,3,0,2,3,5,4,4},
	{0,1,2,3,0,2,3,5,4,4}
};*/

/*const int map3[5][10] = {
	{0,1,2,3,0,2,3,5,4,4},
	{0,1,2,3,0,2,3,5,4,1000},
	{0,1,2,3,0,2,3,5,4,4},
	{999,1,2,3,0,2,3,5,4,4},
	{0,1,2,3,0,2,3,5,4,4}
};*/

/*const int map4[5][10] = {
	{0,1,2,3,0,2,3,5,4,4},
	{0,1,2,3,0,2,3,5,4,1000},
	{0,1,2,3,0,2,3,5,4,4},
	{999,1,2,3,0,2,3,5,4,4},
	{0,1,2,3,0,2,3,5,4,4}
};*/

/*const int map5[5][10] = {
	{0,1,2,3,0,2,3,5,4,4},
	{0,1,2,3,0,2,3,5,4,1000},
	{0,1,2,3,0,2,3,5,4,4},
	{999,1,2,3,0,2,3,5,4,4},
	{0,1,2,3,0,2,3,5,4,4}
};*/

void update_map(int choix) {
	for (int y = 0; y < sizeY; y++) {
		for (int x = 0; x < sizeX; x++) {
			if (choix == 0) {
				map[y][x] = map1[y][x];
			}
			else if (choix == 1) {
				//map[y][x] = map2[y][x];
			}
			if (map[y][x] == entree) {
				entryX = x;
				entryY = y;
			}
			else if (map[y][x] == sortit) {
				exitX = x;
				exitY = y;
			}
		}
	}
};

int detectionMurGauche(int posX, int posY) {
	if (posY >= sizeY || posX >= sizeX || posY < 0 || posX < 0)
		return 1;
	if (map[posY][posX]==0 || map[posY][posX] == sortit || map[posY][posX] == entree)
		return 0;
	else
		return 1;
}
int detectionMurDroite(int posX, int posY) {
	if (posY >= sizeY || posX >= sizeX || posY < 0 || posX < 0)
		return 1;
	if (map[posY][posX] == 0 || map[posY][posX] == sortit || map[posY][posX] == entree)
		return 0;
	else
		return 1;
}
int detectionMurHaut(int posX, int posY) {
	if (posY >= sizeY || posX >= sizeX || posY < 0 || posX < 0)
		return 1;
	if (map[posY][posX] == 0 || map[posY][posX] == sortit || map[posY][posX] == entree)
		return 0;
	else
		return 1;
}
int detectionMurBas(int posX, int posY) {

	if (posY >= sizeY || posX >= sizeX || posY<0 || posX<0)
		return 1;

	if (map[posY][posX] == 0 || map[posY][posX] == sortit || map[posY][posX] == entree)
		return 0;
	else
		return 1;
}

void affichage_map(sfRenderWindow* window) {
	for (int y = 0; y < sizeY; y++) {
		for (int x = 0; x < sizeX; x++) {
			int x_2 = ((map[y][x] - 1) % nbDitems) * sizeD;
			int y_2 = (map[y][x] / nbDitems) * sizeD;
			sfIntRect rectangle = { x_2,y_2,sizeD,sizeD};
			sfVector2f position = { sizeD * x, sizeD * y };
			//case visible
			if (map[y][x] == 11) {
				sfSprite_setColor(sprite_map, sfWhite);
			}
			else{
				sfSprite_setColor(sprite_map, sfBlack);
			}
			sfSprite_setPosition(sprite_map, position);
			sfSprite_setTextureRect(sprite_map,rectangle);
			sfRenderWindow_drawSprite(window, sprite_map, NULL);
		}
	}
}

#endif