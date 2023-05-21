#include <stdio.h>
#include <allegro.h>
#include <time.h>

#define LARGEUR 1500
#define HAUTEUR 800
#define NBR_CROCO_DROITE 4
#define NBR_CROCO_GAUCHE 3

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
    BITMAP * background[2];
    BITMAP * buffer;

    int nbr_croco_droite = 9;

    for (int i = 0; i < nbr_croco_droite; i ++){
        imagecroco_droite [i]= load_bitmap("../1ECEWORLD/crocodile1.bmp", NULL);
        if (!imagecroco_droite[i]){
            allegro_message("Pb image croco droite");
            allegro_exit();
            exit(EXIT_FAILURE);
        }
    }

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

    char nomfichier[100];
    for (int i = 0; i < 2; i ++){
        sprintf (nomfichier, "../1ECEWORLD/background%d.bmp", i+1);
        background[i] = load_bitmap(nomfichier, NULL);
        if (!background[i]) {
            allegro_message("Pb création background");
            allegro_exit();
            exit(EXIT_FAILURE);
        }
    }


    BITMAP* bas;
    BITMAP* gauche;
    BITMAP* droite;
    BITMAP* haut;

    BITMAP* bas1;
    BITMAP* gauche1;
    BITMAP* droite1;
    BITMAP* haut1;

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

    bas1 = load_bitmap("../1ECEWORLD/fantome5.bmp", NULL);
    if (!bas1) {
        allegro_message("impossible de charger l'image5");
        return 1;
    }
    haut1 = load_bitmap("../1ECEWORLD/fantome8.bmp", NULL);
    if (!haut1) {
        allegro_message("impossible de charger l'image6");
        return 1;
    }
    gauche1 = load_bitmap("../1ECEWORLD/fantome6.bmp", NULL);
    if (!gauche1) {
        allegro_message("impossible de charger l'image7");
        return 1;
    }
    droite1 = load_bitmap("../1ECEWORLD/fantome7.bmp", NULL);
    if (!droite1) {
        allegro_message("impossible de charger l'image8");
        return 1;
    }

    int position_x = 800, position_y = 751;
    int position_x1 = 600, position_y1 = 751;

    BITMAP *image_fantome1 = bas;
    BITMAP *image_fantome2 = bas1;

    draw_sprite(buffer, image_fantome1, position_x, position_y);
    draw_sprite(buffer, image_fantome2, position_x1, position_y1);

    Crocodile croco_gauche [4][3];
    Crocodile croco_droite [4][2];


    for (int i = 0; i < NBR_CROCO_DROITE; i++ ){
        croco_droite[i][0].x = rand()% 1500 + rand() % 1000 * i;
        croco_droite[i][0].y = 300 + i*50*2;
        croco_droite[i][0].dx = 10;
    }

    for (int j = 0; j < NBR_CROCO_GAUCHE; j ++){
        croco_gauche[j][0].x = rand()% 1500 + j*100;
        croco_gauche[j][0].y = j*50*2 + 350;
        croco_gauche[j][0].dx = 10;
    }

    for (int i = 0; i < NBR_CROCO_DROITE; i++ ){
        croco_droite[i][1].x = rand()% 1500 + 100*i;
        croco_droite[i][1].y = 300 + i*50*2;
        croco_droite[i][1].dx = 10;
    }

    for (int j = 0; j < NBR_CROCO_GAUCHE; j ++){
        croco_gauche[j][1].x = rand()% 1500 + j*100 + 200;
        croco_gauche[j][1].y = j*2*50 + 350;
        croco_gauche[j][1].dx = 10;
    }

    for (int j = 0; j < NBR_CROCO_GAUCHE; j ++){
        croco_gauche[j][2].x = rand()% 1500 + j*100 + 50;
        croco_gauche[j][2].y = j*2*50 + 350;
        croco_gauche[j][2].dx = 10;
    }

    Rectangle rectangles;
    rectangles.x1 = 0;
    rectangles.y1 = 301;
    rectangles.x2 = 1500;
    rectangles.y2 = 649;

    int fin_partie1 = 0;
    int fin_partie2 = 0;

    while (!key[KEY_ESC]){

            clear_bitmap(buffer);
            blit(background[0], buffer, 0, 0, 0, 0, background[0]->w, background[0]->h);

            rectfill(buffer, rectangles.x1,    rectangles.y1,    rectangles.x2, rectangles.y2 , makecol(0, 0, 255));

            textprintf_ex(buffer, font, 500, 210, makecol(255, 255, 255), -1, "Maintenir la touche ESPACE pour connaitre les regles du jeu");


            for (int i = 0; i < NBR_CROCO_DROITE; i ++ ){
                draw_sprite(buffer, imagecroco_droite[i], croco_droite[i][0].x, croco_droite[i][0].y);
                rect(buffer,croco_droite[i][0].x, croco_droite[i][0].y, croco_droite[i][0].x + 262, croco_droite[i][0].y + 50,
                     makecol(0, 255, 255));
                croco_droite[i][0].x += croco_droite[i][0].dx;
                if (croco_droite[i][0].x >  LARGEUR ){
                    croco_droite[i][0].x = 0;
                }
            }


            for (int i = 0; i < NBR_CROCO_DROITE; i ++){
                if (position_x >= rectangles.x1 && position_x <= rectangles.x2 && position_y >= rectangles.y1 && position_y <=rectangles.y2 ){
                    if (position_x >= croco_droite[i][0].x && position_x <= croco_droite[i][0].x + 300 &&
                        position_y >= croco_droite[i][0].y && position_y <= croco_droite[i][0].y + 50) {
                        position_x += croco_droite[i][0].dx;
                    }
                }
            }

            for (int i = 0; i < NBR_CROCO_DROITE; i ++){
                if (position_x1 >= rectangles.x1 && position_x1 <= rectangles.x2 && position_y1 >= rectangles.y1 && position_y1 <=rectangles.y2 ){
                    if (position_x1 >= croco_droite[i][0].x && position_x1 <= croco_droite[i][0].x + 300 &&
                        position_y1 >= croco_droite[i][0].y && position_y1 <= croco_droite[i][0].y + 50) {
                        position_x1 += croco_droite[i][0].dx;
                    }
                }
            }


            for (int i = 0; i < NBR_CROCO_DROITE; i ++ ){
                draw_sprite(buffer, imagecroco_droite[i], croco_droite[i][1].x, croco_droite[i][1].y);
                rect(buffer,croco_droite[i][1].x, croco_droite[i][1].y, croco_droite[i][1].x + 262, croco_droite[i][1].y + 50,
                     makecol(0, 255, 255));
                croco_droite[i][1].x += croco_droite[i][0].dx;
                if (croco_droite[i][1].x >  LARGEUR ){
                    croco_droite[i][1].x = 0;
                }
            }


            for (int i = 0; i < NBR_CROCO_DROITE; i ++){
                if (position_x >= rectangles.x1 && position_x <= rectangles.x2 && position_y >= rectangles.y1 && position_y <=rectangles.y2 ){
                    if (position_x >= croco_droite[i][1].x && position_x <= croco_droite[i][1].x + 300 &&
                        position_y >= croco_droite[i][1].y && position_y <= croco_droite[i][1].y + 50) {
                        position_x += croco_droite[i][1].dx;
                    }
                }
            }

            for (int i = 0; i < NBR_CROCO_DROITE; i ++){
                if (position_x1 >= rectangles.x1 && position_x1 <= rectangles.x2 && position_y1 >= rectangles.y1 && position_y1 <=rectangles.y2 ){
                    if (position_x1 >= croco_droite[i][1].x && position_x1 <= croco_droite[i][1].x + 300 &&
                        position_y1 >= croco_droite[i][1].y && position_y1 <= croco_droite[i][1].y + 50) {
                        position_x1 += croco_droite[i][1].dx;
                    }
                }
            }


            for (int j = 0; j <NBR_CROCO_GAUCHE; j ++){
                draw_sprite(buffer, imagecroco_gauche[j], croco_gauche[j][0].x, croco_gauche[j][0].y);
                rect(buffer,croco_gauche[j][0].x, croco_gauche[j][0].y, croco_gauche[j][0].x + 265, croco_gauche[j][0].y + 50,
                     makecol(0, 255, 255));
                croco_gauche[j][0].x -= croco_gauche[j][0].dx;
                if (croco_gauche[j][0].x <= -300  ){
                    croco_gauche[j][0].x = LARGEUR;
                }
                if (position_x >= croco_gauche[j][0].x && position_x <= croco_gauche[j][0].x + 265 &&
                    position_y >= croco_gauche[j][0].y && position_y <= croco_gauche[j][0].y + 50)
                {
                    position_x -= croco_gauche[j][0].dx;
                }
                if (position_x1 >= croco_gauche[j][0].x && position_x1 <= croco_gauche[j][0].x + 265 &&
                    position_y1 >= croco_gauche[j][0].y && position_y1 <= croco_gauche[j][0].y + 50)
                {
                    position_x1 -= croco_gauche[j][0].dx;
                }
            }

            for (int j = 0; j <NBR_CROCO_GAUCHE; j ++){
                draw_sprite(buffer, imagecroco_gauche[j], croco_gauche[j][1].x, croco_gauche[j][1].y);
                rect(buffer,croco_gauche[j][1].x, croco_gauche[j][1].y, croco_gauche[j][1].x + 265, croco_gauche[j][1].y + 50,
                     makecol(0, 255, 255));
                croco_gauche[j][1].x -= croco_gauche[j][1].dx;
                if (croco_gauche[j][1].x <= -300  ){
                    croco_gauche[j][1].x = LARGEUR;
                }
                if (position_x >= rectangles.x1 && position_x <= rectangles.x2 && position_y >= rectangles.y1 && position_y <=rectangles.y2 ){
                    if (position_x >= croco_gauche[j][1].x && position_x <= croco_gauche[j][1].x + 265 &&
                        position_y >= croco_gauche[j][1].y && position_y <= croco_gauche[j][1].y + 50) {
                        position_x -= croco_gauche[j][1].dx;
                    }
                }
                if (position_x1 >= rectangles.x1 && position_x1 <= rectangles.x2 && position_y1 >= rectangles.y1 && position_y1 <=rectangles.y2 ){
                    if (position_x1 >= croco_gauche[j][1].x && position_x1 <= croco_gauche[j][1].x + 265 &&
                        position_y1 >= croco_gauche[j][1].y && position_y1 <= croco_gauche[j][1].y + 50) {
                        position_x1 -= croco_gauche[j][1].dx;
                    }
                }
            }



            if (position_x >= rectangles.x1 && position_x <= rectangles.x2 && position_y >= rectangles.y1 && position_y <= rectangles.y2) {
                if ((position_x >= croco_droite[0][0].x && position_x <= croco_droite[0][0].x + 300 && position_y >= croco_droite[0][0].y && position_y <= croco_droite[0][0].y + 50)||
                    (position_x >= croco_droite[1][0].x && position_x <= croco_droite[1][0].x + 300 && position_y >= croco_droite[1][0].y && position_y <= croco_droite[1][0].y + 50)||
                    (position_x >= croco_droite[2][0].x && position_x <= croco_droite[2][0].x + 300 && position_y >= croco_droite[2][0].y && position_y <= croco_droite[2][0].y + 50)||
                    (position_x >= croco_droite[3][0].x && position_x <= croco_droite[3][0].x + 300 && position_y >= croco_droite[3][0].y && position_y <= croco_droite[3][0].y + 50)||
                    (position_x >= croco_gauche[0][0].x && position_x <= croco_gauche[0][0].x + 265 && position_y >= croco_gauche[0][0].y && position_y <= croco_gauche[0][0].y + 50) ||
                    (position_x >= croco_gauche[1][0].x && position_x <= croco_gauche[1][0].x + 265 && position_y >= croco_gauche[1][0].y && position_y <= croco_gauche[1][0].y + 50)||
                    (position_x >= croco_gauche[2][0].x && position_x <= croco_gauche[2][0].x + 265 && position_y >= croco_gauche[2][0].y && position_y <= croco_gauche[2][0].y + 50)||
                    (position_x >= croco_gauche[0][1].x && position_x <= croco_gauche[0][1].x + 265 && position_y >= croco_gauche[0][1].y && position_y <= croco_gauche[0][1].y + 50) ||
                    (position_x >= croco_gauche[1][1].x && position_x <= croco_gauche[1][1].x + 265 && position_y >= croco_gauche[1][1].y && position_y <= croco_gauche[1][1].y + 50)||
                    (position_x >= croco_gauche[2][1].x && position_x <= croco_gauche[2][1].x + 265 && position_y >= croco_gauche[2][1].y && position_y <= croco_gauche[2][1].y + 50)||
                    (position_x >= croco_droite[0][1].x && position_x <= croco_droite[0][1].x + 300 && position_y >= croco_droite[0][1].y && position_y <= croco_droite[0][1].y + 50)||
                    (position_x >= croco_droite[1][1].x && position_x <= croco_droite[1][1].x + 300 && position_y >= croco_droite[1][1].y && position_y <= croco_droite[1][1].y + 50)||
                    (position_x >= croco_droite[2][1].x && position_x <= croco_droite[2][1].x + 300 && position_y >= croco_droite[2][1].y && position_y <= croco_droite[2][1].y + 50)||
                    (position_x >= croco_droite[3][1].x && position_x <= croco_droite[3][1].x + 300 && position_y >= croco_droite[3][1].y && position_y <= croco_droite[3][1].y + 50)) {
                    fin_partie1 = 0;
                }
                else {
                    fin_partie1 = 1;
                }
            }


            if (position_x1 >= rectangles.x1 && position_x1 <= rectangles.x2 && position_y1 >= rectangles.y1 && position_y1 <= rectangles.y2) {
                if ((position_x1 >= croco_droite[0][0].x && position_x1 <= croco_droite[0][0].x + 300 && position_y1 >= croco_droite[0][0].y && position_y1 <= croco_droite[0][0].y + 50)||
                    (position_x1 >= croco_droite[1][0].x && position_x1 <= croco_droite[1][0].x + 300 && position_y1 >= croco_droite[1][0].y && position_y1 <= croco_droite[1][0].y + 50)||
                    (position_x1 >= croco_droite[2][0].x && position_x1 <= croco_droite[2][0].x + 300 && position_y1 >= croco_droite[2][0].y && position_y1 <= croco_droite[2][0].y + 50)||
                    (position_x1 >= croco_droite[3][0].x && position_x1 <= croco_droite[3][0].x + 300 && position_y1 >= croco_droite[3][0].y && position_y1 <= croco_droite[3][0].y + 50)||
                    (position_x1 >= croco_gauche[0][0].x && position_x1 <= croco_gauche[0][0].x + 265 && position_y1 >= croco_gauche[0][0].y && position_y1 <= croco_gauche[0][0].y + 50) ||
                    (position_x1 >= croco_gauche[1][0].x && position_x1 <= croco_gauche[1][0].x + 265 && position_y1 >= croco_gauche[1][0].y && position_y1 <= croco_gauche[1][0].y + 50)||
                    (position_x1 >= croco_gauche[2][0].x && position_x1 <= croco_gauche[2][0].x + 265 && position_y1 >= croco_gauche[2][0].y && position_y1 <= croco_gauche[2][0].y + 50)||
                    (position_x1 >= croco_gauche[0][1].x && position_x1 <= croco_gauche[0][1].x + 265 && position_y1 >= croco_gauche[0][1].y && position_y1 <= croco_gauche[0][1].y + 50) ||
                    (position_x1 >= croco_gauche[1][1].x && position_x1 <= croco_gauche[1][1].x + 265 && position_y1 >= croco_gauche[1][1].y && position_y1 <= croco_gauche[1][1].y + 50)||
                    (position_x1 >= croco_gauche[2][1].x && position_x1 <= croco_gauche[2][1].x + 265 && position_y1 >= croco_gauche[2][1].y && position_y1 <= croco_gauche[2][1].y + 50)||
                    (position_x1 >= croco_droite[0][1].x && position_x1 <= croco_droite[0][1].x + 300 && position_y1 >= croco_droite[0][1].y && position_y1 <= croco_droite[0][1].y + 50)||
                    (position_x1 >= croco_droite[1][1].x && position_x1 <= croco_droite[1][1].x + 300 && position_y1 >= croco_droite[1][1].y && position_y1 <= croco_droite[1][1].y + 50)||
                    (position_x1 >= croco_droite[2][1].x && position_x1 <= croco_droite[2][1].x + 300 && position_y1 >= croco_droite[2][1].y && position_y1 <= croco_droite[2][1].y + 50)||
                    (position_x1 >= croco_droite[3][1].x && position_x1 <= croco_droite[3][1].x + 300 && position_y1 >= croco_droite[3][1].y && position_y1 <= croco_droite[3][1].y + 50)) {
                    fin_partie2 = 0;
                }
                else {
                    fin_partie2 = 2;
                }
            }

            if (key[KEY_LEFT] && position_x > -100) {
                position_x -= 50;
                image_fantome1 = gauche;
            }
            if (key[KEY_RIGHT] && position_x+image_fantome1->w < SCREEN_W) {
                position_x += 50;
                image_fantome1 = droite;
            }
            if (key[KEY_UP] && position_y > 0) {
                position_y -= 50;
                image_fantome1 = haut;
            }
            if (key[KEY_DOWN] && position_y+image_fantome1->h < SCREEN_H) {
                position_y += 50;
                image_fantome1 = bas;
            }


            if (key[KEY_D] && position_x1 > -100) {
                position_x1 -= 50;
                image_fantome2 = gauche1;
            }
            if (key[KEY_G] && position_x1 + image_fantome2->w < SCREEN_W) {
                position_x1 += 50;
                image_fantome2 = droite1;
            }
            if (key[KEY_R] && position_y1 > 0) {
                position_y1 -= 50;
                image_fantome2 = haut1;
            }
            if (key[KEY_F] && position_y1+image_fantome2->h < SCREEN_H) {
                position_y1 += 50;
                image_fantome2 = bas1;
            }


            if (position_y  < 300){
                textprintf_ex (buffer, font, 700, 240, makecol(255, 0, 0), -1, "Joueur 2 a gagne");
            }
            if (position_y1  < 300){
                textprintf_ex (buffer, font, 600, 240, makecol(255, 0, 0), -1, "Joueur 1 a gagne");
            }
            if ( position_x >= 1460 || position_x < 0 ){
                fin_partie1 = 1;
            }
            if ( position_x1 >= 1460 || position_x1 < 0 ){
                fin_partie2 = 1;
            }

            if (fin_partie1 == 1) {
                textprintf_ex(buffer, font, 700, 250, makecol(255, 0, 0), -1, "Joueur 2 a perdu");
                position_x = 800;
                position_y = 751;
            }
            if (fin_partie2 == 2) {
                textprintf_ex(buffer, font, 600, 250, makecol(255, 0, 0), -1, "Joueur 1 a perdu");
                position_x1 = 600;
                position_y1 = 751;
            }
        if (fin_partie1 == 1 && fin_partie2 == 2){
            allegro_message("Les deux joueurs ont perdu, fin du jeux");
            return 1;
        }

            rect(buffer, position_x -2, position_y , position_x + 42, position_y+50, makecol(255,255,255));
            rect(buffer, position_x1 -2, position_y1 -2 , position_x1 + 40, position_y1+50, makecol(255,255,255));
            draw_sprite(buffer, image_fantome2,position_x1, position_y1);
            draw_sprite(buffer, image_fantome1,position_x, position_y);
        if (key[KEY_SPACE]){
            blit(background[1], buffer, 0, 0, 0, 0, background[1]->w, background[1]->h);
        }

            blit(buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
            rest (100);


    }

    destroy_bitmap(buffer);
    for (int i = 0; i < NBR_CROCO_DROITE; i ++){
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
    set_window_title("Traversee Riviere");
}