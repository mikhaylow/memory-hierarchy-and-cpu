#include <stdio.h>

int get_char_to_int(void);
void print_num(long long n);
int get_cpu_model(char *cpu_model);
int my_print(char *s);
int ull_to_str(char *buff, unsigned long long n);
int cipher(char *cpu_model, char *sum_s, char *cipher);
long long sum_loop(char *memory, char *data, int n);
void example();

char memory[65536];
char data[256 * 1024];
char cpu_model[64];
char buff[32];
char cipher_buff[32];

int main(void)
{
    int num, status;
    long long sum;

    num = 0;
    status = 0;
    sum = 0;

    setbuf(stdin, NULL);

    num = get_char_to_int();

    sum = sum_loop(memory, data, num);
    if (sum < 0) return -1;

    my_print("sum: ");
    print_num(sum);
    putchar('\n');

    get_cpu_model(cpu_model);

    my_print("cpu_model: ");
    my_print(cpu_model);
    putchar('\n');

    ull_to_str(buff, sum);

    status = cipher(cpu_model, buff, cipher_buff);
    if (status != -1)
    {
        my_print("cipher: ");
        my_print(cipher_buff);
        putchar('\n');
    }

    // example(); // Example output

    return 0;
}

long long sum_loop(char *memory, char *data, int n)
{
    if (memory == NULL || data == NULL) return -1;

    if (n < 0 || n > 100000)
        return -1;

    long long sum = 0;

    for (int i = 1; i <= n; i++)
    {
        sum += i;
        memory[i % 65536] = i % 256;
        data[i % (256*1024)] = (sum + i) % 256;
    }
    
    return sum;
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

    while (ch != '\n' && ch != EOF) 
        ch = getchar();
    
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

int get_cpu_model(char *cpu_model)
{
    if (cpu_model == NULL) return -1;

    int ch, i;

    i = 0;
    while ((ch = getchar()) != EOF && ch != '\n' && i < 63)
    {
        cpu_model[i] = ch;
        i++;
    }
    cpu_model[i] = '\0';

    return 0;
}

int my_print(char *s)
{
    if (s == NULL)
        return -1;

    int count = 0;

    for (int i = 0; s[i] != '\0'; i++)
    {
        putchar(s[i]);
        count++;
    }

    return count;
}

int ull_to_str(char *buff, unsigned long long sum)
{
    if (buff == NULL) return -1;

    char tmp[32];

    int i;
    i = 0;
    do
    {
        tmp[i] = (sum % 10) + '0';
        sum = sum / 10;
        i++;
    } while (sum > 0);
    tmp[i] = '\0';

    int j = 0;
    for (int k = i -1; k >= 0; k--)
    {
        buff[j] = tmp[k];
        j++;
    }
    buff[j] = '\0';

    return 0;
}

int cipher(char *cpu_model, char *sum_s, char *buff)
{
    if (cpu_model == NULL || sum_s == NULL || buff == NULL) return -1;
    
    int i;
    i = 0;

    while (sum_s[i] != '\0' && cpu_model[i] != '\0')
    {
        buff[i] = (((sum_s[i] - '0') + cpu_model[i]) % 10) + '0';
        i++;
    }
    buff[i] = '\0';
    
    return 0;
}

/*
 * Example output
*/
void example()
{
    my_print("sum: ");
    print_num(7626);
    putchar('\n');

    my_print("cpu_model: ");
    my_print("Ryzen 5 5500");
    putchar('\n');

    my_print("cipher: ");
    my_print("9747");
    putchar('\n');
}