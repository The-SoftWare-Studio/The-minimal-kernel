// Writed on 2025/05/02
// By: Michael

void put_char(char c)
{
    asm volatile("outb %0, %1" : : "a"(c), "Nd"(0x3f8));
}

void puts(char *s)
{
    while (*s)
        put_char(*s++);
}

char get_char()
{
    char c;
    asm volatile("inb %1, %0" : "=a"(c) : "Nd"(0x3f8));
    return c;
}

void panic(const char *msg)
{
    puts(msg);
    while (1)
        ;
}

void gets(char *s)
{
    char c;
    while ((c = get_char()) != '\n')
        *s++ = c;
    *s = '\0';
}

void _start()
{
    puts("Hello, World!\n");
    panic("This is a test\n");
}