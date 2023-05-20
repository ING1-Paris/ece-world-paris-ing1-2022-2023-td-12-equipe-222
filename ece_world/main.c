#include<allegro.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480
#define NB_CANARD 8

typedef struct canard {
    int x,y,depx,depy;
    int drag;
}t_canard;

BITMAP *Image;
int canardX[NB_CANARD];
int canardY[NB_CANARD];

int colision(t_canard canard[], int i, int w, int h)
{
    if (canard[i].x +canard[i].depx < 0 || canard[i].x+canard[i].depx + w > SCREEN_W || canard[i].y +canard[i].depy < 0 || canard[i].y +canard[i].depy + h > SCREEN_H)
        return 1;
    return 0;
}

void update_positions(t_canard canard[], int w, int h)
{
    int i;
    for (i = 0; i < NB_CANARD; i++)
    {
        if (!canard[i].drag) {
            if (!colision(canard, i, w, h)) {
                canard[i].x += canard[i].depx;
                canard[i].y += canard[i].depy;
            } else {
                canard[i].depx = rand() % 2;
                canard[i].depy = rand() % 2;
                if (!canard[i].depx)
                    canard[i].depx = -5;
                else
                    canard[i].depx = 5;
                if (!canard[i].depy)
                    canard[i].depy = -5;
                else
                    canard[i].depy = 5;
            }
        }


    }
}

void draw(t_canard canard[], BITMAP *buffer)
{
    int i;
    for (i = 0; i < NB_CANARD; i++)
    {
        if (canard[i].drag == 0)
            stretch_sprite(buffer, Image,canard[i].x, canard[i].y,Image->w / 15,Image->h / 15);
        else
            stretch_sprite(buffer, Image, mouse_x, mouse_y,Image->w / 15,Image->h / 15);
    }
}

void getDrag(t_canard canard[], int w, int h, int *alreadyDrag)
{
    for (int i = 0; i < NB_CANARD; i++) {
        if (!*alreadyDrag && !canard[i].drag && mouse_b & 1 && (mouse_x >= canard[i].x && mouse_x <= canard[i].x + w) && (mouse_y >= canard[i].y && mouse_y <= canard[i].y + h)) {
            canard[i].drag = 1;
            *alreadyDrag = 1;
        }
    }
}

void pullDown(t_canard canard[], int *alreadyDrag, int *score)
{
    if (*alreadyDrag) {
        for (int i = 0; i < NB_CANARD; i++) {
            if (canard[i].drag && !(mouse_b & 1)) { // repose le canard
                if (mouse_x >= 570 && mouse_y >= 450) {
                    *score += 1;
                    canard[i].x = -1000;
                }
                *alreadyDrag = 0;
                canard[i].drag = 0;
            }
        }
    }
}

int main()
{
    int i;
    int score = 0;

    char tempo[10];
    int alreadyDrag = 0;
    BITMAP *buffer;
    BITMAP *panier;
    t_canard canard[NB_CANARD];
    srand(time(NULL));

    // Lancer allegro et le mode graphique
    allegro_init();
    install_keyboard();
    install_mouse();

    set_color_depth(desktop_color_depth());
    if (set_gfx_mode(GFX_AUTODETECT_WINDOWED,800,650,0,0)!=0){
        allegro_message("probleme mode graphique");
        allegro_exit();
        exit(EXIT_FAILURE);
    }

    buffer = create_bitmap(SCREEN_W, SCREEN_H);
    Image = load_bitmap("../canard.bmp", NULL);
    BITMAP*fond = load_bitmap("../eauFond.bmp", NULL);
    panier = load_bitmap("../panier.bmp", NULL);

    if (!Image) {
        printf("Erreur: Impossible de charger l'image");
        exit(-1);
    }

    for (i = 0; i < NB_CANARD; i++)
    {
        canard[i].x = rand() % (SCREEN_W - Image->w / 15);
        canard[i].y = rand() % (SCREEN_H- Image->h / 15);
        canard[i].depx = rand() % 2;
        canard[i].depy = rand() % 2;
        canard[i].drag = 0;
        if (!canard[i].depx)
            canard[i].depx = -5;
        else
            canard[i].depx = 5;
        if (!canard[i].depy)
            canard[i].depy = -5;
        else
            canard[i].depy = 5;
    }
    show_mouse(screen);
    clock_t temps = clock();
    while (!key[KEY_ESC])
    {
        clear_bitmap(buffer);
        blit(fond, buffer, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
        getDrag(canard, Image->w / 15, Image->h / 15, &alreadyDrag);
        pullDown(canard, &alreadyDrag, &score);
        update_positions(canard, Image->w / 15, Image->h / 15);
        draw(canard, buffer);

        sprintf(tempo, "%d", score);
        textout_ex(buffer, font, "score:", 30, 30, makecol(0, 0, 0), -1);
        textout_ex(buffer, font, tempo, 100, 30, makecol(0, 0, 0), -1);

        sprintf(tempo, "%d", (3000 - ((clock() - temps) / 1000))/100);
        textout_ex(buffer, font, "temps:", 30, 50, makecol(0, 0, 0), -1);
        textout_ex(buffer, font, tempo, 100, 50, makecol(0, 0, 0), -1);

        if ((3000 - ((clock() - temps) / 1000))/100 <= 0) { // fin du temps
            break;
        }

        stretch_sprite(buffer, panier, 570, 450, panier->w / 2, panier->h / 2);
        blit(buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
    }

    destroy_bitmap(Image);
    allegro_exit() ;

    return 0;

}
END_OF_MAIN();