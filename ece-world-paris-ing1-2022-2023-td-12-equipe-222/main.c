#include <allegro.h>
#include <stdbool.h>
#define SCREEN_W 768
#define SCREEN_H 632


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
    BITMAP *BallonF1;
    BITMAP *BallonF2;
    BITMAP *BallonF3;
    BITMAP *BallonF4;
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

    int posx6,posy6;    // coordonn�es
    int tx6,ty6;        // taille
    int depx6,depy6;    // vecteur d�placement effectif en x et y

    int posx7,posy7;    // coordonn�es
    int tx7,ty7;        // taille
    int depx7,depy7;    // vecteur d�placement effectif en x et y

    int posx8,posy8;    // coordonn�es
    int tx8,ty8;        // taille
    int depx8,depy8;    // vecteur d�placement effectif en x et y

    int posx9,posy9;    // coordonn�es
    int tx9,ty9;        // taille
    int depx9,depy9;    // vecteur d�placement effectif en x et y

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
    BallonF1=load_bitmap("BallonF1.bmp",NULL);
    BallonF2=load_bitmap("BallonF2.bmp",NULL);
    BallonF3=load_bitmap("BallonF3.bmp",NULL);
    BallonF4=load_bitmap("BallonF4.bmp",NULL);
    BITMAP *souris = load_bitmap("souris.bmp", NULL);





    // Initialisation des param�tres de l'�l�ment 2
    tx1=Ballon1->w;            ty1=Ballon1->h;
    posx1=SCREEN_W/2-tx1/2;  posy1=SCREEN_H/2-ty1/2;
    depx1=13;                 depy1=10;

    tx3=Ballon2->w;            ty3=Ballon2->h;
    posx3=SCREEN_W/2-tx3/2;  posy3=SCREEN_H/2-ty3/2;
    depx3=16;                 depy3=10;

    tx4=Ballon3->w;            ty4=Ballon3->h;
    posx4=SCREEN_W/2-tx4/2;  posy4=SCREEN_H/2-ty4/2;
    depx4=43;                 depy4=40;

    tx5=Ballon4->w;            ty5=Ballon4->h;
    posx5=SCREEN_W/2-tx5/2;  posy5=SCREEN_H/2-ty5/2;
    depx5=19;                 depy5=20;

    tx6=BallonF1->w;            ty6=BallonF1->h;
    posx6=100;  posy6=100;
    depx6=5;                 depy6=5;

    tx7=BallonF2->w;            ty7=BallonF2->h;
    posx7=SCREEN_W/2-tx7/2;  posy7=SCREEN_H/2-ty7/2;
    depx7=12;                 depy7=9;

    tx8=BallonF3->w;            ty8=BallonF3->h;
    posx8=300;  posy8=300;
    depx8=5;                 depy8=5;

    tx9=BallonF4->w;            ty9=BallonF4->h;
    posx9=400;  posy9=400;
    depx9=5;                 depy9=5;


    bool ballon_affiche1 = true;
    bool ballon_affiche2 = true;
    bool ballon_affiche3 = true;
    bool ballon_affiche4 = true;
    bool ballon_affiche5 = true;
    bool ballon_affiche6 = true;
    bool ballon_affiche7 = true;
    bool ballon_affiche8 = true;
    int score_ballon=0;


    // Boucle interactive
    while (!key[KEY_ESC])
    {

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
            ballon_affiche1 = false;
        }
        if (mouse_b & 1 && mouse_x >= posx3 && mouse_x <= posx3 + Ballon2->w && mouse_y >= posy3 && mouse_y <= posy3 + Ballon2->h) {
            // Effacement de l'image
            ballon_affiche2 = false;
        }
        if (mouse_b & 1 && mouse_x >= posx4 && mouse_x <= posx4 + Ballon3->w && mouse_y >= posy4 && mouse_y <= posy4 + Ballon3->h) {
            // Effacement de l'image
            ballon_affiche3 = false;
        }
        if (mouse_b & 1 && mouse_x >= posx5 && mouse_x <= posx5 + Ballon4->w && mouse_y >= posy5 && mouse_y <= posy5 + Ballon4->h) {
            // Effacement de l'image
            ballon_affiche4 = false;
        }
        textprintf_ex(page, font, 650, 20, makecol(0, 0, 0), -1, "Score : %d", score_ballon);
        if (ballon_affiche1 == false && ballon_affiche2 == false && ballon_affiche3 == false && ballon_affiche4 == false){
            if ( (posx6<0 && depx6<0) || (posx6+tx6>SCREEN_W && depx6>0) )
                depx6=-depx6;
            if ( (posy6<0 && depy6<0) || (posy6+ty6>SCREEN_H && depy6>0) )
                depy6=-depy6;

            if ( (posx7<0 && depx7<0) || (posx7+tx7>SCREEN_W && depx7>0) )
                depx7=-depx7;
            if ( (posy7<0 && depy7<0) || (posy7+ty7>SCREEN_H && depy7>0) )
                depy7=-depy7;

            if ( (posx8<0 && depx8<0) || (posx8+tx8>SCREEN_W && depx8>0) )
                depx8=-depx8;
            if ( (posy8<0 && depy8<0) || (posy8+ty8>SCREEN_H && depy8>0) )
                depy8=-depy8;

            if ( (posx9<0 && depx9<0) || (posx9+tx9>SCREEN_W && depx9>0) )
                depx9=-depx9;
            if ( (posy9<0 && depy9<0) || (posy9+ty9>SCREEN_H && depy9>0) )
                depy9=-depy9;

            posx6=posx6+depx6;
            posy6=posy6+depy6;

            posx7=posx7+depx7;
            posy7=posy7+depy7;

            posx8=posx8+depx8;
            posy8=posy8+depy8;

            posx9=posx9+depx9;
            posy9=posy9+depy9;

            if (ballon_affiche5) {
                // Afficher l'image seulement si ballon_affiche est vrai
                draw_sprite(page, BallonF1, posx6, posy6);
            }
            if (ballon_affiche6) {
                // Afficher l'image seulement si ballon_affiche est vrai
                draw_sprite(page, BallonF2, posx7, posy7);
            }
            if (ballon_affiche7) {
                // Afficher l'image seulement si ballon_affiche est vrai
                draw_sprite(page, BallonF3, posx8, posy8);
            }
            if (ballon_affiche8) {
                // Afficher l'image seulement si ballon_affiche est vrai
                draw_sprite(page, BallonF4, posx9, posy9);
            }

            if (mouse_b & 1 && mouse_x >= posx6 && mouse_x <= posx6 + BallonF1->w && mouse_y >= posy6 && mouse_y <= posy6 + BallonF1->h) {
                // Effacement de l'image
                ballon_affiche5 = false;
            }
            if (mouse_b & 1 && mouse_x >= posx7 && mouse_x <= posx7 + BallonF2->w && mouse_y >= posy7 && mouse_y <= posy7 + BallonF2->h) {
                // Effacement de l'image
                ballon_affiche6 = false;
            }
            if (mouse_b & 1 && mouse_x >= posx8 && mouse_x <= posx8 + BallonF3->w && mouse_y >= posy8 && mouse_y <= posy8 + BallonF3->h) {
                // Effacement de l'image
                ballon_affiche7 = false;
            }
            if (mouse_b & 1 && mouse_x >= posx9 && mouse_x <= posx9 + BallonF4->w && mouse_y >= posy9 && mouse_y <= posy9 + BallonF4->h) {
                // Effacement de l'image
                ballon_affiche8 = false;
            }
        }
        draw_sprite(page, souris, mouse_x, mouse_y);


        blit(page,screen,0,0,0,0,SCREEN_W,SCREEN_H);
        rest(20);
    }

    return 0;
}
//attention ne pas oublier !
END_OF_MAIN();


