// Copyright (c) 2025 Sylar129. All rights reserved

#pragma once

#include <chrono>
#include <numbers>
#include <random>
#include <vector>

#include "glm/glm.hpp"

namespace prototype {

class Shader;

struct PointLight {
  glm::vec3 position;

  glm::vec3 ambient;
  glm::vec3 diffuse;
  glm::vec3 specular;

  void DrawContextMenu();
};

class LightCube {
 public:
  LightCube();

  void Draw(Shader& shader);

 private:
  uint32_t vao_;
  uint32_t vbo_;
  uint32_t ebo_;
};

// -------------------- Perlin Noise (improved) --------------------
class Perlin {
 public:
  Perlin(uint32_t seed = 0) {
    // permutation table 0..255 shuffled
    p.resize(512);
    std::vector<int> perm(256);
    for (int i = 0; i < 256; ++i) perm[i] = i;
    std::mt19937 rng(
        seed ? seed
             : std::uint32_t(std::chrono::high_resolution_clock::now()
                                 .time_since_epoch()
                                 .count()));
    std::shuffle(perm.begin(), perm.end(), rng);
    for (int i = 0; i < 512; ++i) p[i] = perm[i & 255];
  }

  // 3D Perlin noise in [-1,1]
  double noise(double x, double y, double z) const {
    // Find unit cube that contains point
    int X = fastfloor(x) & 255;
    int Y = fastfloor(y) & 255;
    int Z = fastfloor(z) & 255;
    // Find relative x,y,z of point in cube
    x -= std::floor(x);
    y -= std::floor(y);
    z -= std::floor(z);
    // Compute fade curves for each of x,y,z
    double u = fade(x);
    double v = fade(y);
    double w = fade(z);
    // Hash coordinates of the cube corners
    int A = p[X] + Y, AA = p[A] + Z, AB = p[A + 1] + Z;
    int B = p[X + 1] + Y, BA = p[B] + Z, BB = p[B + 1] + Z;

    // Add blended results from 8 corners of cube
    double res = lerp(
        w,
        lerp(v, lerp(u, grad(p[AA], x, y, z), grad(p[BA], x - 1, y, z)),
             lerp(u, grad(p[AB], x, y - 1, z), grad(p[BB], x - 1, y - 1, z))),
        lerp(v,
             lerp(u, grad(p[AA + 1], x, y, z - 1),
                  grad(p[BA + 1], x - 1, y, z - 1)),
             lerp(u, grad(p[AB + 1], x, y - 1, z - 1),
                  grad(p[BB + 1], x - 1, y - 1, z - 1))));
    // Perlin returns in approx [-1,1]
    return res;
  }

  // fractal brownian motion: sum of octaves
  double fbm(double x, double y, double z, int octaves = 3,
             double lacunarity = 2.0, double gain = 0.5) const {
    double amp = 1.0;
    double freq = 1.0;
    double sum = 0.0;
    double maxAmp = 0.0;
    for (int i = 0; i < octaves; ++i) {
      sum += amp * noise(x * freq, y * freq, z * freq);
      maxAmp += amp;
      amp *= gain;
      freq *= lacunarity;
    }
    return (maxAmp > 0.0) ? (sum / maxAmp)
                          : 0.0;  // normalized to roughly [-1,1]
  }

 private:
  std::vector<int> p;

  static inline int fastfloor(double x) {
    return (x > 0) ? (int)x : (int)x - 1;
  }

  static inline double fade(double t) {
    // 6t^5 - 15t^4 + 10t^3
    return t * t * t * (t * (t * 6 - 15) + 10);
  }

  static inline double lerp(double t, double a, double b) {
    return a + t * (b - a);
  }

  static inline double grad(int hash, double x, double y, double z) {
    int h = hash & 15;
    double u = h < 8 ? x : y;
    double v = h < 4 ? y : (h == 12 || h == 14 ? x : z);
    return ((h & 1) ? -u : u) + ((h & 2) ? -v : v);
  }
};

class SmoothOrbitLight {
 public:
  SmoothOrbitLight(
      glm::vec3 center = {0.0, 0.0, 0.0}, double baseRadius = 5.0,
      double radiusJitter = 1.0,
      double angularSpeed = 0.5,  // global rotation speed (radians per second)
      double noiseSpeed = 0.6,    // how fast noise evolves over time
      int seed = 42)
      : center(center),
        baseRadius(baseRadius),
        radiusJitter(radiusJitter),
        angularSpeed(angularSpeed),
        noiseSpeed(noiseSpeed),
        perlin(seed) {}

  // Call each frame with accumulated time (seconds). Returns world position.
  glm::vec3 update(double dt) const {
    static double t = 0;
    t += dt;
    // Use fbm to compute smooth "random" theta/phi/radius variations
    // We feed different noise coordinates so the channels are decorrelated.
    double nt = t * noiseSpeed;

    // fbm returns approx in [-1,1]. remap to angles/radius.
    double nTheta =
        perlin.fbm(nt + 10.0, 0.1, 0.1, 4);  // change offsets to de-correlate
    double nPhi = perlin.fbm(0.2, nt + 20.0, 0.3, 4);
    double nRad = perlin.fbm(0.3, 0.4, nt + 30.0, 4);

    // Map to angles
    double theta = (nTheta * 0.5 + 0.5) * (2.0 * std::numbers::pi);  // [0,2pi]
    double phi = (nPhi * 0.5 + 0.5) * std::numbers::pi;              // [0,pi]

    // Radius
    double radius = baseRadius + nRad * radiusJitter;

    // Add a steady spinning around (so it "orbits" even if noise is low)
    theta += angularSpeed * t;

    // Convert spherical -> cartesian
    double sinphi = std::sin(phi);
    glm::vec3 offset;
    offset.x = radius * sinphi * std::cos(theta);
    offset.y = radius * std::cos(phi);
    offset.z = radius * sinphi * std::sin(theta);

    return center + offset;
  }

 private:
  glm::vec3 center;
  double baseRadius;
  double radiusJitter;
  double angularSpeed;
  double noiseSpeed;
  Perlin perlin;
};

}  // namespace prototype
