#ifndef MATH_HPP
#define MATH_HPP

#include "exprtk.hpp"

#include <cmath>
#include <vector>
#include <algorithm>
#include <cstdint>
#include <climits>
#include <limits>
#include <string>

using namespace std;

uint32_t state = 730182364;

// Interpolation
float lerp(float& a, float& b, float& t) { return a + (b - a) * t; }
float smoothstep(float& edge0, float& edge1, float& x) { float t = clamp((x - edge0) / (edge1 - edge0), .0f, 1.f); return t * t * (3 - 2 * t); }
float smootherstep(float& edge0, float& edge1, float& x) { float t = clamp((x - edge0) / (edge1 - edge0), .0f, 1.f); return t * t * t * (t * (t * 6 - 15) + 10); }
float easeInSine(float& t) { return 1 - cos((t * M_PI) / 2); }
float easeOutSine(float& t) { return sin((t * M_PI) / 2); }
float easeInOutSine(float& t) { return -(cos(M_PI * t) - 1) / 2; }
float easeInExpo(float& t) { return (t == 0) ? 0 : pow(2, 10 * (t - 1)); }
float easeOutExpo(float& t) { return (t == 1) ? 1 : 1 - pow(2, -10 * t); }
float easeInOutExpo(float& t) {
    if (t == 0) return 0;
    if (t == 1) return 1;
    if (t < .5f) return pow(2, 20 * t - 10) / 2;
    return (2 - pow(2, -20 * t + 10)) / 2;
}
float easeInCirc(float& t) { return 1 - sqrt(1 - t * t); }
float easeOutCirc(float& t) { return sqrt(1 - (t - 1) * (t - 1)); }
float easeInOutCirc(float& t) { if (t < .5f) return (1 - sqrt(1 - 4 * t * t)) / 2; return (sqrt(1 - pow(-2 * t + 2, 2)) + 1) / 2; }
float easeOutBounce(float& t) {
    if (t < 4 / 11.f) { return (121 * t * t) / 16.f; } 
    else if (t < 8 / 11.f) { return (363 / 40.f * t * t) - (99 / 10.f * t) + 17 / 5.f; }
    else if (t < 9 / 10.f) { return (4356 / 361.f * t * t) - (35442 / 1805.f * t) + 16061 / 1805.f; }
    return (54 / 5.f * t * t) - (513 / 25.f * t) + 268 / 25.f;
}

// Averages
short averageShort(vector<short>& shorts) {
    int average;
    for (const short a : shorts) { average += a; }
    return { average / shorts.size() };
}

int averageInt(vector<int>& ints) {
    long long average;
    for (const int a : ints) { average += a; }
    return { average / ints.size() };
}

long long averageLong(vector<long long>& longs) {
    long long average;
    for (const long long a : longs) { average += a; }
    return { average / longs.size() };
}

float averageFloat(vector<float>& floats) {
    float average;
    for (const float a : floats) { average += a; }
    return { average / floats.size() };
}

bool averageBool(vector<bool>& bools) {
    int averageFalse;
    int averageTrue;

    for (const int a : bools) { if (bools[a]) { averageTrue++; } else { averageFalse++; } }
    if (averageTrue > averageFalse) { return true; }
    if (averageFalse > averageTrue) { return false; }
    return { randomBool(); }
}

short averageMinMaxShort(const vector<short>& shorts) {
    short minVal = 0;
    short maxVal = 0;
    int sum;

    for (const short a : shorts) {
        if (a < minVal) { minVal = a; }
        else if (a > maxVal) { maxVal = a; }
    }
    for (const short a : shorts) { if (a != minVal && a != maxVal) { sum += a; } }
    return sum / shorts.size();
}

int averageMinMaxInt(const vector<int>& ints) {
    int minVal = 0;
    int maxVal = 0;
    long long sum;

    for (const int a : ints) {
        if (a < minVal) { minVal = a; }
        else if (a > maxVal) { maxVal = a; }
    }
    for (const int a : ints) { if (a != minVal && a != maxVal) { sum += a; } }
    return sum / ints.size();
}

long long averageMinMaxLong(const vector<long long>& longs) {
    long long minVal = 0;
    long long maxVal = 0;
    long long sum;

    for (const long long a : longs) {
        if (a < minVal) { minVal = a; }
        else if (a > maxVal) { maxVal = a; }
    }
    for (const long long a : longs) { if (a != minVal && a != maxVal) { sum += a; } }
    return sum / longs.size();
}

float averageMinMaxFloat(const vector<float>& floats) {
    float minVal = 0;
    float maxVal = 0;
    float sum;

    for (const long long a : floats) {
        if (a < minVal) { minVal = a; }
        else if (a > maxVal) { maxVal = a; }
    }
    for (const float a : floats) { if (a != minVal && a != maxVal) { sum += a; } }
    return sum / floats.size();
}

// Random
uint32_t xorshift32() {
    state ^= state << 13;
    state ^= state >> 17;
    state ^= state << 5;
    return state;
}

short randomShort(short& min, short& max) { return min + (xorshift32() % (max - min + 1)); }
int randomInt(int& min, int& max) { return min + (xorshift32() % (max - min + 1)); }
long long randomLong(long long& min, long long& max) { return min + (((xorshift32() << 32) | xorshift32()) % (max - min + 1)); }
float randomFloat(float& min, float& max) { return min + (max - min) * (xorshift32() / 4,294,967,295.0f); }
bool randomBool() { return (xorshift32() & 1) == 0; }

// Solve
double solve(const std::string& expression) {
    typedef exprtk::symbol_table<double> symbol_table_t;
    typedef exprtk::expression<double> expression_t;
    typedef exprtk::parser<double> parser_t;

    symbol_table_t symbol_table;
    expression_t expr;
    expr.register_symbol_table(symbol_table);

    parser_t parser;
    if (!parser.compile(expression, expr)) { return 0.0; }
    return expr.value();
}

#endif