#ifndef MAP
#define MAP

#include <stdio.h>
#include <stdlib.h>
#include <SFML/Graphics.h>

const int sizeY = 5;const int sizeX = 10;
const int sizeD = 32; //32 pixels dessin
const int nbDitems = 10; //10 items max dans le tileset par ligne

sfTexture* texture_map;
sfSprite* sprite_map;

int map[5][10];

const int map1[5][10] = {
	{0,1,2,3,0,2,3,5,7,4},
	{0,1,2,3,0,2,3,5,10,1000},
	{0,1,2,3,0,2,3,5,11,4},
	{999,1,2,3,0,2,3,5,4,4},
	{0,1,2,3,0,2,3,5,4,4}
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

void update_map(int choix) {
	for (int y = 0; y < sizeY; y++) {
		for (int x = 0; x < sizeX; x++) {
			if (choix == 0) {
				map[y][x] = map1[y][x];
			}
			else if (choix == 1) {
				//map[y][x] = map2[y][x];
			}
		}
	}
};

void affichage_map(sfText* text, sfWindow* window, sfView* view) {
	for (int y = 0; y < sizeY; y++) {
		for (int x = 0; x < sizeX; x++) {
			sfRenderWindow_setView(window, view);
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
			sfRenderWindow_getDefaultView(window);
		}
	}
}

#endif