
#include <allegro.h>



int main()
{
    // initialisation allegro obligatoire
    allegro_init();
    install_mouse();

    BITMAP *page;
    BITMAP *image;
    BITMAP *Ballon1;
    BITMAP *Ballon2;
    BITMAP *Ballon3;
    BITMAP *Ballon4;
    srand(time(NULL));


    int posx1,posy1;    // coordonn�es
    int tx1, ty1;          // taille
    int depx1,depy1;    // vecteur d�placement effectif en x et y


    int posx2,posy2;    // coordonn�es
    int tx2,ty2;        // taille
    int depx2,depy2;    // vecteur d�placement effectif en x et y

    // pour disposer du clavier
    install_keyboard();
    // d�finir un mode graphique
    set_color_depth(desktop_color_depth());
    if (set_gfx_mode(GFX_AUTODETECT_WINDOWED,800,600,0,0)!=0)
    {
        allegro_message("prb gfx mode");
        allegro_exit();
        exit(EXIT_FAILURE);
    }
    // CREATION DU BUFFER D'AFFICHAGE � la taille de l'�cran
    page=create_bitmap(SCREEN_W,SCREEN_H);
    clear_bitmap(page);
    image=load_bitmap("mon_image.bmp",NULL);
    Ballon1=load_bitmap("Ballon1.bmp",NULL);
    Ballon2=load_bitmap("Ballon2.bmp",NULL);
    Ballon3=load_bitmap("Ballon3.bmp",NULL);
    Ballon4=load_bitmap("Ballon4.bmp",NULL);

    // V�rification que l'image est bien charg�e (dans le cas contraire image vaut NULL)
    // TOUJOURS LE FAIRE CAR ON N'EST JAMAIS CERTAIN DE BIEN TROUVER L'IMAGE
    if (!image)
    {
        allegro_message("pas pu trouver/charger mon_image.bmp");
        allegro_exit();
        exit(EXIT_FAILURE);
    }

    // Affichage de l'image sur l'�cran au milieu
    blit(image,screen,0,0, 0, 0, image->w, image->h);
    blit(Ballon1,screen,0,0, 0, 0, Ballon1->w, Ballon1->h);
    blit(Ballon2,screen,0,0, 0, 0, image->w, image->h);
    blit(Ballon3,screen,0,0, 0, 0, image->w, image->h);
    blit(Ballon4,screen,0,0, 0, 0, image->w, image->h);

    // Initialisation des param�tres de l'�l�ment 2
    tx2=image->w;            ty2=image->h;
    posx2=SCREEN_W/2-tx2/2;  posy2=SCREEN_H/2-ty2/2;
    depx2=9;                 depy2=5;

    // Initialisation des param�tres de l'�l�ment 2
    tx1=Ballon1->w;            ty1=Ballon1->h;
    posx1=SCREEN_W/2-tx1/2;  posy1=SCREEN_H/2-ty1/2;
    depx1=13;                 depy1=10;

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


        if ( (posx2<0 && depx2<0) || (posx2+tx2>SCREEN_W && depx2>0) )
            depx2=-depx2;
        if ( (posy2<0 && depy2<0) || (posy2+ty2>SCREEN_H && depy2>0) )
            depy2=-depy2;

        // calculer nouvelles positions
        posx1=posx1+depx1;
        posy1=posy1+depy1;

        posx2=posx2+depx2;
        posy2=posy2+depy2;

        // 3) AFFICHAGE NOUVELLEs POSITIONs SUR LE BUFFER
        //    ON UTILISE page AU LIEU DE screen
        blit(image,page,0,0,posx2,posy2,tx2,ty2); // astuce : image en 1er...
        //blit(Ballon1,page,0,0, posx1, posy1, tx1, ty1);
        draw_sprite(page, Ballon1, posx1, posy1);
        if (mouse_b & 1 && mouse_x >= posx2 && mouse_x <= posx2 + image->w && mouse_y >= posy2 && mouse_y <= posy2 + image->h) {
            // Effacement de l'image
            clear_bitmap(image);
        }
        if (mouse_b & 1 && mouse_x >= posx1 && mouse_x <= posx1 + Ballon1->w && mouse_y >= posy1 && mouse_y <= posy1 + Ballon1->h) {
            // Effacement de l'image
            clear_bitmap(Ballon1);
        }

        // 4) AFFICHAGE DU BUFFER MIS A JOUR A L'ECRAN
        //    le nouveau contenu graphique remplace l'ancien
        //    sans que l'ancien ait �t� effac� � l'�cran (pas de clignotement)
        blit(page,screen,0,0,0,0,SCREEN_W,SCREEN_H);


        // 5) ON FAIT UNE PETITE PAUSE � chaque fois sinon �a va trop vite...
        rest(20);
    }

    return 0;
}
//attention ne pas oublier !
END_OF_MAIN();
