#ifndef PERSO
#define PERSO

#include "libs.h"

sfTexture* texture_perso;
sfSprite* sprite_perso;
sfClock* cloak;

int persoY = 0; int persoX = 0;
int sizePixels = 32; //32 pixels dessin
int deplacement = 32;
int valeur = 0;

int maxY = 0; int maxX = 0;

void set_max(int x, int y) {
	maxY = y; maxX = x;
}

void deplacement_perso(int valeur) {
	sfVector2f position = { 0, 0 };
	if (valeur == 0) {
		if(sfSprite_getPosition(sprite_perso).x<maxX-deplacement)
			position.x += deplacement;
	}
	else if (valeur == 1) {
		if (sfSprite_getPosition(sprite_perso).x > 0)
			position.x -= deplacement;
	}
	else if (valeur == 2) {
		if (sfSprite_getPosition(sprite_perso).y < maxY - deplacement)
			position.y += deplacement;
	}
	else if (valeur == 3) {
		if (sfSprite_getPosition(sprite_perso).y > 0)
			position.y -= deplacement;
	}
	sfSprite_move(sprite_perso, position);
}

void update_perso(int choix) {
	if (choix == 0) {
		persoY = 3;
		persoX = 0;
	}
	else if (choix == 1) {
		//persoY = 0;
		//persoX = 0;
	}
	sfVector2f position = { sizePixels * persoX, sizePixels * persoY };
	sfSprite_setPosition(sprite_perso, position);
};

void affichage_perso(sfWindow* window, sfInt32 temps) {
	if (temps > 100) {
		sfClock_restart(cloak);
		valeur = valeur + 1;
		if (valeur > 3)
			valeur = 0;
		sfIntRect rectangle = { valeur * sizePixels,0,32,32 };
		sfSprite_setTextureRect(sprite_perso, rectangle);
	}
	sfRenderWindow_drawSprite(window, sprite_perso, NULL);
}

#endif