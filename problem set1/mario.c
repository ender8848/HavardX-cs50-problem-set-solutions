#include <stdio.h>
#include <cs50.h>

int get_positive_int(void);
int draw_pym(int n);

int main(void)
{
    int n = get_positive_int();
    draw_pym(n);
    return 0;
}

int get_positive_int(void)
{
    int n = 0;
    do
    {
        n = get_int("Height(1-8): ");
    }
    while (n < 1 || n > 8);
    return n;
}

int draw_pym(n)
{
    for (int i = 1; i < n + 1; i++)
    {
        for (int j = 0; j < n - i; j++)
        {
            printf(" ");
        }

        for (int j = 0; j < i; j++)
        {
            printf("#");
        }
        printf(" ");

        for (int j = 0; j < i; j++)
        {
            printf("#");
        }
        for (int j = 0; j < n - i; j++)
        {
            printf("  ");
        }
        printf("\n");
    }
    return 0;
}