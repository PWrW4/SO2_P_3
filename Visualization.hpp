#pragma once
//                              157x54
#include <ncurses.h>
#include <string>
#include <unistd.h>

#define ROWS 10
#define COLUMNS 4
#define ROWS_STEP 4
#define COLUMNS_STEP 23

using namespace std;

class Visualization
{
public:

    string horizontal_line;
    string header;
    string flusher;
    string flusher_half;
    
    int rows, columns;
    int x_actual, y_actual;
    int x_chars, y_chars;
    int x_step, y_step;
    int ec_width;                            // Effective Column Width
    int philosopher_nr=0;

    Visualization(int _ROWS,  int _COLUMNS, int _ROWS_STEP, int _COLUMNS_STEP);
    ~Visualization();

    void DrawTable();
    void PrintCenter(int philosopher, int column, string text);
    void Print(int philosopher, int column, string text);
    void Flush(int philosopher, int column);
    void PrintFork(int philosopher, bool isLeft, int fork_nr); // true - left    false - right
    void FlushFork(int philosopher, bool isLeft);
    void Scroll(int step);

};
