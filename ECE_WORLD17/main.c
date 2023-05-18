#include <stdio.h>
#include <allegro.h>
#include <time.h>

#define LARGEUR 1500
#define HAUTEUR 800
#define NBR_CROCO 5
#define NBR_CROCO_DROITE 4
#define NBR_CROCO_GAUCHE 3
#define NBR_FANTOMES 4

typedef struct {
    int x;
    int y;
    int dx;
} Crocodile;

typedef struct {
    int x1, x2;
    int y1, y2;
} Rectangle;


void initialisationAllegro();


int main() {
    initialisationAllegro();
    install_keyboard();
    install_mouse();

    show_mouse(screen);
    srand(time(NULL));

    BITMAP * imagecroco_droite [NBR_CROCO_DROITE];
    BITMAP * imagecroco_gauche [NBR_CROCO_GAUCHE];
    BITMAP * image_fantome [NBR_FANTOMES];
    BITMAP * background;
    BITMAP * buffer;

    char nomfichier [100];

    int nbr_croco_droite = 9;

    for (int i = 0; i < nbr_croco_droite; i ++){
        imagecroco_droite [i]= load_bitmap("../1ECEWORLD/crocodile1.bmp", NULL);
        if (!imagecroco_droite[i]){
            allegro_message("Pb image croco droite");
            allegro_exit();
            exit(EXIT_FAILURE);
        }
    }

    //int nbr_croco_gauche = rand()%10 + 5;

    for (int i = 0; i < NBR_CROCO_GAUCHE; i ++){
        imagecroco_gauche [i]= load_bitmap("../1ECEWORLD/crocodile2.bmp", NULL);
        if (!imagecroco_gauche[i]){
            allegro_message("Pb image croco gauche");
            allegro_exit();
            exit(EXIT_FAILURE);
        }
    }

    buffer = create_bitmap(SCREEN_W, SCREEN_H);
    if (!buffer) {
        allegro_message("Pb création buffer");
        allegro_exit();
        exit(EXIT_FAILURE);
    }

    background = load_bitmap("../1ECEWORLD/background1.bmp", NULL);
    if (!background) {
        allegro_message("Pb création background");
        allegro_exit();
        exit(EXIT_FAILURE);
    }

    BITMAP* bas;
    BITMAP* gauche;
    BITMAP* droite;
    BITMAP* haut;

    bas = load_bitmap("../1ECEWORLD/fantome1.bmp", NULL);
    if (!bas) {
        allegro_message("impossible de charger l'image1");
        return 1;
    }
    haut = load_bitmap("../1ECEWORLD/fantome4.bmp", NULL);
    if (!haut) {
        allegro_message("impossible de charger l'image2");
        return 1;
    }
    gauche = load_bitmap("../1ECEWORLD/fantome2.bmp", NULL);
    if (!gauche) {
        allegro_message("impossible de charger l'image3");
        return 1;
    }
    droite = load_bitmap("../1ECEWORLD/fantome3.bmp", NULL);
    if (!droite) {
        allegro_message("impossible de charger l'image4");
        return 1;
    }

    int position_x = 700, position_y = 600;

    BITMAP *image_fantome1 = bas;
    draw_sprite(buffer, image_fantome1, position_x, position_y);

    Crocodile croco_gauche [4][2];
    Crocodile croco_droite [4][2];


    for (int i = 0; i < nbr_croco_droite; i++ ){
        croco_droite[i][0].x = rand()% 1500 + 100*i;
        croco_droite[i][0].y = (2*(i*50)+i*10) + 263;
        croco_droite[i][0].dx = 10;
    }

    for (int j = 0; j < NBR_CROCO_GAUCHE; j ++){
        croco_gauche[j][0].x = rand()% 1500 + j*100;
        croco_gauche[j][0].y = (((j*2)+1)*55) + 257;
        croco_gauche[j][0].dx = 10;
    }

    for (int i = 0; i < nbr_croco_droite; i++ ){
        croco_droite[i][1].x = rand()% 1500 + 100*i;
        croco_droite[i][1].y = (2*(i*50)+i*10) + 263;
        croco_droite[i][1].dx = 10;
    }

    for (int j = 0; j < NBR_CROCO_GAUCHE; j ++){
        croco_gauche[j][1].x = rand()% 1500 + j*100;
        croco_gauche[j][1].y = (((j*2)+1)*55) + 257;
        croco_gauche[j][1].dx = 10;
    }

    Rectangle rectangles;
    rectangles.x1 = 0;
    rectangles.y1 = 298;
    rectangles.x2 = 1500;
    rectangles.y2 = 674;



    while (!key[KEY_ESC]){

        clear_bitmap(buffer);
        blit(background, buffer, 0, 0, 0, 0, background->w, background->h);

        rect(buffer, rectangles.x1,    rectangles.y1,    rectangles.x2, rectangles.y2 , makecol(0, 0, 255));

        textprintf_ex(buffer, font, 300, 100, makecol(0, 200, 10), -1, "souris.x : %d  et souris.y : %d", mouse_x, mouse_y);


        for (int i = 0; i < NBR_CROCO_DROITE; i ++ ){
            draw_sprite(buffer, imagecroco_droite[i], croco_droite[i][0].x, croco_droite[i][0].y);
            croco_droite[i][0].x += croco_droite[i][0].dx;
            if (croco_droite[i][0].x >  LARGEUR ){
                croco_droite[i][0].x = 0;
            }
        }
        for (int j = 0; j <NBR_CROCO_GAUCHE; j ++){
            draw_sprite(buffer, imagecroco_gauche[j], croco_gauche[j][0].x, croco_gauche[j][0].y);
            croco_gauche[j][0].x -= croco_gauche[j][0].dx;
            if (croco_gauche[j][0].x <= -300  ){
                croco_gauche[j][0].x = LARGEUR;
                }
        }
        for (int i = 0; i < NBR_CROCO_DROITE; i ++ ){
            draw_sprite(buffer, imagecroco_droite[i], croco_droite[i][1].x, croco_droite[i][1].y);
            croco_droite[i][1].x += croco_droite[i][1].dx;
            if (croco_droite[i][1].x >  LARGEUR ){
                croco_droite[i][1].x = 0;
            }
        }
        for (int j = 0; j <NBR_CROCO_GAUCHE; j ++){
            draw_sprite(buffer, imagecroco_gauche[j], croco_gauche[j][1].x, croco_gauche[j][1].y);
            croco_gauche[j][1].x -= croco_gauche[j][1].dx;
            if (croco_gauche[j][1].x <= -300  ){
                croco_gauche[j][1].x = LARGEUR;
            }
        }


        if (key[KEY_LEFT] && position_x > 0) {
            position_x -= 55;
            image_fantome1 = gauche;
        }
        if (key[KEY_RIGHT] && position_x+image_fantome1->w < SCREEN_W) {
            position_x += 55;
            image_fantome1 = droite;
        }
        if (key[KEY_UP] && position_y > 0) {
            position_y -= 55;
            image_fantome1 = haut;
        }
        if (key[KEY_DOWN] && position_y+image_fantome1->h < SCREEN_H) {
            position_y += 55;
            image_fantome1 = bas;
        }
        if (position_y  < 250){
            textprintf_ex (buffer, font, 200, 200, makecol(255, 0, 0), -1, "Vous avez gagne");
             }

                draw_sprite(buffer, image_fantome1,position_x, position_y);
                blit(buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
                rest (100);

        }
    destroy_bitmap(buffer);
    for (int i = 0; i < nbr_croco_droite ; i ++){
        destroy_bitmap(imagecroco_droite[i]);
    }
    for (int i = 0; i < NBR_CROCO_GAUCHE ; i ++){
        destroy_bitmap(imagecroco_gauche[i]);
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