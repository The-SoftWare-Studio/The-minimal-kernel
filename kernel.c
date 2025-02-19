// Writed on 2025/05/02
// By: Michael

#define MAX_LENGTH 256 // максимальная длина буфера

char buffer[MAX_LENGTH]; // Инициализация массива с размером

void put_char(char c)
{
    asm volatile("outb %0, %1" : : "a"(c), "Nd"(0x3f8));
}

void puts(char *s)
{
    if (s == NULL) return;
    while (*s)
        put_char(*s++);
}

char get_char()
{
    char c;
    asm volatile("inb %1, %0" : "=a"(c) : "Nd"(0x3f8));
    return c;
}

void add_buffer(char c, int num)
{
    if (num >= 0 && num < MAX_LENGTH) {
        buffer[num] = c;
    }
}

void panic(const char *msg)
{
    puts(msg);
    for (volatile int i = 0; i < 1000000; i++) { // Задержка для тестирования
        // Пустой цикл
    }
    while (1)
        ;
}

void gets(char *s)
{
    char c;
    int i = 0;
    while ((c = get_char()) != '\n' && i < MAX_LENGTH - 1) {
        *s++ = c;
        i++;
    }
    *s = '\0';  // Завершающий нулевой символ
}

void _start()
{
    puts("Hello, World!\n");

    // Пример использования буфера и add_buffer
    add_buffer('H', 0);
    add_buffer('e', 1);
    add_buffer('l', 2);
    add_buffer('l', 3);
    add_buffer('o', 4);
    add_buffer('!', 5);

    // Печать буфера
    puts("Buffer content: ");
    for (int i = 0; i < 6; i++) {
        put_char(buffer[i]);
    }
    put_char('\n');

    panic("This is a test\n");
}
