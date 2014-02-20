#include "pngreader.h"

#include <lodepng.h>

//Loads a PNG image, must be sized as a power of two.
void *read_png(const char *filename, unsigned int *width, unsigned int *height)
{
	std::vector<unsigned char> *image = new std::vector<unsigned char>();
	unsigned error = lodepng::decode(*image, *width, *height, filename);

	// If there's an error, display it.
	if (error != 0)
	{
		fprintf(stderr, "Error decoding %s\n", filename);
		return NULL;
	}

	return &image[0];
}