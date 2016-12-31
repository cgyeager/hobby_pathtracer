#include "RandomNumbers.hpp"

#include <stdlib.h>

float
RandomFloat()
{
    return float(rand() % 10000)* 0.0001f;
}
