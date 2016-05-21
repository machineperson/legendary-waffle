#ifndef MOB_H
#define MOB_H

/*
  A mobile object (mob) in the game

*/
class Mob {
private:
  int x;
  int y;
  char symbol;
public:
  Mob(int x_, int y_, char symbol_) : x(x_), y(y_), symbol(symbol_) {
  }

  void move(int dx, int dy) {
    x += dx;
    y += dy;
  }

  int getX() {
    return x;
  }

  int getY() {
    return y;
  }

  int getSymbol() {
    return symbol;
  }
};


#endif
