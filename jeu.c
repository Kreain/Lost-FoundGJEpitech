#include "libs.h"
#include "map.h"
#include "perso.h"

int compteurNiveau = 0;
float volumeCoeur = 20.f;
float vitesseCoeur = 0.8f;

void jeu(){
	//fenetre fullscreen par défault
	sfVideoMode mode = { sfVideoMode_getDesktopMode().width, sfVideoMode_getDesktopMode().height, sfVideoMode_getDesktopMode().bitsPerPixel };
	sfRenderWindow* window = sfRenderWindow_create(mode, "SFML window", sfFullscreen, NULL);
	sfEvent event;
	//font & text
	sfFont* font; 
	font = sfFont_createFromFile("base.ttf");
	if (!font)
		return EXIT_FAILURE;
	/*sfText* text;
	text = sfText_create();
	sfText_setFont(text, font);
	sfText_setFillColor(text, sfWhite);
	sfText_setString(text, "0");
	sfText_setCharacterSize(text, 25);*/
	//musique
	sfMusic* music = sfMusic_createFromFile("music/battement.ogg");
	sfMusic_play(music);
	sfMusic_setLoop(music, sfTrue);
	sfMusic_setVolume(music, volumeCoeur);
	sfMusic_setPitch(music, vitesseCoeur);
	//personnage
	texture_perso = sfTexture_createFromFile("pict/perso.png", NULL);
	if (!texture_perso)
		return EXIT_FAILURE;
	sprite_perso = sfSprite_create();
	sfSprite_setTexture(sprite_perso, texture_perso, sfTrue);
	//temps
	cloak = sfClock_create();
	sfClock_restart(cloak);
	//timer.microseconds;
	//map dessins
	texture_map = sfTexture_createFromFile("pict/tilesheet.png", NULL);
	if (!texture_map)
		return EXIT_FAILURE;
	sprite_map = sfSprite_create();
	sfSprite_setTexture(sprite_map, texture_map, sfTrue);
	//map (y/x)
	update_map(compteurNiveau);
	update_perso(entryX,entryY);
	set_max(sizeX* sizeD,sizeY* sizeD);
	//cam�ra
	sfView* view;
	view = sfView_create();
	sfVector2f size = {sizeX*sizeD,sizeY*sizeD};
	sfVector2f sizeCenter = {(sizeX*sizeD)/2,sizeY*sizeD/2};
	sfView_setSize(view, size);
	sfView_setCenter(view, sizeCenter);
	//boucle
	while (sfRenderWindow_isOpen(window)){

		int lookX = sfSprite_getPosition(sprite_perso).x / sizePixels;
		int lookY = sfSprite_getPosition(sprite_perso).y / sizePixels;

		if (lookX == exitX && lookY == exitY) {
			//changer de niveau etc
			compteurNiveau++;
			update_map(compteurNiveau);
			update_perso(entryX, entryY);
			//nombre de map max fin de jeu
			if (compteurNiveau > maxMapFinJeu) {
				sfWindow_close(window);
			}
		}

		while (sfRenderWindow_pollEvent(window, &event)){
			//�v�nements clavier
			if (event.type == sfEvtClosed) {
				sfRenderWindow_close(window);
			}

			if (event.type == sfEvtKeyPressed) {

				if (sfKeyboard_isKeyPressed(sfKeyEscape))
					sfRenderWindow_close(window);

				if (sfKeyboard_isKeyPressed(sfKeyLeft))
					deplacement_perso(1);
				else if (sfKeyboard_isKeyPressed(sfKeyRight))
					deplacement_perso(0);
				else if (sfKeyboard_isKeyPressed(sfKeyUp))
					deplacement_perso(3);
				else if (sfKeyboard_isKeyPressed(sfKeyDown))
					deplacement_perso(2);
			}

		}
		//render
		sfRenderWindow_clear(window, sfBlack);
		//affichage
		sfRenderWindow_setView(window, view);
		affichage_map(window);
		affichage_perso(window, sfTime_asMilliseconds(sfClock_getElapsedTime(cloak)));
		sfRenderWindow_getDefaultView(window);
		sfRenderWindow_display(window);
	}
	//destroy
	sfRenderWindow_destroy(window);
	sfFont_destroy(font);
	//sfText_destroy(text);
	sfMusic_destroy(music);
	sfSprite_destroy(sprite_map);
	sfTexture_destroy(texture_map);
	sfSprite_destroy(sprite_perso);
	sfTexture_destroy(texture_perso);
	sfClock_destroy(cloak);
	sfView_destroy(view);
	return EXIT_SUCCESS;
}