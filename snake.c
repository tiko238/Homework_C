#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>

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
    int color; 
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
    int color; 
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
void setColor(int color);
void startMenu();

void setup() {
    snake.length = 3; 
    snake.symbol_head = '@';
    snake.symbol_body = '*';
    snake.color = FOREGROUND_GREEN | FOREGROUND_INTENSITY; 
    snake.body = malloc(sizeof(Point) * snake.length);
    snake.body[0].x = WIDTH / 2;
    snake.body[0].y = HEIGHT / 2;
    for (int i = 1; i < snake.length; ++i) {
        snake.body[i].x = snake.body[i - 1].x - 1;
        snake.body[i].y = snake.body[i - 1].y;
    }

    food.symbol = '$';
    food.color = FOREGROUND_BLUE | FOREGROUND_INTENSITY; 
    spawnFood();

    isGameOver = 0;
    currentDirection = RIGHT; 
    level = 1;
    delay = 100000; 
    isPaused = 0;
}

void setColor(int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void draw() {
    system("cls");

    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            int isBodyPart = 0;
            for (int i = 0; i < snake.length; i++) {
                if (x == snake.body[i].x && y == snake.body[i].y) {
                    setColor(snake.color);
                    printf("%c", (i == 0) ? snake.symbol_head : snake.symbol_body);
                    isBodyPart = 1;
                    break;
                }
            }
            if (!isBodyPart && x == food.position.x && y == food.position.y) {
                setColor(food.color);
                printf("%c", food.symbol);
            }
            else if (!isBodyPart) {
                setColor(FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_INTENSITY);
                printf(" ");
            }
        }
        printf("\n");
    }

    setColor(FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_INTENSITY);
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
        snake.body[snake.length - 1] = snake.body[snake.length - 2];
        spawnFood();
        level++;
        increaseSpeed(); 
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
    delay -= 10000; 
}

void togglePause() {
    isPaused = !isPaused;
}

void startMenu() {
    system("cls");
    printf("Welcome to Snake Game!\n");
    printf("Choose mode:\n");
    printf("1. Single Player\n");
    printf("2. Multiplayer\n");
    printf("Your choice: ");
    char mode = _getch();
    switch (mode) {
        case '1':
            printf("\nSingle Player mode selected.\n");
            break;
        case '2':
            printf("\nMultiplayer mode selected.\n");
            
            break;
        default:
            printf("\nInvalid choice. Please choose again.\n");
            startMenu();
    }
    printf("Press any key to start...");
    _getch();
}

int main() {
    startMenu();
    setup();

    while (!isGameOver) {
        draw();
        input();
        move();
        Sleep(delay / 1000); 
    }

    printf("Game Over!\n");
    printExit();
    free(snake.body);
    return 0;
}
