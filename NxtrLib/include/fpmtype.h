/*****************************************************************************
* Copyright 2010 Nexteer, Inc., All Rights Reserved.
* Nexteer Confidential
*
* Module File Name  : fixmath.h
* Module Description: This file contains fixed point math definitons
* Product           : Gen II Plus - EA3.0
* Author            : Lucas Wendling
*****************************************************************************/
/*---------------------------------------------------------------------------
* Version Control:
* Date Created:      Sun Nov 28 13:37:13 2010
* %version:          2 %
* %derived_by:       xz0btk %
* %date_modified:    Wed Feb 13 12:24:12 2013 %
*---------------------------------------------------------------------------*/

#ifndef FPMTYPE_H
#define FPMTYPE_H

#include "Platform_Types.h"  


/* Min-Max Range Of u16p0, u32p0 Data Types */

#define d_MIN_u16p0      0
#define d_MAX_u16p0      65535

#define d_MIN_u32p0      0
#define d_MAX_u32p0      4294967295

/*****************************************************************************
* The following fixed point type definitions are made up of 3 elements:
* 1) The typedef itself.
* 2) The Binary point position for this type.
* 3) The indicator of whether the type is signed or not.
* These are used within the Fix macro. The Fix macro appends BBP_ and
* SIGNED_ to the types given to it.
*****************************************************************************/

/**********************************/
/* Extended Types.                */
/**********************************/

/***********************************/
/* Unsigned 8 bit Extended Types.  */
/***********************************/

/******** Commented for not use in 16  bit processors **************/

//typedef UINT8 um10p18_T;        /*  .__________bbbbbbbb */
//#define BPP_um10p18_T 18
//#define SIGNED_um10p18_T FALSE

//typedef UINT8 um9p17_T;         /*  ._________bbbbbbbb */
//#define BPP_um9p17_T 17
//#define SIGNED_um9p17_T FALSE

//typedef UINT8 um8p16_T;        /*  .________bbbbbbbb */
//#define BPP_um8p16_T 16
//#define SIGNED_um8p16_T FALSE

//typedef UINT8 um7p15_T;        /*  ._______bbbbbbbb */
//#define BPP_um7p15_T 15
//#define SIGNED_um7p15_T FALSE

//typedef UINT8 um6p14_T;        /*  .______bbbbbbbb */
//#define BPP_um6p14_T 14
//#define SIGNED_um6p14_T FALSE

//typedef UINT8 um5p13_T;        /*  ._____bbbbbbbb */
//#define BPP_um5p13_T 13
//#define SIGNED_um5p13_T FALSE

//typedef UINT8 um4p12_T;        /*  .____bbbbbbbb */
//#define BPP_um4p12_T 12
//#define SIGNED_um4p12_T FALSE

//typedef UINT8 um3p11_T;        /*  .___bbbbbbbb */
//#define BPP_um3p11_T 11
//#define SIGNED_um3p11_T FALSE

//typedef UINT8 um2p10_T;         /*  .__bbbbbbbb */
//#define BPP_um2p10_T 10
//#define SIGNED_um2p10_T FALSE

//typedef UINT8 um1p9_T;         /*  ._bbbbbbbb */
//#define BPP_um1p9_T 9
//#define SIGNED_um1p9_T FALSE

//typedef UINT8 u9pm1_T;         /*  bbbbbbbb_. */
//#define BPP_u9pm1_T -1
//#define SIGNED_u9pm1_T FALSE

//typedef UINT8 u10pm2_T;        /*  bbbbbbbb__. */
//#define BPP_u10pm2_T -2
//#define SIGNED_u10pm2_T FALSE

//typedef UINT8 u11pm3_T;        /*  bbbbbbbb___. */
//#define BPP_u11pm3_T -3
//#define SIGNED_u11pm3_T FALSE

//typedef UINT8 u12pm4_T;        /*  bbbbbbbb____. */
//#define BPP_u12pm4_T -4
//#define SIGNED_u12pm4_T FALSE

//typedef UINT8 u13pm5_T;        /*  bbbbbbbb_____. */
//#define BPP_u13pm5_T -5
//#define SIGNED_u13pm5_T FALSE

//typedef UINT8 u14pm6_T;        /*  bbbbbbbb______. */
//#define BPP_u14pm6_T -6
//#define SIGNED_u14pm6_T FALSE

//typedef UINT8 u15pm7_T;        /*  bbbbbbbb_______. */
//#define BPP_u15pm7_T -7
//#define SIGNED_u15pm7_T FALSE

//typedef UINT8 u16pm8_T;        /*  bbbbbbbb________. */
//#define BPP_u16pm8_T -8
//#define SIGNED_u16pm8_T FALSE

//typedef UINT8 u17pm9_T;        /*  bbbbbbbb_________. */
//#define BPP_u17pm9_T -9
//#define SIGNED_u17pm9_T FALSE

/**************** End Of Comments *****************************/

/***********************************/
/* Unsigned 16 bit Extended Types. */
/***********************************/
typedef uint16 um1p17_T;         /* _bbbbbbbbbbbbbbbbb. */
#define BPP_um1p17_T 17
#define SIGNED_um1p17_T FALSE
#define FIXEDTOFLOAT_um1p17_T 0.00000762939453125f
#define FLOATTOFIXED_um1p17_T 131072.0f

typedef uint16 um2p18_T;
#define BPP_um2p18_T  18
#define SIGNED_um2p18_T FALSE
#define FIXEDTOFLOAT_um2p18_T 0.000003814697265625f
#define FLOATTOFIXED_um2p18_T 262144.0f

typedef uint16 um3p19_T;        /*  .___bbbbbbbbbbbbbbbb */
#define BPP_um3p19_T 19
#define SIGNED_um3p19_T FALSE
#define FIXEDTOFLOAT_um3p19_T 1.9073486328125E-06f
#define FLOATTOFIXED_um3p19_T 524288.0f

typedef uint16 um4p20_T;       /*   .____bbbbbbbbbbbbbbbb */
#define BPP_um4p20_T 20
#define SIGNED_um4p20_T FALSE
#define FIXEDTOFLOAT_um4p20_T 9.5367431640625E-07f
#define FLOATTOFIXED_um4p20_T 1048576.0f

typedef uint16 um5p21_T;       /*   ._____bbbbbbbbbbbbbbbb */
#define BPP_um5p21_T 21
#define SIGNED_um5p21_T FALSE
#define FIXEDTOFLOAT_um5p21_T 4.76837158203125E-07f
#define FLOATTOFIXED_um5p21_T 2097152.0f

typedef uint16 um6p22_T;       /*   .______bbbbbbbbbbbbbbbb */
#define BPP_um6p22_T 22
#define SIGNED_um6p22_T FALSE
#define FIXEDTOFLOAT_um6p22_T 2.38418579101562E-07f
#define FLOATTOFIXED_um6p22_T 4194304.0f

typedef uint16 um7p23_T;       /*   ._______bbbbbbbbbbbbbbbb */
#define BPP_um7p23_T 23
#define SIGNED_um7p23_T FALSE
#define FIXEDTOFLOAT_um7p23_T 1.19209289550781E-07f
#define FLOATTOFIXED_um7p23_T 8388608.0f

typedef uint16 um8p24_T;       /*   .________bbbbbbbbbbbbbbbb */
#define BPP_um8p24_T 24
#define SIGNED_um8p24_T FALSE
#define FIXEDTOFLOAT_um8p24_T 5.96046447753906E-08f
#define FLOATTOFIXED_um8p24_T 16777216.0f

typedef uint16 um9p25_T;        /* ._________bbbbbbbbbbbbbbbb */
#define BPP_um9p25_T 25
#define SIGNED_um9p25_T FALSE
#define FIXEDTOFLOAT_um9p25_T 2.98023223876953E-08f
#define FLOATTOFIXED_um9p25_T 33554432.0f

typedef uint16 um10p26_T;        /* .__________bbbbbbbbbbbbbbbb */
#define BPP_um10p26_T 26
#define SIGNED_um10p26_T FALSE
#define FIXEDTOFLOAT_um10p26_T 1.49011611938477E-08f
#define FLOATTOFIXED_um10p26_T 67108864.0f

typedef uint16 um11p27_T;
#define BPP_um11p27_T  27
#define SIGNED_um11p27_T FALSE
#define FIXEDTOFLOAT_um11p27_T 7.45058059692383E-09f
#define FLOATTOFIXED_um11p27_T 134217728.0f

typedef uint16 u17pm1_T;         /* bbbbbbbbbbbbbbbb_. */
#define BPP_u17pm1_T -1
#define SIGNED_u17pm1_T FALSE
#define FIXEDTOFLOAT_u17pm1_T 2.0f
#define FLOATTOFIXED_u17pm1_T 0.5f

typedef uint16 u18pm2_T;         /* bbbbbbbbbbbbbbbb__. */
#define BPP_u18pm2_T -2
#define SIGNED_u18pm2_T FALSE
#define FIXEDTOFLOAT_u18pm2_T 4.0f
#define FLOATTOFIXED_u18pm2_T 0.25f

typedef uint16 u19pm3_T;         /* bbbbbbbbbbbbbbbb___. */
#define BPP_u19pm3_T -3
#define SIGNED_u19pm3_T FALSE
#define FIXEDTOFLOAT_u19pm3_T 8.0f
#define FLOATTOFIXED_u19pm3_T 0.125f

typedef uint16 u20pm4_T;         /* bbbbbbbbbbbbbbbb____. */
#define BPP_u20pm4_T -4
#define SIGNED_u20pm4_T FALSE
#define FIXEDTOFLOAT_u20pm4_T 16.0f
#define FLOATTOFIXED_u20pm4_T 0.0625f

typedef uint16 u21pm5_T;         /* bbbbbbbbbbbbbbbb_____. */
#define BPP_u21pm5_T -5
#define SIGNED_u21pm5_T FALSE
#define FIXEDTOFLOAT_u21pm5_T 32.0f
#define FLOATTOFIXED_u21pm5_T 0.03125f

typedef uint16 u22pm6_T;         /* bbbbbbbbbbbbbbbb______. */
#define BPP_u22pm6_T -6
#define SIGNED_u22pm6_T FALSE
#define FIXEDTOFLOAT_u22pm6_T 64.0f
#define FLOATTOFIXED_u22pm6_T 0.015625f


/***********************************/
/* Unsigned 32 bit Extended Types. */
/***********************************/

typedef uint32 u34pm2_T;     /* bbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbb__. */
#define BPP_u34pm2_T -2
#define SIGNED_u34pm2_T FALSE
#define FIXEDTOFLOAT_u34pm2_T 4.0f
#define FLOATTOFIXED_u34pm2_T 0.25f

typedef uint32 u33pm1_T;     /* bbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbb_. */
#define BPP_u33pm1_T -1
#define SIGNED_u33pm1_T FALSE
#define FIXEDTOFLOAT_u33pm1_T 2.0f
#define FLOATTOFIXED_u33pm1_T 0.5f

typedef uint32 um1p33_T;     /* _bbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbb. */
#define BPP_um1p33_T 33
#define SIGNED_um1p33_T FALSE
#define FIXEDTOFLOAT_um1p33_T 1.16415321826935E-10f
#define FLOATTOFIXED_um1p33_T 8589934592.0f

typedef uint32 um3p35_T;     /* ___bbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbb. */
#define BPP_um3p35_T 35
#define SIGNED_um3p35_T FALSE
#define FIXEDTOFLOAT_um3p35_T 2.91038304567337E-11f
#define FLOATTOFIXED_um3p35_T 34359738368.0f


/***********************************/
/* Signed 8 bit Extended Types.    */
/***********************************/
/******** Commented for not use in 16  bit processors ********/

//typedef SINT8    sm1p8_T;        /*  s._bbbbbbb */
//#define BPP_sm1p8_T 8
//define SIGNED_sm1p8_T TRUE

//typedef SINT8    sm2p9_T;        /*  s.__bbbbbbb */
//#define BPP_sm2p9_T 9
//#define SIGNED_sm2p9_T TRUE

//typedef SINT8    sm3p10_T;       /*  s.___bbbbbbb */
//#define BPP_sm3p10_T 10
//#define SIGNED_sm3p10_T TRUE

//typedef SINT8    sm4p11_T;       /*  s.____bbbbbbb */
//#define BPP_sm4p11_T 11
//#define SIGNED_sm4p11_T TRUE

//typedef SINT8    sm5p12_T;       /*  s._____bbbbbbb */
//#define BPP_sm5p12_T 12
//#define SIGNED_sm5p12_T TRUE

//typedef SINT8    sm6p13_T;       /*  s.______bbbbbbb */
//#define BPP_sm6p13_T 13
//#define SIGNED_sm6p13_T TRUE

//typedef SINT8    sm7p14_T;       /*  s._______bbbbbbb */
//#define BPP_sm7p14_T 14
//#define SIGNED_sm7p14_T TRUE

//typedef SINT8    s8pm1_T;        /*  sbbbbbbb_. */
//#define BPP_s8pm1_T -1
//define SIGNED_s8pm1_T TRUE

//typedef SINT8 s9pm2_T;           /*  sbbbbbbb__. */
//#define BPP_s9pm2_T -2
//#define SIGNED_s9pm2_T TRUE

/******** End Of Comments ********/


/***********************************/
/* Signed 16 bit Extended Types.   */
/***********************************/


typedef sint16   sm1p16_T;       /* s._bbbbbbbbbbbbbbb */
#define BPP_sm1p16_T 16
#define SIGNED_sm1p16_T TRUE
#define FIXEDTOFLOAT_sm1p16_T 0.0000152587890625f
#define FLOATTOFIXED_sm1p16_T 65536.0f

typedef sint16   sm2p17_T;       /* s.__bbbbbbbbbbbbbbb */
#define BPP_sm2p17_T 17
#define SIGNED_sm2p17_T TRUE
#define FIXEDTOFLOAT_sm2p17_T 0.00000762939453125f
#define FLOATTOFIXED_sm2p17_T 131072.0f

typedef sint16    sm3p18_T;      /* s.___bbbbbbbbbbbbbbb */
#define BPP_sm3p18_T 18
#define SIGNED_sm3p18_T TRUE
#define FIXEDTOFLOAT_sm3p18_T 0.000003814697265625f
#define FLOATTOFIXED_sm3p18_T 262144.0f

typedef sint16   sm4p19_T;       /* s.____bbbbbbbbbbbbbbb */
#define BPP_sm4p19_T 19
#define SIGNED_sm4p19_T TRUE
#define FIXEDTOFLOAT_sm4p19_T 1.9073486328125E-06f
#define FLOATTOFIXED_sm4p19_T 524288.0f

typedef sint16   sm5p20_T;       /* s._____bbbbbbbbbbbbbbb */
#define BPP_sm5p20_T 20
#define SIGNED_sm5p20_T TRUE
#define FIXEDTOFLOAT_sm5p20_T 9.5367431640625E-07f
#define FLOATTOFIXED_sm5p20_T 1048576.0f

typedef sint16   sm6p21_T;       /* s.______bbbbbbbbbbbbbbb */
#define BPP_sm6p21_T 21
#define SIGNED_sm6p21_T TRUE
#define FIXEDTOFLOAT_sm6p21_T 4.76837158203125E-07f
#define FLOATTOFIXED_sm6p21_T 2097152.0f

typedef sint16   sm7p22_T;       /* s._______bbbbbbbbbbbbbbb */
#define BPP_sm7p22_T 22
#define SIGNED_sm7p22_T TRUE
#define FIXEDTOFLOAT_sm7p22_T 2.38418579101562E-07f
#define FLOATTOFIXED_sm7p22_T 4194304.0f

typedef sint16   sm8p23_T;       /* s.________bbbbbbbbbbbbbbb */
#define BPP_sm8p23_T 23
#define SIGNED_sm8p23_T TRUE
#define FIXEDTOFLOAT_sm8p23_T 1.19209289550781E-07f
#define FLOATTOFIXED_sm8p23_T 8388608.0f

typedef sint16   sm9p24_T;       /* s._________bbbbbbbbbbbbbbb */
#define BPP_sm9p24_T 24
#define SIGNED_sm9p24_T TRUE
#define FIXEDTOFLOAT_sm9p24_T 5.96046447753906E-08f
#define FLOATTOFIXED_sm9p24_T 16777216.0f

typedef sint16   sm10p25_T;      /* s.__________bbbbbbbbbbbbbbb */
#define BPP_sm10p25_T 25
#define SIGNED_sm10p25_T TRUE
#define FIXEDTOFLOAT_sm10p25_T 2.98023223876953E-08f
#define FLOATTOFIXED_sm10p25_T 33554432.0f

typedef sint16   sm11p26_T;      /* s.___________bbbbbbbbbbbbbbb */
#define BPP_sm11p26_T 26
#define SIGNED_sm11p26_T TRUE
#define FIXEDTOFLOAT_sm11p26_T 1.49011611938477E-08f
#define FLOATTOFIXED_sm11p26_T 67108864.0f

typedef sint16   sm12p27_T;      /* s.____________bbbbbbbbbbbbbbb */
#define BPP_sm12p27_T 27
#define SIGNED_sm12p27_T TRUE
#define FIXEDTOFLOAT_sm12p27_T 7.45058059692383E-09f
#define FLOATTOFIXED_sm12p27_T 134217728.0f

typedef sint16   sm13p28_T;      /* s._____________bbbbbbbbbbbbbbb */
#define BPP_sm13p28_T 28
#define SIGNED_sm13p28_T TRUE
#define FIXEDTOFLOAT_sm13p28_T 3.72529029846191E-09f
#define FLOATTOFIXED_sm13p28_T 268435456.0f

typedef sint16   s16pm1_T;       /* sbbbbbbbbbbbbbbbbb_. */
#define BPP_s16pm1_T -1
#define SIGNED_s16pm1_T TRUE
#define FIXEDTOFLOAT_s16pm1_T 2.0f
#define FLOATTOFIXED_s16pm1_T 0.5f

typedef sint16   s17pm2_T;       /* sbbbbbbbbbbbbbbbbb__. */
#define BPP_s17pm2_T -2
#define SIGNED_s17pm2_T TRUE
#define FIXEDTOFLOAT_s17pm2_T 4.0f
#define FLOATTOFIXED_s17pm2_T 0.25f

