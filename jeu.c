#include "libs.h"
#include "map.h"
#include "perso.h"

int compteurNiveau = 0;

float volumeCoeur = 15.f;
float vitesseCoeur = 0.8f;

int valeurwaw = 0;
bool waw = false;
bool canWaw = true;
sfClock* timerwaw;
bool rect1bool = false;
bool rect2bool = false;
bool rect3bool = false;
bool rect4bool = false;

void jeu(){
	//fenetre fullscreen par défault
	sfVideoMode mode = { sfVideoMode_getDesktopMode().width, sfVideoMode_getDesktopMode().height, sfVideoMode_getDesktopMode().bitsPerPixel };
	sfRenderWindow* window = sfRenderWindow_create(mode, "SFML window", sfFullscreen, NULL);
	sfEvent event;
	//font & text
	sfFont* font; 
	font = sfFont_createFromFile("base.ttf");
	if (!font)
		exit(EXIT_FAILURE);
	/*sfText* text;
	text = sfText_create();
	sfText_setFont(text, font);
	sfText_setFillColor(text, sfWhite);
	sfText_setString(text, "0");
	sfText_setCharacterSize(text, 25);*/
	//waw
	sfTexture* waw_playerT = sfTexture_createFromFile("pict/waw.png",NULL);
	if (!waw_playerT)
		exit(EXIT_FAILURE);
	sfSprite* waw_playerS = sfSprite_create();
	sfSprite_setTexture(waw_playerS, waw_playerT, sfTrue);
	sfRectangleShape* rect1 = sfRectangleShape_create();
	sfRectangleShape* rect2 = sfRectangleShape_create();
	sfRectangleShape* rect3 = sfRectangleShape_create();
	sfRectangleShape* rect4 = sfRectangleShape_create();
	//musique
	sfMusic* music = sfMusic_createFromFile("music/battement.ogg");
	sfMusic_play(music);
	sfMusic_setLoop(music, sfTrue);
	sfMusic_setVolume(music, volumeCoeur);
	sfMusic_setPitch(music, vitesseCoeur);
	//personnage
	texture_perso = sfTexture_createFromFile("pict/perso.png", NULL);
	if (!texture_perso)
		exit(EXIT_FAILURE);
	sprite_perso = sfSprite_create();
	sfSprite_setTexture(sprite_perso, texture_perso, sfTrue);
	//temps
	cloak = sfClock_create();
	sfClock_restart(cloak);
	//timer.microseconds;
	timerwaw = sfClock_create();
	sfClock_restart(timerwaw);
	//map dessins
	texture_map = sfTexture_createFromFile("pict/tilesheet.png", NULL);
	if (!texture_map)
		exit(EXIT_FAILURE);
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
				sfRenderWindow_close(window);
			}
		}

		int joueurX = sfSprite_getPosition(sprite_perso).x / 32;
		int joueurY = sfSprite_getPosition(sprite_perso).y / 32;

		while (sfRenderWindow_pollEvent(window, &event)){
			//�v�nements clavier
			if (event.type == sfEvtClosed) {
				sfRenderWindow_close(window);
			}

			if (event.type == sfEvtKeyPressed) {

				if (sfKeyboard_isKeyPressed(sfKeyEscape))
					sfRenderWindow_close(window);

				if (sfKeyboard_isKeyPressed(sfKeySpace) && canWaw) {
					waw = true;
					canWaw = false;
				}

				if (sfKeyboard_isKeyPressed(sfKeyLeft)){
					if(detectionMurGauche(joueurX-1, joueurY) == 0)
						deplacement_perso(1);
				}
				else if (sfKeyboard_isKeyPressed(sfKeyRight)){
					if (detectionMurDroite(joueurX+1, joueurY) == 0)
						deplacement_perso(0);
				}
				if (sfKeyboard_isKeyPressed(sfKeyUp)){
					if (detectionMurHaut(joueurX , joueurY-1) == 0)
						deplacement_perso(3);
				}
				else if (sfKeyboard_isKeyPressed(sfKeyDown)){
					if (detectionMurBas(joueurX , joueurY+1) == 0)
						deplacement_perso(2);
				}
			}

		}
		//render
		sfRenderWindow_clear(window, sfBlack);
		//affichage
		sfRenderWindow_setView(window, view);
		affichage_map(window);
		affichage_perso(window, sfTime_asMilliseconds(sfClock_getElapsedTime(cloak)));

		if (waw) {
			if (valeurwaw == 0) {
				if (detectionMurGauche(joueurX-1, joueurY) == 1) {
					sfVector2f positionRect = { sfSprite_getPosition(sprite_perso).x ,sfSprite_getPosition(sprite_perso).y };
					sfRectangleShape_setPosition(rect1, positionRect);
					sfVector2f sizeRect = { 1,32 };
					sfRectangleShape_setSize(rect1, sizeRect);
					sfRectangleShape_setFillColor(rect1, sfRed);
					rect1bool = true;
				}
				else {
					rect1bool = false;
				}
				if (detectionMurDroite(joueurX + 1, joueurY) == 1) {
					sfVector2f positionRect = { sfSprite_getPosition(sprite_perso).x + 31 ,sfSprite_getPosition(sprite_perso).y };
					sfRectangleShape_setPosition(rect2, positionRect);
					sfVector2f sizeRect = { 1,32 };
					sfRectangleShape_setSize(rect2, sizeRect);
					sfRectangleShape_setFillColor(rect2, sfRed);
					rect2bool = true;
				}
				else {
					rect2bool = false;
				}
				if (detectionMurHaut(joueurX, joueurY-1) == 1) {
					sfVector2f positionRect = { sfSprite_getPosition(sprite_perso).x  ,sfSprite_getPosition(sprite_perso).y };
					sfRectangleShape_setPosition(rect3, positionRect);
					sfVector2f sizeRect = { 32,1 };
					sfRectangleShape_setSize(rect3, sizeRect);
					sfRectangleShape_setFillColor(rect3, sfRed);
					rect3bool = true;
				}
				else {
					rect3bool = false;
				}
				if (detectionMurBas(joueurX, joueurY + 1) == 1) {
					sfVector2f positionRect = { sfSprite_getPosition(sprite_perso).x  ,sfSprite_getPosition(sprite_perso).y + 31 };
					sfRectangleShape_setPosition(rect4, positionRect);
					sfVector2f sizeRect = { 32,1 };
					sfRectangleShape_setSize(rect4, sizeRect);
					sfRectangleShape_setFillColor(rect4, sfRed);
					rect4bool = true;
				}
				else {
					rect4bool = false;
				}
			}
			if (sfTime_asMilliseconds(sfClock_getElapsedTime(timerwaw)) > 150) {
				sfClock_restart(timerwaw);
				valeurwaw = valeurwaw + 1;
				if (valeurwaw > 3) {
					valeurwaw = 0;
					canWaw = true;
					waw = false;
				}
				sfIntRect rectangle = { valeurwaw * sizePixels,0,32,32 };
				sfVector2f positionwaw = { sfSprite_getPosition(sprite_perso).x ,sfSprite_getPosition(sprite_perso).y};
				sfSprite_setPosition(waw_playerS, positionwaw);
				sfSprite_setTextureRect(waw_playerS, rectangle);
			}
			if(rect1bool)
				sfRenderWindow_drawRectangleShape(window, rect1, NULL);
			if(rect2bool)
				sfRenderWindow_drawRectangleShape(window, rect2, NULL);
			if(rect3bool)
				sfRenderWindow_drawRectangleShape(window, rect3, NULL);
			if(rect4bool)
				sfRenderWindow_drawRectangleShape(window, rect4, NULL);
			sfRenderWindow_drawSprite(window, waw_playerS, NULL);
		}
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
	sfRectangleShape_destroy(rect1);
	sfRectangleShape_destroy(rect2);
	sfRectangleShape_destroy(rect3);
	sfRectangleShape_destroy(rect4);
	sfClock_destroy(cloak);
	sfClock_destroy(timerwaw);
	sfView_destroy(view);
	exit(EXIT_SUCCESS);
}