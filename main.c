#include <stdio.h>

int get_char_to_int(void);
void print_num(long long n);

char memory[65536];

int main(void)
{
    int number;
    long long sum;

    number = 0;
    sum = 0;

    number = get_char_to_int();

    if (number < 0 || number > 100000)
        return -1;

    print_num(number);
    putchar('\n');

    for (int i = 1; i <= number; i++)
    {
        sum += i;
        memory[i % 65536] = i % 256;
    }

    print_num(sum);
    putchar('\n');

    return 0;
}

int get_char_to_int(void)
{
    int ch, number, sign;

    ch = 0;
    number = 0;
    sign = 1;

    while ((ch = getchar()) != EOF && (ch < '0' || ch > '9') && ch != '-'){}

    if (ch == '-')
    {
        sign = -1;
        ch = getchar();
    }

    while (ch != EOF && ch >= '0' && ch <= '9')
    {
        number = number * 10 + (ch - '0');
        ch = getchar();
    }
    
    return number * sign;
}

void print_num(long long n)
{
    if (n < 0)
    {
        putchar('-');
        n = -n;
    }

    if (n >= 10)
        print_num(n / 10);

    putchar((n % 10) + '0');
}