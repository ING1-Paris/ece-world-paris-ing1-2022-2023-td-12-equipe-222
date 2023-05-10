#include <allegro.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
void initialisation_allegro();
// 8 exemples d'utilisation des sprites ...
#define NEXEMPLES 8
#define NBTAUPES 8

int main()
{
    // BITMAP servant de buffer d'affichage (double buffer)
    BITMAP *page;

    // Image de fond
    BITMAP *decor;

    // Pour faire un peu de maths (calculs de coordonn�es)
    /*int i,x[NEXEMPLES],y[NEXEMPLES];
    float phase=0,alpha=2.0*M_PI/NEXEMPLES,radius=250.0;
    float echelle;*/


    // Lancer allegro et le mode graphique
    initialisation_allegro();
    // CREATION DU BUFFER D'AFFICHAGE � la taille de l'�cran
    page=create_bitmap(SCREEN_W,SCREEN_H);
    clear_bitmap(page);

    // charger image de fond
    decor=load_bitmap("Images/TERRAIN_2.bmp",NULL);
    if (decor==NULL)
    {
        allegro_message("pas pu trouver le terrain");
        exit(EXIT_FAILURE);
    }

    BITMAP* sprite[NBTAUPES];
    int sprite_x = 25; // Position horizontale du sprite
    int sprite_y = 50; // Position verticale du sprite
    int sprite_speed = 30; // Vitesse de déplacement du sprite
    for(int i=0; i<NBTAUPES;i++){
        sprite[i] = load_bitmap("Taupe.bmp", NULL);
    }

    //draw_sprite(page, sprite, sprite_x, sprite_y);

    // Boucle d'animation (pas d'interaction)
    /*while (!key[KEY_ESC])
    {
        // effacer buffer en appliquant d�cor  (pas de clear_bitmap)
        blit(decor,page,0,0,0,0,SCREEN_W,SCREEN_H);

        // d�terminer positions des exemples (et afficher indice � la position)
        // coordonn�es polaires -> cartesien
        for (i=0;i<NEXEMPLES;i++)
        {
            x[i] = SCREEN_W/2 - sprite_transp->w/2 + radius*cos(phase+alpha*i);
            y[i] = SCREEN_H/2 - sprite_transp->h/2 + radius*sin(phase+alpha*i);

            textprintf_ex(page,font,x[i]-16,y[i]-8,makecol(255,255,255),-1,"%d",i);
        }

        // faire avancer tout �a (pour la prochaine it�ration)
        phase+=M_PI/1000;


        // Affichages utilisant diff�rentes techniques de blit et de draw_sprite

        // 0 simple blit d'une image sans info de transparence
        blit(sprite_solide, page, 0, 0, x[0], y[0], sprite_solide->w, sprite_solide->h);

        // 1 simple blit d'une image avec info de transparence (transparence non prise en compte)
        blit(sprite_transp, page, 0, 0, x[1], y[1], sprite_transp->w, sprite_transp->h);

        // 2 draw_sprite d'une image sans info de transparence
        draw_sprite(page, sprite_solide, x[2] ,y[2]);

        // 3 draw_sprite d'une image avec info de transparence
        draw_sprite(page, sprite_transp, x[3], y[3]);

        // 4 draw_sprite renvers� verticalement
        draw_sprite_v_flip(page, sprite_transp, x[4], y[4]);

        // 5 draw_sprite renvers� horizontalement
        draw_sprite_h_flip(page, sprite_transp, x[5], y[5]);

        // 6 draw_sprite avec mise � l'�chelle (anamorphose)
        stretch_sprite(page, sprite_transp, x[6], y[6], 0.5*sprite_transp->w, 0.75*sprite_transp->h);

        // 7 rotate_sprite : le sprite tourne autour de son centre
        // le param�tre de rotation est donn� par   ftofix(angle*128/M_PI)
        // (en supposante la valeur angle en radians)
        rotate_sprite(page, sprite_transp, x[7], y[7], ftofix((phase-7*alpha)*128/M_PI));

        // un dernier au centre : rotation et mise � l'�chelle simultan�e
        echelle=(cos(phase)+1.0)*0.75; // valeur �voluant entre 0 et 1.5
        rotate_scaled_sprite(page, sprite_transp,
                             SCREEN_W/2-echelle*sprite_transp->w/2, SCREEN_H/2-echelle*sprite_transp->h/2,
                             ftofix(-phase*128/M_PI), ftofix(echelle));


        // Affichage (�ventuel) d'un avant plan avec transparence
        masked_blit(avantplan,page,0,0,0,SCREEN_H-150,avantplan->w,avantplan->h);


        // affichage du buffer � l'�crane
        blit(page,screen,0,0,0,0,SCREEN_W,SCREEN_H);

        // la petite pause...
        rest(2);
    }
    allegro_exit();
    return 0;
}
END_OF_MAIN();*/




void initialisation_allegro(){
    allegro_init(); // appel obligatoire (var.globales, recup. infos syst�me ...)
    install_keyboard(); //pour utiliser le clavier
    install_mouse(); //pour utiliser la souris
    //pour choisir la profondeur de couleurs (8,16,24 ou 32 bits)
    set_color_depth(desktop_color_depth()); //ici�: identique � celle du bureau
    //s�lection du mode graphique
    // avec choix d'un driver+mode+r�solution de l'�cran
    if (set_gfx_mode(GFX_AUTODETECT_WINDOWED,800,600,0,0)!=0){
        // message et sortie de prog. si �chec
        allegro_message("prb gfx mode");
        allegro_exit();
        exit(EXIT_FAILURE);
    }
    show_mouse(screen);
}

void mouvement_taupe(){
    for(int i=0; i<NBTAUPES;i++){
        srand(time(NULL));
        // Générer un numéro aléatoire entre 1 et 5
        int numero = rand() % 5 + 1;
        // Afficher le numéro généré
        if(numero == 1){
            for(int i=0;i<NBTAUPES;i++){
                draw_sprite(page, sprite[i], x[1] ,y[1]);
            }
        }
        if(numero == 2) {
            for (int i = 0; i < NBTAUPES; i++) {
                draw_sprite(page, sprite[i], x[2], y[2]);
            }
        }
        if(numero == 3) {
            for (int i = 0; i < NBTAUPES; i++) {
                draw_sprite(page, sprite[i], x[3], y[3]);
            }
        }
        if(numero == 4) {
            for (int i = 0; i < NBTAUPES; i++) {
                draw_sprite(page, sprite[i], x[4], y[4]);
            }
        }
        if(numero == 5) {
            for (int i = 0; i < NBTAUPES; i++) {
                draw_sprite(page, sprite[i], x[5], y[5]);
            }
        }

        }

        }
    }
}
