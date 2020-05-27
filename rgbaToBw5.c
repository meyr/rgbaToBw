#include "bmp.h"

void before()
{
}

char *getOutputImageFile()
{
	return "./pictures/01_version5.bmp";
}

void after()
{

}

asm(
    "   .global    rgbaToBw             \n"
    "   .type    rgbaToBw, %function    \n"
    "rgbaToBw: \n"
    "   @ args = 0, pretend = 0, frame = 8 \n"
    "   @ frame_needed = 0, uses_anonymous_args = 0 \n"
    "   cmp    r2, #0 \n"
    "   bxle    lr \n"
    "   stmfd    sp!,{r4-r6,lr}            \n"

    "   pld    [r0, #0]                    \n"
    "   pld    [r0, #64]                   \n"
    "   mov    r3, #77                     \n"
    "   mov    r4, #151                    \n"
    "   mov    r5, #28                     \n"
    "   vdup.8    d0, r3                   \n"
    "   vdup.8    d1, r4                   \n"
    "   vdup.8    d2, r5                   \n"

    "   mul    r3, r1, r2                  \n"
    "   add    r4, r0, r3, lsl #2          \n"
    "   mov    r3, r0                      \n"

    ".V5_LOOP:                             \n"
    "   pld    [r0, #128]                  \n"
    "   pld    [r0, #192]                  \n"
    "   vld4.8    {d4-d7}, [r0]!           \n"
    "   vld4.8    {d8-d11}, [r0]!          \n"
    "   vld4.8    {d12-d15}, [r0]!         \n"
    "   vld4.8    {d16-d19}, [r0]!         \n"
    "   vmull.u8    q10, d4, d2            \n"
    "   vmull.u8    q11, d8, d2            \n"
    "   vmull.u8    q12, d12, d2           \n"
    "   vmull.u8    q13, d16, d2           \n"
    "   vmlal.u8    q10, d5, d1            \n"
    "   vmlal.u8    q11, d9, d1            \n"
    "   vmlal.u8    q12, d13, d1           \n"
    "   vmlal.u8    q13, d17, d1           \n"
    "   vmlal.u8    q10, d6, d0            \n"
    "   vmlal.u8    q11, d10, d0           \n"
    "   vmlal.u8    q12, d14, d0           \n"
    "   vmlal.u8    q13, d18, d0           \n"
    "   vshrn.u16   d4, q10, #8            \n"
    "   vshrn.u16   d8, q11, #8            \n"
    "   vshrn.u16   d12, q12, #8           \n"
    "   vshrn.u16   d16, q13, #8           \n"
    "   vmov    d5, d4                     \n"
    "   vmov    d6, d4                     \n"
    "   vst4.8    {d4-d7}, [r3]!           \n"
    "   vmov    d9, d8                     \n"
    "   vmov    d10, d8                    \n"
    "   vst4.8    {d8-d11}, [r3]!          \n"
    "   vmov    d13, d12                   \n"
    "   vmov    d14, d12                   \n"
    "   vst4.8    {d12-d15}, [r3]!         \n"
    "   vmov    d17, d16                   \n"
    "   vmov    d18, d16                   \n"
    "   vst4.8    {d16-d19}, [r3]!         \n"
    "   cmp        r0, r4                  \n"
    "   blt    .V5_LOOP                    \n"
    "   @ sp needed                        \n"
    "   ldmfd    sp!, {r4-r6,pc}           \n"
    "   .size    rgbaToBw, .-rgbaToBw \n"
);
