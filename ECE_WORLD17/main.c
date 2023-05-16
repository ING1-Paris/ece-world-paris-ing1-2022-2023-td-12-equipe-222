#include <stdio.h>
#include <allegro.h>

#define LARGEUR 1500
#define HAUTEUR 800
#define NBR_CROCODILES 2

void initialisationAllegro();


int main() {
    initialisationAllegro();
    install_keyboard();
    install_mouse();

    BITMAP * imagecroco [NBR_CROCODILES];
    BITMAP * buffer;

    buffer = create_bitmap(SCREEN_W, SCREEN_H);
    if (!buffer) {
        allegro_message("Pb création buffer");
        allegro_exit();
        exit(EXIT_FAILURE);
    }

    char nomfichier[100];

    for (int i = 0; i < NBR_CROCODILES; i ++ ){
        sprintf(nomfichier, "../1ECEWORLD/crocodile%d.bmp", i + 1);
        imagecroco[i] = load_bitmap(nomfichier, NULL);

        if (!imagecroco[i]){
            allegro_message("Pb image chargee");
            allegro_exit();
            exit(EXIT_FAILURE);
        }
    }

    while (!key[KEY_ESC]){
        clear_bitmap(buffer);

        draw_sprite(buffer, imagecroco[0], 100, 100);
        draw_sprite(buffer, imagecroco[1], 200, 200);

        textprintf_ex(buffer, font, 200, 400, makecol(255, 255, 255), -1, "ça marche ");
        blit(buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);

    }


    destroy_bitmap(buffer);
    for (int i = 0; i < NBR_CROCODILES; i ++){
        destroy_bitmap(imagecroco[i]);
    }

    return 0;
}END_OF_MAIN();


void initialisationAllegro() {
    allegro_init();
    set_color_depth(desktop_color_depth());
    if ((set_gfx_mode(GFX_AUTODETECT_WINDOWED, LARGEUR, HAUTEUR, 0, 0)) != 0) {
        allegro_message("Pb de mode graphique");
        allegro_exit();
        exit(EXIT_FAILURE);
    }
}