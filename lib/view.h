#ifndef VIEW_H
#define VIEW_H

#include <ncurses.h>
#include <iostream>
#include <ctime>
#include "territory.h"

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
    w = newwin(height, width, y_0, x_0);
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
     w = derwin(parent, height, width, y_0, x_0);

     touchwin(parent);
     wrefresh(w);
    }

    ~Frame() {
	     delwin(w);
     }

    char add(Mob &mob) {
      char prev = mvwinch(w, mob.getY(), mob.getX());
      mvwaddch(w, mob.getY(), mob.getX(), mob.getSymbol());
      std::cerr << "prev " << prev << '\n';
      return prev;
    }

    void erase(Mob &x) {
      mvwaddch(w, x.getY(), x.getX(), ' ');
    }

    char add(Mob &mob, int y, int x) {
        if((y >= 0 && y_0 + y < height)
        && (x >= 0 && x_0 + x < width)) {
          char prev = mvwinch(w, y, x);

          erase(mob);
          mvwaddch(w, y, x, mob.getSymbol());
          mob.pos(y, x);
          return prev;
        }
        return '0';
    }

    void add(char c, int y, int x) {
        if((y >= 0 && y_0 + y < height)
        && (x >= 0 && x_0 + x < width)) {
          std::cerr << "adding char "<< c << " at " << y << ", " << x << "\n";
          mvwaddch(w, y, x, c);
        }
        else {
          std::cerr << "out of bounds\n";
        }
    }

    void refresh() {
     if(parent) {
       touchwin(parent);
     }
     wrefresh(w);
   }

   void populateRandom() {
     Territory territory;

     std::clock_t start;
     int count = 0;
     for(int i = 0; i < height; i++) {
       for(int k = 0; k < width; k++) {
           double x = (double) k / ((double) width);
           double y = (double) i / ((double) width);
           start = std::clock();

           char cell = territory.random(5.0*x, 5.0*y);
           std::cerr << "Time: " << (std::clock() - start) / (double)(CLOCKS_PER_SEC / 1000) << " ms" << std::endl;
           add(cell, i, k);
           count++;
       }
     }
     std::cerr << "COUNT: " << count << std::endl;
   }

    void center(Mob &mob) {
      // TODO
      int new_x0 = x_0, new_y0 = y_0;
      int parent_height, parent_width;

      std::cerr << "Mob is at " << mob.getY() << ", " << mob.getX() << "\n";
      std::cerr << "viewport is at " << new_y0 << ", " << new_x0 << "\n";

      int center_dist_y = mob.getY() - height / 2;
      int center_dist_x = mob.getX() - width / 2;

      getmaxyx(parent, parent_height, parent_width);

      if(center_dist_x + width >= parent_width) {
        int delta = parent_width - (center_dist_x + width);
        new_x0 = center_dist_x + delta;
      }
      else {
        new_x0 = center_dist_x;
      }

      if(center_dist_y + height >= parent_height) {
        int delta = parent_height - (center_dist_y + height);
        new_y0 = center_dist_y + delta;
      }
      else {
        new_y0 = center_dist_y;
      }

      if (center_dist_y < 0) {
        new_y0 = 0;
      }

      if(center_dist_x < 0) {
        new_x0 = 0;
      }
      move(new_y0, new_x0);
      std::cerr << "Mob is at " << mob.getY() << ", " << mob.getX() << "\n";
      std::cerr << "viewport is at " << new_y0 << ", " << new_x0 << "\n";
      std::cerr << "parent has size " << parent_height << ", " << parent_width << "\n";
      char symbol = mvwinch(parent, mob.getY(), mob.getX());
      std::cerr << "Player symbol " << symbol;


      }

    void move(int y, int x) {
      if(parent) {
        mvderwin(w, y, x);
        x_0 = x;
        y_0 = y;
    //    box(w, 0, 0);
        refresh();
      }

    }


    int getHeight() {
      return height;
    }

    int getWidth() {
      return width;
    }
};


#endif