typedef sint16   s18pm3_T;       /* sbbbbbbbbbbbbbbbbb___. */
#define BPP_s18pm3_T -3
#define SIGNED_s18pm3_T TRUE
#define FIXEDTOFLOAT_s18pm3_T 8.0f
#define FLOATTOFIXED_s18pm3_T 0.125f

typedef sint16   s19pm4_T;       /* sbbbbbbbbbbbbbbb____. */
#define BPP_s19pm4_T -4
#define SIGNED_s19pm4_T TRUE
#define FIXEDTOFLOAT_s19pm4_T 16.0f
#define FLOATTOFIXED_s19pm4_T 0.0625f

typedef sint16   s20pm5_T;       /* sbbbbbbbbbbbbbbb_____. */
#define BPP_s20pm5_T -5
#define SIGNED_s20pm5_T TRUE
#define FIXEDTOFLOAT_s20pm5_T 32.0f
#define FLOATTOFIXED_s20pm5_T 0.03125f

typedef sint16   s21pm6_T;       /* sbbbbbbbbbbbbbbb______. */
#define BPP_s21pm6_T -6
#define SIGNED_s21pm6_T TRUE
#define FIXEDTOFLOAT_s21pm6_T 64.0f
#define FLOATTOFIXED_s21pm6_T 0.015625f

typedef sint16   s22pm7_T;       /* sbbbbbbbbbbbbbbb_______. */
#define BPP_s22pm7_T -7
#define SIGNED_s22pm7_T TRUE
#define FIXEDTOFLOAT_s22pm7_T 128.0f
#define FLOATTOFIXED_s22pm7_T 0.0078125f

typedef sint16   s23pm8_T;       /* sbbbbbbbbbbbbbbb________. */
#define BPP_s23pm8_T -8
#define SIGNED_s23pm8_T TRUE
#define FIXEDTOFLOAT_s23pm8_T 256.0f
#define FLOATTOFIXED_s23pm8_T 0.00390625f

typedef sint16   s24pm9_T;       /* sbbbbbbbbbbbbbbb_________. */
#define BPP_s24pm9_T -9
#define SIGNED_s24pm9_T TRUE
#define FIXEDTOFLOAT_s24pm9_T 512.0f
#define FLOATTOFIXED_s24pm9_T 0.001953125f

typedef sint16 s25pm10_T;        /* sbbbbbbbbbbbbbbb__________. */
#define BPP_s25pm10_T -10
#define SIGNED_s25pm10_T TRUE
#define FIXEDTOFLOAT_s25pm10_T 1024.0f
#define FLOATTOFIXED_s25pm10_T 0.0009765625f

/***********************************/
/* Signed 32 bit Extended Types.   */
/***********************************/


typedef sint32   sm1p32_T;  /* s._bbbbbbbbbbbbbbbbbbbbbbbbbbbbbbb */
#define BPP_sm1p32_T 32
#define SIGNED_sm1p32_T TRUE
#define FIXEDTOFLOAT_sm1p32_T 2.3283064365387E-10f
#define FLOATTOFIXED_sm1p32_T 4294967296.0f

typedef sint32   sm2p33_T;  /* s.__bbbbbbbbbbbbbbbbbbbbbbbbbbbbbbb */
#define BPP_sm2p33_T 33
#define SIGNED_sm2p33_T TRUE
#define FIXEDTOFLOAT_sm2p33_T 1.16415321826935E-10f
#define FLOATTOFIXED_sm2p33_T 8589934592.0f

typedef sint32   sm3p34_T;  /* s.___bbbbbbbbbbbbbbbbbbbbbbbbbbbbbbb */
#define BPP_sm3p34_T 34
#define SIGNED_sm3p34_T TRUE
#define FIXEDTOFLOAT_sm3p34_T 5.82076609134674E-11f
#define FLOATTOFIXED_sm3p34_T 17179869184.0f

typedef sint32   sm4p35_T;  /* s.____bbbbbbbbbbbbbbbbbbbbbbbbbbbbbbb */
#define BPP_sm4p35_T 35
#define SIGNED_sm4p35_T TRUE
#define FIXEDTOFLOAT_sm4p35_T 2.91038304567337E-11f
#define FLOATTOFIXED_sm4p35_T 34359738368.0f

typedef sint32   sm11p42_T;  /* s.____bbbbbbbbbbbbbbbbbbbbbbbbbbbbbbb */
#define BPP_sm11p42_T 42
#define SIGNED_sm11p42_T TRUE
#define FIXEDTOFLOAT_sm11p42_T 2.27373675443232059478759765625E-13f
#define FLOATTOFIXED_sm11p42_T 4398046511104.0f

typedef sint32 s32pm1_T;    /* sbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbb_. */
#define BPP_s32pm1_T -1
#define SIGNED_s32pm1_T TRUE
#define FIXEDTOFLOAT_s32pm1_T 2.0f
#define FLOATTOFIXED_s32pm1_T 0.5f

typedef sint32 s38pm7_T;    /* sbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbb_. */
#define BPP_s38pm7_T -7
#define SIGNED_s38pm7_T TRUE
#define FIXEDTOFLOAT_s38pm7_T 128.0f
#define FLOATTOFIXED_s38pm7_T 0.0078125f

/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
 * All of the following generic types are generated automatically.
 * Please do not place any custom or extended types below this
 * comment.
 *%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/

/**********************************/
/* Unsigned 8 bit Generic Types.  */
/**********************************/

/******** Commented for not use in 16  bit processors ********

typedef UINT8 u8p0_T;
#define BPP_u8p0_T 0
#define SIGNED_u8p0_T FALSE

typedef UINT8 u7p1_T;
#define BPP_u7p1_T 1
#define SIGNED_u7p1_T FALSE

typedef UINT8 u6p2_T;
#define BPP_u6p2_T 2
#define SIGNED_u6p2_T FALSE

typedef UINT8 u5p3_T;
#define BPP_u5p3_T 3
#define SIGNED_u5p3_T FALSE

typedef UINT8 u4p4_T;
#define BPP_u4p4_T 4
#define SIGNED_u4p4_T FALSE

typedef UINT8 u3p5_T;
#define BPP_u3p5_T 5
#define SIGNED_u3p5_T FALSE

typedef UINT8 u2p6_T;
#define BPP_u2p6_T 6
#define SIGNED_u2p6_T FALSE

typedef UINT8 u1p7_T;
#define BPP_u1p7_T 7
#define SIGNED_u1p7_T FALSE

typedef UINT8 u0p8_T;
#define BPP_u0p8_T 8
#define SIGNED_u0p8_T FALSE

******** End of Comment ********/

/**********************************/
/* Signed 8 bit Generic Types.    */
/**********************************/

/******** Commented for not use in 16  bit processors ********
typedef SINT8 s7p0_T;
#define BPP_s7p0_T 0
#define SIGNED_s7p0_T TRUE

typedef SINT8 s6p1_T;
#define BPP_s6p1_T 1
#define SIGNED_s6p1_T TRUE

typedef SINT8 s5p2_T;
#define BPP_s5p2_T 2
#define SIGNED_s5p2_T TRUE

typedef SINT8 s4p3_T;
#define BPP_s4p3_T 3
#define SIGNED_s4p3_T TRUE

typedef SINT8 s3p4_T;
#define BPP_s3p4_T 4
#define SIGNED_s3p4_T TRUE

typedef SINT8 s2p5_T;
#define BPP_s2p5_T 5
#define SIGNED_s2p5_T TRUE

typedef SINT8 s1p6_T;
#define BPP_s1p6_T 6
#define SIGNED_s1p6_T TRUE

typedef SINT8 s0p7_T;
#define BPP_s0p7_T 7
#define SIGNED_s0p7_T TRUE

******** End of Comment ********/

/**********************************/
/* Unsigned 16 bit Generic Types. */
/**********************************/

typedef uint16 u16p0_T;
#define BPP_u16p0_T 0
#define SIGNED_u16p0_T FALSE
#define FIXEDTOFLOAT_u16p0_T 1.0f
#define FLOATTOFIXED_u16p0_T 1.0f

typedef uint16 u15p1_T;
#define BPP_u15p1_T 1
#define SIGNED_u15p1_T FALSE
#define FIXEDTOFLOAT_u15p1_T 0.5f
#define FLOATTOFIXED_u15p1_T 2.0f

typedef uint16 u14p2_T;
#define BPP_u14p2_T 2
#define SIGNED_u14p2_T FALSE
#define FIXEDTOFLOAT_u14p2_T 0.25f
#define FLOATTOFIXED_u14p2_T 4.0f

typedef uint16 u13p3_T;
#define BPP_u13p3_T 3
#define SIGNED_u13p3_T FALSE
#define FIXEDTOFLOAT_u13p3_T 0.125f
#define FLOATTOFIXED_u13p3_T 8.0f

typedef uint16 u12p4_T;
#define BPP_u12p4_T 4
#define SIGNED_u12p4_T FALSE
#define FIXEDTOFLOAT_u12p4_T 0.0625f
#define FLOATTOFIXED_u12p4_T 16.0f

typedef uint16 u11p5_T;
#define BPP_u11p5_T 5
#define SIGNED_u11p5_T FALSE
#define FIXEDTOFLOAT_u11p5_T 0.03125f
#define FLOATTOFIXED_u11p5_T 32.0f

typedef uint16 u10p6_T;
#define BPP_u10p6_T 6
#define SIGNED_u10p6_T FALSE
#define FIXEDTOFLOAT_u10p6_T 0.015625f
#define FLOATTOFIXED_u10p6_T 64.0f

typedef uint16 u9p7_T;
#define BPP_u9p7_T 7
#define SIGNED_u9p7_T FALSE
#define FIXEDTOFLOAT_u9p7_T 0.0078125f
#define FLOATTOFIXED_u9p7_T 128.0f

typedef uint16 u8p8_T;
#define BPP_u8p8_T 8
#define SIGNED_u8p8_T FALSE
#define FIXEDTOFLOAT_u8p8_T 0.00390625f
#define FLOATTOFIXED_u8p8_T 256.0f

typedef uint16 u7p9_T;
#define BPP_u7p9_T 9
#define SIGNED_u7p9_T FALSE
#define FIXEDTOFLOAT_u7p9_T 0.001953125f
#define FLOATTOFIXED_u7p9_T 512.0f

typedef uint16 u6p10_T;
#define BPP_u6p10_T 10
#define SIGNED_u6p10_T FALSE
#define FIXEDTOFLOAT_u6p10_T 0.0009765625f
#define FLOATTOFIXED_u6p10_T 1024.0f

typedef uint16 u5p11_T;
#define BPP_u5p11_T 11
#define SIGNED_u5p11_T FALSE
#define FIXEDTOFLOAT_u5p11_T 0.00048828125f
#define FLOATTOFIXED_u5p11_T 2048.0f

typedef uint16 u4p12_T;
#define BPP_u4p12_T 12
#define SIGNED_u4p12_T FALSE
#define FIXEDTOFLOAT_u4p12_T 0.000244140625f
#define FLOATTOFIXED_u4p12_T 4096.0f

typedef uint16 u3p13_T;
#define BPP_u3p13_T 13
#define SIGNED_u3p13_T FALSE
#define FIXEDTOFLOAT_u3p13_T 0.0001220703125f
#define FLOATTOFIXED_u3p13_T 8192.0f

typedef uint16 u2p14_T;
#define BPP_u2p14_T 14
#define SIGNED_u2p14_T FALSE
#define FIXEDTOFLOAT_u2p14_T 0.00006103515625f
#define FLOATTOFIXED_u2p14_T 16384.0f

typedef uint16 u1p15_T;
#define BPP_u1p15_T 15
#define SIGNED_u1p15_T FALSE
#define FIXEDTOFLOAT_u1p15_T 0.000030517578125f
#define FLOATTOFIXED_u1p15_T 32768.0f

typedef uint16 u0p16_T;
#define BPP_u0p16_T 16
#define SIGNED_u0p16_T FALSE
#define FIXEDTOFLOAT_u0p16_T 0.0000152587890625f
#define FLOATTOFIXED_u0p16_T 65536.0f


/**********************************/
/* Signed 16 bit Generic Types.   */
/**********************************/
typedef sint16 s15p0_T;
#define BPP_s15p0_T 0
#define SIGNED_s15p0_T TRUE
#define FIXEDTOFLOAT_s15p0_T 1.0f
#define FLOATTOFIXED_s15p0_T 1.0f

typedef sint16 s14p1_T;
#define BPP_s14p1_T 1
#define SIGNED_s14p1_T TRUE
#define FIXEDTOFLOAT_s14p1_T 0.5f
#define FLOATTOFIXED_s14p1_T 2.0f

typedef sint16 s13p2_T;
#define BPP_s13p2_T 2
#define SIGNED_s13p2_T TRUE
#define FIXEDTOFLOAT_s13p2_T 0.25f
#define FLOATTOFIXED_s13p2_T 4.0f

typedef sint16 s12p3_T;
#define BPP_s12p3_T 3
#define SIGNED_s12p3_T TRUE
#define FIXEDTOFLOAT_s12p3_T 0.125f
#define FLOATTOFIXED_s12p3_T 8.0f

typedef sint16 s11p4_T;
#define BPP_s11p4_T 4
#define SIGNED_s11p4_T TRUE
#define FIXEDTOFLOAT_s11p4_T 0.0625f
#define FLOATTOFIXED_s11p4_T 16.0f

typedef sint16 s10p5_T;
#define BPP_s10p5_T 5
#define SIGNED_s10p5_T TRUE
#define FIXEDTOFLOAT_s10p5_T 0.03125f
#define FLOATTOFIXED_s10p5_T 32.0f

typedef sint16 s9p6_T;
#define BPP_s9p6_T 6
#define SIGNED_s9p6_T TRUE
#define FIXEDTOFLOAT_s9p6_T 0.015625f
#define FLOATTOFIXED_s9p6_T 64.0f

typedef sint16 s8p7_T;
#define BPP_s8p7_T 7
#define SIGNED_s8p7_T TRUE
#define FIXEDTOFLOAT_s8p7_T 0.0078125f
#define FLOATTOFIXED_s8p7_T 128.0f

typedef sint16 s7p8_T;
#define BPP_s7p8_T 8
#define SIGNED_s7p8_T TRUE
#define FIXEDTOFLOAT_s7p8_T 0.00390625f
#define FLOATTOFIXED_s7p8_T 256.0f

typedef sint16 s6p9_T;
#define BPP_s6p9_T 9
#define SIGNED_s6p9_T TRUE
#define FIXEDTOFLOAT_s6p9_T 0.001953125f
#define FLOATTOFIXED_s6p9_T 512.0f

typedef sint16 s5p10_T;
#define BPP_s5p10_T 10
#define SIGNED_s5p10_T TRUE
#define FIXEDTOFLOAT_s5p10_T 0.0009765625f
#define FLOATTOFIXED_s5p10_T 1024.0f

typedef sint16 s4p11_T;
#define BPP_s4p11_T 11
#define SIGNED_s4p11_T TRUE
#define FIXEDTOFLOAT_s4p11_T 0.00048828125f
#define FLOATTOFIXED_s4p11_T 2048.0f

typedef sint16 s3p12_T;
#define BPP_s3p12_T 12
#define SIGNED_s3p12_T TRUE
#define FIXEDTOFLOAT_s3p12_T 0.000244140625f
#define FLOATTOFIXED_s3p12_T 4096.0f

typedef sint16 s2p13_T;
#define BPP_s2p13_T 13
#define SIGNED_s2p13_T TRUE
#define FIXEDTOFLOAT_s2p13_T 0.0001220703125f
#define FLOATTOFIXED_s2p13_T 8192.0f

typedef sint16 s1p14_T;
#define BPP_s1p14_T 14
#define SIGNED_s1p14_T TRUE
#define FIXEDTOFLOAT_s1p14_T 0.00006103515625f
#define FLOATTOFIXED_s1p14_T 16384.0f

typedef sint16 s0p15_T;
#define BPP_s0p15_T 15
#define SIGNED_s0p15_T TRUE
#define FIXEDTOFLOAT_s0p15_T 0.000030517578125f
#define FLOATTOFIXED_s0p15_T 32768.0f

/**********************************/
/* Unsigned 32 bit Generic Types. */
/**********************************/
typedef uint32 u32p0_T;
#define BPP_u32p0_T 0
#define SIGNED_u32p0_T FALSE
#define FIXEDTOFLOAT_u32p0_T 1.0f
#define FLOATTOFIXED_u32p0_T 1.0f

typedef uint32 u31p1_T;
#define BPP_u31p1_T 1
#define SIGNED_u31p1_T FALSE
#define FIXEDTOFLOAT_u31p1_T 0.5f
#define FLOATTOFIXED_u31p1_T 2.0f

typedef uint32 u30p2_T;
#define BPP_u30p2_T 2
#define SIGNED_u30p2_T FALSE
#define FIXEDTOFLOAT_u30p2_T 0.25f
#define FLOATTOFIXED_u30p2_T 4.0f

typedef uint32 u29p3_T;
#define BPP_u29p3_T 3
#define SIGNED_u29p3_T FALSE
#define FIXEDTOFLOAT_u29p3_T 0.125f
#define FLOATTOFIXED_u29p3_T 8.0f

typedef uint32 u28p4_T;
#define BPP_u28p4_T 4
#define SIGNED_u28p4_T FALSE
#define FIXEDTOFLOAT_u28p4_T 0.0625f
#define FLOATTOFIXED_u28p4_T 16.0f

typedef uint32 u27p5_T;
#define BPP_u27p5_T 5
#define SIGNED_u27p5_T FALSE
#define FIXEDTOFLOAT_u27p5_T 0.03125f
#define FLOATTOFIXED_u27p5_T 32.0f

typedef uint32 u26p6_T;
#define BPP_u26p6_T 6
#define SIGNED_u26p6_T FALSE
#define FIXEDTOFLOAT_u26p6_T 0.015625f
#define FLOATTOFIXED_u26p6_T 64.0f

typedef uint32 u25p7_T;
#define BPP_u25p7_T 7
#define SIGNED_u25p7_T FALSE
#define FIXEDTOFLOAT_u25p7_T 0.0078125f
#define FLOATTOFIXED_u25p7_T 128.0f

