#include <allegro.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SCREEN_WIDTH 800
#define hauteur \
600
#define IMAGE_WIDTH 50
#define IMAGE_HEIGHT 50
#define NUM_LOCATIONS 6
#define GAME_DURATION 10

BITMAP* image;
BITMAP* decor;
BITMAP* Buf;
int score = 0;
int game_timer = GAME_DURATION * 60;
int ghost_timer = 0;
int ghost_duration = 1; // temps que le fantome reste à l'acran avant le clique


struct Location {
    int x;
    int y;
};

struct Location locations[NUM_LOCATIONS];

void initialisation() {
    allegro_init();
    install_keyboard();
    install_mouse();

    set_color_depth(desktop_color_depth());
    if (set_gfx_mode(GFX_AUTODETECT_WINDOWED, SCREEN_WIDTH, hauteur
            , 0, 0) != 0) {
        allegro_message("ERREUR TELECHARGEMENT");
        allegro_exit();
        exit(EXIT_FAILURE);
    }

    show_mouse(screen);

    Buf = create_bitmap(SCREEN_WIDTH, hauteur);
    if (Buf == NULL) {
        allegro_message("Erreur avec le double buffer");
        allegro_exit();
        exit(EXIT_FAILURE);
    }
}

void chargement_images() {
    image = load_bitmap("fantome.bmp", NULL);

    if (image == NULL) {
        allegro_message("le fantome n'est pas là encore");
        allegro_exit();
        exit(EXIT_FAILURE);
    }

    decor = load_bitmap("cimetiere.bmp", NULL);
    if (decor == NULL) {
        allegro_message("le decor n'est pas chargé ");
        allegro_exit();
        exit(EXIT_FAILURE);
    }
}

void generate_locations() {
    int i;
    for (i = 0; i < NUM_LOCATIONS; i++) {
        locations[i].x = rand() % (SCREEN_WIDTH - IMAGE_WIDTH);
        locations[i].y = rand() % (hauteur- IMAGE_HEIGHT);
    }
}

void positions_fantome(){
    int i=0;
    int randomIndex = rand() % NUM_LOCATIONS;
    locations[0].x= 40;
    locations[0].y=350;
    locations[1].x=80;
    locations[1].y= 445;
    locations[2].x= 200;
    locations[2].y= 390;
    locations[3].x= 285;
    locations[3].y= 390;
    locations[4].x= 480;
    locations[4].y= 390;
    locations[5].x= 580;
    locations[5].y= 480;
    /*for(i; i < NUM_LOCATIONS; i++){
        locations[i].x=rand() % (30, 80, 250, 450, 560);
        locations[i].y=390;
    }*/

}


void update_score() {
    score++;
}

void draw_game_over() {
    clear_bitmap(Buf);
    textprintf_centre_ex(Buf, font, SCREEN_WIDTH / 2, hauteur
                                                      / 2, makecol(255, 255, 255), -1, "Game Over! Your score: %d", score);
    blit(Buf, screen, 0, 0, 0, 0, SCREEN_WIDTH, hauteur
    );
}

void draw_timer() {
    int seconds = game_timer / 60;
    int minutes = seconds / 60;
    seconds %= 60;

    textprintf_centre_ex(Buf, font, SCREEN_WIDTH / 2, 30, makecol(255, 255, 255), -1, "Temps: %02d:%02d", minutes, seconds);
}

void draw() {
    clear_bitmap(Buf);
    blit(decor, Buf, 0, 0, 0, 0, SCREEN_WIDTH, hauteur);
    textprintf_centre_ex(Buf, font, SCREEN_WIDTH / 2, 10, makecol(255, 255, 255), -1, "Score: %d", score);

    if (ghost_timer >= ghost_duration * 60) {
        generate_locations(); // Générer de nouvelles positions pour le fantôme
        ghost_timer = 0; // Réinitialiser la minuterie du fantôme
    }

    masked_blit(image, Buf, 0, 0, locations[score % NUM_LOCATIONS].x, locations[score % NUM_LOCATIONS].y, IMAGE_WIDTH, IMAGE_HEIGHT);
    draw_timer();
    blit(Buf, screen, 0, 0, 0, 0, SCREEN_WIDTH, hauteur);

    ghost_timer++; // Incrémenter la minuterie du fantôme
}

int main() {
    srand(time(NULL));

    initialisation();
    chargement_images();
    generate_locations();
    //positions_fantome();
    while (!key[KEY_ESC] && game_timer > 0) {
        if (mouse_b & 1) {
            if (mouse_x >= locations[score % NUM_LOCATIONS].x &&
                mouse_x < locations[score % NUM_LOCATIONS].x + IMAGE_WIDTH &&
                mouse_y >= locations[score % NUM_LOCATIONS].y &&
                mouse_y < locations[score % NUM_LOCATIONS].y + IMAGE_HEIGHT) {
                update_score();
            }
        }

        draw();

        rest(16); // Delay to limit the frame rate to approximately 60 FPS
        game_timer--;
    }

    draw_game_over();

    allegro_exit();
    printf("Game Over! Your score: %d\n", score);

    return 0;
}
END_OF_MAIN();

