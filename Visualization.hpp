#pragma once
//                              157x54
#include <ncurses.h>
#include <string>
#include <mutex>
#include <unistd.h>
#include "DeanOffice.hpp"

#define ROWS 10
#define COLUMNS 4
#define ROWS_STEP 4
#define COLUMNS_STEP 23

#define WORKING_COLOR   COLOR_YELLOW
#define WAITING_COLOR   COLOR_RED
#define IDLE_COLOR      COLOR_GREEN

enum DeanOfficeCols
{
    percent = 0,
    used_stamps = 1,
    waiting = 2,
    idle = 3,
    working = 4,
    docs = 5,
    stud = 6
};

using namespace std;

class Visualization
{
public:
    int CloakroomX = 0,
        CloakroomY = 45;
    int DeanOfficeX = 0,
        DeanOfficeY = 0;
    int DeanOfficeRows = STAMPS_CNT,
        DeanOfficeColumns = 6+STAMPS_CNT,
        DeanOfficeColumnsWidth = 3;

    mutex *disp_mutex;
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

    void DrawDeanOffice();
    void DrawCloakroom();
    void PutChar(int x, int y, string smth, int color);
    void PutChar(int x, int y, string smth);

};
