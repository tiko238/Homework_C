/*
Добавить возможность управления змейкой клавишами WSAD (вне
зависимости от раскладки и регистра).
Зависимости от регистра в соответствии с таблицей.
W, w Вверх
S, s Вниз
A, a Влево
D, d Вправо
Для решения предлагается сделать массив кодов управления struct
control_buttons default_controls[CONTROLS]. CONTROLS – определяем
количество элементов массива.
В необходимых функциях в цикле необходимо сравнивать с каждым типом
управления в цикле: for (int i = 0; i < CONTROLS; i++)

*/

enum {LEFT=1, UP, RIGHT, DOWN, STOP_GAME=KEY_F(10), CONTROLS=3};
struct control_buttons default_controls[CONTROLS]= {{KEY_DOWN, KEY_UP, KEY_LEFT, KEY_RIGHT,}
    {'s', 'w', 'a', 'd'},
    {'S', 'W', 'A', 'D'}};
    
    void changeDirection(snake_t* snake, const int32_t key)
{
    // Проверяем стандартные клавиши и WSAD
    if (key == snake->controls.down || key == 's')
        snake->direction = DOWN;
    else if (key == snake->controls.up || key == 'w')
        snake->direction = UP;
    else if (key == snake->controls.right || key == 'd')
        snake->direction = RIGHT;
    else if (key == snake->controls.left || key == 'a')
        snake->direction = LEFT;
}