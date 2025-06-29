#ifndef MATH_HPP
#define MATH_HPP

#include <cmath>
#include <vector>
#include <algorithm>

using namespace std;

// Interpolation
float lerp(float a, float b, float t) { return a + (b - a) * t; }
float smoothstep(float edge0, float edge1, float x) { float t = clamp((x - edge0) / (edge1 - edge0), .0f, 1.f); return t * t * (3 - 2 * t); }
float smootherstep(float edge0, float edge1, float x) { float t = clamp((x - edge0) / (edge1 - edge0), .0f, 1.f); return t * t * t * (t * (t * 6 - 15) + 10); }
float easeInSine(float t) { return 1 - cos((t * M_PI) / 2); }
float easeOutSine(float t) { return sin((t * M_PI) / 2); }
float easeInOutSine(float t) { return -(cos(M_PI * t) - 1) / 2; }
float easeInExpo(float t) { return (t == 0) ? 0 : pow(2, 10 * (t - 1)); }
float easeOutExpo(float t) { return (t == 1) ? 1 : 1 - pow(2, -10 * t); }
float easeInOutExpo(float t) {
    if (t == 0) return 0;
    if (t == 1) return 1;
    if (t < .5f) return pow(2, 20 * t - 10) / 2;
    return (2 - pow(2, -20 * t + 10)) / 2;
}
float easeInCirc(float t) { return 1 - sqrt(1 - t * t); }
float easeOutCirc(float t) { return sqrt(1 - (t - 1) * (t - 1)); }
float easeInOutCirc(float t) { if (t < .5f) return (1 - sqrt(1 - 4 * t * t)) / 2; return (sqrt(1 - pow(-2 * t + 2, 2)) + 1) / 2; }
float easeOutBounce(float t) {
    if (t < 4 / 11.f) { return (121 * t * t) / 16.f; } 
    else if (t < 8 / 11.f) { return (363 / 40.f * t * t) - (99 / 10.f * t) + 17 / 5.f; }
    else if (t < 9 / 10.f) { return (4356 / 361.f * t * t) - (35442 / 1805.f * t) + 16061 / 1805.f; }
    return (54 / 5.f * t * t) - (513 / 25.f * t) + 268 / 25.f;
}

#endif