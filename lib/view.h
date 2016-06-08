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
     w = derwin(parent, height, width, x_0, y_0);
     box(w, 0, 0);
     touchwin(parent);
     wrefresh(w);
    }

    ~Frame() {
	     delwin(w);
     }

    void add(Mob &x) {
      mvwaddch(w, x.getY(), x.getX(), x.getSymbol());
    }

    void erase(Mob &x) {
      mvwaddch(w, x.getY(), x.getX(), ' ');

    }

    void add(Mob &mob, int y, int x) {
        if((y >= 0 && y_0 + y < height)
        && (x >= 0 && x_0 + x < width)) {
          erase(mob);
          mvwaddch(w, y, x, mob.getSymbol());
          mob.pos(y, x);
        }
    }

    void refresh() {
     if(parent) {
       touchwin(parent);
     }
     wrefresh(w);
    }

    void fillWindow() {
      int max_x = width / 2;
      int max_y = height / 2;


    	for(int y = 0; y < max_y; ++y) {
    		for(int x = 0; x < max_x; ++x) {
    			mvwaddch(w, y, x, '0');
    		}
    	}

      for(int y = 0; y < max_y; ++y) {
        for(int x = max_x; x < width; ++x) {
          mvwaddch(w, y, x, '1');
        }
      }

      for(int y = max_y; y < height; ++y) {
        for(int x = 0; x < max_x; ++x) {
          mvwaddch(w, y, x, '2');
        }
      }
      for(int y = max_y; y < height; ++y) {
        for(int x = max_x; x < width; ++x) {
          mvwaddch(w, y, x, '3');
        }
      }
    }

    void center(Mob &mob) {
      // TODO
      int new_x0 = x_0, new_y0 = y_0;
      int parent_height, parent_width;

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

    }

    void move(int y, int x) {
      if(parent) {
        mvderwin(w, y, x);
        x_0 = x;
        y_0 = y;
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
