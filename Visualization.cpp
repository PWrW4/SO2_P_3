//                              157x54
#include "Visualization.hpp"

using namespace std;

    Visualization::Visualization(int _ROWS,  int _COLUMNS, int _ROWS_STEP, int _COLUMNS_STEP)
    : rows(_ROWS),
      columns(_COLUMNS),
      x_actual(0),
      y_actual(0),
      x_step(_COLUMNS_STEP),
      y_step(_ROWS_STEP)
    {
        disp_mutex = new mutex;
        initscr(); 
        curs_set(0);
        start_color();
        getmaxyx( stdscr, y_chars, x_chars );
        init_pair( COLOR_RED, COLOR_RED, COLOR_BLACK );
        init_pair( COLOR_GREEN, COLOR_GREEN, COLOR_BLACK );
        init_pair( COLOR_YELLOW, COLOR_YELLOW, COLOR_BLACK );
        init_pair( COLOR_BLUE, COLOR_BLUE, COLOR_BLACK );
        init_pair( COLOR_MAGENTA, COLOR_MAGENTA, COLOR_BLACK );
        init_pair( COLOR_CYAN, COLOR_CYAN, COLOR_BLACK );

        if(x_chars > x_step * columns)
            x_chars = x_step * columns;

        if(y_chars > y_step * rows + 1)
            y_chars = y_step * rows + 1;
        ec_width = x_step - 3;
        for(int i=0;i<ec_width;i++)
        {
            flusher+=" ";
            if(i<ec_width/2)
                flusher_half+=" ";
        }

        for(int i=0;i<x_chars;i++)          // Build Horizontal Lines
        {
         horizontal_line +="-"; 
         if(i%x_step==0)
            header+="|";
          else
            header+=" ";
        }
    }

    Visualization::~Visualization()
    {
//        getch();
        curs_set(1);
        endwin();
    }

    void Visualization::DrawTable()
    {
        x_actual = y_actual = 0;

        mvprintw(y_actual, x_actual, header.c_str());       // print real header
        PrintCenter(-1,0,"PaniZDziekanatu");
        PrintCenter(-1,1,"Czynnosc");
        PrintCenter(-1,2,"Pieczatki");
        PrintCenter(-1,3,"Postep");

        y_actual++;                                         // y_actual = 1

        mvprintw(y_actual, x_actual, horizontal_line.c_str());  // print horizontal line
        y_actual++;                                         // y_actual = 2

        for(int i=2;y_actual<y_chars ;i++, y_actual++)
        {
            if(y_actual%y_step==1)
                mvprintw(y_actual, x_actual, horizontal_line.c_str());
            else
                mvprintw(y_actual, x_actual, header.c_str());
        }
        refresh();
    } 

    void Visualization::PrintCenter(int philosopher, int column, string text)
    {
        int y = y_step * philosopher + 3;
        int x = x_step * column;

        if(philosopher>=0)
        {
            mvprintw(y, x + x_step/2 - text.length()/2, text.c_str());
        }
        else
        {
            mvprintw(0, x + x_step/2 - text.length()/2, text.c_str());
        }
        refresh();
    }
    void Visualization::Print(int philosopher, int column, string text)
    {
        int y = y_step * philosopher + 3;
        int x = x_step * column +2;
        mvprintw(y, x, text.c_str());
        refresh();
    }   
    void Visualization::Flush(int philosopher, int column)
    {
        int y = y_step * philosopher + 3;
        int x = x_step * column +2;
        mvprintw(y, x, flusher.c_str());
        refresh();
    }
    void Visualization::PrintFork(int philosopher, bool isLeft, int fork_nr) // true - left    false - right
    {
        int y = y_step * philosopher + 3;
        int x;
        if(isLeft)
        {
            x = (x_step * 2) + 2 + ec_width/4 - ("L("+ to_string(fork_nr)+")").length()/2;
            attron( COLOR_PAIR( COLOR_CYAN ) );
            mvprintw(y, x, ("L("+ to_string(fork_nr)+")").c_str());
            attroff( COLOR_PAIR( COLOR_CYAN ) );
        }
        else
        {
            x = (x_step * 2) + 2 + (3 * ec_width/4) - ("R("+ to_string(fork_nr)+")").length()/2;
            attron( COLOR_PAIR( COLOR_RED ) );
            mvprintw(y, x, ("R("+ to_string(fork_nr)+")").c_str());
            attroff( COLOR_PAIR( COLOR_RED ) );
        }
        refresh();
    }
    void Visualization::FlushFork(int philosopher, bool isLeft)
    {
        int y = y_step * philosopher + 3;
        int x;
        if(isLeft)
        {
            x = (x_step * 2) + 2 ;
        }
        else
        {
            x = (x_step * 2) + 2 + ec_width/2;
        }

        mvprintw(y, x, flusher_half.c_str());
        refresh();
    }

    void Visualization::Scroll(int step)
    {
        scrl(step);
        refresh();
    }

    void Visualization::DrawDeanOffice()
    {
        disp_mutex->lock();
        for(int j=0;j<DeanOfficeColumns*(DeanOfficeColumnsWidth+1)+1;j++)
        {
            mvprintw(DeanOfficeX,DeanOfficeY+j,"-");
        }
        for(int i=1;i<=DeanOfficeRows;i++)
        {
            for(int j=0 ; j<DeanOfficeColumns*(DeanOfficeColumnsWidth+1)+1 ; j+=(DeanOfficeColumnsWidth+1))
            {
                mvprintw(DeanOfficeX+i,DeanOfficeY+j,"|");
            }
        }
        for(int j=0;j<=(DeanOfficeColumns-1)*(DeanOfficeColumnsWidth+1);j++)
        {
            mvprintw(DeanOfficeX+DeanOfficeRows+1,DeanOfficeY+j,"-");
        }
        refresh();
        disp_mutex->unlock();
    }

    void Visualization::PutChar(int x, int y, string smth, int color)
    {
        disp_mutex->lock();
        attron( COLOR_PAIR( color ) );
        mvprintw(y,x,smth.c_str());
        attroff( COLOR_PAIR( color ) );
        refresh();
        disp_mutex->unlock();
    }

    void Visualization::PutChar(int x, int y, string smth)
    {
        disp_mutex->lock();
        mvprintw(y,x,smth.c_str());
        refresh();
        disp_mutex->unlock();
    }