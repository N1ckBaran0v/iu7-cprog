#include <stdio.h>

int count(int);

int main(void)
{
    int money;
    scanf("%i", &money);
    int bottles = count(money);
    printf("%i\n", bottles);
    return 0;
}

int count(int money)
{
    int bottle = 45, empty = 20, diff = bottle - empty;
    money -= bottle;
    int result = money / diff + 1;
    if (money < 0)
    {
        result = 0;
    }
    return result;
}
