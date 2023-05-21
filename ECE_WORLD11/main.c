#include <allegro.h>
#include <stdio.h>
#include <time.h>
#include"stdbool.h"

#define LARGEUR 1500
#define HAUTEUR 800

#define MAX_IMAGES_CHEVAL 6
#define NOMBRE_DE_CHEVAUX 5
#define NBR_BACKGROUND 3
#define NBR_JOUEURS 2

// definition des structures 
typedef struct {
    int choix;
    bool achoisi;
} Joueur;

typedef struct {
    int x;
    int y;
    int dx;
    char nom[100];
} Cheval;

typedef struct {
    int x;
    int y;
} Background;

typedef struct {
    int x1, x2;
    int y1, y2;
    int numeroCheval;
} Rectangle;

//sous programme pour initialiser allegro 
void initialisationAllegro();

//sous programme pour télécharger les backgrounds
void telechargementBackground();


BITMAP *imageChargee[NBR_BACKGROUND];
BITMAP *background_Actuel;

//sous programme pour alterner entre les backgrounds
void switchBackground(int key)
{
    if (key == KEY_1)
        background_Actuel = imageChargee[2];
    else if (key == KEY_2)
        background_Actuel = imageChargee[1];
}

//programme principal
int main() {
    initialisationAllegro();
    install_keyboard();
    install_mouse();

    BITMAP *imageChargee[NBR_BACKGROUND];
    BITMAP *buffer;
    BITMAP *sprite1[MAX_IMAGES_CHEVAL];
    BITMAP *sprite2[MAX_IMAGES_CHEVAL];
    BITMAP *sprite3[MAX_IMAGES_CHEVAL];
    BITMAP *sprite4[MAX_IMAGES_CHEVAL];
    BITMAP *sprite5[MAX_IMAGES_CHEVAL];
    BITMAP *sprite_presentation[MAX_IMAGES_CHEVAL] ;


    srand(time(NULL));
    show_mouse(screen);

    char nomfichier1[20];
//téléchargement images backgrounds 
    for (int i = 0; i < NBR_BACKGROUND; i ++){
        sprintf (nomfichier1, "../ECEWORLD/Background%d.bmp", i+1);
        imageChargee[i]=load_bitmap(nomfichier1, NULL);

        if (!imageChargee[i]){
            allegro_message("Pb image chargee");
            allegro_exit();
            exit(EXIT_FAILURE);
        }
    }
// création du buffer 
    buffer = create_bitmap(LARGEUR,HAUTEUR);
    if (!buffer) {
        allegro_message("Pb création buffer");
        allegro_exit();
        exit(EXIT_FAILURE);
    }
    
//téléchargement sprites des chevaux : 5 chevaux différents avec 6 images chacun 
    char nomfichier2[20];
    Cheval cheval[NOMBRE_DE_CHEVAUX];

    for (int i = 0; i < MAX_IMAGES_CHEVAL; i++) {
        sprintf(nomfichier2,"../ECEWORLD/cheval%d.bmp", i+11);
        sprite1[i] = load_bitmap(nomfichier2, NULL);

        if (!sprite1[i]) {
            allegro_message("prb chargement image 1");
            allegro_exit();
            exit(-1);
        }
    }

    for (int i = 0; i < MAX_IMAGES_CHEVAL; i++) {
        sprintf(nomfichier2,"../ECEWORLD/cheval%d.bmp", i+21);
        sprite2[i] = load_bitmap(nomfichier2, NULL);

        if (!sprite2[i]) {
            allegro_message("prb chargement image 2");
            allegro_exit();
            exit(-1);
        }
    }

    for (int i = 0; i < MAX_IMAGES_CHEVAL; i++) {
        sprintf(nomfichier2,"../ECEWORLD/cheval%d.bmp", i+31);
        sprite3[i] = load_bitmap(nomfichier2, NULL);

        if (!sprite3[i]) {
            allegro_message("prb chargement image 3");
            allegro_exit();
            exit(-1);
        }
    }

    for (int i = 0; i < MAX_IMAGES_CHEVAL; i++) {
        sprintf(nomfichier2,"../ECEWORLD/cheval%d.bmp", i+41);
        sprite4[i] = load_bitmap(nomfichier2, NULL);

        if (!sprite4[i]) {
            allegro_message("prb chargement image 4");
            allegro_exit();
            exit(-1);
        }
    }

    for (int i = 0; i < MAX_IMAGES_CHEVAL; i++) {
        sprintf(nomfichier2,"../ECEWORLD/cheval%d.bmp", i+51);
        sprite5[i] = load_bitmap(nomfichier2, NULL);

        if (!sprite5[i]) {
            allegro_message("prb chargement image 5");
            allegro_exit();
            exit(-1);
        }
    }

    //initialisation position de départ et vitesse aléatoire
    
    for (int j = 0; j < NOMBRE_DE_CHEVAUX; j ++){
        cheval[j].dx = rand() % 15 + 20;
    }

    for (int j = 0; j < NOMBRE_DE_CHEVAUX; j ++){
        cheval[j].x = 50;
    }

    for (int j = 0; j < NOMBRE_DE_CHEVAUX; j ++){
        cheval[j].y = (j+1)*90 + 115;
    }

 
    Rectangle rectangles[NOMBRE_DE_CHEVAUX];

    Joueur joueur[NBR_JOUEURS];

    int compteur = 0;
    int gagnant = 1;

    bool clic = false;

    background_Actuel = imageChargee[2];

    char nomfichier_pres[100];

    
 for (int i = 0; i < NOMBRE_DE_CHEVAUX; i++) {
     sprintf(nomfichier_pres,"../ECEWORLD/cheval%d.bmp", i+1);
     sprite_presentation[i] = load_bitmap(nomfichier_pres, NULL);

     if (!sprite_presentation[i]) {
         allegro_message("prb chargement image presentation");
         allegro_exit();
         exit(-1);
     }
 }


    for (int i = 0; i < NBR_JOUEURS; i++) {
        joueur[i].choix = -1;
        joueur[i].achoisi = false;
    }

    strcpy(cheval[0].nom, "Yoda");
    strcpy(cheval[1].nom, "FISH");
    strcpy(cheval[2].nom, "FLASH");
    strcpy(cheval[3].nom, "CARAMEL");
    strcpy(cheval[4].nom, "TORTANK");

    while (!key[KEY_ESC]) {

        clear_bitmap(buffer);


        blit(imageChargee[1], buffer, 0, 0, 0, 0, imageChargee[1]->w, imageChargee[1]->h);
        for (int i = 0; i < NBR_JOUEURS; i ++){
          
        }

     // dessin des rectangles d'encadrements des chevaux pour pouvoir les selectionner dans le but de parier
        rectangles[0].x1 = 87;
        rectangles[0].y1 = 180;
        rectangles[0].x2 = 411;
        rectangles[0].y2 = 354;
        rectangles[0].numeroCheval = 1;

        rectangles[1].x1 = 575;
        rectangles[1].y1 = 181;
        rectangles[1].x2 = 920;
        rectangles[1].y2 = 362;
        rectangles[1].numeroCheval = 2;

        rectangles[2].x1 = 1057;
        rectangles[2].y1 = 184;
        rectangles[2].x2 = 1385;
        rectangles[2].y2 = 357;
        rectangles[2].numeroCheval = 3;

        rectangles[3].x1 = 319;
        rectangles[3].y1 = 484;
        rectangles[3].x2 = 646;
        rectangles[3].y2 = 651;
        rectangles[3].numeroCheval = 4;

        rectangles[4].x1 = 836;
        rectangles[4].y1 = 483;
        rectangles[4].x2 = 1180;
        rectangles[4].y2 = 656;
        rectangles[4].numeroCheval = 5;

        rect(buffer, rectangles[0].x1, rectangles[0].y1, rectangles[0].x2, rectangles[0].y2, makecol(255, 0, 0));
        rect(buffer, rectangles[1].x1, rectangles[1].y1, rectangles[1].x2, rectangles[1].y2, makecol(255, 0, 0));
        rect(buffer, rectangles[2].x1, rectangles[2].y1, rectangles[2].x2, rectangles[2].y2, makecol(255, 0, 0));
        rect(buffer, rectangles[3].x1, rectangles[3].y1, rectangles[3].x2, rectangles[3].y2, makecol(255, 0, 0));
        rect(buffer, rectangles[4].x1, rectangles[4].y1, rectangles[4].x2, rectangles[4].y2, makecol(255, 0, 0));

// lorsque qu'un joueur clique sur le cheval de son choix, c'est à l'autre d'enchainer 
        if (mouse_b & 1 && !clic) {
            int mouseX = mouse_x;
            int mouseY = mouse_y;
            for (int i = 0; i < NOMBRE_DE_CHEVAUX; i++) {
                if (mouseX >= rectangles[i].x1 && mouseX <= rectangles[i].x2 && mouseY >= rectangles[i].y1 && mouseY <= rectangles[i].y2) {
                    if (!joueur[0].achoisi) {
                        joueur[0].choix = i + 1;
                        joueur[0].achoisi = true;
                    } else if (!joueur[1].achoisi) {
                        joueur[1].choix = i + 1;
                        joueur[1].achoisi = true;
                    }
                }
            }
            clic = true;
        }

        if (!(mouse_b & 1)) {
            clic = false;
        }

        if (joueur[0].achoisi == true && joueur[1].achoisi == true) {
            if (key[KEY_1]) {
                switchBackground(KEY_1);

                blit(imageChargee[2], buffer, 0, 0, 0, 0, imageChargee[2]->w, imageChargee[2]->h);
// affichage de l'ecran recapitulatif des paris des joueurs avec affichage des images des sprites
                textprintf_ex(buffer, font, 240, 250, makecol(255, 255, 255), -1, "Joueur 1 a parie pour le cheval numero %d", joueur[0].choix);
                if (joueur[0].choix == 1){
                    draw_sprite(buffer, sprite_presentation[0],150 , 320);
                    textprintf_ex(buffer, font, 360, 340, makecol(255, 255, 255), -1, " %s", cheval[0].nom);
                }else if (joueur[0].choix == 2){
                    draw_sprite(buffer, sprite2[0],300 , 400);
                    textprintf_ex(buffer, font, 360, 340, makecol(255, 255, 255), -1, " %s", cheval[1].nom);
                    draw_sprite(buffer, sprite_presentation[1],150 , 320);
                }else if (joueur[0].choix == 3){
                    draw_sprite(buffer, sprite3[0],300 , 400);
                    textprintf_ex(buffer, font, 360, 340, makecol(255, 255, 255), -1, " %s", cheval[2].nom);
                    draw_sprite(buffer, sprite_presentation[2],150 , 320);
                }else if (joueur[0].choix == 4){
                    draw_sprite(buffer, sprite4[0],300 , 400);
                    textprintf_ex(buffer, font, 360, 340, makecol(255, 255, 255), -1, " %s", cheval[3].nom);
                    draw_sprite(buffer, sprite_presentation[3],150 , 320);
                }else if (joueur[0].choix == 5){
                    draw_sprite(buffer, sprite5[0],300 , 400);
                    textprintf_ex(buffer, font, 360, 340, makecol(255, 255, 255), -1, " %s", cheval[4].nom);
                    draw_sprite(buffer, sprite_presentation[4],150 , 320);
                }

                textprintf_ex(buffer, font, 940, 250, makecol(255, 255, 255), -1, "Joueur 2 a parie pour le cheval numero %d", joueur[1].choix);
                if (joueur[1].choix == 1){
                    draw_sprite(buffer, sprite_presentation[0],850 , 320);
                    textprintf_ex(buffer, font, 1060, 340, makecol(255, 255, 255), -1, " %s", cheval[0].nom);
                }else if (joueur[1].choix == 2){
                     draw_sprite(buffer, sprite_presentation[1],850, 320);
                    textprintf_ex(buffer, font, 1060, 340, makecol(255, 255, 255), -1, " %s", cheval[1].nom);
                }else if (joueur[1].choix == 3){
                    draw_sprite(buffer, sprite_presentation[2],850, 320);
                    textprintf_ex(buffer, font, 1060, 340, makecol(255, 255, 255), -1, " %s", cheval[2].nom);
                }else if (joueur[1].choix == 4){
                     draw_sprite(buffer, sprite_presentation[3],850, 320);
                    textprintf_ex(buffer, font, 1060, 340, makecol(255, 255, 255), -1, " %s", cheval[3].nom);
                }else if (joueur[1].choix == 5){
                     draw_sprite(buffer, sprite_presentation[4],850, 320);
                    textprintf_ex(buffer, font, 1060, 340, makecol(255, 255, 255), -1, " %s", cheval[4].nom);
                }
            
            }
        }


// lancement de la course

        if (key[KEY_2]){
            switchBackground(KEY_2);
            blit(imageChargee[0], buffer, 0, 0, 0, 0, imageChargee[0]->w, imageChargee[0]->h);
            for (int i = 0; i < NOMBRE_DE_CHEVAUX; i++) {
                if (i == 0) {
                    draw_sprite(buffer, sprite1[compteur], cheval[i].x, cheval[i].y);
                }else if (i == 1){
                    draw_sprite(buffer, sprite2[compteur], cheval[i].x, cheval[i].y);
                }else if (i==2) {
                    draw_sprite(buffer, sprite3[compteur], cheval[i].x, cheval[i].y);
                }else if (i==3){
                    draw_sprite(buffer, sprite4[compteur], cheval[i].x, cheval[i].y);
                }else {
                    draw_sprite(buffer, sprite5[compteur], cheval[i].x, cheval[i].y);
                }
                cheval[i].x += cheval[i].dx;

                if (cheval[i].x > LARGEUR - 150 && gagnant == 1) {
                    gagnant = i;
                }
                if (cheval[i].x >  LARGEUR - 125){
                    cheval[i].dx = 0;
                }
            }
// Affiche le numéro du cheval gagnant en gros sur l'écran
            if (gagnant != 1) {

                textprintf_ex(buffer, font, 630, 150, makecol(400, 10, 300), -1, "LE CHEVAL %d A GAGNE LA COURSE", gagnant + 1);
                if (gagnant + 1 == joueur[0].choix){
                    textprintf_ex(buffer, font, 630, 110, makecol(400, 10, 300), -1, "Joueur 1 a gagne son pari");
                }else if (gagnant + 1 == joueur[1].choix){
                    textprintf_ex(buffer, font, 630, 100, makecol(400, 10, 300), -1, "Joueur 2 a gagné son pari");
                }else if ((gagnant + 1 != joueur[0].choix) && (gagnant + 1 != joueur[1].choix)){
                    textprintf_ex(buffer, font, 630, 100, makecol(400, 10, 300), -1, " Les deux joueurs ont perdu leur pari");
                }
              
            }
        }

        blit(buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
// contrôler la vitesse d'animation en mettant un temps de latence 
        rest(100);  

        compteur = (compteur + 1) % MAX_IMAGES_CHEVAL;

    }

    // destruction des bitmaps
    destroy_bitmap(buffer);
    for (int i = 0; i < NBR_BACKGROUND; i ++){
        destroy_bitmap(imageChargee[i]);
    }
    for (int i = 0; i < MAX_IMAGES_CHEVAL ; i++) {
        destroy_bitmap(sprite1[i]);
        destroy_bitmap(sprite2[i]);
        destroy_bitmap(sprite3[i]);
        destroy_bitmap(sprite4[i]);
        destroy_bitmap(sprite5[i]);
    }

    return 0;
}
END_OF_MAIN();


void initialisationAllegro() {
    allegro_init();
    set_color_depth(desktop_color_depth());
    if ((set_gfx_mode(GFX_AUTODETECT_WINDOWED, LARGEUR, HAUTEUR, 0, 0)) != 0) {
        allegro_message("Pb de mode graphique");
        allegro_exit();
        exit(EXIT_FAILURE);
    }
       set_window_title("Course Hippiques");
}
