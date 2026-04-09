#ifndef __triangle__
#define __triangle__

#include "vector3.hpp"
#include <vector>

using namespace std;

struct Triangle{
    Vector3 p0, p1, p2;

    vector<float> (&shader)();
};

#endif