typedef uint32 u24p8_T;
#define BPP_u24p8_T 8
#define SIGNED_u24p8_T FALSE
#define FIXEDTOFLOAT_u24p8_T 0.00390625f
#define FLOATTOFIXED_u24p8_T 256.0f

typedef uint32 u23p9_T;
#define BPP_u23p9_T 9
#define SIGNED_u23p9_T FALSE
#define FIXEDTOFLOAT_u23p9_T 0.001953125f
#define FLOATTOFIXED_u23p9_T 512.0f

typedef uint32 u22p10_T;
#define BPP_u22p10_T 10
#define SIGNED_u22p10_T FALSE
#define FIXEDTOFLOAT_u22p10_T 0.0009765625f
#define FLOATTOFIXED_u22p10_T 1024.0f

typedef uint32 u21p11_T;
#define BPP_u21p11_T 11
#define SIGNED_u21p11_T FALSE
#define FIXEDTOFLOAT_u21p11_T 0.00048828125f
#define FLOATTOFIXED_u21p11_T 2048.0f

typedef uint32 u20p12_T;
#define BPP_u20p12_T 12
#define SIGNED_u20p12_T FALSE
#define FIXEDTOFLOAT_u20p12_T 0.000244140625f
#define FLOATTOFIXED_u20p12_T 4096.0f

typedef uint32 u19p13_T;
#define BPP_u19p13_T 13
#define SIGNED_u19p13_T FALSE
#define FIXEDTOFLOAT_u19p13_T 0.0001220703125f
#define FLOATTOFIXED_u19p13_T 8192.0f

typedef uint32 u18p14_T;
#define BPP_u18p14_T 14
#define SIGNED_u18p14_T FALSE
#define FIXEDTOFLOAT_u18p14_T 0.00006103515625f
#define FLOATTOFIXED_u18p14_T 16384.0f

typedef uint32 u17p15_T;
#define BPP_u17p15_T 15
#define SIGNED_u17p15_T FALSE
#define FIXEDTOFLOAT_u17p15_T 0.000030517578125f
#define FLOATTOFIXED_u17p15_T 32768.0f

typedef uint32 u16p16_T;
#define BPP_u16p16_T 16
#define SIGNED_u16p16_T FALSE
#define FIXEDTOFLOAT_u16p16_T 0.0000152587890625f
#define FLOATTOFIXED_u16p16_T 65536.0f

typedef uint32 u15p17_T;
#define BPP_u15p17_T 17
#define SIGNED_u15p17_T FALSE
#define FIXEDTOFLOAT_u15p17_T 0.00000762939453125f
#define FLOATTOFIXED_u15p17_T 131072.0f

typedef uint32 u14p18_T;
#define BPP_u14p18_T 18
#define SIGNED_u14p18_T FALSE
#define FIXEDTOFLOAT_u14p18_T 0.000003814697265625f
#define FLOATTOFIXED_u14p18_T 262144.0f

typedef uint32 u13p19_T;
#define BPP_u13p19_T 19
#define SIGNED_u13p19_T FALSE
#define FIXEDTOFLOAT_u13p19_T 1.9073486328125E-06f
#define FLOATTOFIXED_u13p19_T 524288.0f

typedef uint32 u12p20_T;
#define BPP_u12p20_T 20
#define SIGNED_u12p20_T FALSE
#define FIXEDTOFLOAT_u12p20_T 9.5367431640625E-07f
#define FLOATTOFIXED_u12p20_T 1048576.0f

typedef uint32 u11p21_T;
#define BPP_u11p21_T 21
#define SIGNED_u11p21_T FALSE
#define FIXEDTOFLOAT_u11p21_T 4.76837158203125E-07f
#define FLOATTOFIXED_u11p21_T 2097152.0f

typedef uint32 u10p22_T;
#define BPP_u10p22_T 22
#define SIGNED_u10p22_T FALSE
#define FIXEDTOFLOAT_u10p22_T 2.38418579101562E-07f
#define FLOATTOFIXED_u10p22_T 4194304.0f

typedef uint32 u9p23_T;
#define BPP_u9p23_T 23
#define SIGNED_u9p23_T FALSE
#define FIXEDTOFLOAT_u9p23_T 1.19209289550781E-07f
#define FLOATTOFIXED_u9p23_T 8388608.0f

typedef uint32 u8p24_T;
#define BPP_u8p24_T 24
#define SIGNED_u8p24_T FALSE
#define FIXEDTOFLOAT_u8p24_T 5.96046447753906E-08f
#define FLOATTOFIXED_u8p24_T 16777216.0f

typedef uint32 u7p25_T;
#define BPP_u7p25_T 25
#define SIGNED_u7p25_T FALSE
#define FIXEDTOFLOAT_u7p25_T 2.98023223876953E-08f
#define FLOATTOFIXED_u7p25_T 33554432.0f

typedef uint32 u6p26_T;
#define BPP_u6p26_T 26
#define SIGNED_u6p26_T FALSE
#define FIXEDTOFLOAT_u6p26_T 1.49011611938477E-08f
#define FLOATTOFIXED_u6p26_T 67108864.0f

typedef uint32 u5p27_T;
#define BPP_u5p27_T 27
#define SIGNED_u5p27_T FALSE
#define FIXEDTOFLOAT_u5p27_T 7.45058059692383E-09f
#define FLOATTOFIXED_u5p27_T 134217728.0f

typedef uint32 u4p28_T;
#define BPP_u4p28_T 28
#define SIGNED_u4p28_T FALSE
#define FIXEDTOFLOAT_u4p28_T 3.72529029846191E-09f
#define FLOATTOFIXED_u4p28_T 268435456.0f

typedef uint32 u3p29_T;
#define BPP_u3p29_T 29
#define SIGNED_u3p29_T FALSE
#define FIXEDTOFLOAT_u3p29_T 1.86264514923096E-09f
#define FLOATTOFIXED_u3p29_T 536870912.0f

typedef uint32 u2p30_T;
#define BPP_u2p30_T 30
#define SIGNED_u2p30_T FALSE
#define FIXEDTOFLOAT_u2p30_T 9.31322574615479E-10f
#define FLOATTOFIXED_u2p30_T 1073741824.0f

typedef uint32 u1p31_T;
#define BPP_u1p31_T 31
#define SIGNED_u1p31_T FALSE
#define FIXEDTOFLOAT_u1p31_T 4.65661287307739E-10f
#define FLOATTOFIXED_u1p31_T 2147483648.0f

typedef uint32 u0p32_T;
#define BPP_u0p32_T 32
#define SIGNED_u0p32_T FALSE
#define FIXEDTOFLOAT_u0p32_T 2.3283064365387E-10f
#define FLOATTOFIXED_u0p32_T 4294967296.0f


/**********************************/
/* Signed 32 bit Generic Types.   */
/**********************************/

typedef sint32 s31p0_T;
#define BPP_s31p0_T 0
#define SIGNED_s31p0_T TRUE
#define FIXEDTOFLOAT_s31p0_T 1.0f
#define FLOATTOFIXED_s31p0_T 1.0f

typedef sint32 s30p1_T;
#define BPP_s30p1_T 1
#define SIGNED_s30p1_T TRUE
#define FIXEDTOFLOAT_s30p1_T 0.5f
#define FLOATTOFIXED_s30p1_T 2.0f

typedef sint32 s29p2_T;
#define BPP_s29p2_T 2
#define SIGNED_s29p2_T TRUE
#define FIXEDTOFLOAT_s29p2_T 0.25f
#define FLOATTOFIXED_s29p2_T 4.0f

typedef sint32 s28p3_T;
#define BPP_s28p3_T 3
#define SIGNED_s28p3_T TRUE
#define FIXEDTOFLOAT_s28p3_T 0.125f
#define FLOATTOFIXED_s28p3_T 8.0f

typedef sint32 s27p4_T;
#define BPP_s27p4_T 4
#define SIGNED_s27p4_T TRUE
#define FIXEDTOFLOAT_s27p4_T 0.0625f
#define FLOATTOFIXED_s27p4_T 16.0f

typedef sint32 s26p5_T;
#define BPP_s26p5_T 5
#define SIGNED_s26p5_T TRUE
#define FIXEDTOFLOAT_s26p5_T 0.03125f
#define FLOATTOFIXED_s26p5_T 32.0f

typedef sint32 s25p6_T;
#define BPP_s25p6_T 6
#define SIGNED_s25p6_T TRUE
#define FIXEDTOFLOAT_s25p6_T 0.015625f
#define FLOATTOFIXED_s25p6_T 64.0f

typedef sint32 s24p7_T;
#define BPP_s24p7_T 7
#define SIGNED_s24p7_T TRUE
#define FIXEDTOFLOAT_s24p7_T 0.0078125f
#define FLOATTOFIXED_s24p7_T 128.0f

typedef sint32 s23p8_T;
#define BPP_s23p8_T 8
#define SIGNED_s23p8_T TRUE
#define FIXEDTOFLOAT_s23p8_T 0.00390625f
#define FLOATTOFIXED_s23p8_T 256.0f

typedef sint32 s22p9_T;
#define BPP_s22p9_T 9
#define SIGNED_s22p9_T TRUE
#define FIXEDTOFLOAT_s22p9_T 0.001953125f
#define FLOATTOFIXED_s22p9_T 512.0f

typedef sint32 s21p10_T;
#define BPP_s21p10_T 10
#define SIGNED_s21p10_T TRUE
#define FIXEDTOFLOAT_s21p10_T 0.0009765625f
#define FLOATTOFIXED_s21p10_T 1024.0f

typedef sint32 s20p11_T;
#define BPP_s20p11_T 11
#define SIGNED_s20p11_T TRUE
#define FIXEDTOFLOAT_s20p11_T 0.00048828125f
#define FLOATTOFIXED_s20p11_T 2048.0f

typedef sint32 s19p12_T;
#define BPP_s19p12_T 12
#define SIGNED_s19p12_T TRUE
#define FIXEDTOFLOAT_s19p12_T 0.000244140625f
#define FLOATTOFIXED_s19p12_T 4096.0f

typedef sint32 s18p13_T;
#define BPP_s18p13_T 13
#define SIGNED_s18p13_T TRUE
#define FIXEDTOFLOAT_s18p13_T 0.0001220703125f
#define FLOATTOFIXED_s18p13_T 8192.0f

typedef sint32 s17p14_T;
#define BPP_s17p14_T 14
#define SIGNED_s17p14_T TRUE
#define FIXEDTOFLOAT_s17p14_T 0.00006103515625f
#define FLOATTOFIXED_s17p14_T 16384.0f

typedef sint32 s16p15_T;
#define BPP_s16p15_T 15
#define SIGNED_s16p15_T TRUE
#define FIXEDTOFLOAT_s16p15_T 0.000030517578125f
#define FLOATTOFIXED_s16p15_T 32768.0f

typedef sint32 s15p16_T;
#define BPP_s15p16_T 16
#define SIGNED_s15p16_T TRUE
#define FIXEDTOFLOAT_s15p16_T 0.0000152587890625f
#define FLOATTOFIXED_s15p16_T 65536.0f

typedef sint32 s14p17_T;
#define BPP_s14p17_T 17
#define SIGNED_s14p17_T TRUE
#define FIXEDTOFLOAT_s14p17_T 0.00000762939453125f
#define FLOATTOFIXED_s14p17_T 131072.0f

typedef sint32 s13p18_T;
#define BPP_s13p18_T 18
#define SIGNED_s13p18_T TRUE
#define FIXEDTOFLOAT_s13p18_T 0.000003814697265625f
#define FLOATTOFIXED_s13p18_T 262144.0f

typedef sint32 s12p19_T;
#define BPP_s12p19_T 19
#define SIGNED_s12p19_T TRUE
#define FIXEDTOFLOAT_s12p19_T 1.9073486328125E-06f
#define FLOATTOFIXED_s12p19_T 524288.0f

typedef sint32 s11p20_T;
#define BPP_s11p20_T 20
#define SIGNED_s11p20_T TRUE
#define FIXEDTOFLOAT_s11p20_T 9.5367431640625E-07f
#define FLOATTOFIXED_s11p20_T 1048576.0f

typedef sint32 s10p21_T;
#define BPP_s10p21_T 21
#define SIGNED_s10p21_T TRUE
#define FIXEDTOFLOAT_s10p21_T 4.76837158203125E-07f
#define FLOATTOFIXED_s10p21_T 2097152.0f

typedef sint32 s9p22_T;
#define BPP_s9p22_T 22
#define SIGNED_s9p22_T TRUE
#define FIXEDTOFLOAT_s9p22_T 2.38418579101562E-07f
#define FLOATTOFIXED_s9p22_T 4194304.0f

typedef sint32 s8p23_T;
#define BPP_s8p23_T 23
#define SIGNED_s8p23_T TRUE
#define FIXEDTOFLOAT_s8p23_T 1.19209289550781E-07f
#define FLOATTOFIXED_s8p23_T 8388608.0f

typedef sint32 s7p24_T;
#define BPP_s7p24_T 24
#define SIGNED_s7p24_T TRUE
#define FIXEDTOFLOAT_s7p24_T 5.96046447753906E-08f
#define FLOATTOFIXED_s7p24_T 16777216.0f

typedef sint32 s6p25_T;
#define BPP_s6p25_T 25
#define SIGNED_s6p25_T TRUE
#define FIXEDTOFLOAT_s6p25_T 2.98023223876953E-08f
#define FLOATTOFIXED_s6p25_T 33554432.0f

typedef sint32 s5p26_T;
#define BPP_s5p26_T 26
#define SIGNED_s5p26_T TRUE
#define FIXEDTOFLOAT_s5p26_T 1.49011611938477E-08f
#define FLOATTOFIXED_s5p26_T 67108864.0f

typedef sint32 s4p27_T;
#define BPP_s4p27_T 27
#define SIGNED_s4p27_T TRUE
#define FIXEDTOFLOAT_s4p27_T 7.45058059692383E-09f
#define FLOATTOFIXED_s4p27_T 134217728.0f

typedef sint32 s3p28_T;
#define BPP_s3p28_T 28
#define SIGNED_s3p28_T TRUE
#define FIXEDTOFLOAT_s3p28_T 3.72529029846191E-09f
#define FLOATTOFIXED_s3p28_T 268435456.0f

typedef sint32 s2p29_T;
#define BPP_s2p29_T 29
#define SIGNED_s2p29_T TRUE
#define FIXEDTOFLOAT_s2p29_T 1.86264514923096E-09f
#define FLOATTOFIXED_s2p29_T 536870912.0f

typedef sint32 s1p30_T;
#define BPP_s1p30_T 30
#define SIGNED_s1p30_T TRUE
#define FIXEDTOFLOAT_s1p30_T 9.31322574615479E-10f
#define FLOATTOFIXED_s1p30_T 1073741824.0f

typedef sint32 s0p31_T;
#define BPP_s0p31_T 31
#define SIGNED_s0p31_T TRUE
#define FIXEDTOFLOAT_s0p31_T 4.65661287307739E-10f
#define FLOATTOFIXED_s0p31_T 2147483648.0f

