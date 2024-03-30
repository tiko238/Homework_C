/*
На стандартном потоке ввода задается натуральное число N (N > 0), после которого следует последовательность из N целых чисел.
На стандартный поток вывода напечатайте, сколько раз в этой последовательности встречается максимум.

Указание: использовать массивы запрещается.

Данные на входе: Натуральное число N (N > 0), после которого следует
последовательность из N целых чисел.
Данные на выходе: Одно целое число.

Пример №1
Данные на входе: 6 1 2 3 2 0 3
Данные на выходе: 2
*/
#include <stdio.h>
#include <stdint.h>

int main() {
int N, num, max_num, max_count;
scanf("%d", &N);
scanf("%d", &max_num);
max_count = 1;
for (int i = 1; i < N; i++) {
    scanf("%d", &num);
    if (num > max_num) {
        max_num = num;
        max_count = 1;
    } else if (num == max_num) {
        max_count++;
    }
}
printf("%d\n", max_count);
return 0;
}