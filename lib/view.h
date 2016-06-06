#ifndef VIEW_H
#define VIEW_H

#include <ncurses.h>

class Screen {
  int height, width;

public:
  Screen() {

    initscr();
    getmaxyx(stdscr, height, width);
    clear();
    noecho();
    cbreak();
    keypad(stdscr, TRUE);
    curs_set(0);



  }
  ~Screen() {};

  void printMessage(const char *message) {
    printw(message);
    refresh();

  }

  int getHeight() {
    return height;
  }
  int getWidth() {
    return width;
  }

};

class Frame {
  int height, width;
  int y_0, x_0;

  bool isSubwindow;

  // the current ncurses window
  WINDOW *w;

  // NULL for a window, the parent for a subwindow
  WINDOW *parent;

public:
  // initialise a main window
  Frame(int n_rows, int n_cols, int row_0, int col_0) :
    height(n_rows),
    width(n_cols),
    y_0(row_0),
    x_0(col_0),
    isSubwindow(false)
  {

    parent = NULL;
    w = newwin(height, width, x_0, y_0);
    box(w, 0, 0);
    wrefresh(w);
  }

  Frame(Frame& pw, int n_rows, int n_cols, int row_0, int col_0) :
    parent(pw.w),
    height(n_rows),
    width(n_cols),
    y_0(row_0),
    x_0(col_0),
    isSubwindow(true)
    {
     w = newwin(height, width, x_0, y_0);
     box(w, 0, 0);
     wrefresh(w);
    }
};


#endif