/* Maximum Values for Data type Conversions */
#define	MAX_s29p2_Ts33pm2_T	2147483639uL
#define	MAX_s29p2_Ts32pm1_T	2147483643uL
#define	MAX_s29p2_Ts31p0_T	2147483645uL
#define	MAX_s29p2_Ts30p1_T	2147483646uL
#define	MAX_s25p6_Ts33pm2_T	2147483519uL
#define	MAX_s25p6_Ts32pm1_T	2147483583uL
#define	MAX_s25p6_Ts31p0_T	2147483615uL
#define	MAX_s25p6_Ts30p1_T	2147483631uL
#define	MAX_s25p6_Ts29p2_T	2147483639uL
#define	MAX_s25p6_Ts28p3_T	2147483643uL
#define	MAX_s25p6_Ts27p4_T	2147483645uL
#define	MAX_s25p6_Ts26p5_T	2147483646uL
#define	MAX_s21p10_Ts33pm2_T	2147481599uL
#define	MAX_s21p10_Ts32pm1_T	2147482623uL
#define	MAX_s21p10_Ts31p0_T	2147483135uL
#define	MAX_s21p10_Ts30p1_T	2147483391uL
#define	MAX_s21p10_Ts29p2_T	2147483519uL
#define	MAX_s21p10_Ts28p3_T	2147483583uL
#define	MAX_s21p10_Ts27p4_T	2147483615uL
#define	MAX_s21p10_Ts26p5_T	2147483631uL
#define	MAX_s21p10_Ts25p6_T	2147483639uL
#define	MAX_s21p10_Ts24p7_T	2147483643uL
#define	MAX_s21p10_Ts23p8_T	2147483645uL
#define	MAX_s21p10_Ts22p9_T	2147483646uL
#define	MAX_s17p14_Ts33pm2_T	2147450879uL
#define	MAX_s17p14_Ts32pm1_T	2147467263uL
#define	MAX_s17p14_Ts31p0_T	2147475455uL
#define	MAX_s17p14_Ts30p1_T	2147479551uL
#define	MAX_s17p14_Ts29p2_T	2147481599uL
#define	MAX_s17p14_Ts28p3_T	2147482623uL
#define	MAX_s17p14_Ts27p4_T	2147483135uL
#define	MAX_s17p14_Ts26p5_T	2147483391uL
#define	MAX_s17p14_Ts25p6_T	2147483519uL
#define	MAX_s17p14_Ts24p7_T	2147483583uL
#define	MAX_s17p14_Ts23p8_T	2147483615uL
#define	MAX_s17p14_Ts22p9_T	2147483631uL
#define	MAX_s17p14_Ts21p10_T	2147483639uL
#define	MAX_s17p14_Ts20p11_T	2147483643uL
#define	MAX_s17p14_Ts19p12_T	2147483645uL
#define	MAX_s17p14_Ts18p13_T	2147483646uL
#define	MAX_s13p18_Ts33pm2_T	2146959359uL
#define	MAX_s13p18_Ts32pm1_T	2147221503uL
#define	MAX_s13p18_Ts31p0_T	2147352575uL
#define	MAX_s13p18_Ts30p1_T	2147418111uL
#define	MAX_s13p18_Ts29p2_T	2147450879uL
#define	MAX_s13p18_Ts28p3_T	2147467263uL
#define	MAX_s13p18_Ts27p4_T	2147475455uL
#define	MAX_s13p18_Ts26p5_T	2147479551uL
#define	MAX_s13p18_Ts25p6_T	2147481599uL
#define	MAX_s13p18_Ts24p7_T	2147482623uL
#define	MAX_s13p18_Ts23p8_T	2147483135uL
#define	MAX_s13p18_Ts22p9_T	2147483391uL
#define	MAX_s13p18_Ts21p10_T	2147483519uL
#define	MAX_s13p18_Ts20p11_T	2147483583uL
#define	MAX_s13p18_Ts19p12_T	2147483615uL
#define	MAX_s13p18_Ts18p13_T	2147483631uL
#define	MAX_s13p18_Ts17p14_T	2147483639uL
#define	MAX_s13p18_Ts16p15_T	2147483643uL
#define	MAX_s13p18_Ts15p16_T	2147483645uL
#define	MAX_s13p18_Ts14p17_T	2147483646uL
#define	MAX_s9p22_Ts33pm2_T	2139095039uL
#define	MAX_s9p22_Ts32pm1_T	2143289343uL
#define	MAX_s9p22_Ts31p0_T	2145386495uL
#define	MAX_s9p22_Ts30p1_T	2146435071uL
#define	MAX_s9p22_Ts29p2_T	2146959359uL
#define	MAX_s9p22_Ts28p3_T	2147221503uL
#define	MAX_s9p22_Ts27p4_T	2147352575uL
#define	MAX_s9p22_Ts26p5_T	2147418111uL
#define	MAX_s9p22_Ts25p6_T	2147450879uL
#define	MAX_s9p22_Ts24p7_T	2147467263uL
#define	MAX_s9p22_Ts23p8_T	2147475455uL
#define	MAX_s9p22_Ts22p9_T	2147479551uL
#define	MAX_s9p22_Ts21p10_T	2147481599uL
#define	MAX_s9p22_Ts20p11_T	2147482623uL
#define	MAX_s9p22_Ts19p12_T	2147483135uL
#define	MAX_s9p22_Ts18p13_T	2147483391uL
#define	MAX_s9p22_Ts17p14_T	2147483519uL
#define	MAX_s9p22_Ts16p15_T	2147483583uL
#define	MAX_s9p22_Ts15p16_T	2147483615uL
#define	MAX_s9p22_Ts14p17_T	2147483631uL
#define	MAX_s9p22_Ts13p18_T	2147483639uL
#define	MAX_s9p22_Ts12p19_T	2147483643uL
#define	MAX_s9p22_Ts11p20_T	2147483645uL
#define	MAX_s9p22_Ts10p21_T	2147483646uL
#define	MAX_s5p26_Ts33pm2_T	2013265919uL
#define	MAX_s5p26_Ts32pm1_T	2080374783uL
#define	MAX_s5p26_Ts31p0_T	2113929215uL
#define	MAX_s5p26_Ts30p1_T	2130706431uL
#define	MAX_s5p26_Ts29p2_T	2139095039uL
#define	MAX_s5p26_Ts28p3_T	2143289343uL
#define	MAX_s5p26_Ts27p4_T	2145386495uL
#define	MAX_s5p26_Ts26p5_T	2146435071uL
#define	MAX_s5p26_Ts25p6_T	2146959359uL
#define	MAX_s5p26_Ts24p7_T	2147221503uL
#define	MAX_s5p26_Ts23p8_T	2147352575uL
#define	MAX_s5p26_Ts22p9_T	2147418111uL
#define	MAX_s5p26_Ts21p10_T	2147450879uL
#define	MAX_s5p26_Ts20p11_T	2147467263uL
#define	MAX_s5p26_Ts19p12_T	2147475455uL
#define	MAX_s5p26_Ts18p13_T	2147479551uL
#define	MAX_s5p26_Ts17p14_T	2147481599uL
#define	MAX_s5p26_Ts16p15_T	2147482623uL
#define	MAX_s5p26_Ts15p16_T	2147483135uL
#define	MAX_s5p26_Ts14p17_T	2147483391uL
#define	MAX_s5p26_Ts13p18_T	2147483519uL
#define	MAX_s5p26_Ts12p19_T	2147483583uL
#define	MAX_s5p26_Ts11p20_T	2147483615uL
#define	MAX_s5p26_Ts10p21_T	2147483631uL
#define	MAX_s5p26_Ts9p22_T	2147483639uL
#define	MAX_s5p26_Ts8p23_T	2147483643uL
#define	MAX_s5p26_Ts7p24_T	2147483645uL
#define	MAX_s5p26_Ts6p25_T	2147483646uL
#define	MAX_s1p30_Ts32pm1_T	1073741823uL
#define	MAX_s1p30_Ts31p0_T	1610612735uL
#define	MAX_s1p30_Ts30p1_T	1879048191uL
#define	MAX_s1p30_Ts29p2_T	2013265919uL
#define	MAX_s1p30_Ts28p3_T	2080374783uL
#define	MAX_s1p30_Ts27p4_T	2113929215uL
#define	MAX_s1p30_Ts26p5_T	2130706431uL
#define	MAX_s1p30_Ts25p6_T	2139095039uL
#define	MAX_s1p30_Ts24p7_T	2143289343uL
#define	MAX_s1p30_Ts23p8_T	2145386495uL
#define	MAX_s1p30_Ts22p9_T	2146435071uL
#define	MAX_s1p30_Ts21p10_T	2146959359uL
#define	MAX_s1p30_Ts20p11_T	2147221503uL
#define	MAX_s1p30_Ts19p12_T	2147352575uL
#define	MAX_s1p30_Ts18p13_T	2147418111uL
#define	MAX_s1p30_Ts17p14_T	2147450879uL
#define	MAX_s1p30_Ts16p15_T	2147467263uL
#define	MAX_s1p30_Ts15p16_T	2147475455uL
#define	MAX_s1p30_Ts14p17_T	2147479551uL
#define	MAX_s1p30_Ts13p18_T	2147481599uL
#define	MAX_s1p30_Ts12p19_T	2147482623uL
#define	MAX_s1p30_Ts11p20_T	2147483135uL
#define	MAX_s1p30_Ts10p21_T	2147483391uL
#define	MAX_s1p30_Ts9p22_T	2147483519uL
#define	MAX_s1p30_Ts8p23_T	2147483583uL
#define	MAX_s1p30_Ts7p24_T	2147483615uL
#define	MAX_s1p30_Ts6p25_T	2147483631uL
#define	MAX_s1p30_Ts5p26_T	2147483639uL
#define	MAX_s1p30_Ts4p27_T	2147483643uL
#define	MAX_s1p30_Ts3p28_T	2147483645uL
#define	MAX_s1p30_Ts2p29_T	2147483646uL
#define	MAX_sm3p34_Ts28p3_T	1073741823uL
#define	MAX_sm3p34_Ts27p4_T	1610612735uL
#define	MAX_sm3p34_Ts26p5_T	1879048191uL
#define	MAX_sm3p34_Ts25p6_T	2013265919uL
#define	MAX_sm3p34_Ts24p7_T	2080374783uL
#define	MAX_sm3p34_Ts23p8_T	2113929215uL
#define	MAX_sm3p34_Ts22p9_T	2130706431uL
#define	MAX_sm3p34_Ts21p10_T	2139095039uL
#define	MAX_sm3p34_Ts20p11_T	2143289343uL
#define	MAX_sm3p34_Ts19p12_T	2145386495uL
#define	MAX_sm3p34_Ts18p13_T	2146435071uL
#define	MAX_sm3p34_Ts17p14_T	2146959359uL
#define	MAX_sm3p34_Ts16p15_T	2147221503uL
#define	MAX_sm3p34_Ts15p16_T	2147352575uL
#define	MAX_sm3p34_Ts14p17_T	2147418111uL
#define	MAX_sm3p34_Ts13p18_T	2147450879uL
#define	MAX_sm3p34_Ts12p19_T	2147467263uL
#define	MAX_sm3p34_Ts11p20_T	2147475455uL
#define	MAX_sm3p34_Ts10p21_T	2147479551uL
#define	MAX_sm3p34_Ts9p22_T	2147481599uL
#define	MAX_sm3p34_Ts8p23_T	2147482623uL
#define	MAX_sm3p34_Ts7p24_T	2147483135uL
#define	MAX_sm3p34_Ts6p25_T	2147483391uL
#define	MAX_sm3p34_Ts5p26_T	2147483519uL
#define	MAX_sm3p34_Ts4p27_T	2147483583uL
#define	MAX_sm3p34_Ts3p28_T	2147483615uL
#define	MAX_sm3p34_Ts2p29_T	2147483631uL
#define	MAX_sm3p34_Ts1p30_T	2147483639uL
#define	MAX_sm3p34_Ts0p31_T	2147483643uL
#define	MAX_sm3p34_Tsm1p32_T	2147483645uL
#define	MAX_sm3p34_Tsm2p33_T	2147483646uL
#define	MAX_sm4p35_Ts27p4_T	1073741823uL
#define	MAX_sm4p35_Ts26p5_T	1610612735uL
#define	MAX_sm4p35_Ts25p6_T	1879048191uL
#define	MAX_sm4p35_Ts24p7_T	2013265919uL
#define	MAX_sm4p35_Ts23p8_T	2080374783uL
#define	MAX_sm4p35_Ts22p9_T	2113929215uL
#define	MAX_sm4p35_Ts21p10_T	2130706431uL
#define	MAX_sm4p35_Ts20p11_T	2139095039uL
#define	MAX_sm4p35_Ts19p12_T	2143289343uL
#define	MAX_sm4p35_Ts18p13_T	2145386495uL
#define	MAX_sm4p35_Ts17p14_T	2146435071uL
#define	MAX_sm4p35_Ts16p15_T	2146959359uL
#define	MAX_sm4p35_Ts15p16_T	2147221503uL
#define	MAX_sm4p35_Ts14p17_T	2147352575uL
#define	MAX_sm4p35_Ts13p18_T	2147418111uL
#define	MAX_sm4p35_Ts12p19_T	2147450879uL
#define	MAX_sm4p35_Ts11p20_T	2147467263uL
#define	MAX_sm4p35_Ts10p21_T	2147475455uL
#define	MAX_sm4p35_Ts9p22_T	2147479551uL
#define	MAX_sm4p35_Ts8p23_T	2147481599uL
#define	MAX_sm4p35_Ts7p24_T	2147482623uL
#define	MAX_sm4p35_Ts6p25_T	2147483135uL
#define	MAX_sm4p35_Ts5p26_T	2147483391uL
#define	MAX_sm4p35_Ts4p27_T	2147483519uL
#define	MAX_sm4p35_Ts3p28_T	2147483583uL
#define	MAX_sm4p35_Ts2p29_T	2147483615uL
#define	MAX_sm4p35_Ts1p30_T	2147483631uL
#define	MAX_sm4p35_Ts0p31_T	2147483639uL
#define	MAX_sm4p35_Tsm1p32_T	2147483643uL
#define	MAX_sm4p35_Tsm2p33_T	2147483645uL
#define	MAX_sm4p35_Tsm3p34_T	2147483646uL
#define	MAX_s0p31_Ts31p0_T	1073741823uL
#define	MAX_s0p31_Ts30p1_T	1610612735uL
#define	MAX_s0p31_Ts29p2_T	1879048191uL
#define	MAX_s0p31_Ts28p3_T	2013265919uL
#define	MAX_s0p31_Ts27p4_T	2080374783uL
#define	MAX_s0p31_Ts26p5_T	2113929215uL
#define	MAX_s0p31_Ts25p6_T	2130706431uL
#define	MAX_s0p31_Ts24p7_T	2139095039uL
#define	MAX_s0p31_Ts23p8_T	2143289343uL
#define	MAX_s0p31_Ts22p9_T	2145386495uL
#define	MAX_s0p31_Ts21p10_T	2146435071uL
#define	MAX_s0p31_Ts20p11_T	2146959359uL
#define	MAX_s0p31_Ts19p12_T	2147221503uL
#define	MAX_s0p31_Ts18p13_T	2147352575uL
#define	MAX_s0p31_Ts17p14_T	2147418111uL
#define	MAX_s0p31_Ts16p15_T	2147450879uL
#define	MAX_s0p31_Ts15p16_T	2147467263uL
#define	MAX_s0p31_Ts14p17_T	2147475455uL
#define	MAX_s0p31_Ts13p18_T	2147479551uL
#define	MAX_s0p31_Ts12p19_T	2147481599uL
#define	MAX_s0p31_Ts11p20_T	2147482623uL
#define	MAX_s0p31_Ts10p21_T	2147483135uL
#define	MAX_s0p31_Ts9p22_T	2147483391uL
#define	MAX_s0p31_Ts8p23_T	2147483519uL
#define	MAX_s0p31_Ts7p24_T	2147483583uL
#define	MAX_s0p31_Ts6p25_T	2147483615uL
#define	MAX_s0p31_Ts5p26_T	2147483631uL
#define	MAX_s0p31_Ts4p27_T	2147483639uL
#define	MAX_s0p31_Ts3p28_T	2147483643uL
#define	MAX_s0p31_Ts2p29_T	2147483645uL
#define	MAX_s0p31_Ts1p30_T	2147483646uL
#define	MAX_s4p27_Ts33pm2_T	1879048191uL
#define	MAX_s4p27_Ts32pm1_T	2013265919uL
#define	MAX_s4p27_Ts31p0_T	2080374783uL
#define	MAX_s4p27_Ts30p1_T	2113929215uL
#define	MAX_s4p27_Ts29p2_T	2130706431uL
#define	MAX_s4p27_Ts28p3_T	2139095039uL
#define	MAX_s4p27_Ts27p4_T	2143289343uL
#define	MAX_s4p27_Ts26p5_T	2145386495uL
#define	MAX_s4p27_Ts25p6_T	2146435071uL
#define	MAX_s4p27_Ts24p7_T	2146959359uL
#define	MAX_s4p27_Ts23p8_T	2147221503uL
#define	MAX_s4p27_Ts22p9_T	2147352575uL
#define	MAX_s4p27_Ts21p10_T	2147418111uL
#define	MAX_s4p27_Ts20p11_T	2147450879uL
#define	MAX_s4p27_Ts19p12_T	2147467263uL
#define	MAX_s4p27_Ts18p13_T	2147475455uL
#define	MAX_s4p27_Ts17p14_T	2147479551uL
#define	MAX_s4p27_Ts16p15_T	2147481599uL
#define	MAX_s4p27_Ts15p16_T	2147482623uL
#define	MAX_s4p27_Ts14p17_T	2147483135uL
#define	MAX_s4p27_Ts13p18_T	2147483391uL
#define	MAX_s4p27_Ts12p19_T	2147483519uL
#define	MAX_s4p27_Ts11p20_T	2147483583uL
#define	MAX_s4p27_Ts10p21_T	2147483615uL
#define	MAX_s4p27_Ts9p22_T	2147483631uL
#define	MAX_s4p27_Ts8p23_T	2147483639uL
#define	MAX_s4p27_Ts7p24_T	2147483643uL
#define	MAX_s4p27_Ts6p25_T	2147483645uL
#define	MAX_s4p27_Ts5p26_T	2147483646uL
#define	MAX_s8p23_Ts33pm2_T	2130706431uL
#define	MAX_s8p23_Ts32pm1_T	2139095039uL
#define	MAX_s8p23_Ts31p0_T	2143289343uL
#define	MAX_s8p23_Ts30p1_T	2145386495uL
#define	MAX_s8p23_Ts29p2_T	2146435071uL
#define	MAX_s8p23_Ts28p3_T	2146959359uL
#define	MAX_s8p23_Ts27p4_T	2147221503uL
#define	MAX_s8p23_Ts26p5_T	2147352575uL
#define	MAX_s8p23_Ts25p6_T	2147418111uL
#define	MAX_s8p23_Ts24p7_T	2147450879uL
#define	MAX_s8p23_Ts23p8_T	2147467263uL
#define	MAX_s8p23_Ts22p9_T	2147475455uL
#define	MAX_s8p23_Ts21p10_T	2147479551uL
#define	MAX_s8p23_Ts20p11_T	2147481599uL
#define	MAX_s8p23_Ts19p12_T	2147482623uL
#define	MAX_s8p23_Ts18p13_T	2147483135uL
#define	MAX_s8p23_Ts17p14_T	2147483391uL
#define	MAX_s8p23_Ts16p15_T	2147483519uL
#define	MAX_s8p23_Ts15p16_T	2147483583uL
#define	MAX_s8p23_Ts14p17_T	2147483615uL
#define	MAX_s8p23_Ts13p18_T	2147483631uL
#define	MAX_s8p23_Ts12p19_T	2147483639uL
#define	MAX_s8p23_Ts11p20_T	2147483643uL
#define	MAX_s8p23_Ts10p21_T	2147483645uL
#define	MAX_s8p23_Ts9p22_T	2147483646uL
#define	MAX_s12p19_Ts33pm2_T	2146435071uL
#define	MAX_s12p19_Ts32pm1_T	2146959359uL
#define	MAX_s12p19_Ts31p0_T	2147221503uL
#define	MAX_s12p19_Ts30p1_T	2147352575uL
#define	MAX_s12p19_Ts29p2_T	2147418111uL
#define	MAX_s12p19_Ts28p3_T	2147450879uL
#define	MAX_s12p19_Ts27p4_T	2147467263uL
#define	MAX_s12p19_Ts26p5_T	2147475455uL
#define	MAX_s12p19_Ts25p6_T	2147479551uL
#define	MAX_s12p19_Ts24p7_T	2147481599uL
#define	MAX_s12p19_Ts23p8_T	2147482623uL
#define	MAX_s12p19_Ts22p9_T	2147483135uL
#define	MAX_s12p19_Ts21p10_T	2147483391uL
#define	MAX_s12p19_Ts20p11_T	2147483519uL
#define	MAX_s12p19_Ts19p12_T	2147483583uL
#define	MAX_s12p19_Ts18p13_T	2147483615uL
#define	MAX_s12p19_Ts17p14_T	2147483631uL
#define	MAX_s12p19_Ts16p15_T	2147483639uL
#define	MAX_s12p19_Ts15p16_T	2147483643uL
#define	MAX_s12p19_Ts14p17_T	2147483645uL
#define	MAX_s12p19_Ts13p18_T	2147483646uL
#define	MAX_s16p15_Ts33pm2_T	2147418111uL
#define	MAX_s16p15_Ts32pm1_T	2147450879uL
#define	MAX_s16p15_Ts31p0_T	2147467263uL
#define	MAX_s16p15_Ts30p1_T	2147475455uL
#define	MAX_s16p15_Ts29p2_T	2147479551uL
#define	MAX_s16p15_Ts28p3_T	2147481599uL
#define	MAX_s16p15_Ts27p4_T	2147482623uL
#define	MAX_s16p15_Ts26p5_T	2147483135uL
#define	MAX_s16p15_Ts25p6_T	2147483391uL
#define	MAX_s16p15_Ts24p7_T	2147483519uL
#define	MAX_s16p15_Ts23p8_T	2147483583uL
#define	MAX_s16p15_Ts22p9_T	2147483615uL
#define	MAX_s16p15_Ts21p10_T	2147483631uL
#define	MAX_s16p15_Ts20p11_T	2147483639uL
#define	MAX_s16p15_Ts19p12_T	2147483643uL
#define	MAX_s16p15_Ts18p13_T	2147483645uL
#define	MAX_s16p15_Ts17p14_T	2147483646uL
#define	MAX_s20p11_Ts33pm2_T	2147479551uL
#define	MAX_s20p11_Ts32pm1_T	2147481599uL
#define	MAX_s20p11_Ts31p0_T	2147482623uL
#define	MAX_s20p11_Ts30p1_T	2147483135uL
#define	MAX_s20p11_Ts29p2_T	2147483391uL
#define	MAX_s20p11_Ts28p3_T	2147483519uL
#define	MAX_s20p11_Ts27p4_T	2147483583uL
#define	MAX_s20p11_Ts26p5_T	2147483615uL
#define	MAX_s20p11_Ts25p6_T	2147483631uL
#define	MAX_s20p11_Ts24p7_T	2147483639uL
#define	MAX_s20p11_Ts23p8_T	2147483643uL
#define	MAX_s20p11_Ts22p9_T	2147483645uL
#define	MAX_s20p11_Ts21p10_T	2147483646uL
#define	MAX_s24p7_Ts33pm2_T	2147483391uL
#define	MAX_s24p7_Ts32pm1_T	2147483519uL
#define	MAX_s24p7_Ts31p0_T	2147483583uL
#define	MAX_s24p7_Ts30p1_T	2147483615uL
#define	MAX_s24p7_Ts29p2_T	2147483631uL
#define	MAX_s24p7_Ts28p3_T	2147483639uL
#define	MAX_s24p7_Ts27p4_T	2147483643uL
#define	MAX_s24p7_Ts26p5_T	2147483645uL
#define	MAX_s24p7_Ts25p6_T	2147483646uL
#define	MAX_s28p3_Ts33pm2_T	2147483631uL
#define	MAX_s28p3_Ts32pm1_T	2147483639uL
#define	MAX_s28p3_Ts31p0_T	2147483643uL
#define	MAX_s28p3_Ts30p1_T	2147483645uL
#define	MAX_s28p3_Ts29p2_T	2147483646uL
#define	MAX_s32pm1_Ts33pm2_T	2147483646uL
#define	MAX_s31p0_Ts33pm2_T	2147483645uL
#define	MAX_s31p0_Ts32pm1_T	2147483646uL
#define	MAX_s27p4_Ts33pm2_T	2147483615uL
#define	MAX_s27p4_Ts32pm1_T	2147483631uL
#define	MAX_s27p4_Ts31p0_T	2147483639uL
#define	MAX_s27p4_Ts30p1_T	2147483643uL
#define	MAX_s27p4_Ts29p2_T	2147483645uL
#define	MAX_s27p4_Ts28p3_T	2147483646uL
#define	MAX_s23p8_Ts33pm2_T	2147483135uL
#define	MAX_s23p8_Ts32pm1_T	2147483391uL
#define	MAX_s23p8_Ts31p0_T	2147483519uL
#define	MAX_s23p8_Ts30p1_T	2147483583uL
#define	MAX_s23p8_Ts29p2_T	2147483615uL
#define	MAX_s23p8_Ts28p3_T	2147483631uL
#define	MAX_s23p8_Ts27p4_T	2147483639uL
#define	MAX_s23p8_Ts26p5_T	2147483643uL
#define	MAX_s23p8_Ts25p6_T	2147483645uL
#define	MAX_s23p8_Ts24p7_T	2147483646uL
#define	MAX_s19p12_Ts33pm2_T	2147475455uL
#define	MAX_s19p12_Ts32pm1_T	2147479551uL
#define	MAX_s19p12_Ts31p0_T	2147481599uL
#define	MAX_s19p12_Ts30p1_T	2147482623uL
#define	MAX_s19p12_Ts29p2_T	2147483135uL
#define	MAX_s19p12_Ts28p3_T	2147483391uL
#define	MAX_s19p12_Ts27p4_T	2147483519uL
#define	MAX_s19p12_Ts26p5_T	2147483583uL
#define	MAX_s19p12_Ts25p6_T	2147483615uL
#define	MAX_s19p12_Ts24p7_T	2147483631uL
#define	MAX_s19p12_Ts23p8_T	2147483639uL
#define	MAX_s19p12_Ts22p9_T	2147483643uL
#define	MAX_s19p12_Ts21p10_T	2147483645uL
#define	MAX_s19p12_Ts20p11_T	2147483646uL
#define	MAX_s15p16_Ts33pm2_T	2147352575uL
#define	MAX_s15p16_Ts32pm1_T	2147418111uL
#define	MAX_s15p16_Ts31p0_T	2147450879uL
#define	MAX_s15p16_Ts30p1_T	2147467263uL
#define	MAX_s15p16_Ts29p2_T	2147475455uL
#define	MAX_s15p16_Ts28p3_T	2147479551uL
#define	MAX_s15p16_Ts27p4_T	2147481599uL
#define	MAX_s15p16_Ts26p5_T	2147482623uL
#define	MAX_s15p16_Ts25p6_T	2147483135uL
#define	MAX_s15p16_Ts24p7_T	2147483391uL
#define	MAX_s15p16_Ts23p8_T	2147483519uL
#define	MAX_s15p16_Ts22p9_T	2147483583uL
#define	MAX_s15p16_Ts21p10_T	2147483615uL
#define	MAX_s15p16_Ts20p11_T	2147483631uL
#define	MAX_s15p16_Ts19p12_T	2147483639uL
#define	MAX_s15p16_Ts18p13_T	2147483643uL
#define	MAX_s15p16_Ts17p14_T	2147483645uL
#define	MAX_s15p16_Ts16p15_T	2147483646uL
#define	MAX_s11p20_Ts33pm2_T	2145386495uL
#define	MAX_s11p20_Ts32pm1_T	2146435071uL
#define	MAX_s11p20_Ts31p0_T	2146959359uL
#define	MAX_s11p20_Ts30p1_T	2147221503uL
#define	MAX_s11p20_Ts29p2_T	2147352575uL
#define	MAX_s11p20_Ts28p3_T	2147418111uL
#define	MAX_s11p20_Ts27p4_T	2147450879uL
#define	MAX_s11p20_Ts26p5_T	2147467263uL
#define	MAX_s11p20_Ts25p6_T	2147475455uL
#define	MAX_s11p20_Ts24p7_T	2147479551uL
#define	MAX_s11p20_Ts23p8_T	2147481599uL
#define	MAX_s11p20_Ts22p9_T	2147482623uL
#define	MAX_s11p20_Ts21p10_T	2147483135uL
#define	MAX_s11p20_Ts20p11_T	2147483391uL
#define	MAX_s11p20_Ts19p12_T	2147483519uL
#define	MAX_s11p20_Ts18p13_T	2147483583uL
#define	MAX_s11p20_Ts17p14_T	2147483615uL
#define	MAX_s11p20_Ts16p15_T	2147483631uL
#define	MAX_s11p20_Ts15p16_T	2147483639uL
#define	MAX_s11p20_Ts14p17_T	2147483643uL
#define	MAX_s11p20_Ts13p18_T	2147483645uL
#define	MAX_s11p20_Ts12p19_T	2147483646uL
#define	MAX_s7p24_Ts33pm2_T	2113929215uL
#define	MAX_s7p24_Ts32pm1_T	2130706431uL
#define	MAX_s7p24_Ts31p0_T	2139095039uL
#define	MAX_s7p24_Ts30p1_T	2143289343uL
#define	MAX_s7p24_Ts29p2_T	2145386495uL
#define	MAX_s7p24_Ts28p3_T	2146435071uL
#define	MAX_s7p24_Ts27p4_T	2146959359uL
#define	MAX_s7p24_Ts26p5_T	2147221503uL
#define	MAX_s7p24_Ts25p6_T	2147352575uL
#define	MAX_s7p24_Ts24p7_T	2147418111uL
#define	MAX_s7p24_Ts23p8_T	2147450879uL
#define	MAX_s7p24_Ts22p9_T	2147467263uL
#define	MAX_s7p24_Ts21p10_T	2147475455uL
#define	MAX_s7p24_Ts20p11_T	2147479551uL
#define	MAX_s7p24_Ts19p12_T	2147481599uL
#define	MAX_s7p24_Ts18p13_T	2147482623uL
#define	MAX_s7p24_Ts17p14_T	2147483135uL
#define	MAX_s7p24_Ts16p15_T	2147483391uL
#define	MAX_s7p24_Ts15p16_T	2147483519uL
#define	MAX_s7p24_Ts14p17_T	2147483583uL
#define	MAX_s7p24_Ts13p18_T	2147483615uL
#define	MAX_s7p24_Ts12p19_T	2147483631uL
#define	MAX_s7p24_Ts11p20_T	2147483639uL
#define	MAX_s7p24_Ts10p21_T	2147483643uL
#define	MAX_s7p24_Ts9p22_T	2147483645uL
#define	MAX_s7p24_Ts8p23_T	2147483646uL
#define	MAX_s3p28_Ts33pm2_T	1610612735uL
#define	MAX_s3p28_Ts32pm1_T	1879048191uL
#define	MAX_s3p28_Ts31p0_T	2013265919uL
#define	MAX_s3p28_Ts30p1_T	2080374783uL
#define	MAX_s3p28_Ts29p2_T	2113929215uL
#define	MAX_s3p28_Ts28p3_T	2130706431uL
#define	MAX_s3p28_Ts27p4_T	2139095039uL
#define	MAX_s3p28_Ts26p5_T	2143289343uL
#define	MAX_s3p28_Ts25p6_T	2145386495uL
#define	MAX_s3p28_Ts24p7_T	2146435071uL
#define	MAX_s3p28_Ts23p8_T	2146959359uL
#define	MAX_s3p28_Ts22p9_T	2147221503uL
#define	MAX_s3p28_Ts21p10_T	2147352575uL
#define	MAX_s3p28_Ts20p11_T	2147418111uL
#define	MAX_s3p28_Ts19p12_T	2147450879uL
#define	MAX_s3p28_Ts18p13_T	2147467263uL
#define	MAX_s3p28_Ts17p14_T	2147475455uL
#define	MAX_s3p28_Ts16p15_T	2147479551uL
#define	MAX_s3p28_Ts15p16_T	2147481599uL
#define	MAX_s3p28_Ts14p17_T	2147482623uL
#define	MAX_s3p28_Ts13p18_T	2147483135uL
#define	MAX_s3p28_Ts12p19_T	2147483391uL
#define	MAX_s3p28_Ts11p20_T	2147483519uL
#define	MAX_s3p28_Ts10p21_T	2147483583uL
#define	MAX_s3p28_Ts9p22_T	2147483615uL
#define	MAX_s3p28_Ts8p23_T	2147483631uL
#define	MAX_s3p28_Ts7p24_T	2147483639uL
#define	MAX_s3p28_Ts6p25_T	2147483643uL
#define	MAX_s3p28_Ts5p26_T	2147483645uL
#define	MAX_s3p28_Ts4p27_T	2147483646uL
#define	MAX_sm1p32_Ts30p1_T	1073741823uL
#define	MAX_sm1p32_Ts29p2_T	1610612735uL
#define	MAX_sm1p32_Ts28p3_T	1879048191uL
#define	MAX_sm1p32_Ts27p4_T	2013265919uL
#define	MAX_sm1p32_Ts26p5_T	2080374783uL
#define	MAX_sm1p32_Ts25p6_T	2113929215uL
#define	MAX_sm1p32_Ts24p7_T	2130706431uL
#define	MAX_sm1p32_Ts23p8_T	2139095039uL
#define	MAX_sm1p32_Ts22p9_T	2143289343uL
#define	MAX_sm1p32_Ts21p10_T	2145386495uL
#define	MAX_sm1p32_Ts20p11_T	2146435071uL
#define	MAX_sm1p32_Ts19p12_T	2146959359uL
#define	MAX_sm1p32_Ts18p13_T	2147221503uL
#define	MAX_sm1p32_Ts17p14_T	2147352575uL
#define	MAX_sm1p32_Ts16p15_T	2147418111uL
#define	MAX_sm1p32_Ts15p16_T	2147450879uL
#define	MAX_sm1p32_Ts14p17_T	2147467263uL
#define	MAX_sm1p32_Ts13p18_T	2147475455uL
#define	MAX_sm1p32_Ts12p19_T	2147479551uL
#define	MAX_sm1p32_Ts11p20_T	2147481599uL
#define	MAX_sm1p32_Ts10p21_T	2147482623uL
#define	MAX_sm1p32_Ts9p22_T	2147483135uL
#define	MAX_sm1p32_Ts8p23_T	2147483391uL
#define	MAX_sm1p32_Ts7p24_T	2147483519uL
#define	MAX_sm1p32_Ts6p25_T	2147483583uL
#define	MAX_sm1p32_Ts5p26_T	2147483615uL
#define	MAX_sm1p32_Ts4p27_T	2147483631uL
#define	MAX_sm1p32_Ts3p28_T	2147483639uL
#define	MAX_sm1p32_Ts2p29_T	2147483643uL
#define	MAX_sm1p32_Ts1p30_T	2147483645uL
#define	MAX_sm1p32_Ts0p31_T	2147483646uL
#define	MAX_s30p1_Ts33pm2_T	2147483643uL
#define	MAX_s30p1_Ts32pm1_T	2147483645uL
#define	MAX_s30p1_Ts31p0_T	2147483646uL
#define	MAX_s26p5_Ts33pm2_T	2147483583uL
#define	MAX_s26p5_Ts32pm1_T	2147483615uL
#define	MAX_s26p5_Ts31p0_T	2147483631uL
#define	MAX_s26p5_Ts30p1_T	2147483639uL
#define	MAX_s26p5_Ts29p2_T	2147483643uL
#define	MAX_s26p5_Ts28p3_T	2147483645uL
#define	MAX_s26p5_Ts27p4_T	2147483646uL
#define	MAX_s22p9_Ts33pm2_T	2147482623uL
#define	MAX_s22p9_Ts32pm1_T	2147483135uL
#define	MAX_s22p9_Ts31p0_T	2147483391uL
#define	MAX_s22p9_Ts30p1_T	2147483519uL
#define	MAX_s22p9_Ts29p2_T	2147483583uL
#define	MAX_s22p9_Ts28p3_T	2147483615uL
#define	MAX_s22p9_Ts27p4_T	2147483631uL
#define	MAX_s22p9_Ts26p5_T	2147483639uL
#define	MAX_s22p9_Ts25p6_T	2147483643uL
#define	MAX_s22p9_Ts24p7_T	2147483645uL
#define	MAX_s22p9_Ts23p8_T	2147483646uL
#define	MAX_s18p13_Ts33pm2_T	2147467263uL
#define	MAX_s18p13_Ts32pm1_T	2147475455uL
#define	MAX_s18p13_Ts31p0_T	2147479551uL
#define	MAX_s18p13_Ts30p1_T	2147481599uL
#define	MAX_s18p13_Ts29p2_T	2147482623uL
#define	MAX_s18p13_Ts28p3_T	2147483135uL
#define	MAX_s18p13_Ts27p4_T	2147483391uL
#define	MAX_s18p13_Ts26p5_T	2147483519uL
#define	MAX_s18p13_Ts25p6_T	2147483583uL
#define	MAX_s18p13_Ts24p7_T	2147483615uL
#define	MAX_s18p13_Ts23p8_T	2147483631uL
#define	MAX_s18p13_Ts22p9_T	2147483639uL
#define	MAX_s18p13_Ts21p10_T	2147483643uL
#define	MAX_s18p13_Ts20p11_T	2147483645uL
#define	MAX_s18p13_Ts19p12_T	2147483646uL
#define	MAX_s14p17_Ts33pm2_T	2147221503uL
#define	MAX_s14p17_Ts32pm1_T	2147352575uL
#define	MAX_s14p17_Ts31p0_T	2147418111uL
#define	MAX_s14p17_Ts30p1_T	2147450879uL
#define	MAX_s14p17_Ts29p2_T	2147467263uL
#define	MAX_s14p17_Ts28p3_T	2147475455uL
#define	MAX_s14p17_Ts27p4_T	2147479551uL
#define	MAX_s14p17_Ts26p5_T	2147481599uL
#define	MAX_s14p17_Ts25p6_T	2147482623uL
#define	MAX_s14p17_Ts24p7_T	2147483135uL
#define	MAX_s14p17_Ts23p8_T	2147483391uL
#define	MAX_s14p17_Ts22p9_T	2147483519uL
#define	MAX_s14p17_Ts21p10_T	2147483583uL
#define	MAX_s14p17_Ts20p11_T	2147483615uL
#define	MAX_s14p17_Ts19p12_T	2147483631uL
#define	MAX_s14p17_Ts18p13_T	2147483639uL
#define	MAX_s14p17_Ts17p14_T	2147483643uL
#define	MAX_s14p17_Ts16p15_T	2147483645uL
#define	MAX_s14p17_Ts15p16_T	2147483646uL
#define	MAX_s14p17_Ts7p8_T	16776959uL
#define	MAX_s10p21_Ts33pm2_T	2143289343uL
#define	MAX_s10p21_Ts32pm1_T	2145386495uL
#define	MAX_s10p21_Ts31p0_T	2146435071uL
#define	MAX_s10p21_Ts30p1_T	2146959359uL
#define	MAX_s10p21_Ts29p2_T	2147221503uL
#define	MAX_s10p21_Ts28p3_T	2147352575uL
#define	MAX_s10p21_Ts27p4_T	2147418111uL
#define	MAX_s10p21_Ts26p5_T	2147450879uL
#define	MAX_s10p21_Ts25p6_T	2147467263uL
#define	MAX_s10p21_Ts24p7_T	2147475455uL
#define	MAX_s10p21_Ts23p8_T	2147479551uL
#define	MAX_s10p21_Ts22p9_T	2147481599uL
#define	MAX_s10p21_Ts21p10_T	2147482623uL
#define	MAX_s10p21_Ts20p11_T	2147483135uL
#define	MAX_s10p21_Ts19p12_T	2147483391uL
#define	MAX_s10p21_Ts18p13_T	2147483519uL
#define	MAX_s10p21_Ts17p14_T	2147483583uL
#define	MAX_s10p21_Ts16p15_T	2147483615uL
#define	MAX_s10p21_Ts15p16_T	2147483631uL
#define	MAX_s10p21_Ts14p17_T	2147483639uL
#define	MAX_s10p21_Ts13p18_T	2147483643uL
#define	MAX_s10p21_Ts12p19_T	2147483645uL
#define	MAX_s10p21_Ts11p20_T	2147483646uL
#define	MAX_s6p25_Ts33pm2_T	2080374783uL
#define	MAX_s6p25_Ts32pm1_T	2113929215uL
#define	MAX_s6p25_Ts31p0_T	2130706431uL
#define	MAX_s6p25_Ts30p1_T	2139095039uL
#define	MAX_s6p25_Ts29p2_T	2143289343uL
#define	MAX_s6p25_Ts28p3_T	2145386495uL
#define	MAX_s6p25_Ts27p4_T	2146435071uL
#define	MAX_s6p25_Ts26p5_T	2146959359uL
#define	MAX_s6p25_Ts25p6_T	2147221503uL
#define	MAX_s6p25_Ts24p7_T	2147352575uL
#define	MAX_s6p25_Ts23p8_T	2147418111uL
#define	MAX_s6p25_Ts22p9_T	2147450879uL
#define	MAX_s6p25_Ts21p10_T	2147467263uL
#define	MAX_s6p25_Ts20p11_T	2147475455uL
#define	MAX_s6p25_Ts19p12_T	2147479551uL
#define	MAX_s6p25_Ts18p13_T	2147481599uL
#define	MAX_s6p25_Ts17p14_T	2147482623uL
#define	MAX_s6p25_Ts16p15_T	2147483135uL
#define	MAX_s6p25_Ts15p16_T	2147483391uL
#define	MAX_s6p25_Ts14p17_T	2147483519uL
#define	MAX_s6p25_Ts13p18_T	2147483583uL
#define	MAX_s6p25_Ts12p19_T	2147483615uL
#define	MAX_s6p25_Ts11p20_T	2147483631uL
#define	MAX_s6p25_Ts10p21_T	2147483639uL
#define	MAX_s6p25_Ts9p22_T	2147483643uL
#define	MAX_s6p25_Ts8p23_T	2147483645uL
#define	MAX_s6p25_Ts7p24_T	2147483646uL
#define	MAX_s2p29_Ts33pm2_T	1073741823uL
#define	MAX_s2p29_Ts32pm1_T	1610612735uL
#define	MAX_s2p29_Ts31p0_T	1879048191uL
#define	MAX_s2p29_Ts30p1_T	2013265919uL
#define	MAX_s2p29_Ts29p2_T	2080374783uL
#define	MAX_s2p29_Ts28p3_T	2113929215uL
#define	MAX_s2p29_Ts27p4_T	2130706431uL
#define	MAX_s2p29_Ts26p5_T	2139095039uL
#define	MAX_s2p29_Ts25p6_T	2143289343uL
#define	MAX_s2p29_Ts24p7_T	2145386495uL
#define	MAX_s2p29_Ts23p8_T	2146435071uL
#define	MAX_s2p29_Ts22p9_T	2146959359uL
#define	MAX_s2p29_Ts21p10_T	2147221503uL
#define	MAX_s2p29_Ts20p11_T	2147352575uL
#define	MAX_s2p29_Ts19p12_T	2147418111uL
#define	MAX_s2p29_Ts18p13_T	2147450879uL
#define	MAX_s2p29_Ts17p14_T	2147467263uL
#define	MAX_s2p29_Ts16p15_T	2147475455uL
#define	MAX_s2p29_Ts15p16_T	2147479551uL
#define	MAX_s2p29_Ts14p17_T	2147481599uL
#define	MAX_s2p29_Ts13p18_T	2147482623uL
#define	MAX_s2p29_Ts12p19_T	2147483135uL
#define	MAX_s2p29_Ts11p20_T	2147483391uL
#define	MAX_s2p29_Ts10p21_T	2147483519uL
#define	MAX_s2p29_Ts9p22_T	2147483583uL
#define	MAX_s2p29_Ts8p23_T	2147483615uL
#define	MAX_s2p29_Ts7p24_T	2147483631uL
#define	MAX_s2p29_Ts6p25_T	2147483639uL
#define	MAX_s2p29_Ts5p26_T	2147483643uL
#define	MAX_s2p29_Ts4p27_T	2147483645uL
#define	MAX_s2p29_Ts3p28_T	2147483646uL
#define	MAX_sm2p33_Ts29p2_T	1073741823uL
#define	MAX_sm2p33_Ts28p3_T	1610612735uL
#define	MAX_sm2p33_Ts27p4_T	1879048191uL
#define	MAX_sm2p33_Ts26p5_T	2013265919uL
#define	MAX_sm2p33_Ts25p6_T	2080374783uL
#define	MAX_sm2p33_Ts24p7_T	2113929215uL
#define	MAX_sm2p33_Ts23p8_T	2130706431uL
#define	MAX_sm2p33_Ts22p9_T	2139095039uL
#define	MAX_sm2p33_Ts21p10_T	2143289343uL
#define	MAX_sm2p33_Ts20p11_T	2145386495uL
#define	MAX_sm2p33_Ts19p12_T	2146435071uL
#define	MAX_sm2p33_Ts18p13_T	2146959359uL
#define	MAX_sm2p33_Ts17p14_T	2147221503uL
#define	MAX_sm2p33_Ts16p15_T	2147352575uL
#define	MAX_sm2p33_Ts15p16_T	2147418111uL
#define	MAX_sm2p33_Ts14p17_T	2147450879uL
#define	MAX_sm2p33_Ts13p18_T	2147467263uL
#define	MAX_sm2p33_Ts12p19_T	2147475455uL
#define	MAX_sm2p33_Ts11p20_T	2147479551uL
#define	MAX_sm2p33_Ts10p21_T	2147481599uL
#define	MAX_sm2p33_Ts9p22_T	2147482623uL
#define	MAX_sm2p33_Ts8p23_T	2147483135uL
#define	MAX_sm2p33_Ts7p24_T	2147483391uL
#define	MAX_sm2p33_Ts6p25_T	2147483519uL
#define	MAX_sm2p33_Ts5p26_T	2147483583uL
#define	MAX_sm2p33_Ts4p27_T	2147483615uL
#define	MAX_sm2p33_Ts3p28_T	2147483631uL
#define	MAX_sm2p33_Ts2p29_T	2147483639uL
#define	MAX_sm2p33_Ts1p30_T	2147483643uL
#define	MAX_sm2p33_Ts0p31_T	2147483645uL
#define	MAX_sm2p33_Tsm1p32_T	2147483646uL
		
