#ifndef PERLIN_H
#define PERLIN_H

class PerlinNoise {
  std::vector<int> p;

  double fade(double t);
  double lerp(double t, double a, double b);
  double grad(int hash, double x, double z);

public:
  PerlinNoise() {}

  PerlinNoise(unsigned int seed) {}

  double noise(double x, double y, double z) {

  }

  // for 2d
  double noise(double x, double y) {
    return noise(x, y, 0.0);
  }
};


#endif
