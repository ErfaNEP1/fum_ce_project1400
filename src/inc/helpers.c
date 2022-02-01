/*
    The different color codes are
    0   BLACK
    1   BLUE
    2   GREEN
    3   CYAN
    4   RED
    5   MAGENTA
    6   BROWN
    7   LIGHTGRAY
    8   DARKGRAY
    9   LIGHTBLUE
    10  LIGHTGREEN
    11  LIGHTCYAN
    12  LIGHTRED
    13  LIGHTMAGENTA
    14  YELLOW
    15  WHITE
*/

/**
 * Changes the color of output in console.
 *
 * @param {unsigned-short-color} color number.
 * @return {void}.
 */

void textcolor(unsigned short color)
{
    HANDLE hcon = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hcon, color);
}

/**
 * Clears the screen.
 *
 * @return {void}.
 */
void clearScreen()
{
    for (int i = 0; i < 40; i++)
    {
        printf("\n");
    }
    // system("cls");
}
/**
 * Set cursor position
 * 
 * @param {int-x} x coordinate.
 * @param {int-y} y coordinate.
 * @return {void}.
 */
void goToXY(int x, int y)
{
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD cursorCoord;
    cursorCoord.X = x;
    cursorCoord.Y = y;
    SetConsoleCursorPosition(consoleHandle, cursorCoord);
}
/**
 * Set timeout for program.
 * 
 * @param {int-mseconds}  miliseconds to sleep.
 * @return {void}.
 */
void sleep(unsigned int mseconds)
{
    clock_t goal = mseconds + clock();
    while (goal > clock())
        ;
}
/**
 * trim the string.
 * 
 * @param {char*} char pointer to trim.
 * @return {char} trimmed char.
 */
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
/**
 * Generates random number.
 * 
 * @param {number} minimum.
 * @param {number} maximum.
 * @return {void}.
 */
int random(int min, int max)
{
    int randomnumber;
    srand(time(0));
    randomnumber=rand() % (max - min + 1) + min;
    return randomnumber;
}