#ifndef UTILITY_HPP
#define UTILITY_HPP

#include "../Libraries/glm/glm.hpp"
#include <cstdio>
#include <string>

void
SavePPM(std::string &filename, glm::vec3 * buffer, const int width, const int height, bool gammaCorrectionOn);

#endif
