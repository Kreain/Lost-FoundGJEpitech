/*
** EPITECH PROJECT, 2021
** Lost-FoundGJEpitech
** File description:
** main_menu
*/

#include "libs.h"

sfSprite *create_menu_background(void)
{
    sfSprite *back = sfSprite_create();
    sfTexture *texture = sfTexture_createFromFile("pict/back.jpg", NULL);
    sfVector2f scale = {0.9, 0.6};

    sfSprite_setTexture(back, texture, sfFalse);
    sfSprite_scale(back, scale);
    return back;
}

sfRectangleShape *create_banner(void)
{
    sfRectangleShape *banner = sfRectangleShape_create();
    sfVector2f size = {350, 1000};
    sfVector2f position = {150, -1};

    sfRectangleShape_setPosition(banner, position);
    sfRectangleShape_setFillColor(banner, sfBlack);
    sfRectangleShape_setSize(banner, size);
    return banner;
}

sfSprite *create_start_button(void)
{
    sfSprite *start = sfSprite_create();
    sfTexture *texture = sfTexture_createFromFile("pict/start.png", NULL);
    sfVector2f adapt = {0.758, 0.769};
    sfVector2f position = {180, 40};

    sfSprite_setTexture(start, texture, sfFalse);
    sfSprite_scale(start, adapt);
    sfSprite_setPosition(start, position);
    return start;
}

sfSprite *create_quit_button(void)
{
    sfSprite *quit = sfSprite_create();
    sfTexture *texture = sfTexture_createFromFile("pict/quit.png", NULL);
    sfVector2f adapt = {0.806, 0.667};
    sfVector2f position = {190, 440};

    sfSprite_setTexture(quit, texture, sfFalse);
    sfSprite_scale(quit, adapt);
    sfSprite_setPosition(quit, position);
    return quit;
}

sfSprite *create_help_button(void)
{
    sfSprite *help = sfSprite_create();
    sfTexture *texture = sfTexture_createFromFile("pict/help.png", NULL);
    sfVector2f adapt = {0.806, 0.769};
    sfVector2f position = {190, 240};

    sfSprite_setTexture(help, texture, sfFalse);
    sfSprite_scale(help, adapt);
    sfSprite_setPosition(help, position);
    return help;
}

void check_mouse_button(sfRenderWindow *window)
{
    sfVector2i pos_mouse = sfMouse_getPositionRenderWindow(window);
    int x = 0;

    if (pos_mouse.x >= 190 && pos_mouse.x <= 440)
        if (pos_mouse.y <= 140 && pos_mouse.y >= 40)
            //start
            x++;
        if (pos_mouse.y <= 340 && pos_mouse.y >= 140)
            //help
            x++;
        if (pos_mouse.y <= 540 && pos_mouse.y >= 440)
            sfRenderWindow_close(window);
}

int main_menu(void)
{
    sfVideoMode video_mode = {1200, 600, 32};
    sfRenderWindow *window = sfRenderWindow_create(video_mode, "Menu", sfResize | sfClose, NULL);
    sfRectangleShape *banner = create_banner();
    sfSprite *back = create_menu_background();
    sfSprite *start = create_start_button();
    sfSprite *help = create_help_button();
    sfSprite *quit = create_quit_button();
    sfEvent event;
    sfMusic *music = sfMusic_createFromFile("music/evolve_main_theme.ogg");
    sfText *title = sfText_create(); 

    sfMusic_play(music);
    sfMusic_setLoop(music, sfTrue);
    while (sfRenderWindow_isOpen(window)) {
        sfRenderWindow_clear(window, sfBlack);
        sfRenderWindow_drawSprite(window, back, NULL);
        sfRenderWindow_drawRectangleShape(window, banner, NULL);
        sfRenderWindow_drawSprite(window, start, NULL);
        sfRenderWindow_drawSprite(window, help, NULL);
        sfRenderWindow_drawSprite(window, quit, NULL);
        sfRenderWindow_display(window);
        while (sfRenderWindow_pollEvent(window, &event)) {
            if (event.type == sfEvtClosed)
                sfRenderWindow_close(window);
            if (event.mouseButton.button == sfMouseLeft)
                check_mouse_button(window);
        }
    }
    sfMusic_destroy(music);
    sfSprite_destroy(back);
    sfSprite_destroy(start);
    sfSprite_destroy(help);
    sfSprite_destroy(quit);
    sfRectangleShape_destroy(banner);
    sfRenderWindow_destroy(window);
    return 0;
}