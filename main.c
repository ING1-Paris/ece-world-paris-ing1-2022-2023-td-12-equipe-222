
#include <allegro.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define SCREEN_W 768
#define SCREEN_H 632

struct Joueurs{
        char nom[10];
        int ticket;
};
struct Joueurs joueur[2];

int main(){
    BITMAP *page = NULL ; // BITMAP de la page (double buffer)
    BITMAP *im1_down; // p1 face
    BITMAP *im1_right; // p1 profil droit
    BITMAP *im1_left; // p1 profil gauche
    BITMAP *im1_up; // p1 de dos
    BITMAP *im2_down; // p2 face
    BITMAP *im2_right; // p2 profil droit
    BITMAP *im2_left; // p2 profil gauche
    BITMAP *im2_up; // p2 de dos

    // Lancer allegro et le mode graphique
    srand(time(NULL));
    allegro_init();
    install_keyboard();
    install_mouse();

    set_color_depth(desktop_color_depth());
    if (set_gfx_mode(GFX_AUTODETECT_WINDOWED,SCREEN_W,SCREEN_H,0,0)!=0)
    {
        allegro_message("prb gfx mode");
        allegro_exit();
        exit(EXIT_FAILURE);
    }

    // Charger un fond
    BITMAP *carte = load_bitmap("cartedujeu_negate.bmp", NULL);
    if (!carte) {
        allegro_message("prb chargement image");
        allegro_exit();
        exit(EXIT_FAILURE);
    }

    //BITMAP VAINQUEUR
    BITMAP *vainqueur1 = load_bitmap("vainqueur1.bmp", NULL);
    if (!vainqueur1) {
        allegro_message("prb chargement image quitte");
        allegro_exit();
        exit(EXIT_FAILURE);
    }
    BITMAP *vainqueur2 = load_bitmap("vainqueur2.bmp", NULL);
    if (!vainqueur2){
        allegro_message("prb chargement image quitte");
        allegro_exit();
        exit(EXIT_FAILURE);
    }

    // CREATION DU BUFFER D'AFFICHAGE à la taille de l'écran
    page = create_bitmap(SCREEN_W,SCREEN_H);
    clear_bitmap(page);

    im1_down = load_bitmap("player10.bmp", NULL);
    if (!im1_down) {
        allegro_message("impossible de charger l'image1");
        return 1;
    }
    im1_right = load_bitmap("player11.bmp", NULL);
    if (!im1_right) {
        allegro_message("impossible de charger l'image2");
        return 1;
    }
    im1_left = load_bitmap("player12.bmp", NULL);
    if (!im1_left) {
        allegro_message("impossible de charger l'image3");
        return 1;
    }
    im1_up = load_bitmap("player13.bmp", NULL);
    if (!im1_up) {
        allegro_message("impossible de charger l'image4");
        return 1;
    }

    im2_down = load_bitmap("player20.bmp", NULL);
    if (!im2_down) {
        allegro_message("impossible de charger l'image1");
        return 1;
    }
    im2_right = load_bitmap("player21.bmp", NULL);
    if (!im2_right) {
        allegro_message("impossible de charger l'image2");
        return 1;
    }
    im2_left = load_bitmap("player22.bmp", NULL);
    if (!im2_left) {
        allegro_message("impossible de charger l'image3");
        return 1;
    }
    im2_up = load_bitmap("player23.bmp", NULL);
    if (!im2_up) {
        allegro_message("impossible de charger l'image4");
        return 1;
    }

    // Demander les pseudos des joueurs
    allegro_message("Entrez le pseudo du joueur 1 :");
    scanf("%s",joueur[1].nom);
    allegro_message("Entrez le pseudo du joueur 2 :");
    scanf("%s",joueur[2].nom);

    ////////////////////
    ///INITIALISATION///
    ////////////////////

    float x1 = 165, y1 = 424; // position initiale du perso1
    float x2 = 140, y2 = 425; // position initiale du perso2

    int mur1_w = 1;   // largeur du mur
    int mur1_x = 73;  // position x du mur
    int mur1_y = 0;  // position y du mur
    int mur1_h = SCREEN_H;  // hauteur du mur

    int mur2_x = 73;
    int mur2_y = 437;
    int mur2_h = 1;
    int mur2_w = 60;

    int mur02_x = 201;
    int mur02_y = 437;
    int mur02_h = 1;
    int mur02_w = 55;

    int mur02g_x = 140;
    int mur02g_y = 437;
    int mur02g_h = 50;
    int mur02g_w = 1;

    int mur02d_x = 197;
    int mur02d_y = 437;
    int mur02d_h = 50;
    int mur02d_w = 1;

    int mur3_x = 265;
    int mur3_y = 386;
    int mur3_h = 93;
    int mur3_w = 5;

    int mur4_x = 272;
    int mur4_y = 483;
    int mur4_h = 1;
    int mur4_w = 190;

    int mur5_x = 134;
    int mur5_y = 178;
    int mur5_h = 180;
    int mur5_w = 3;

    int mur6_x = 80;
    int mur6_y = 178;
    int mur6_h = 1;
    int mur6_w = 130;

    int mur7_x = 199;
    int mur7_y = 371;
    int mur7_h = 2;
    int mur7_w = 79;

    int mur8_x = 140;
    int mur8_y = 215;
    int mur8_h = 1;
    int mur8_w = 33;

    int mur9_x = 470;
    int mur9_y = 192;
    int mur9_h = 138;
    int mur9_w = 1;

    int mur10_x = 470;
    int mur10_y = 330;
    int mur10_h = 1;
    int mur10_w = 267;

    int mur11_x = 211;
    int mur11_y = 210;
    int mur11_h = 1;
    int mur11_w = 170;

    int mur12_x = 600;
    int mur12_y = 329;
    int mur12_h = 105;
    int mur12_w = 1;

    int mur13_x = 501;
    int mur13_y = 440;
    int mur13_h = 50;
    int mur13_w = 1;

    int mur14_x = 218;
    int mur14_y = 275;
    int mur14_h = 1;
    int mur14_w = 190;

    int mur15_x = 411;
    int mur15_y = 275;
    int mur15_h = 45;
    int mur15_w = 1;

    int mur16_x = 317;
    int mur16_y = 320;
    int mur16_h = 1;
    int mur16_w = 90;

    int mur17_x = 218;
    int mur17_y = 275;
    int mur17_h = 45;
    int mur17_w = 1;

    int mur18_x = 218;
    int mur18_y = 320;
    int mur18_h = 1;
    int mur18_w = 60;

    int mur19_x = 501;
    int mur19_y = 497;
    int mur19_h = 1;
    int mur19_w = 170;

    int mur20_x = 664;
    int mur20_y = 300;
    int mur20_h = 300;
    int mur20_w = 1;

    int mur21_x = 556;
    int mur21_y = 372;
    int mur21_h = 1;
    int mur21_w = 100;

    int mur22_x = 323;
    int mur22_y = 380;
    int mur22_h = 1;
    int mur22_w = 140;


    // Definir la zone de collision de la maison
    int maison1_x = 296;  // position x de la maison
    int maison1_y = 280;  // position y de la maison
    int maison2_x = 360;
    int maison2_y = 380;
    int maison3_x = 200;
    int maison3_y = 173;
    int maison4_x = 408;
    int maison4_y = 185;
    int maison5_x = 536;
    int maison5_y = 328;
    int maison_w = 15;
    int maison_h = 15;
    int spawn_x = 130;
    int spawn_y = 450;

    joueur[1].ticket=joueur[2].ticket =5;

    BITMAP *im1 = im1_down; // image initiale du poisson
    draw_sprite(page, im1, x1, y1);
    BITMAP *im2 = im2_down; // image initiale du poisson
    draw_sprite(page, im2, x2, y2);

////////////////////////////////
////////BOUCLE DE JEU///////////
////////////////////////////////

    while (!key[KEY_ESC]) {
    // Effacer le buffer d'affichage
        clear_bitmap(page);
        //blit(carte,page,0,0,0,0,SCREEN_W, SCREEN_H);
        //blit(page, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
        // rectfill(page, x, y, x+im->w, y+im->h, makecol(255,255,255));

        //COLLISION MAISON 1
        if ((x1 + im1->w > maison1_x && x1 < maison1_x + maison_w && y1 + im1->h > maison1_y && y1 < maison1_y + maison_h)
        ||(x2 + im2->w > maison1_x && x2 < maison1_x + maison_w && y2 + im2->h > maison1_y && y2 < maison1_y + maison_h)) {
            // Collision détectée, appeler la fonction JEU1()
            allegro_message("LANCEMENT DU JEU : LA PECHE AU CANARD");
            allegro_message("Au tour de %s de jouer",joueur[1].nom);
            allegro_exit();
            jeupeche();
            allegro_message("Au tour de %s de jouer",joueur[2].nom);
            allegro_exit();
            jeupeche();
            show_mouse(screen);
            blit(vainqueur1, screen, 0, 0, 160, 269, SCREEN_W, SCREEN_H);
            rest(4000);
            //joueur 1 vainqueur
            if ((mouse_b & 1) && (mouse_x > 0) && (mouse_x < 285) && (mouse_y > 328) && (mouse_y < 525)) {
                destroy_bitmap(vainqueur1);
                joueur[1].ticket++;
            }
                //joueur 2 vainquer
            else if ((mouse_b & 1) && (mouse_x > 285) && (mouse_x < 470) && (mouse_y > 328) && (mouse_y < 525)) {
                destroy_bitmap(vainqueur1);
                joueur[2].ticket++;
            }
                //egalite
            else if ((mouse_b & 1) && (mouse_x > 270) && (mouse_x < SCREEN_W) && (mouse_y > 328) && (mouse_y < 525)) {
                destroy_bitmap(vainqueur1);
                joueur[1].ticket+=0;
                joueur[2].ticket+=0;
            }
            y1 += 3;
            im1 = im1_down;
            y2 += 3;
            im2 = im2_down;
            (joueur[1].ticket -=1) && (joueur[2].ticket-=1);
        }

        //COLLISION MAISON 2
        if ((x1 + im1->w > maison2_x && x1 < maison2_x + maison_w && y1 + im1->h > maison2_y && y1 < maison2_y + maison_h)
            ||(x2 + im2->w > maison2_x && x2 < maison2_x + maison_w && y2 + im2->h > maison2_y && y2 < maison2_y + maison_h)) {
            // Collision détectée, appeler la fonction JEU1()
            allegro_message("LANCEMENT DU JEU : PARIS HIPPIQUES !");
            allegro_message("sous prog");
            show_mouse(screen);
            blit(vainqueur2, screen, 0, 0, 160, 269, SCREEN_W, SCREEN_H);
            rest(4000);
            //joueur 1 vainqueur
            if ((mouse_b & 1) && (mouse_x > 0) && (mouse_x < 240) && (mouse_y > 328) && (mouse_y < 525)) {
                destroy_bitmap(vainqueur2);
                joueur[1].ticket++;
            }
                //joueur 2 vainquer
            else if ((mouse_b & 1) && (mouse_x > 240) && (mouse_x < 370) && (mouse_y > 328) && (mouse_y < 525)) {
                destroy_bitmap(vainqueur2);
                joueur[2].ticket++;
            }
                //LES DEUX
            else if ((mouse_b & 1) && (mouse_x > 370) && (mouse_x < 500) && (mouse_y > 328) && (mouse_y < 525)) {
                destroy_bitmap(vainqueur2);
                joueur[1].ticket += 1;
                joueur[2].ticket += 1;
            }
                //LES DEUX
            else if ((mouse_b & 1) && (mouse_x > 500) && (mouse_x < SCREEN_W) && (mouse_y > 328) && (mouse_y < 525)) {
                destroy_bitmap(vainqueur2);
                joueur[1].ticket+=0;
                joueur[2].ticket+=0;
            }
            y1 += 3;
            im1 = im1_down;
            y2 += 3;
            im2 = im2_down;
            (joueur[1].ticket -=1) && (joueur[2].ticket-=1);
        }

        //COLLISION MAISON 3
        if ((x1 + im1->w > maison3_x && x1 < maison3_x + maison_w && y1 + im1->h > maison3_y && y1 < maison3_y + maison_h)
            ||(x2 + im2->w > maison3_x && x2 < maison3_x + maison_w && y2 + im2->h > maison3_y && y2 < maison3_y + maison_h)) {
            // Collision détectée, appeler la fonction JEU1()
            allegro_message("LANCEMENT DU JEU : FANTOME LA !");
            allegro_message("Au tour de %s de jouer",joueur[1].nom);
            allegro_exit();
            jeufantomela();
            allegro_message("Au tour de %s de jouer",joueur[2].nom);
            allegro_exit();
            jeufantomela();
            show_mouse(screen);
            blit(vainqueur1, screen, 0, 0, 160, 269, SCREEN_W, SCREEN_H);
            rest(4000);
            //joueur 1 vainqueur
            if ((mouse_b & 1) && (mouse_x > 0) && (mouse_x < 285) && (mouse_y > 328) && (mouse_y < 525)) {
                destroy_bitmap(vainqueur1);
                joueur[1].ticket++;
            }
                //joueur 2 vainquer
            else if ((mouse_b & 1) && (mouse_x > 285) && (mouse_x < 470) && (mouse_y > 328) && (mouse_y < 525)) {
                destroy_bitmap(vainqueur1);
                joueur[2].ticket++;
            }
                //egalite
            else if ((mouse_b & 1) && (mouse_x > 270) && (mouse_x < SCREEN_W) && (mouse_y > 328) && (mouse_y < 525)) {
                destroy_bitmap(vainqueur1);
                joueur[1].ticket+=0;
                joueur[2].ticket+=0;
            }
            y1 += 3;
            im1 = im1_down;
            y2 += 3;
            im2 = im2_down;
            (joueur[1].ticket -=1) && (joueur[2].ticket-=1);
        }

        //COLLISION MAISON 4
        if ((x1 + im1->w > maison4_x && x1 < maison4_x + maison_w && y1 + im1->h > maison4_y && y1 < maison4_y + maison_h)
             ||(x2 + im2->w > maison4_x && x2 < maison4_x + maison_w && y2 + im2->h > maison4_y && y2 < maison4_y + maison_h)) {
            // Collision détectée, appeler la fonction JEU1()
            allegro_message("LANCEMENT DU JEU : TIR AU BALLONS !");
            allegro_message("Au tour de %s de jouer",joueur[1].nom);
            allegro_exit();
            jeuballon();
            allegro_message("Au tour de %s de jouer",joueur[2].nom);
            allegro_exit();
            jeuballon();
            show_mouse(screen);
            blit(vainqueur1, screen, 0, 0, 160, 269, SCREEN_W, SCREEN_H);
            rest(4000);
            //joueur 1 vainqueur
            if ((mouse_b & 1) && (mouse_x > 0) && (mouse_x < 285) && (mouse_y > 328) && (mouse_y < 525)) {
                destroy_bitmap(vainqueur1);
                joueur[1].ticket++;
            }
                //joueur 2 vainquer
            else if ((mouse_b & 1) && (mouse_x > 285) && (mouse_x < 470) && (mouse_y > 328) && (mouse_y < 525)) {
                destroy_bitmap(vainqueur1);
                joueur[2].ticket++;
            }
                //egalite
            else if ((mouse_b & 1) && (mouse_x > 270) && (mouse_x < SCREEN_W) && (mouse_y > 328) && (mouse_y < 525)) {
                destroy_bitmap(vainqueur1);
                joueur[1].ticket+=0;
                joueur[2].ticket+=0;
            }
            y1 += 3;
            im1 = im1_down;
            y2 += 3;
            im2 = im2_down;
            (joueur[1].ticket -=1) && (joueur[2].ticket-=1);
        }

        //COLLISION MAISON 5
        if ((x1 + im1->w > maison5_x && x1 < maison5_x + maison_w && y1 + im1->h > maison5_y && y1 < maison5_y + maison_h)
            ||(x2 + im2->w > maison5_x && x2 < maison5_x + maison_w && y2 + im2->h > maison5_y && y2 < maison5_y + maison_h)) {
            // Collision détectée, appeler la fonction JEU1()
            allegro_message("LANCEMENT DU JEU : TRAVERSEE DE RIVIERE !");
            allegro_message("Au tour de %s de jouer",joueur[1].nom);
            allegro_exit();
            jeuriviere();
            allegro_message("Au tour de %s de jouer",joueur[2].nom);
            allegro_exit();
            jeuriviere();
            show_mouse(screen);
            blit(vainqueur1, screen, 0, 0, 160, 269, SCREEN_W, SCREEN_H);
            rest(4000);
            //joueur 1 vainqueur
            if ((mouse_b & 1) && (mouse_x > 0) && (mouse_x < 285) && (mouse_y > 328) && (mouse_y < 525)) {
                destroy_bitmap(vainqueur1);
                joueur[1].ticket++;
            }
                //joueur 2 vainquer
            else if ((mouse_b & 1) && (mouse_x > 285) && (mouse_x < 470) && (mouse_y > 328) && (mouse_y < 525)) {
                destroy_bitmap(vainqueur1);
                joueur[2].ticket++;
            }
                //egalite
            else if ((mouse_b & 1) && (mouse_x > 270) && (mouse_x < SCREEN_W) && (mouse_y > 328) && (mouse_y < 525)) {
                destroy_bitmap(vainqueur1);
                joueur[1].ticket+=0;
                joueur[2].ticket+=0;
            }
            y1 += 3;
            im1 = im1_down;
            y2 += 3;
            im2 = im2_down;
            (joueur[1].ticket -=1) && (joueur[2].ticket-=1);
        }

////////////////////////////////
////////MOUVEMENT JOUEURS///////
////////////////////////////////

        //MOUVEMENT PERSO 1
        if (key[KEY_LEFT] && x1 > 0) {
            x1 -= 1.5;
            im1 = im1_right;
        }
        if (key[KEY_RIGHT] && x1+im1->w < SCREEN_W) {
            x1 += 1.5;
            im1 = im1_left;
        }
        if (key[KEY_UP] && y1 > 0) {
            y1 -= 1.5;
            im1 = im1_up;
        }
        if (key[KEY_DOWN] && y1+im1->h < SCREEN_H) {
            y1 += 1.5;
            im1 = im1_down;
        }

        //MOUVEMENT PERSO2
        if (key[KEY_A] && x1 > 0) {
            x2 -= 1.5;
            im2 = im2_right;
        }
        if (key[KEY_D] && x2+im2->w < SCREEN_W) {
            x2 += 1.5;
            im2 = im2_left;
        }
        if (key[KEY_W] && y2 > 0) {
            y2 -= 1.5;
            im2 = im2_up;
        }
        if (key[KEY_S] && y2+im2->h < SCREEN_H) {
            y2 += 1.5;
            im2 = im2_down;
        }

////////////////////////////////
/////LIMITE DE LA CARTE/////////
////////////////////////////////

        /////////////
        ///PLAYER1///
        /////////////

        if (x1 + im1->w > mur1_x && x1 < mur1_x + mur1_w && y1 + im1->h > mur1_y && y1 < mur1_y + mur1_h){
            x1 += 1.5;
        }else if (x1 + im1->w > mur2_x && x1 < mur2_x + mur2_w && y1 + im1->h > mur2_y && y1 < mur2_y + mur2_h){
            y1 -= 1.5;
        }else if (x1 + im1->w > mur02_x && x1 < mur02_x + mur02_w && y1 + im1->h > mur02_y && y1 < mur02_y + mur02_h) {
            y1 -= 1.5;
        }else if (x1 + im1->w > mur02g_x && x1 < mur02g_x + mur02g_w && y1 + im1->h > mur02g_y && y1 < mur02g_y + mur02g_h) {
            x1 += 1.5;
        }else if (x1 + im1->w > mur02d_x && x1 < mur02d_x + mur02d_w && y1 + im1->h > mur02d_y && y1 < mur02d_y + mur02d_h) {
            x1 -= 1.5;
        }else if (x1 + im1->w > mur3_x && x1 < mur3_x + mur3_w && y1 + im1->h > mur3_y && y1 < mur3_y + mur3_h){
            x1 -= 1.5;
        }else if (x1 + im1->w > mur4_x && x1 < mur4_x + mur4_w && y1 + im1->h > mur4_y && y1 < mur4_y + mur4_h){
            y1 -= 1.5;
        }else if (x1 + im1->w > mur5_x && x1 < mur5_x + mur5_w && y1 + im1->h > mur5_y && y1 < mur5_y + mur5_h){
            x1 -= 1.5;
        }else if (x1 + im1->w > mur6_x && x1 < mur6_x + mur6_w && y1 + im1->h > mur6_y && y1 < mur6_y + mur6_h){
            y1 += 1.5;
        }else if (x1 + im1->w > mur7_x && x1 < mur7_x + mur7_w && y1 + im1->h > mur7_y && y1 < mur7_y + mur7_h){
            y1 += 1.5;
        }else if (x1 + im1->w > mur8_x && x1 < mur8_x + mur8_w && y1 + im1->h > mur8_y && y1 < mur8_y + mur8_h){
            y1 += 1.5;
        }else if (x1 + im1->w > mur9_x && x1 < mur9_x + mur9_w && y1 + im1->h > mur9_y && y1 < mur9_y + mur9_h){
            x1 -= 1.5;
        }else if (x1 + im1->w > mur10_x && x1 < mur10_x + mur10_w && y1 + im1->h > mur10_y && y1 < mur10_y + mur10_h) {
            y1 += 1.5;
        }else if (x1 + im1->w > mur11_x && x1 < mur11_x + mur11_w && y1 + im1->h > mur11_y && y1 < mur11_y + mur11_h) {
            y1 += 1.5;
        }else if (x1 + im1->w > mur12_x && x1 < mur12_x + mur12_w && y1 + im1->h > mur12_y && y1 < mur12_y + mur12_h) {
            x1 += 1.5;
        }else if (x1 + im1->w > mur13_x && x1 < mur13_x + mur13_w && y1 + im1->h > mur13_y && y1 < mur13_y + mur13_h) {
            x1 += 1.5;
        }else if (x1 + im1->w > mur14_x && x1 < mur14_x + mur14_w && y1 + im1->h > mur14_y && y1 < mur14_y + mur14_h) {
            y1 -= 1.5;
        }else if (x1 + im1->w > mur15_x && x1 < mur15_x + mur15_w && y1 + im1->h > mur15_y && y1 < mur15_y + mur15_h) {
            x1 += 1.5;
        }else if (x1 + im1->w > mur16_x && x1 < mur16_x + mur16_w && y1 + im1->h > mur16_y && y1 < mur16_y + mur16_h) {
            y1 += 1.5;
        }else if (x1 + im1->w > mur17_x && x1 < mur17_x + mur17_w && y1 + im1->h > mur17_y && y1 < mur17_y + mur17_h) {
            x1 -= 1.5;
        }else if (x1 + im1->w > mur18_x && x1 < mur18_x + mur18_w && y1 + im1->h > mur18_y && y1 < mur18_y + mur18_h) {
            y1 += 1.5;
        }else if (x1 + im1->w > mur19_x && x1 < mur19_x + mur19_w && y1 + im1->h > mur19_y && y1 < mur19_y + mur19_h) {
            y1 -= 1.5;
        }else if (x1 + im1->w > mur20_x && x1 < mur20_x + mur20_w && y1 + im1->h > mur20_y && y1 < mur20_y + mur20_h) {
            x1 -= 1.5;
        }else if (x1 + im1->w > mur21_x && x1 < mur21_x + mur21_w && y1 + im1->h > mur21_y && y1 < mur21_y + mur21_h) {
            y1 += 1.5;
        }else if (x1 + im1->w > mur22_x && x1 < mur22_x + mur22_w && y1 + im1->h > mur22_y && y1 < mur22_y + mur22_h) {
            y1 -= 1.5;
        }

        /////////////
        ///PLAYER2///
        /////////////

        if (x2 + im2->w > mur1_x && x2 < mur1_x + mur1_w && y2 + im2->h > mur1_y && y2 < mur1_y + mur1_h){
            x2 += 1.5;
        }else if (x2 + im2->w > mur2_x && x2 < mur2_x + mur2_w && y2 + im2->h > mur2_y && y2 < mur2_y + mur2_h){
            y2 -= 1.5;
        }else if (x2 + im2->w > mur02_x && x2 < mur02_x + mur02_w && y2 + im2->h > mur02_y && y2 < mur02_y + mur02_h) {
            y2 -= 1.5;
        }else if (x2 + im2->w > mur02g_x && x2 < mur02g_x + mur02g_w && y2 + im2->h > mur02g_y && y2 < mur02g_y + mur02g_h) {
            x2 += 1.5;
        }else if (x2 + im2->w > mur02d_x && x2 < mur02d_x + mur02d_w && y2 + im2->h > mur02d_y && y2 < mur02d_y + mur02d_h) {
            x2 -= 1.5;
        }else if (x2 + im2->w > mur3_x && x2 < mur3_x + mur3_w && y2 + im2->h > mur3_y && y2 < mur3_y + mur3_h){
            x2 -= 1.5;
        }else if (x2 + im2->w > mur4_x && x2 < mur4_x + mur4_w && y2 + im2->h > mur4_y && y2 < mur4_y + mur4_h){
            y2 -= 1.5;
        }else if (x2 + im2->w > mur5_x && x2 < mur5_x + mur5_w && y2 + im2->h > mur5_y && y2 < mur5_y + mur5_h){
            x2 -= 1.5;
        }else if (x2 + im2->w > mur6_x && x2 < mur6_x + mur6_w && y2 + im2->h > mur6_y && y2 < mur6_y + mur6_h){
            y2 += 1.5;
        }else if (x2 + im2->w > mur7_x && x2 < mur7_x + mur7_w && y2 + im2->h > mur7_y && y2 < mur7_y + mur7_h){
            y2 += 1.5;
        }else if (x2 + im2->w > mur8_x && x2 < mur8_x + mur8_w && y2 + im2->h > mur8_y && y2 < mur8_y + mur8_h){
            y2 += 1.5;
        }else if (x2 + im2->w > mur9_x && x2 < mur9_x + mur9_w && y2 + im2->h > mur9_y && y2 < mur9_y + mur9_h){
            x2 -= 1.5;
        }else if (x2 + im2->w > mur10_x && x2 < mur10_x + mur10_w && y2 + im2->h > mur10_y && y2 < mur10_y + mur10_h) {
            y2 += 1.5;
        }else if (x2 + im2->w > mur11_x && x2 < mur11_x + mur11_w && y2 + im2->h > mur11_y && y2 < mur11_y + mur11_h) {
            y2 += 1.5;
        }else if (x2 + im2->w > mur12_x && x2 < mur12_x + mur12_w && y2 + im2->h > mur12_y && y2 < mur12_y + mur12_h) {
            x2 += 1.5;
        }else if (x2 + im2->w > mur13_x && x2 < mur13_x + mur13_w && y2 + im2->h > mur13_y && y2 < mur13_y + mur13_h) {
            x2 += 1.5;
        }else if (x2 + im2->w > mur14_x && x2 < mur14_x + mur14_w && y2 + im2->h > mur14_y && y2 < mur14_y + mur14_h) {
            y2 -= 1.5;
        }else if (x2 + im2->w > mur15_x && x2 < mur15_x + mur15_w && y2 + im2->h > mur15_y && y2 < mur15_y + mur15_h) {
            x2 += 1.5;
        }else if (x2 + im2->w > mur16_x && x2 < mur16_x + mur16_w && y2 + im2->h > mur16_y && y2 < mur16_y + mur16_h) {
            y2 += 1.5;
        }else if (x2 + im2->w > mur17_x && x2 < mur17_x + mur17_w && y2 + im2->h > mur17_y && y2 < mur17_y + mur17_h) {
            x2 -= 1.5;
        }else if (x2 + im2->w > mur18_x && x2 < mur18_x + mur18_w && y2 + im2->h > mur18_y && y2 < mur18_y + mur18_h) {
            y2 += 1.5;
        }else if (x2 + im2->w > mur19_x && x2 < mur19_x + mur19_w && y2 + im2->h > mur19_y && y2 < mur19_y + mur19_h) {
            y2 -= 1.5;
        }else if (x2 + im2->w > mur20_x && x2 < mur20_x + mur20_w && y2 + im2->h > mur20_y && y2 < mur20_y + mur20_h) {
            x2 -= 1.5;
        }else if (x2 + im2->w > mur21_x && x2 < mur21_x + mur21_w && y2 + im2->h > mur21_y && y2 < mur21_y + mur21_h) {
            y2 += 1.5;
        }else if (x2 + im2->w > mur22_x && x2 < mur22_x + mur22_w && y2 + im2->h > mur22_y && y2 < mur22_y + mur22_h) {
            y2 -= 1.5;
        }

        blit(carte,page,0,0,0,0,SCREEN_W, SCREEN_H);
        draw_sprite(page, im1,x1, y1);
        draw_sprite(page,im2,x2,y2);
        blit(page, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
        rest(10);

        //TICKETS
        bool displayTickets = false;
        if (key[KEY_TAB]) {
            displayTickets = true;
        }

        if (displayTickets) {
            BITMAP *popup2 = load_bitmap("tickets_negate.bmp", NULL);
            if (!popup2) {
                allegro_message("prb chargement image tickets");
                allegro_exit();
                exit(EXIT_FAILURE);
            }
            blit(popup2, screen, 0, 0, 150, 269, SCREEN_W, SCREEN_H);
            textprintf_ex(screen, font, 180, 300, makecol(255, 255, 255), -1, "%s",joueur[1].nom);
            textprintf_ex(screen, font, 180, 360, makecol(255, 255, 255), -1, "%s",joueur[2].nom);
            textprintf_ex(screen, font, 340, 300, makecol(255, 255, 255), -1, "Tickets restants : %d", joueur[1].ticket);
            textprintf_ex(screen, font, 340, 360, makecol(255, 255, 255), -1, "Tickets restants : %d", joueur[2].ticket);

            while (key[KEY_TAB]) {
                rest(10);
            }
            destroy_bitmap(popup2);
            displayTickets = false;
        }
        if ((joueur[1].ticket <= 0)||(joueur[2].ticket <= 0)){
            // Afficher le message de défaite
            if (joueur[1].ticket <= 0) {
                allegro_message("%s n'a plus de ticket", joueur[1].nom);
                allegro_message("Bravo %s vous avez gagné !",joueur[2].nom);
            } else {
                allegro_message("%s n'a plus de ticket", joueur[2].nom);
                allegro_message("Bravo %s vous avez gagné !", joueur[1].nom);
            }
            // Fermer le jeu
            destroy_bitmap(page);
            allegro_exit();
            return 0;
        }

        if ((x1 >= spawn_x && x1 <= spawn_x + maison_w && y1 >= spawn_y && y1 <= spawn_y + maison_h)
        ||(x2 >= spawn_x && x2 <= spawn_x + maison_w && y2 >= spawn_y && y2 <= spawn_y + maison_h)){
            show_mouse(screen);

            // Afficher le message de confirmation
            BITMAP *popup = load_bitmap("quitterlejeu.bmp", NULL);
            if (!popup) {
                allegro_message("prb chargement image quitte");
                allegro_exit();
                exit(EXIT_FAILURE);
            }

            blit(popup, screen, 0, 0, 160, 269, SCREEN_W, SCREEN_H);
            rest(300);

            //COORDONNEES OUI
            if ((mouse_b & 1) && (mouse_x > 0) && (mouse_x < SCREEN_W/2) && (mouse_y > 0) && (mouse_y < SCREEN_H)) {
                destroy_bitmap(page);
                allegro_exit();
                return 0;
            }

            //COORDONNEES NON
            else if ((mouse_b & 1) && (mouse_x > SCREEN_W/2) && (mouse_x < SCREEN_W) && (mouse_y > 0) && (mouse_y < SCREEN_H)) {
                destroy_bitmap(popup);
                y1 -= 3;
                im1 = im1_up;
                y2 -= 3;
                im2 = im2_up;
            }
        }
    }
    // SECTION J : FERMETURE MODE GRAPHIQUE
    destroy_bitmap(page);
    allegro_exit();
    return 0;
} END_OF_MAIN()
