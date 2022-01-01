#include <stdio.h>
#include <conio.h>

enum
{
  KEY_ESC     = 27,
  ARROW_UP    = 72,
  ARROW_DOWN  = 80,
  ARROW_LEFT  = 75,
  ARROW_RIGHT = 77,
  ARROW_LEFTUP  = 71,
  ARROW_LEFTDOWN  = 79,
  ARROW_RIGHTUP  = 73,
  ARROW_RIGHTDOWN  = 81
};

int get_code()
{
    int ch = getch();

    if (ch == 0 || ch == 224)
        return getch();

    return getch();
}
int main()
{
    int ch;

    while ((ch = get_code()) != KEY_ESC)
    {
        switch (ch)
        {
        case ARROW_UP:
            printf("UP\n");
            break;
        case ARROW_DOWN:
            printf("DOWN\n");
            break;
        case ARROW_LEFT:
            printf("LEFT\n");
            break;
        case ARROW_RIGHT:
            printf("RIGHT\n");
            break;
        case ARROW_LEFTUP:
            printf("LEFT UP\n");
            break;
        case ARROW_LEFTDOWN:
            printf("LEFT DOWN\n");
            break;
        case ARROW_RIGHTUP:
            printf("RIGHT UP\n");
            break;
        case ARROW_RIGHTDOWN:
            printf("RIGHT DOWN\n");
            break;
        default:
            printf("%d",ch);
            break;
        }
        
    }

    return 0;
}