#define	MAX_u30p2_Tu34pm2_T	4294967287uL
#define	MAX_u30p2_Tu33pm1_T	4294967291uL
#define	MAX_u30p2_Tu32p0_T	4294967293uL
#define	MAX_u30p2_Tu31p1_T	4294967294uL
#define	MAX_u26p6_Tu34pm2_T	4294967167uL
#define	MAX_u26p6_Tu33pm1_T	4294967231uL
#define	MAX_u26p6_Tu32p0_T	4294967263uL
#define	MAX_u26p6_Tu31p1_T	4294967279uL
#define	MAX_u26p6_Tu30p2_T	4294967287uL
#define	MAX_u26p6_Tu29p3_T	4294967291uL
#define	MAX_u26p6_Tu28p4_T	4294967293uL
#define	MAX_u26p6_Tu27p5_T	4294967294uL
#define	MAX_u22p10_Tu34pm2_T	4294965247uL
#define	MAX_u22p10_Tu33pm1_T	4294966271uL
#define	MAX_u22p10_Tu32p0_T	4294966783uL
#define	MAX_u22p10_Tu31p1_T	4294967039uL
#define	MAX_u22p10_Tu30p2_T	4294967167uL
#define	MAX_u22p10_Tu29p3_T	4294967231uL
#define	MAX_u22p10_Tu28p4_T	4294967263uL
#define	MAX_u22p10_Tu27p5_T	4294967279uL
#define	MAX_u22p10_Tu26p6_T	4294967287uL
#define	MAX_u22p10_Tu25p7_T	4294967291uL
#define	MAX_u22p10_Tu24p8_T	4294967293uL
#define	MAX_u22p10_Tu23p9_T	4294967294uL
#define	MAX_u18p14_Tu34pm2_T	4294934527uL
#define	MAX_u18p14_Tu33pm1_T	4294950911uL
#define	MAX_u18p14_Tu32p0_T	4294959103uL
#define	MAX_u18p14_Tu31p1_T	4294963199uL
#define	MAX_u18p14_Tu30p2_T	4294965247uL
#define	MAX_u18p14_Tu29p3_T	4294966271uL
#define	MAX_u18p14_Tu28p4_T	4294966783uL
#define	MAX_u18p14_Tu27p5_T	4294967039uL
#define	MAX_u18p14_Tu26p6_T	4294967167uL
#define	MAX_u18p14_Tu25p7_T	4294967231uL
#define	MAX_u18p14_Tu24p8_T	4294967263uL
#define	MAX_u18p14_Tu23p9_T	4294967279uL
#define	MAX_u18p14_Tu22p10_T	4294967287uL
#define	MAX_u18p14_Tu21p11_T	4294967291uL
#define	MAX_u18p14_Tu20p12_T	4294967293uL
#define	MAX_u18p14_Tu19p13_T	4294967294uL
#define	MAX_u14p18_Tu34pm2_T	4294443007uL
#define	MAX_u14p18_Tu33pm1_T	4294705151uL
#define	MAX_u14p18_Tu32p0_T	4294836223uL
#define	MAX_u14p18_Tu31p1_T	4294901759uL
#define	MAX_u14p18_Tu30p2_T	4294934527uL
#define	MAX_u14p18_Tu29p3_T	4294950911uL
#define	MAX_u14p18_Tu28p4_T	4294959103uL
#define	MAX_u14p18_Tu27p5_T	4294963199uL
#define	MAX_u14p18_Tu26p6_T	4294965247uL
#define	MAX_u14p18_Tu25p7_T	4294966271uL
#define	MAX_u14p18_Tu24p8_T	4294966783uL
#define	MAX_u14p18_Tu23p9_T	4294967039uL
#define	MAX_u14p18_Tu22p10_T	4294967167uL
#define	MAX_u14p18_Tu21p11_T	4294967231uL
#define	MAX_u14p18_Tu20p12_T	4294967263uL
#define	MAX_u14p18_Tu19p13_T	4294967279uL
#define	MAX_u14p18_Tu18p14_T	4294967287uL
#define	MAX_u14p18_Tu17p15_T	4294967291uL
#define	MAX_u14p18_Tu16p16_T	4294967293uL
#define	MAX_u14p18_Tu15p17_T	4294967294uL
#define	MAX_u10p22_Tu34pm2_T	4286578687uL
#define	MAX_u10p22_Tu33pm1_T	4290772991uL
#define	MAX_u10p22_Tu32p0_T	4292870143uL
#define	MAX_u10p22_Tu31p1_T	4293918719uL
#define	MAX_u10p22_Tu30p2_T	4294443007uL
#define	MAX_u10p22_Tu29p3_T	4294705151uL
#define	MAX_u10p22_Tu28p4_T	4294836223uL
#define	MAX_u10p22_Tu27p5_T	4294901759uL
#define	MAX_u10p22_Tu26p6_T	4294934527uL
#define	MAX_u10p22_Tu25p7_T	4294950911uL
#define	MAX_u10p22_Tu24p8_T	4294959103uL
#define	MAX_u10p22_Tu23p9_T	4294963199uL
#define	MAX_u10p22_Tu22p10_T	4294965247uL
#define	MAX_u10p22_Tu21p11_T	4294966271uL
#define	MAX_u10p22_Tu20p12_T	4294966783uL
#define	MAX_u10p22_Tu19p13_T	4294967039uL
#define	MAX_u10p22_Tu18p14_T	4294967167uL
#define	MAX_u10p22_Tu17p15_T	4294967231uL
#define	MAX_u10p22_Tu16p16_T	4294967263uL
#define	MAX_u10p22_Tu15p17_T	4294967279uL
#define	MAX_u10p22_Tu14p18_T	4294967287uL
#define	MAX_u10p22_Tu13p19_T	4294967291uL
#define	MAX_u10p22_Tu12p20_T	4294967293uL
#define	MAX_u10p22_Tu11p21_T	4294967294uL
#define	MAX_u6p26_Tu34pm2_T	4160749567uL
#define	MAX_u6p26_Tu33pm1_T	4227858431uL
#define	MAX_u6p26_Tu32p0_T	4261412863uL
#define	MAX_u6p26_Tu31p1_T	4278190079uL
#define	MAX_u6p26_Tu30p2_T	4286578687uL
#define	MAX_u6p26_Tu29p3_T	4290772991uL
#define	MAX_u6p26_Tu28p4_T	4292870143uL
#define	MAX_u6p26_Tu27p5_T	4293918719uL
#define	MAX_u6p26_Tu26p6_T	4294443007uL
#define	MAX_u6p26_Tu25p7_T	4294705151uL
#define	MAX_u6p26_Tu24p8_T	4294836223uL
#define	MAX_u6p26_Tu23p9_T	4294901759uL
#define	MAX_u6p26_Tu22p10_T	4294934527uL
#define	MAX_u6p26_Tu21p11_T	4294950911uL
#define	MAX_u6p26_Tu20p12_T	4294959103uL
#define	MAX_u6p26_Tu19p13_T	4294963199uL
#define	MAX_u6p26_Tu18p14_T	4294965247uL
#define	MAX_u6p26_Tu17p15_T	4294966271uL
#define	MAX_u6p26_Tu16p16_T	4294966783uL
#define	MAX_u6p26_Tu15p17_T	4294967039uL
#define	MAX_u6p26_Tu14p18_T	4294967167uL
#define	MAX_u6p26_Tu13p19_T	4294967231uL
#define	MAX_u6p26_Tu12p20_T	4294967263uL
#define	MAX_u6p26_Tu11p21_T	4294967279uL
#define	MAX_u6p26_Tu10p22_T	4294967287uL
#define	MAX_u6p26_Tu9p23_T	4294967291uL
#define	MAX_u6p26_Tu8p24_T	4294967293uL
#define	MAX_u6p26_Tu7p25_T	4294967294uL
#define	MAX_u6p26_Tum1p17_T	33553664uL
#define	MAX_u2p30_Tu34pm2_T	2147483647uL
#define	MAX_u2p30_Tu33pm1_T	3221225471uL
#define	MAX_u2p30_Tu32p0_T	3758096383uL
#define	MAX_u2p30_Tu31p1_T	4026531839uL
#define	MAX_u2p30_Tu30p2_T	4160749567uL
#define	MAX_u2p30_Tu29p3_T	4227858431uL
#define	MAX_u2p30_Tu28p4_T	4261412863uL
#define	MAX_u2p30_Tu27p5_T	4278190079uL
#define	MAX_u2p30_Tu26p6_T	4286578687uL
#define	MAX_u2p30_Tu25p7_T	4290772991uL
#define	MAX_u2p30_Tu24p8_T	4292870143uL
#define	MAX_u2p30_Tu23p9_T	4293918719uL
#define	MAX_u2p30_Tu22p10_T	4294443007uL
#define	MAX_u2p30_Tu21p11_T	4294705151uL
#define	MAX_u2p30_Tu20p12_T	4294836223uL
#define	MAX_u2p30_Tu19p13_T	4294901759uL
#define	MAX_u2p30_Tu18p14_T	4294934527uL
#define	MAX_u2p30_Tu17p15_T	4294950911uL
#define	MAX_u2p30_Tu16p16_T	4294959103uL
#define	MAX_u2p30_Tu15p17_T	4294963199uL
#define	MAX_u2p30_Tu14p18_T	4294965247uL
#define	MAX_u2p30_Tu13p19_T	4294966271uL
#define	MAX_u2p30_Tu12p20_T	4294966783uL
#define	MAX_u2p30_Tu11p21_T	4294967039uL
#define	MAX_u2p30_Tu10p22_T	4294967167uL
#define	MAX_u2p30_Tu9p23_T	4294967231uL
#define	MAX_u2p30_Tu8p24_T	4294967263uL
#define	MAX_u2p30_Tu7p25_T	4294967279uL
#define	MAX_u2p30_Tu6p26_T	4294967287uL
#define	MAX_u2p30_Tu5p27_T	4294967291uL
#define	MAX_u2p30_Tu4p28_T	4294967293uL
#define	MAX_u2p30_Tu3p29_T	4294967294uL
#define	MAX_u33pm1_Tu34pm2_T	4294967294uL
#define	MAX_u29p3_Tu34pm2_T	4294967279uL
#define	MAX_u29p3_Tu33pm1_T	4294967287uL
#define	MAX_u29p3_Tu32p0_T	4294967291uL
#define	MAX_u29p3_Tu31p1_T	4294967293uL
#define	MAX_u29p3_Tu30p2_T	4294967294uL
#define	MAX_u25p7_Tu34pm2_T	4294967039uL
#define	MAX_u25p7_Tu33pm1_T	4294967167uL
#define	MAX_u25p7_Tu32p0_T	4294967231uL
#define	MAX_u25p7_Tu31p1_T	4294967263uL
#define	MAX_u25p7_Tu30p2_T	4294967279uL
#define	MAX_u25p7_Tu29p3_T	4294967287uL
#define	MAX_u25p7_Tu28p4_T	4294967291uL
#define	MAX_u25p7_Tu27p5_T	4294967293uL
#define	MAX_u25p7_Tu26p6_T	4294967294uL
#define	MAX_u21p11_Tu34pm2_T	4294963199uL
#define	MAX_u21p11_Tu33pm1_T	4294965247uL
#define	MAX_u21p11_Tu32p0_T	4294966271uL
#define	MAX_u21p11_Tu31p1_T	4294966783uL
#define	MAX_u21p11_Tu30p2_T	4294967039uL
#define	MAX_u21p11_Tu29p3_T	4294967167uL
#define	MAX_u21p11_Tu28p4_T	4294967231uL
#define	MAX_u21p11_Tu27p5_T	4294967263uL
#define	MAX_u21p11_Tu26p6_T	4294967279uL
#define	MAX_u21p11_Tu25p7_T	4294967287uL
#define	MAX_u21p11_Tu24p8_T	4294967291uL
#define	MAX_u21p11_Tu23p9_T	4294967293uL
#define	MAX_u21p11_Tu22p10_T	4294967294uL
#define	MAX_u17p15_Tu34pm2_T	4294901759uL
#define	MAX_u17p15_Tu33pm1_T	4294934527uL
#define	MAX_u17p15_Tu32p0_T	4294950911uL
#define	MAX_u17p15_Tu31p1_T	4294959103uL
#define	MAX_u17p15_Tu30p2_T	4294963199uL
#define	MAX_u17p15_Tu29p3_T	4294965247uL
#define	MAX_u17p15_Tu28p4_T	4294966271uL
#define	MAX_u17p15_Tu27p5_T	4294966783uL
#define	MAX_u17p15_Tu26p6_T	4294967039uL
#define	MAX_u17p15_Tu25p7_T	4294967167uL
#define	MAX_u17p15_Tu24p8_T	4294967231uL
#define	MAX_u17p15_Tu23p9_T	4294967263uL
#define	MAX_u17p15_Tu22p10_T	4294967279uL
#define	MAX_u17p15_Tu21p11_T	4294967287uL
#define	MAX_u17p15_Tu20p12_T	4294967291uL
#define	MAX_u17p15_Tu19p13_T	4294967293uL
#define	MAX_u17p15_Tu18p14_T	4294967294uL
#define	MAX_u13p19_Tu34pm2_T	4293918719uL
#define	MAX_u13p19_Tu33pm1_T	4294443007uL
#define	MAX_u13p19_Tu32p0_T	4294705151uL
#define	MAX_u13p19_Tu31p1_T	4294836223uL
#define	MAX_u13p19_Tu30p2_T	4294901759uL
#define	MAX_u13p19_Tu29p3_T	4294934527uL
#define	MAX_u13p19_Tu28p4_T	4294950911uL
#define	MAX_u13p19_Tu27p5_T	4294959103uL
#define	MAX_u13p19_Tu26p6_T	4294963199uL
#define	MAX_u13p19_Tu25p7_T	4294965247uL
#define	MAX_u13p19_Tu24p8_T	4294966271uL
#define	MAX_u13p19_Tu23p9_T	4294966783uL
#define	MAX_u13p19_Tu22p10_T	4294967039uL
#define	MAX_u13p19_Tu21p11_T	4294967167uL
#define	MAX_u13p19_Tu20p12_T	4294967231uL
#define	MAX_u13p19_Tu19p13_T	4294967263uL
#define	MAX_u13p19_Tu18p14_T	4294967279uL
#define	MAX_u13p19_Tu17p15_T	4294967287uL
#define	MAX_u13p19_Tu16p16_T	4294967291uL
#define	MAX_u13p19_Tu15p17_T	4294967293uL
#define	MAX_u13p19_Tu14p18_T	4294967294uL
#define	MAX_u9p23_Tu34pm2_T	4278190079uL
#define	MAX_u9p23_Tu33pm1_T	4286578687uL
#define	MAX_u9p23_Tu32p0_T	4290772991uL
#define	MAX_u9p23_Tu31p1_T	4292870143uL
#define	MAX_u9p23_Tu30p2_T	4293918719uL
#define	MAX_u9p23_Tu29p3_T	4294443007uL
#define	MAX_u9p23_Tu28p4_T	4294705151uL
#define	MAX_u9p23_Tu27p5_T	4294836223uL
#define	MAX_u9p23_Tu26p6_T	4294901759uL
#define	MAX_u9p23_Tu25p7_T	4294934527uL
#define	MAX_u9p23_Tu24p8_T	4294950911uL
#define	MAX_u9p23_Tu23p9_T	4294959103uL
#define	MAX_u9p23_Tu22p10_T	4294963199uL
#define	MAX_u9p23_Tu21p11_T	4294965247uL
#define	MAX_u9p23_Tu20p12_T	4294966271uL
#define	MAX_u9p23_Tu19p13_T	4294966783uL
#define	MAX_u9p23_Tu18p14_T	4294967039uL
#define	MAX_u9p23_Tu17p15_T	4294967167uL
#define	MAX_u9p23_Tu16p16_T	4294967231uL
#define	MAX_u9p23_Tu15p17_T	4294967263uL
#define	MAX_u9p23_Tu14p18_T	4294967279uL
#define	MAX_u9p23_Tu13p19_T	4294967287uL
#define	MAX_u9p23_Tu12p20_T	4294967291uL
#define	MAX_u9p23_Tu11p21_T	4294967293uL
#define	MAX_u9p23_Tu10p22_T	4294967294uL
#define	MAX_u5p27_Tu34pm2_T	4026531839uL
#define	MAX_u5p27_Tu33pm1_T	4160749567uL
#define	MAX_u5p27_Tu32p0_T	4227858431uL
#define	MAX_u5p27_Tu31p1_T	4261412863uL
#define	MAX_u5p27_Tu30p2_T	4278190079uL
#define	MAX_u5p27_Tu29p3_T	4286578687uL
#define	MAX_u5p27_Tu28p4_T	4290772991uL
#define	MAX_u5p27_Tu27p5_T	4292870143uL
#define	MAX_u5p27_Tu26p6_T	4293918719uL
#define	MAX_u5p27_Tu25p7_T	4294443007uL
#define	MAX_u5p27_Tu24p8_T	4294705151uL
#define	MAX_u5p27_Tu23p9_T	4294836223uL
#define	MAX_u5p27_Tu22p10_T	4294901759uL
#define	MAX_u5p27_Tu21p11_T	4294934527uL
#define	MAX_u5p27_Tu20p12_T	4294950911uL
#define	MAX_u5p27_Tu19p13_T	4294959103uL
#define	MAX_u5p27_Tu18p14_T	4294963199uL
#define	MAX_u5p27_Tu17p15_T	4294965247uL
#define	MAX_u5p27_Tu16p16_T	4294966271uL
#define	MAX_u5p27_Tu15p17_T	4294966783uL
#define	MAX_u5p27_Tu14p18_T	4294967039uL
#define	MAX_u5p27_Tu13p19_T	4294967167uL
#define	MAX_u5p27_Tu12p20_T	4294967231uL
#define	MAX_u5p27_Tu11p21_T	4294967263uL
#define	MAX_u5p27_Tu10p22_T	4294967279uL
#define	MAX_u5p27_Tu9p23_T	4294967287uL
#define	MAX_u5p27_Tu8p24_T	4294967291uL
#define	MAX_u5p27_Tu7p25_T	4294967293uL
#define	MAX_u5p27_Tu6p26_T	4294967294uL
#define	MAX_u1p31_Tu33pm1_T	2147483647uL
#define	MAX_u1p31_Tu32p0_T	3221225471uL
#define	MAX_u1p31_Tu31p1_T	3758096383uL
#define	MAX_u1p31_Tu30p2_T	4026531839uL
#define	MAX_u1p31_Tu29p3_T	4160749567uL
#define	MAX_u1p31_Tu28p4_T	4227858431uL
#define	MAX_u1p31_Tu27p5_T	4261412863uL
#define	MAX_u1p31_Tu26p6_T	4278190079uL
#define	MAX_u1p31_Tu25p7_T	4286578687uL
#define	MAX_u1p31_Tu24p8_T	4290772991uL
#define	MAX_u1p31_Tu23p9_T	4292870143uL
#define	MAX_u1p31_Tu22p10_T	4293918719uL
#define	MAX_u1p31_Tu21p11_T	4294443007uL
#define	MAX_u1p31_Tu20p12_T	4294705151uL
#define	MAX_u1p31_Tu19p13_T	4294836223uL
#define	MAX_u1p31_Tu18p14_T	4294901759uL
#define	MAX_u1p31_Tu17p15_T	4294934527uL
#define	MAX_u1p31_Tu16p16_T	4294950911uL
#define	MAX_u1p31_Tu15p17_T	4294959103uL
#define	MAX_u1p31_Tu14p18_T	4294963199uL
#define	MAX_u1p31_Tu13p19_T	4294965247uL
#define	MAX_u1p31_Tu12p20_T	4294966271uL
#define	MAX_u1p31_Tu11p21_T	4294966783uL
#define	MAX_u1p31_Tu10p22_T	4294967039uL
#define	MAX_u1p31_Tu9p23_T	4294967167uL
#define	MAX_u1p31_Tu8p24_T	4294967231uL
#define	MAX_u1p31_Tu7p25_T	4294967263uL
#define	MAX_u1p31_Tu6p26_T	4294967279uL
#define	MAX_u1p31_Tu5p27_T	4294967287uL
#define	MAX_u1p31_Tu4p28_T	4294967291uL
#define	MAX_u1p31_Tu3p29_T	4294967293uL
#define	MAX_u1p31_Tu2p30_T	4294967294uL
#define	MAX_u32p0_Tu34pm2_T	4294967293uL
#define	MAX_u32p0_Tu33pm1_T	4294967294uL
#define	MAX_u28p4_Tu34pm2_T	4294967263uL
#define	MAX_u28p4_Tu33pm1_T	4294967279uL
#define	MAX_u28p4_Tu32p0_T	4294967287uL
#define	MAX_u28p4_Tu31p1_T	4294967291uL
#define	MAX_u28p4_Tu30p2_T	4294967293uL
#define	MAX_u28p4_Tu29p3_T	4294967294uL
#define	MAX_u24p8_Tu34pm2_T	4294966783uL
#define	MAX_u24p8_Tu33pm1_T	4294967039uL
#define	MAX_u24p8_Tu32p0_T	4294967167uL
#define	MAX_u24p8_Tu31p1_T	4294967231uL
#define	MAX_u24p8_Tu30p2_T	4294967263uL
#define	MAX_u24p8_Tu29p3_T	4294967279uL
#define	MAX_u24p8_Tu28p4_T	4294967287uL
#define	MAX_u24p8_Tu27p5_T	4294967291uL
#define	MAX_u24p8_Tu26p6_T	4294967293uL
#define	MAX_u24p8_Tu25p7_T	4294967294uL
#define	MAX_u20p12_Tu34pm2_T	4294959103uL
#define	MAX_u20p12_Tu33pm1_T	4294963199uL
#define	MAX_u20p12_Tu32p0_T	4294965247uL
#define	MAX_u20p12_Tu31p1_T	4294966271uL
#define	MAX_u20p12_Tu30p2_T	4294966783uL
#define	MAX_u20p12_Tu29p3_T	4294967039uL
#define	MAX_u20p12_Tu28p4_T	4294967167uL
#define	MAX_u20p12_Tu27p5_T	4294967231uL
#define	MAX_u20p12_Tu26p6_T	4294967263uL
#define	MAX_u20p12_Tu25p7_T	4294967279uL
#define	MAX_u20p12_Tu24p8_T	4294967287uL
#define	MAX_u20p12_Tu23p9_T	4294967291uL
#define	MAX_u20p12_Tu22p10_T	4294967293uL
#define	MAX_u20p12_Tu21p11_T	4294967294uL
#define	MAX_u16p16_Tu34pm2_T	4294836223uL
#define	MAX_u16p16_Tu33pm1_T	4294901759uL
#define	MAX_u16p16_Tu32p0_T	4294934527uL
#define	MAX_u16p16_Tu31p1_T	4294950911uL
#define	MAX_u16p16_Tu30p2_T	4294959103uL
#define	MAX_u16p16_Tu29p3_T	4294963199uL
#define	MAX_u16p16_Tu28p4_T	4294965247uL
#define	MAX_u16p16_Tu27p5_T	4294966271uL
#define	MAX_u16p16_Tu26p6_T	4294966783uL
#define	MAX_u16p16_Tu25p7_T	4294967039uL
#define	MAX_u16p16_Tu24p8_T	4294967167uL
#define	MAX_u16p16_Tu23p9_T	4294967231uL
#define	MAX_u16p16_Tu22p10_T	4294967263uL
#define	MAX_u16p16_Tu21p11_T	4294967279uL
#define	MAX_u16p16_Tu20p12_T	4294967287uL
#define	MAX_u16p16_Tu19p13_T	4294967291uL
#define	MAX_u16p16_Tu18p14_T	4294967293uL
#define	MAX_u16p16_Tu17p15_T	4294967294uL
#define	MAX_u12p20_Tu34pm2_T	4292870143uL
#define	MAX_u12p20_Tu33pm1_T	4293918719uL
#define	MAX_u12p20_Tu32p0_T	4294443007uL
#define	MAX_u12p20_Tu31p1_T	4294705151uL
#define	MAX_u12p20_Tu30p2_T	4294836223uL
#define	MAX_u12p20_Tu29p3_T	4294901759uL
#define	MAX_u12p20_Tu28p4_T	4294934527uL
#define	MAX_u12p20_Tu27p5_T	4294950911uL
#define	MAX_u12p20_Tu26p6_T	4294959103uL
#define	MAX_u12p20_Tu25p7_T	4294963199uL
#define	MAX_u12p20_Tu24p8_T	4294965247uL
#define	MAX_u12p20_Tu23p9_T	4294966271uL
#define	MAX_u12p20_Tu22p10_T	4294966783uL
#define	MAX_u12p20_Tu21p11_T	4294967039uL
#define	MAX_u12p20_Tu20p12_T	4294967167uL
#define	MAX_u12p20_Tu19p13_T	4294967231uL
#define	MAX_u12p20_Tu18p14_T	4294967263uL
#define	MAX_u12p20_Tu17p15_T	4294967279uL
#define	MAX_u12p20_Tu16p16_T	4294967287uL
#define	MAX_u12p20_Tu15p17_T	4294967291uL
#define	MAX_u12p20_Tu14p18_T	4294967293uL
#define	MAX_u12p20_Tu13p19_T	4294967294uL
#define	MAX_u8p24_Tu34pm2_T	4261412863uL
#define	MAX_u8p24_Tu33pm1_T	4278190079uL
#define	MAX_u8p24_Tu32p0_T	4286578687uL
#define	MAX_u8p24_Tu31p1_T	4290772991uL
#define	MAX_u8p24_Tu30p2_T	4292870143uL
#define	MAX_u8p24_Tu29p3_T	4293918719uL
#define	MAX_u8p24_Tu28p4_T	4294443007uL
#define	MAX_u8p24_Tu27p5_T	4294705151uL
#define	MAX_u8p24_Tu26p6_T	4294836223uL
#define	MAX_u8p24_Tu25p7_T	4294901759uL
#define	MAX_u8p24_Tu24p8_T	4294934527uL
#define	MAX_u8p24_Tu23p9_T	4294950911uL
#define	MAX_u8p24_Tu22p10_T	4294959103uL
#define	MAX_u8p24_Tu21p11_T	4294963199uL
#define	MAX_u8p24_Tu20p12_T	4294965247uL
#define	MAX_u8p24_Tu19p13_T	4294966271uL
#define	MAX_u8p24_Tu18p14_T	4294966783uL
#define	MAX_u8p24_Tu17p15_T	4294967039uL
#define	MAX_u8p24_Tu16p16_T	4294967167uL
#define	MAX_u8p24_Tu15p17_T	4294967231uL
#define	MAX_u8p24_Tu14p18_T	4294967263uL
#define	MAX_u8p24_Tu13p19_T	4294967279uL
#define	MAX_u8p24_Tu12p20_T	4294967287uL
#define	MAX_u8p24_Tu11p21_T	4294967291uL
#define	MAX_u8p24_Tu10p22_T	4294967293uL
#define	MAX_u8p24_Tu9p23_T	4294967294uL
#define	MAX_u4p28_Tu34pm2_T	3758096383uL
#define	MAX_u4p28_Tu33pm1_T	4026531839uL
#define	MAX_u4p28_Tu32p0_T	4160749567uL
#define	MAX_u4p28_Tu31p1_T	4227858431uL
#define	MAX_u4p28_Tu30p2_T	4261412863uL
#define	MAX_u4p28_Tu29p3_T	4278190079uL
#define	MAX_u4p28_Tu28p4_T	4286578687uL
#define	MAX_u4p28_Tu27p5_T	4290772991uL
#define	MAX_u4p28_Tu26p6_T	4292870143uL
#define	MAX_u4p28_Tu25p7_T	4293918719uL
#define	MAX_u4p28_Tu24p8_T	4294443007uL
#define	MAX_u4p28_Tu23p9_T	4294705151uL
#define	MAX_u4p28_Tu22p10_T	4294836223uL
#define	MAX_u4p28_Tu21p11_T	4294901759uL
#define	MAX_u4p28_Tu20p12_T	4294934527uL
#define	MAX_u4p28_Tu19p13_T	4294950911uL
#define	MAX_u4p28_Tu18p14_T	4294959103uL
#define	MAX_u4p28_Tu17p15_T	4294963199uL
#define	MAX_u4p28_Tu16p16_T	4294965247uL
#define	MAX_u4p28_Tu15p17_T	4294966271uL
#define	MAX_u4p28_Tu14p18_T	4294966783uL
#define	MAX_u4p28_Tu13p19_T	4294967039uL
#define	MAX_u4p28_Tu12p20_T	4294967167uL
#define	MAX_u4p28_Tu11p21_T	4294967231uL
#define	MAX_u4p28_Tu10p22_T	4294967263uL
#define	MAX_u4p28_Tu9p23_T	4294967279uL
#define	MAX_u4p28_Tu8p24_T	4294967287uL
#define	MAX_u4p28_Tu7p25_T	4294967291uL
#define	MAX_u4p28_Tu6p26_T	4294967293uL
#define	MAX_u4p28_Tu5p27_T	4294967294uL
#define	MAX_u0p32_Tu32p0_T	2147483647uL
#define	MAX_u0p32_Tu31p1_T	3221225471uL
#define	MAX_u0p32_Tu30p2_T	3758096383uL
#define	MAX_u0p32_Tu29p3_T	4026531839uL
#define	MAX_u0p32_Tu28p4_T	4160749567uL
#define	MAX_u0p32_Tu27p5_T	4227858431uL
#define	MAX_u0p32_Tu26p6_T	4261412863uL
#define	MAX_u0p32_Tu25p7_T	4278190079uL
#define	MAX_u0p32_Tu24p8_T	4286578687uL
#define	MAX_u0p32_Tu23p9_T	4290772991uL
#define	MAX_u0p32_Tu22p10_T	4292870143uL
#define	MAX_u0p32_Tu21p11_T	4293918719uL
#define	MAX_u0p32_Tu20p12_T	4294443007uL
#define	MAX_u0p32_Tu19p13_T	4294705151uL
#define	MAX_u0p32_Tu18p14_T	4294836223uL
#define	MAX_u0p32_Tu17p15_T	4294901759uL
#define	MAX_u0p32_Tu16p16_T	4294934527uL
#define	MAX_u0p32_Tu15p17_T	4294950911uL
#define	MAX_u0p32_Tu14p18_T	4294959103uL
#define	MAX_u0p32_Tu13p19_T	4294963199uL
#define	MAX_u0p32_Tu12p20_T	4294965247uL
#define	MAX_u0p32_Tu11p21_T	4294966271uL
#define	MAX_u0p32_Tu10p22_T	4294966783uL
#define	MAX_u0p32_Tu9p23_T	4294967039uL
#define	MAX_u0p32_Tu8p24_T	4294967167uL
#define	MAX_u0p32_Tu7p25_T	4294967231uL
#define	MAX_u0p32_Tu6p26_T	4294967263uL
#define	MAX_u0p32_Tu5p27_T	4294967279uL
#define	MAX_u0p32_Tu4p28_T	4294967287uL
#define	MAX_u0p32_Tu3p29_T	4294967291uL
#define	MAX_u0p32_Tu2p30_T	4294967293uL
#define	MAX_u0p32_Tu1p31_T	4294967294uL
#define	MAX_u31p1_Tu34pm2_T	4294967291uL
#define	MAX_u31p1_Tu33pm1_T	4294967293uL
#define	MAX_u31p1_Tu32p0_T	4294967294uL
#define	MAX_u27p5_Tu34pm2_T	4294967231uL
#define	MAX_u27p5_Tu33pm1_T	4294967263uL
#define	MAX_u27p5_Tu32p0_T	4294967279uL
#define	MAX_u27p5_Tu31p1_T	4294967287uL
#define	MAX_u27p5_Tu30p2_T	4294967291uL
#define	MAX_u27p5_Tu29p3_T	4294967293uL
#define	MAX_u27p5_Tu28p4_T	4294967294uL
#define	MAX_u23p9_Tu34pm2_T	4294966271uL
#define	MAX_u23p9_Tu33pm1_T	4294966783uL
#define	MAX_u23p9_Tu32p0_T	4294967039uL
#define	MAX_u23p9_Tu31p1_T	4294967167uL
#define	MAX_u23p9_Tu30p2_T	4294967231uL
#define	MAX_u23p9_Tu29p3_T	4294967263uL
#define	MAX_u23p9_Tu28p4_T	4294967279uL
#define	MAX_u23p9_Tu27p5_T	4294967287uL
#define	MAX_u23p9_Tu26p6_T	4294967291uL
#define	MAX_u23p9_Tu25p7_T	4294967293uL
#define	MAX_u23p9_Tu24p8_T	4294967294uL
#define	MAX_u19p13_Tu34pm2_T	4294950911uL
#define	MAX_u19p13_Tu33pm1_T	4294959103uL
#define	MAX_u19p13_Tu32p0_T	4294963199uL
#define	MAX_u19p13_Tu31p1_T	4294965247uL
#define	MAX_u19p13_Tu30p2_T	4294966271uL
#define	MAX_u19p13_Tu29p3_T	4294966783uL
#define	MAX_u19p13_Tu28p4_T	4294967039uL
#define	MAX_u19p13_Tu27p5_T	4294967167uL
#define	MAX_u19p13_Tu26p6_T	4294967231uL
#define	MAX_u19p13_Tu25p7_T	4294967263uL
#define	MAX_u19p13_Tu24p8_T	4294967279uL
#define	MAX_u19p13_Tu23p9_T	4294967287uL
#define	MAX_u19p13_Tu22p10_T	4294967291uL
#define	MAX_u19p13_Tu21p11_T	4294967293uL
#define	MAX_u19p13_Tu20p12_T	4294967294uL
#define	MAX_u15p17_Tu34pm2_T	4294705151uL
#define	MAX_u15p17_Tu33pm1_T	4294836223uL
#define	MAX_u15p17_Tu32p0_T	4294901759uL
#define	MAX_u15p17_Tu31p1_T	4294934527uL
#define	MAX_u15p17_Tu30p2_T	4294950911uL
#define	MAX_u15p17_Tu29p3_T	4294959103uL
#define	MAX_u15p17_Tu28p4_T	4294963199uL
#define	MAX_u15p17_Tu27p5_T	4294965247uL
#define	MAX_u15p17_Tu26p6_T	4294966271uL
#define	MAX_u15p17_Tu25p7_T	4294966783uL
#define	MAX_u15p17_Tu24p8_T	4294967039uL
#define	MAX_u15p17_Tu23p9_T	4294967167uL
#define	MAX_u15p17_Tu22p10_T	4294967231uL
#define	MAX_u15p17_Tu21p11_T	4294967263uL
#define	MAX_u15p17_Tu20p12_T	4294967279uL
#define	MAX_u15p17_Tu19p13_T	4294967287uL
#define	MAX_u15p17_Tu18p14_T	4294967291uL
#define	MAX_u15p17_Tu17p15_T	4294967293uL
#define	MAX_u15p17_Tu16p16_T	4294967294uL
#define	MAX_u11p21_Tu34pm2_T	4290772991uL
#define	MAX_u11p21_Tu33pm1_T	4292870143uL
#define	MAX_u11p21_Tu32p0_T	4293918719uL
#define	MAX_u11p21_Tu31p1_T	4294443007uL
#define	MAX_u11p21_Tu30p2_T	4294705151uL
#define	MAX_u11p21_Tu29p3_T	4294836223uL
#define	MAX_u11p21_Tu28p4_T	4294901759uL
#define	MAX_u11p21_Tu27p5_T	4294934527uL
#define	MAX_u11p21_Tu26p6_T	4294950911uL
#define	MAX_u11p21_Tu25p7_T	4294959103uL
#define	MAX_u11p21_Tu24p8_T	4294963199uL
#define	MAX_u11p21_Tu23p9_T	4294965247uL
#define	MAX_u11p21_Tu22p10_T	4294966271uL
#define	MAX_u11p21_Tu21p11_T	4294966783uL
#define	MAX_u11p21_Tu20p12_T	4294967039uL
#define	MAX_u11p21_Tu19p13_T	4294967167uL
#define	MAX_u11p21_Tu18p14_T	4294967231uL
#define	MAX_u11p21_Tu17p15_T	4294967263uL
#define	MAX_u11p21_Tu16p16_T	4294967279uL
#define	MAX_u11p21_Tu15p17_T	4294967287uL
#define	MAX_u11p21_Tu14p18_T	4294967291uL
#define	MAX_u11p21_Tu13p19_T	4294967293uL
#define	MAX_u11p21_Tu12p20_T	4294967294uL
#define	MAX_u7p25_Tu34pm2_T	4227858431uL
#define	MAX_u7p25_Tu33pm1_T	4261412863uL
#define	MAX_u7p25_Tu32p0_T	4278190079uL
#define	MAX_u7p25_Tu31p1_T	4286578687uL
#define	MAX_u7p25_Tu30p2_T	4290772991uL
#define	MAX_u7p25_Tu29p3_T	4292870143uL
#define	MAX_u7p25_Tu28p4_T	4293918719uL
#define	MAX_u7p25_Tu27p5_T	4294443007uL
#define	MAX_u7p25_Tu26p6_T	4294705151uL
#define	MAX_u7p25_Tu25p7_T	4294836223uL
#define	MAX_u7p25_Tu24p8_T	4294901759uL
#define	MAX_u7p25_Tu23p9_T	4294934527uL
#define	MAX_u7p25_Tu22p10_T	4294950911uL
#define	MAX_u7p25_Tu21p11_T	4294959103uL
#define	MAX_u7p25_Tu20p12_T	4294963199uL
#define	MAX_u7p25_Tu19p13_T	4294965247uL
#define	MAX_u7p25_Tu18p14_T	4294966271uL
#define	MAX_u7p25_Tu17p15_T	4294966783uL
#define	MAX_u7p25_Tu16p16_T	4294967039uL
#define	MAX_u7p25_Tu15p17_T	4294967167uL
#define	MAX_u7p25_Tu14p18_T	4294967231uL
#define	MAX_u7p25_Tu13p19_T	4294967263uL
#define	MAX_u7p25_Tu12p20_T	4294967279uL
#define	MAX_u7p25_Tu11p21_T	4294967287uL
#define	MAX_u7p25_Tu10p22_T	4294967291uL
#define	MAX_u7p25_Tu9p23_T	4294967293uL
#define	MAX_u7p25_Tu8p24_T	4294967294uL
#define	MAX_u3p29_Tu34pm2_T	3221225471uL
#define	MAX_u3p29_Tu33pm1_T	3758096383uL
#define	MAX_u3p29_Tu32p0_T	4026531839uL
#define	MAX_u3p29_Tu31p1_T	4160749567uL
#define	MAX_u3p29_Tu30p2_T	4227858431uL
#define	MAX_u3p29_Tu29p3_T	4261412863uL
#define	MAX_u3p29_Tu28p4_T	4278190079uL
#define	MAX_u3p29_Tu27p5_T	4286578687uL
#define	MAX_u3p29_Tu26p6_T	4290772991uL
#define	MAX_u3p29_Tu25p7_T	4292870143uL
#define	MAX_u3p29_Tu24p8_T	4293918719uL
#define	MAX_u3p29_Tu23p9_T	4294443007uL
#define	MAX_u3p29_Tu22p10_T	4294705151uL
#define	MAX_u3p29_Tu21p11_T	4294836223uL
#define	MAX_u3p29_Tu20p12_T	4294901759uL
#define	MAX_u3p29_Tu19p13_T	4294934527uL
#define	MAX_u3p29_Tu18p14_T	4294950911uL
#define	MAX_u3p29_Tu17p15_T	4294959103uL
#define	MAX_u3p29_Tu16p16_T	4294963199uL
#define	MAX_u3p29_Tu15p17_T	4294965247uL
#define	MAX_u3p29_Tu14p18_T	4294966271uL
#define	MAX_u3p29_Tu13p19_T	4294966783uL
#define	MAX_u3p29_Tu12p20_T	4294967039uL
#define	MAX_u3p29_Tu11p21_T	4294967167uL
#define	MAX_u3p29_Tu10p22_T	4294967231uL
#define	MAX_u3p29_Tu9p23_T	4294967263uL
#define	MAX_u3p29_Tu8p24_T	4294967279uL
#define	MAX_u3p29_Tu7p25_T	4294967287uL
#define	MAX_u3p29_Tu6p26_T	4294967291uL
#define	MAX_u3p29_Tu5p27_T	4294967293uL
#define	MAX_u3p29_Tu4p28_T	4294967294uL
#define	MAX_um1p33_Tu30p2_T	3221225471uL
#define	MAX_um1p33_Tu29p3_T	3758096383uL
#define	MAX_um1p33_Tu28p4_T	4026531839uL
#define	MAX_um1p33_Tu27p5_T	4160749567uL
#define	MAX_um1p33_Tu26p6_T	4227858431uL
#define	MAX_um1p33_Tu25p7_T	4261412863uL
#define	MAX_um1p33_Tu24p8_T	4278190079uL
#define	MAX_um1p33_Tu23p9_T	4286578687uL
#define	MAX_um1p33_Tu22p10_T	4290772991uL
#define	MAX_um1p33_Tu21p11_T	4292870143uL
#define	MAX_um1p33_Tu20p12_T	4293918719uL
#define	MAX_um1p33_Tu19p13_T	4294443007uL
#define	MAX_um1p33_Tu18p14_T	4294705151uL
#define	MAX_um1p33_Tu17p15_T	4294836223uL
#define	MAX_um1p33_Tu16p16_T	4294901759uL
#define	MAX_um1p33_Tu15p17_T	4294934527uL
#define	MAX_um1p33_Tu14p18_T	4294950911uL
#define	MAX_um1p33_Tu13p19_T	4294959103uL
#define	MAX_um1p33_Tu12p20_T	4294963199uL
#define	MAX_um1p33_Tu11p21_T	4294965247uL
#define	MAX_um1p33_Tu10p22_T	4294966271uL
#define	MAX_um1p33_Tu9p23_T	4294966783uL
#define	MAX_um1p33_Tu8p24_T	4294967039uL
#define	MAX_um1p33_Tu7p25_T	4294967167uL
#define	MAX_um1p33_Tu6p26_T	4294967231uL
#define	MAX_um1p33_Tu5p27_T	4294967263uL
#define	MAX_um1p33_Tu4p28_T	4294967279uL
#define	MAX_um1p33_Tu3p29_T	4294967287uL
#define	MAX_um1p33_Tu2p30_T	4294967291uL
#define	MAX_um1p33_Tu1p31_T	4294967293uL
#define	MAX_um1p33_Tu0p32_T	4294967294uL
#define	MAX_um3p35_Tu28p4_T	3221225471uL
#define	MAX_um3p35_Tu27p5_T	3758096383uL
#define	MAX_um3p35_Tu26p6_T	4026531839uL
#define	MAX_um3p35_Tu25p7_T	4160749567uL
#define	MAX_um3p35_Tu24p8_T	4227858431uL
#define	MAX_um3p35_Tu23p9_T	4261412863uL
#define	MAX_um3p35_Tu22p10_T	4278190079uL
#define	MAX_um3p35_Tu21p11_T	4286578687uL
#define	MAX_um3p35_Tu20p12_T	4290772991uL
#define	MAX_um3p35_Tu19p13_T	4292870143uL
#define	MAX_um3p35_Tu18p14_T	4293918719uL
#define	MAX_um3p35_Tu17p15_T	4294443007uL
#define	MAX_um3p35_Tu16p16_T	4294705151uL
#define	MAX_um3p35_Tu15p17_T	4294836223uL
#define	MAX_um3p35_Tu14p18_T	4294901759uL
#define	MAX_um3p35_Tu13p19_T	4294934527uL
#define	MAX_um3p35_Tu12p20_T	4294950911uL
#define	MAX_um3p35_Tu11p21_T	4294959103uL
#define	MAX_um3p35_Tu10p22_T	4294963199uL
#define	MAX_um3p35_Tu9p23_T	4294965247uL
#define	MAX_um3p35_Tu8p24_T	4294966271uL
#define	MAX_um3p35_Tu7p25_T	4294966783uL
#define	MAX_um3p35_Tu6p26_T	4294967039uL
#define	MAX_um3p35_Tu5p27_T	4294967167uL
#define	MAX_um3p35_Tu4p28_T	4294967231uL
#define	MAX_um3p35_Tu3p29_T	4294967263uL
#define	MAX_um3p35_Tu2p30_T	4294967279uL
#define	MAX_um3p35_Tu1p31_T	4294967287uL
#define	MAX_um3p35_Tu0p32_T	4294967291uL
#define	MAX_um3p35_Tum1p33_T	4294967293uL
#define	MAX_um3p35_Tum10p26_T	33553664uL
#define	MAX_s19p12_Ts11p4_T	8388479uL
#define	MAX_s18p13_Ts10p5_T	8388479uL
#define	MAX_s13p18_Ts11p4_T	536862719uL
#define	MAX_s15p16_Ts11p4_T	134215679uL
#define	MAX_s17p14_Ts11p4_T	33553919uL
#define	MAX_s16p15_Ts15p0_T	1073725439uL
#define	MAX_s12p19_Ts11p4_T	1073725439uL
#define	MAX_s16p15_Ts10p5_T     2147483135uL
#define	MAX_s18p13_Ts8p7_T	2097119uL
#define	MAX_s16p15_Ts8p7_T	8388479uL
#define	MAX_u10p22_Tu7p9_T	536866815uL
#define	MAX_u24p8_Tu16p0_T	16777087uL
#define	MAX_u16p16_Tu16p0_T	4294934527uL
#define	MAX_u17p15_Tu9p7_T	16777087uL
#define	MAX_u16p16_Tu8p8_T	16777087uL
#define	MAX_u8p24_Tu0p16_T	16777087uL
#define MAX_u19p13_Tu16p0_T 536866815uL
#define	MAX_u21p11_Tu16p0_T	134216703uL
#define	MAX_u20p12_Tu9p7_T	2097135uL
#define	MAX_u10p6_Tu12p4_T	65535uL
#define	MAX_u12p4_Tu16p0_T	65535uL
#define	MAX_s11p4_Ts14p1_T	32767uL
#define MAX_u16p16_Tu9p7_T	16777087uL
#define MAX_s8p7_Ts10p5_T	32767uL
#define MAX_u18p14_Tu9p7_T	16777087uL
#define MAX_u17p15_Tu9p7_T	16777087uL

#endif

/******************************************************************************
CHANGE HISTORY:

 Date      Rev      Author 			Change Description              SCR #
 				  					 (MDD Rev & Date) 		
-------   -------   --------  -----------------------------------  ----------
11/28/2010	1.0	    LWW       Initial Version
02/13/2013	2.0	    JJW       Added some new 32 bit extended types
					                                
******************************************************************************/

