#ifndef GC_SETUP
#define GC_SETUP

#include "Arduino.h"

#define BTN_PORT PORTA
#define BTN_PIN PINA
#define BTN_DDR DDRA

#define BTN_A 0
#define BTN_B 1
#define BTN_X 2
#define BTN_Y 3
#define BTN_START 4
#define BTN_Z 5
#define BTN_R 6
#define BTN_L 7

#define BTN_LR 192 // 0b 1100 0000


#define CTRL_PORT PORTF
#define CTRL_PIN PINF
#define CTRL_DDR DDRF

#define CTRL_RIGHT 0
#define CTRL_LEFT 1
#define CTRL_UP 2
#define CTRL_DOWN 3
#define CTRL_MX 4
#define CTRL_MY 5

#define CTRL_HORIZ 3 // 0b 0000 0011
#define CTRL_VERT 12 // 0b 0000 1100
#define CTRL_MOD 48 //  0b 0011 0000


#define CSTK_PORT PORTK
#define CSTK_PIN PINK
#define CSTK_DDR DDRK

#define CSTK_RIGHT 0
#define CSTK_LEFT 1
#define CSTK_UP 2
#define CSTK_DOWN 3
#define CSTK_MS 4
#define CSTK_LS 5

#define CSTK_CSTK 15 // 0b 0000 1111

#define CSTK_HORIZ 3 // 0b 0000 0011
#define CSTK_VERT 12 // 0b 0000 1100
#define CSTK_SHLD 48 // 0b 0011 0000


#define RMBL_PORT PORTJ
#define RMBL_PIN PINJ
#define RMBL_DDR DDRJ

#define RMBL_SIG 0
#define RMBL_BRK 1




#define MAXOFFSET 80
#define NEUTRAL 128

// max values
#define HORIZONTAL_X 80
#define HORIZONTAL_Y 0

#define VERTICAL_X 0
#define VERTICAL_Y 80

#define DIAGONAL_X 56
#define DIAGONAL_Y 56

// shield drop
#define DIAG_SHIELD_X 56
#define DIAG_SHIELD_Y 55


// modX
//tilts
#define MODX_H_X 53
#define MODX_H_Y 0

#define MODX_V_X 0
#define MODX_V_Y 43

// side-b nerf
#define MODX_H_B_X 53
#define MODX_H_B_Y 0

#define MODX_V_B_X 0
#define MODX_V_B_Y 43

// upB angles
#define MODX_DIAG_X 59
#define MODX_DIAG_Y 25

#define MODX_D_CD_X 56
#define MODX_D_CD_Y 29

#define MODX_D_CL_X 63
#define MODX_D_CL_Y 39

#define MODX_D_CU_X 56
#define MODX_D_CU_Y 41

#define MODX_D_CR_X 49
#define MODX_D_CR_Y 42

// extended upB angles
#define MODX_DIAG_B_X 73
#define MODX_DIAG_B_Y 31

#define MODX_D_CD_B_X 70
#define MODX_D_CD_B_Y 36

#define MODX_D_CL_B_X 68
#define MODX_D_CL_B_Y 42

#define MODX_D_CU_B_X 59
#define MODX_D_CU_B_Y 43

#define MODX_D_CR_B_X 51
#define MODX_D_CR_B_Y 43

//wavedash
#define MODX_D_SHIELD_X 51
#define MODX_D_SHIELD_Y 30

//angled fsmash
#define MODX_FSMASH_X 68
#define MODX_FSMASH_Y 42


// modY
//tilts//////////////////////////////////
#define MODY_H_X 27
#define MODY_H_Y 0

#define MODY_V_X 0
#define MODY_V_Y 59

// side-b nerf
#define MODY_H_B_X 53
#define MODY_H_B_Y 0

#define MODY_V_B_X 0
#define MODY_V_B_Y 59


// upB angles///////////////////////////////
#define MODY_DIAG_X 25
#define MODY_DIAG_Y 59

#define MODY_D_CD_X 29
#define MODY_D_CD_Y 56

#define MODY_D_CL_X 39
#define MODY_D_CL_Y 63

#define MODY_D_CU_X 41
#define MODY_D_CU_Y 56

#define MODY_D_CR_X 51
#define MODY_D_CR_Y 61


// extended upB angles///////////////////////
#define MODY_DIAG_B_X 31
#define MODY_DIAG_B_Y 73

#define MODY_D_CD_B_X 36
#define MODY_D_CD_B_Y 70

#define MODY_D_CL_B_X 42
#define MODY_D_CL_B_Y 68

#define MODY_D_CU_B_X 47
#define MODY_D_CU_B_Y 64

#define MODY_D_CR_B_X 47
#define MODY_D_CR_B_Y 57


//wavedash//////////////////////////////////////////
#define MODY_D_SHIELD_X 40
#define MODY_D_SHIELD_Y 68

////////////////////////////////////////////////////////////////
#define SHIELD_MID 95
#define SHIELD_LIGHT 50



#endif
