#ifndef UTILITY_HPP
#define UTILITY_HPP

#include "../Libraries/glm/glm.hpp"
#include <stdio.h>

void
SavePPM(const char * filename, glm::vec3 * buffer, const int width, const int height, bool gammaCorrectionOn)
{
    FILE * fp = fopen(filename, "wb");

    fprintf(fp, "P6\n%d %d\n255\n", width, height);
    for (int j = 0; j < height; j++)
    {
        for (int i = 0; i < width; i++)
        {

            if (gammaCorrectionOn)
            {
                buffer[j*width + i].r =	glm::pow(buffer[j*width + i].r, 1.f/2.2f);
                buffer[j*width + i].g =	glm::pow(buffer[j*width + i].g, 1.f/2.2f);
                buffer[j*width + i].b =	glm::pow(buffer[j*width + i].b, 1.f/2.2f);
			}

			static unsigned char color[3];
			color[0] = buffer[j*width + i].r * 255.9f;
			color[1] = buffer[j*width + i].g * 255.9f;
			color[2] = buffer[j*width + i].b * 255.9f;
			fwrite(color, 1, 3, fp);
        }
    }
    fclose(fp);
}


#endif
