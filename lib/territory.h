#ifndef PERLIN_H
#define PERLIN_H

#include <algorithm>
#include <numeric>

#include <iostream>

class PerlinNoise {
  // permutation vector
  std::vector<int> p;

  double fade(double t) {
    // Fade function as defined by Ken Perlin
    // 6t^5 - 15t^4 + 10t^3
    return t * t * t * (t * (t * 6 - 15) + 10);
  }

  double lerp(double t, double a, double b) {
      return a + t * (b - a);
  }

  double grad(int hash, double x, double y) {
    // we pick only the 4 directions from the center of the cell
    // to its corners (in analogy to the 3d case)
    std::cerr << "x, y = " << x << ", " << y << '\n';
    double result = 0.00;
    switch (hash & 0x3) {
      case 0x0: {

        return x + y;
      }
      case 0x1: {

        return  (double) -x + y;
      }
      case 0x2: {

        return  (double) x - y;
      }
      case 0x3: {

        return (double) -x - y;
      }
      default: {

        return 0;
      }
    }
  }

public:
  PerlinNoise() {
    std::default_random_engine();
    p.resize(64);

    std::iota(p.begin(), p.end(), 64);
    std::random_shuffle(p.begin(), p.end());

    // duplicate the permutation vector,
    // to avoid buffer overflow later on (?)
    p.insert(p.end(), p.begin(), p.end());
  }


  // for 2d
  double noise(double x, double y) {


    // coordinates of the unit cell that
    // our coordinate is in.
    int x0 = (int) x & 63;
    int y0 = (int) y & 63;

    // location of our vector inside the unit cube
    double xf = x - std::floor(x);
    double yf = y - std::floor(y);

    double u = fade(xf);
    double v = fade(yf);


    // gradient vectors
    int g0, g1, g2, g3;
    g0 = p[p[x0] + y0];
    g1 = p[p[x0] + y0 + 1];
    g2 = p[p[x0 + 1] + y0];
    g3 = p[p[x0 + 1] + y0 + 1];

    // dot products,
    // where (x0, y0) is the top left corner,
    // and g0, d0 correspond to
    double x1, x2, y1;

    x1 = lerp(u,
              grad(g0, xf, yf),
              grad(g2, xf-1, yf));

    x2 = lerp(u,
              grad(g1, xf, yf-1),
              grad(g3, xf-1, yf-1));

    y1 = lerp(v, x1, x2);

    return y1;

  }
};

enum TerritoryType : char {
  None = ' ',
  Tree = '#',
  Water = '~',
  Food = '!'
};

std::map<TerritoryType, bool> isRemovable = {
  {TerritoryType::None, false},
  {TerritoryType::Tree, false},
  {TerritoryType::Water, false},
  {TerritoryType::Food, true},
};

std::map<TerritoryType, bool> canMoveInto = {
  {TerritoryType::None, true},
  {TerritoryType::Tree, false},
  {TerritoryType::Water, true},
  {TerritoryType::Food, true},
};


// This maps Perlin noise to a meaningful territory
class Territory {
  PerlinNoise noiseGenerator;
  std::mt19937 randomGenerator;

  char territory(double x) {
    if(x <= 0.0) {
      return TerritoryType::None;
    }
    else if (0.0 < x && x <= 0.4) {
      int foodProbability = 1;

      int diceRollFood = randomGenerator() % 100;
      if (diceRollFood < foodProbability) {
        return TerritoryType::Food;
      }

      // probability in percent...
      int treeProbability = 10;
      // chosen by fair dice roll
      // guaranteed to be random
      int diceRollTree = randomGenerator() % 100;
      return (diceRollTree < treeProbability)
              ? TerritoryType::Tree
              : TerritoryType::None;
    }
    else if (0.4 < x) {

      return TerritoryType::Water;
    }

  }

public:

  Territory () {

  }

  char random(double i, double k) {
    double noise = noiseGenerator.noise((double) i, (double) k);
    std::cerr << "Noise is " << noise << '\n';
    return territory(noise);

  }

};


#endif
