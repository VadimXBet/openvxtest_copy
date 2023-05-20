#include "detail/types.h"
#include "detail/momentsStruct.h"
#include <math.h>

void findMoments(const vx_image src_image, momentsStruct moments)
{
	const uint32_t src_width = src_image->width;
	const uint32_t src_height = src_image->height;
	const uint8_t* src_data = src_image->data;

    for (uint32_t x = 0; x < src_width; ++x)
    {
        for (uint32_t y = 0; y < src_height; ++y)
        {
            moments->m00 = moments->m00 + 1.0 * src_data[y * src_width + x];
            moments->m10 = moments->m10 + 1.0 * src_data[y * src_width + x] * x;
            moments->m01 = moments->m01 + 1.0 * src_data[y * src_width + x] * y;
            moments->m20 = moments->m20 + 1.0 * src_data[y * src_width + x] * x * x;
            moments->m11 = moments->m11 + 1.0 * src_data[y * src_width + x] * x * y;
            moments->m02 = moments->m02 + 1.0 * src_data[y * src_width + x] * y * y;
            moments->m30 = moments->m30 + 1.0 * src_data[y * src_width + x] * x * x * x;
            moments->m21 = moments->m21 + 1.0 * src_data[y * src_width + x] * x * x * y;
            moments->m12 = moments->m12 + 1.0 * src_data[y * src_width + x] * x * y * y;
            moments->m03 = moments->m03 + 1.0 * src_data[y * src_width + x] * y * y * y;
        }  
    }
    double xm = moments->m10 / moments->m00;
    double ym = moments->m01 / moments->m00;
    double M2 = moments->m00 * moments->m00;
    double M3 = moments->m00 * sqrt(moments->m00 * moments->m00 * moments->m00);

    moments->mu20 = moments->m20 - xm * moments->m10;
    moments->mu11 = moments->m11 - xm * moments->m01;
    moments->mu02 = moments->m02 - ym * moments->m01;
    moments->mu30 = moments->m30 - 3 * xm * moments->m20 + 2 * xm * xm * moments->m10;
    moments->mu21 = moments->m21 - 2 * xm * moments->m11 - ym * moments->m20 + 2 * xm * xm * moments->m01;
    moments->mu12 = moments->m12 - 2 * ym * moments->m11 - xm * moments->m02 + 2 * ym * ym * moments->m10;
    moments->mu03 = moments->m03 - 3 * ym * moments->m02 + 2 * ym * ym * moments->m01;

    moments->nu20 = moments->mu20 / M2;
    moments->nu11 = moments->mu11 / M2;
    moments->nu02 = moments->mu02 / M2;
    moments->nu30 = moments->mu30 / M3;
    moments->nu21 = moments->mu21 / M3;
    moments->nu12 = moments->mu12 / M3;
    moments->nu03 = moments->mu03 / M3;
}