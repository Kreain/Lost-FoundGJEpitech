#include "libs.h"
#include "map.h"

int compteurNiveau = 0;

int main(){
	//fenetre
	sfVideoMode mode = { 1920, 1080, 32 };
	sfEvent event;
	//sfRenderWindow* window = sfRenderWindow_create(mode, "SFML window", sfResize | sfClose, NULL);
	sfRenderWindow* window = sfRenderWindow_create(mode, "SFML window", sfResize | sfClose, NULL);
	//font & text
	sfFont* font; 
	font = sfFont_createFromFile("base.ttf");
	if (!font)
		return EXIT_FAILURE;
	sfText* text;
	text = sfText_create();
	sfText_setFont(text, font);
	sfText_setFillColor(text, sfWhite);
	sfText_setString(text, "0");
	sfText_setCharacterSize(text, 25);
	//map dessins
	texture_map = sfTexture_createFromFile("tilesheet.png", NULL);
	if (!texture_map)
		return EXIT_FAILURE;
	sprite_map = sfSprite_create();
	sfSprite_setTexture(sprite_map, texture_map, sfTrue);
	//map (y/x)
	update_map(compteurNiveau);
	//caméra
	sfView* view;
	view = sfView_create();
	sfVector2f size = {sizeX*sizeD,sizeY*sizeD};
	sfVector2f sizeCenter = {(sizeX*sizeD)/2,sizeY*sizeD/2};
	sfView_setSize(view, size);
	sfView_setCenter(view, sizeCenter);
	//personnage
	//boucle
	while (sfRenderWindow_isOpen(window)){
		while (sfRenderWindow_pollEvent(window, &event)){
			//événements clavier
			if (event.type == sfEvtClosed)
				sfRenderWindow_close(window);
		}
		//render
		sfRenderWindow_clear(window, sfBlack);
		//affichage
		affichage_map(text, window, view);
		sfRenderWindow_display(window);
	}
	//destroy
	sfRenderWindow_destroy(window);
	sfFont_destroy(font);
	sfText_destroy(text);
	sfSprite_destroy(sprite_map);
	sfTexture_destroy(texture_map);
	sfView_destroy(view);
	return EXIT_SUCCESS;
}