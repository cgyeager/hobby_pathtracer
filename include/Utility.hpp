#ifndef UTILITY_HPP
#define UTILITY_HPP

#include "../Libraries/glm/glm.hpp"
#include <stdio.h>

void
SavePPM(const char * filename, glm::vec3 * buffer, const int width, const int height, bool gammaCorrectionOn);

#endif
