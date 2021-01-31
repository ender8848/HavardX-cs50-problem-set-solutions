#include <stdio.h>
#include <cs50.h>

int get_positive_int(void);
int draw_pym(int n);
void hash(int n);
void blank(int n);

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

void blank(int n)
{
    for (int i = 0; i < n; i++)
    {
        printf(" ");
    }
}

void hash(int n)
{
    for (int i = 0; i < n; i++)
    {
        printf("#");
    }
}


int draw_pym(int n)
{
    for (int i = 1; i < n + 1; i++)
    {
        blank(n - i);
        hash(i);
        blank(2);
        hash(i);
        printf("\n");
    }
    return 0;
}

