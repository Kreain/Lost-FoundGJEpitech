#include "libs.h"

int main(){
	//fenetre
	sfVideoMode mode = { 1200, 600, 32 };
	sfEvent event;
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
	const sizeD = 32;
	//map (y/x)
	const sizeY = 5; const sizeX = 10;
	const int map[5][10] = {
			{0,1,2,3,0,2,3,5,4,4},
			{0,1,2,3,0,2,3,5,4,4},
			{0,1,2,3,0,2,3,5,4,4},
			{0,1,2,3,0,2,3,5,4,4},
			{0,1,2,3,0,2,3,5,4,4}
	};
	//caméra
	sfView* view;
	view = sfView_create();
	sfVector2f size = { (sizeX * sizeD)*1.1,(sizeY*sizeD)*1.1};
	sfVector2f center = { 150,75 };
	sfView_setCenter(view, center);
	sfView_setSize(view, size);
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
		for (int y = 0; y < sizeY; y++) {
			for (int x = 0; x < sizeX; x++) {
				sfVector2f vector = {x*sizeD,y*sizeD};
				char s[10];
				sprintf_s(s, 10, "%d", map[y][x]);
				sfText_setString(text, s);
				sfText_setPosition(text, vector);
				sfRenderWindow_setView(window,view);
				sfRenderWindow_drawText(window, text, NULL);
				sfRenderWindow_getDefaultView(window);
			}
		}
		sfRenderWindow_display(window);
	}
	//destroy
	sfRenderWindow_destroy(window);
	sfFont_destroy(font);
	sfText_destroy(text);
	return EXIT_SUCCESS;
}