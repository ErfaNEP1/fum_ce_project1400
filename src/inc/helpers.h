void textcolor(unsigned short color)
{
    HANDLE hcon = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hcon, color);
}

void clearScreen()
{
    for (int i = 0; i < 40; i++)
    {
        printf("\n");
    }
}

void goToXY(int x, int y)
{
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD cursorCoord;
    cursorCoord.X = x;
    cursorCoord.Y = y;
    SetConsoleCursorPosition(consoleHandle, cursorCoord);
}

void sleep(unsigned int mseconds)
{
    clock_t goal = mseconds + clock();
    while (goal > clock())
        ;
}

char *trim(char *s)
{
    char *ptr;
    if (!s)
        return NULL; // handle NULL string
    if (!*s)
        return s; // handle empty string
    for (ptr = s + strlen(s) - 1; (ptr >= s) && isspace(*ptr); --ptr)
        ;
    ptr[1] = '\0';
    return s;
}
