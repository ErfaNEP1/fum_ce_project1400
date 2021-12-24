void textcolor(unsigned short color) {
    HANDLE hcon = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hcon,color);
}

void clearScreen(){
    system("cls");
}

void goToXY(int x, int y) {
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD cursorCoord;
    cursorCoord.X = x; cursorCoord.Y = y;
    SetConsoleCursorPosition(consoleHandle, cursorCoord);
}

void sleep(unsigned int mseconds){
    clock_t goal = mseconds + clock();
    while(goal>clock());
}