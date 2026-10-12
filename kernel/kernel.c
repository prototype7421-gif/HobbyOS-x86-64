#define SCREEN_WIDTH  80
#define SCREEN_HEIGHT 25
#define SCREEN_SIZE   (SCREEN_WIDTH * SCREEN_HEIGHT)

volatile unsigned short *ptr = (volatile unsigned short *)0xB8000;

unsigned int cursor = 0;

void scroll_screen(void)
{
    for (int i = 0; i < SCREEN_SIZE - SCREEN_WIDTH; i++){
        ptr[i] = ptr[i + SCREEN_WIDTH];
    }

    unsigned short blank =
        ((unsigned short)0x0F << 8) | ' ';

    for (int j = SCREEN_SIZE - SCREEN_WIDTH;
         j < SCREEN_SIZE; j++){
        ptr[j] = blank;
    }

    cursor = SCREEN_SIZE - SCREEN_WIDTH;
}

void clear_screen(void){
    unsigned short blank =
        ((unsigned short)0x0F << 8) | ' ';

    for (int i = 0; i < SCREEN_SIZE; i++)
    {
        ptr[i] = blank;
    }

    cursor = 0;
}

void put_char(char ch){
    if (ch == '\n')
    {
        cursor = ((cursor / SCREEN_WIDTH) + 1)
                 * SCREEN_WIDTH;

        if (cursor >= SCREEN_SIZE)
        {
            scroll_screen();
        }

        return;
    }

    if (cursor >= SCREEN_SIZE)
    {
        scroll_screen();
    }

    ptr[cursor] =
        ((unsigned short)0x0F << 8) |
        (unsigned char)ch;

    cursor++;
}
void print(const char *message)  // 1sr function implemented
{
    for (int i = 0; message[i] != '\0'; i++)
    {
        put_char(message[i]);
    }
}



void kernel_entry(void){
    clear_screen();
    print("Hello!! Lukita\n");
    print("Welcome to my OS\n");
    print("My kernel is working!");
}