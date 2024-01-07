#ifndef __KERNELS_H__
#define __KERNELS_H__

#include "openvx/vx.h"
#include "detail/momentsStruct.h"

#ifdef __cplusplus
extern "C" {
#endif

vx_status ref_threshold(const vx_image src_image, vx_image dst_image, const vx_threshold thresh);
void findMoments(const vx_image src_image, momentsStruct moments);
void findHuMoments(const momentsStruct moments, vx_array humoments);

#ifdef __cplusplus
}
#endif

#endif
