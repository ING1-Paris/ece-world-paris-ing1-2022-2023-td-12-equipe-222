
#include <allegro.h>
#include <stdbool.h>



#define SCREEN_W 768
#define SCREEN_H 632
volatile int counter = 0; // variable de compteur
volatile int ticks = 0;   // variable de compteur de ticks
LOCK_VARIABLE(counter);   // verrouille la variable de compteur
LOCK_VARIABLE(ticks);     // verrouille la variable de compteur de ticks
LOCK_FUNCTION(increment_counter); // verrouille la fonction d'incrémentation
void increment_counter() { counter++; } // fonction d'incrémentation



int main()
{
    // initialisation allegro obligatoire
    allegro_init();
    install_mouse();

    BITMAP *page=NULL;
    BITMAP *Ballon1;
    BITMAP *Ballon2;
    BITMAP *Ballon3;
    BITMAP *Ballon4;
    srand(time(NULL));


    int posx1,posy1;    // coordonn�es
    int tx1, ty1;          // taille
    int depx1,depy1;    // vecteur d�placement effectif en x et y

    int posx3,posy3;    // coordonn�es
    int tx3,ty3;        // taille
    int depx3,depy3;    // vecteur d�placement effectif en x et y

    int posx4,posy4;    // coordonn�es
    int tx4,ty4;        // taille
    int depx4,depy4;    // vecteur d�placement effectif en x et y

    int posx5,posy5;    // coordonn�es
    int tx5,ty5;        // taille
    int depx5,depy5;    // vecteur d�placement effectif en x et y

    // pour disposer du clavier
    install_keyboard();
    // d�finir un mode graphique
    set_color_depth(desktop_color_depth());
    if (set_gfx_mode(GFX_AUTODETECT_WINDOWED,SCREEN_W,SCREEN_H,0,0)!=0)
    {
        allegro_message("prb gfx mode");
        allegro_exit();
        exit(EXIT_FAILURE);
    }
    // CREATION DU BUFFER D'AFFICHAGE � la taille de l'�cran
    BITMAP *image = load_bitmap("image.bmp", NULL);
    if(!image){
        allegro_message("prb chargement image");
        allegro_exit();
        exit(EXIT_FAILURE);
    }

    page=create_bitmap(SCREEN_W,SCREEN_H);
    clear_bitmap(page);
    Ballon1=load_bitmap("Ballon1.bmp",NULL);
    Ballon2=load_bitmap("Ballon2.bmp",NULL);
    Ballon3=load_bitmap("Ballon3.bmp",NULL);
    Ballon4=load_bitmap("Ballon4.bmp",NULL);




    // Initialisation des param�tres de l'�l�ment 2
    tx1=Ballon1->w;            ty1=Ballon1->h;
    posx1=SCREEN_W/2-tx1/2;  posy1=SCREEN_H/2-ty1/2;
    depx1=13;                 depy1=10;

    tx3=Ballon2->w;            ty3=Ballon2->h;
    posx3=SCREEN_W/2-tx1/2;  posy3=SCREEN_H/2-ty1/2;
    depx3=16;                 depy3=10;

    tx4=Ballon3->w;            ty4=Ballon3->h;
    posx4=SCREEN_W/2-tx1/2;  posy4=SCREEN_H/2-ty1/2;
    depx4=23;                 depy4=18;

    tx5=Ballon4->w;            ty5=Ballon4->h;
    posx5=SCREEN_W/2-tx1/2;  posy5=SCREEN_H/2-ty1/2;
    depx5=19;                 depy5=20;


    bool ballon_affiche1 = true;
    bool ballon_affiche2 = true;
    bool ballon_affiche3 = true;
    bool ballon_affiche4 = true;

    // Boucle interactive
    while (!key[KEY_ESC])
    {
        show_mouse(screen);

        // 1) EFFACER POSITIONs ACTUELLEs SUR LE BUFFER
        //    ON EFFACE TOUT LE BUFFER ! (c'est plus simple)
        clear_bitmap(page);

        // 2) DETERMINER NOUVELLEs POSITIONs

        // contr�le des bords : ici on d�cide de rebondir sur les bords
        if ( (posx1<0 && depx1<0) || (posx1+tx1>SCREEN_W && depx1>0) )
            depx1=-depx1;
        if ( (posy1<0 && depy1<0) || (posy1+ty1>SCREEN_H && depy1>0) )
            depy1=-depy1;

        if ( (posx3<0 && depx3<0) || (posx3+tx3>SCREEN_W && depx3>0) )
            depx3=-depx3;
        if ( (posy3<0 && depy3<0) || (posy3+ty3>SCREEN_H && depy3>0) )
            depy3=-depy3;

        if ( (posx4<0 && depx4<0) || (posx4+tx4>SCREEN_W && depx4>0) )
            depx4=-depx4;
        if ( (posy4<0 && depy4<0) || (posy4+ty4>SCREEN_H && depy4>0) )
            depy4=-depy4;

        if ( (posx5<0 && depx5<0) || (posx5+tx5>SCREEN_W && depx5>0) )
            depx5=-depx5;
        if ( (posy5<0 && depy5<0) || (posy5+ty5>SCREEN_H && depy5>0) )
            depy5=-depy5;

        // calculer nouvelles positions
        posx1=posx1+depx1;
        posy1=posy1+depy1;

        posx3=posx3+depx3;
        posy3=posy3+depy3;

        posx4=posx4+depx4;
        posy4=posy4+depy4;

        posx5=posx5+depx5;
        posy5=posy5+depy5;

        // 3) AFFICHAGE NOUVELLEs POSITIONs SUR LE BUFFER
        //    ON UTILISE page AU LIEU DE screen
        blit(image,page, 0, 0, 0, 0,SCREEN_W,SCREEN_H);


        if (ballon_affiche1) {
            // Afficher l'image seulement si ballon_affiche est vrai
            draw_sprite(page, Ballon1, posx1, posy1);
        }
        if (ballon_affiche2) {
            // Afficher l'image seulement si ballon_affiche est vrai
            draw_sprite(page, Ballon2, posx3, posy3);
        }
        if (ballon_affiche3) {
            // Afficher l'image seulement si ballon_affiche est vrai
            draw_sprite(page, Ballon3, posx4, posy4);
        }
        if (ballon_affiche4) {
            // Afficher l'image seulement si ballon_affiche est vrai
            draw_sprite(page, Ballon4, posx5, posy5);
        }


        if (mouse_b & 1 && mouse_x >= posx1 && mouse_x <= posx1 + Ballon1->w && mouse_y >= posy1 && mouse_y <= posy1 + Ballon1->h) {
            // Effacement de l'image
            clear_bitmap(Ballon1);
            ballon_affiche1 = false;
        }
        if (mouse_b & 1 && mouse_x >= posx3 && mouse_x <= posx3 + Ballon2->w && mouse_y >= posy3 && mouse_y <= posy3 + Ballon2->h) {
            // Effacement de l'image
            clear_bitmap(Ballon2);
            ballon_affiche2 = false;
        }
        if (mouse_b & 1 && mouse_x >= posx4 && mouse_x <= posx4 + Ballon3->w && mouse_y >= posy4 && mouse_y <= posy4 + Ballon3->h) {
            // Effacement de l'image
            clear_bitmap(Ballon3);
            ballon_affiche3 = false;
        }
        if (mouse_b & 1 && mouse_x >= posx5 && mouse_x <= posx5 + Ballon4->w && mouse_y >= posy5 && mouse_y <= posy5 + Ballon4->h) {
            // Effacement de l'image
            clear_bitmap(Ballon4);
            ballon_affiche4 = false;
        }

        // 4) AFFICHAGE DU BUFFER MIS A JOUR A L'ECRAN
        //    le nouveau contenu graphique remplace l'ancien
        //    sans que l'ancien ait �t� effac� � l'�cran (pas de clignotement)
        blit(page,screen,0,0,0,0,SCREEN_W,SCREEN_H);

        ticks = counter / 60; // calcule le nombre de secondes écoulées

        textprintf_centre(screen, font, 700, 30, makecol(255, 255, 255), "%02d:%02d", ticks / 60, ticks % 60); // affiche le temps écoulé

        // 5) ON FAIT UNE PETITE PAUSE � chaque fois sinon �a va trop vite...
        rest(5);

    }

    return 0;
}
//attention ne pas oublier !
END_OF_MAIN();
