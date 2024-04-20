#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <unistd.h>

#define WIDTH 20
#define HEIGHT 10

typedef struct {
    int x;
    int y;
} Point;

typedef struct {
    Point *body;
    int length;
    char symbol_head;
    char symbol_body;
} Snake;

typedef enum {
    UP,
    DOWN,
    LEFT,
    RIGHT
} Direction;

typedef struct {
    Point position;
    char symbol;
} Food;

int isGameOver;
Snake snake;
Food food;
Direction currentDirection;
int level;
int delay;
int isPaused;

void setup();
void draw();
void input();
void move();
void spawnFood();
void printLevel();
void printExit();
void increaseSpeed();
void togglePause();

void setup() {
    snake.length = 3; // Initial length of the snake
    snake.symbol_head = '@';
    snake.symbol_body = '*';
    snake.body = malloc(sizeof(Point) * snake.length);
    snake.body[0].x = WIDTH / 2;
    snake.body[0].y = HEIGHT / 2;
    for (int i = 1; i < snake.length; ++i) {
        snake.body[i].x = snake.body[i - 1].x - 1;
        snake.body[i].y = snake.body[i - 1].y;
    }

    food.symbol = '$';
    spawnFood();

    isGameOver = 0;
    currentDirection = RIGHT; // Initial direction of the snake
    level = 1;
    delay = 100000; // Initial delay (100 ms)
    isPaused = 0;
}

void draw() {
    system("cls");

    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            int isBodyPart = 0;
            for (int i = 0; i < snake.length; i++) {
                if (x == snake.body[i].x && y == snake.body[i].y) {
                    printf("%c", (i == 0) ? snake.symbol_head : snake.symbol_body);
                    isBodyPart = 1;
                    break;
                }
            }
            if (!isBodyPart && x == food.position.x && y == food.position.y)
                printf("%c", food.symbol);
            else if (!isBodyPart)
                printf(" ");
        }
        printf("\n");
    }

    printf("Level: %d\n", level);
    if (isPaused)
        printf("Game paused. Press 'P' to resume.\n");
    else
        printf("Press 'P' to pause.\n");
}

void input() {
    if (_kbhit()) {
        switch (_getch()) {
            case 'w':
                currentDirection = UP;
                break;
            case 's':
                currentDirection = DOWN;
                break;
            case 'a':
                currentDirection = LEFT;
                break;
            case 'd':
                currentDirection = RIGHT;
                break;
            case 'x':
                isGameOver = 1;
                break;
            case 'p':
            case 'P':
                togglePause();
                break;
        }
    }
}

void move() {
    if (isPaused)
        return;

    for (int i = snake.length - 1; i > 0; i--) {
        snake.body[i] = snake.body[i - 1];
    }

    switch (currentDirection) {
        case UP:
            snake.body[0].y--;
            break;
        case DOWN:
            snake.body[0].y++;
            break;
        case LEFT:
            snake.body[0].x--;
            break;
        case RIGHT:
            snake.body[0].x++;
            break;
    }

    if (snake.body[0].x == food.position.x && snake.body[0].y == food.position.y) {
        snake.length++;
        snake.body = realloc(snake.body, sizeof(Point) * snake.length);
        snake.body[snake.length - 1] = snake.body[snake.length - 2]; // Grow the tail
        spawnFood();
        level++;
        increaseSpeed(); // Increase speed when reaching a new level
    }

    if (snake.body[0].x < 0 || snake.body[0].x >= WIDTH || snake.body[0].y < 0 || snake.body[0].y >= HEIGHT)
        isGameOver = 1;

    for (int i = 1; i < snake.length; i++) {
        if (snake.body[0].x == snake.body[i].x && snake.body[0].y == snake.body[i].y)
            isGameOver = 1;
    }
}

void spawnFood() {
    food.position.x = rand() % WIDTH;
    food.position.y = rand() % HEIGHT;
}

void printLevel() {
    printf("Level: %d\n", level);
}

void printExit() {
    printf("Final score: %d\n", level);
}

void increaseSpeed() {
    delay -= 10000; // Decrease delay by 10 ms (increase speed)
}

void togglePause() {
    isPaused = !isPaused;
}

int main() {
    setup();

    while (!isGameOver) {
        draw();
        input();
        move();
        usleep(delay); // Adjust snake speed
    }

    printf("Game Over!\n");
    printExit();
    free(snake.body);
    return 0;
}
