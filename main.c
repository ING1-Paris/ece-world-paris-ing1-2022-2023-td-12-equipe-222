#include <allegro.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600
#define IMAGE_WIDTH 50
#define IMAGE_HEIGHT 50
#define NUM_LOCATIONS 5
#define GAME_DURATION 10

BITMAP* image;
BITMAP* decor;
int score = 0;
int game_timer = GAME_DURATION * 60;

struct Location {
    int x;
    int y;
};

struct Location locations[NUM_LOCATIONS];

void initialize() {
    allegro_init();
    install_keyboard();
    install_mouse();

    set_color_depth(desktop_color_depth());
    if (set_gfx_mode(GFX_AUTODETECT_WINDOWED, SCREEN_WIDTH, SCREEN_HEIGHT, 0, 0) != 0) {
        allegro_message("ERREUR TELECHARGEMENT");
        allegro_exit();
        exit(EXIT_FAILURE);
    }

    show_mouse(screen);
}

void load_assets() {
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
        locations[i].y = rand() % (SCREEN_HEIGHT - IMAGE_HEIGHT);
    }
}

void update_score() {
    score++;
}

/*void draw_game_over() {
    clear_bitmap(screen);
    textprintf_centre_ex(screen, font, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, makecol(255, 255, 255), -1, "Game Over! Your score: %d", score);
}*/

void draw_timer() {
    int seconds = game_timer / 60;
    int minutes = seconds / 60;
    seconds %= 60;

    textprintf_centre_ex(screen, font, SCREEN_WIDTH / 2, 30, makecol(255, 255, 255), -1, "Temps: %02d:%02d", minutes, seconds);
}

void draw1() {
    clear_bitmap(screen);
    blit(decor, screen, 0, 0, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
    textprintf_centre_ex(screen, font, SCREEN_WIDTH / 2, 10, makecol(255, 255, 255), -1, "Score: %d", score);
    masked_blit(image, screen, 0, 0, locations[score % NUM_LOCATIONS].x, locations[score % NUM_LOCATIONS].y, IMAGE_WIDTH, IMAGE_HEIGHT);
    draw_timer();
}

int main() {

    srand(time(NULL));

    initialize();
    load_assets();
    generate_locations();

    while (!key[KEY_ESC] && game_timer > 0) {

        if (mouse_b & 1) {
            if (mouse_x >= locations[score % NUM_LOCATIONS].x &&
                mouse_x < locations[score % NUM_LOCATIONS].x + IMAGE_WIDTH &&
                mouse_y >= locations[score % NUM_LOCATIONS].y &&
                mouse_y < locations[score % NUM_LOCATIONS].y + IMAGE_HEIGHT) {
                update_score();
            }
        }

        draw1();

        rest(16); // Delay to limit the frame rate to approximately 60 FPS
        game_timer--;
    }

    allegro_exit();
    printf("Game Over! Your score: %d\n", score);

    return 0;
}
END_OF_MAIN();
