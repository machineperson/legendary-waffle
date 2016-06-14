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
        std::cerr << "case 0, returning " << x + y << " \n";
        return x + y;
      }
      case 0x1: {
        std::cerr << "case 1, returning " << -x + y << " \n";
        return  (double) -x + y;
      }
      case 0x2: {
        std::cerr << "case 2, returning " << x - y << " \n";
        return  (double) x - y;
      }
      case 0x3: {
        std::cerr << "case 3, returning " << -x - y << " \n";
        return (double) -x - y;
      }
      default: {
        std::cerr << "noooooo!\n";
        return 0;
      }
    }
  }

public:
  PerlinNoise() {
    std::default_random_engine();
    p.resize(256);

    std::iota(p.begin(), p.end(), 256);
    std::random_shuffle(p.begin(), p.end());

    // duplicate the permutation vector,
    // to avoid buffer overflow later on (?)
    p.insert(p.end(), p.begin(), p.end());
  }


  // for 2d
  double noise(double x, double y) {


    // coordinates of the unit cell that
    // our coordinate is in.
    int x0 = (int) x & 255;
    int y0 = (int) y & 255;

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
    std::cerr << "g0 is " << grad(g0, xf, yf) << '\n';
    std::cerr << "g2 is " << grad(g2, xf-1, yf) << '\n';
    std::cerr << "x1 is " << x1 << '\n';
    std::cerr << "x is " << x << '\n';
    std::cerr << "y is " << y << '\n';
    std::cerr << "fabs(x) is " << std::fabs(x) << '\n';



    std::cerr << "xf is " << xf << '\n';
    std::cerr << "yf is " << yf << '\n';
    std::cerr << "v is " << v << '\n';

    return y1;

  }
};

// This maps Perlin noise to a meaningful territory
class Territory {
  PerlinNoise noiseGenerator;
  std::mt19937 randomGenerator;

  char territory(double x) {
    if(x <= 0.0) {
      return ' ';
    }
    else if (0.0 < x && x <= 0.4) {
      // probability in percent...
      int treeProbability = 10;
      int diceRoll = randomGenerator() % 100;
      return (diceRoll < treeProbability) ? 'X' : ' ';
    }
    else if (0.4 < x && x <= 1.0) {
      // water
      return '~';
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
