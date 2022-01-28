#include "GC_DAC.h"
//#include "Arduino.h"


GCDAC::GCDAC()
{

}

void GCDAC::DAC()
{
  ControlDAC();
  //CStickDAC();
  TriggersDAC();
}

inline void GCDAC::ControlDAC()
{
  short int posX = SOCD_TwoIPNoR((CTRL_PIN & CTRL_HORIZ), &Ctrl_SOCD_X);
  short int posY = SOCD_TwoIPNoR((CTRL_PIN & CTRL_VERT)>>2, &Ctrl_SOCD_Y);

  short int posCX = SOCD_TwoIPNoR((CSTK_PIN & CSTK_HORIZ), &CStk_SOCD_X);
  short int posCY = SOCD_TwoIPNoR((CSTK_PIN & CSTK_VERT)>>2, &CStk_SOCD_Y);

  CstickX = NEUTRAL + (MAXOFFSET * posCX);
  CstickY = NEUTRAL + (MAXOFFSET * posCY);

  uint8_t mod = (CTRL_PIN & CTRL_MOD)>>4; // bit 0 is MODX and bit 1 is MODY
  uint8_t Direction = 0; // check if input is horizontal (0b0001), vertical (0b0010) or diagonal (0b0100)

  ControlX = NEUTRAL;
  ControlY = NEUTRAL;

  if (posX) Direction |= 0b00000001;
  if (posY) Direction |= 0b00000010;
  if (Direction == 0b00000011) Direction = 0b00000100;

  //modkey = '0';
  //out = mod;
  dPad = false;
  switch(mod) // check combination of ModX and ModY
  {
    case 0b00000011: // neither pressed ///////////////////////////////////////////////////////////////////////
      //modkey = 'n';
      switch(Direction) // check direction
      {
        case(0b00000001): // horizontal
          ControlX += (MAXOFFSET * posX); 
          //out = 'H';
          return;
          
        case(0b00000010): // vertical
          ControlY += (MAXOFFSET * posY); 
          //out = 'V';
          return;
          
        case(0b00000100): // diagonal
          if (~BTN_PIN & BTN_LR)
          {
            ControlX += (DIAG_SHIELD_X * posX); 
            ControlY += (DIAG_SHIELD_Y * posY); 
            //out = 'B';
            return;
          }
          // ELSE
          ControlX += (DIAGONAL_X * posX); 
          ControlY += (DIAGONAL_Y * posY); 
          //out = 'D';
          return;
        
      }
      return;  
    case 0b00000010: // modx pressed //////////////////////////////////////////////////////////////////////////////////
      //modkey = 'x';
      switch(Direction) // check direction
      {
        case(0b00000001): // horizontal /////////////////////////////////
          if (~BTN_PIN & 0b00000010) // if B is pressed
          {
            ControlX += (MODX_H_B_X * posX); // side-b nerf
            break;
          }
          // ELSE
          ControlX += (MODX_H_X * posX); 
          break;
          
        case(0b00000010): // vertical /////////////////////////////////
          if (~BTN_PIN & (1<<BTN_B)) // if B is pressed
          {
            ControlY += (MODX_V_B_Y * posY); // side-b nerf
            break;
          }
          // ELSE
          ControlY += (MODX_V_Y * posY); 
          break;
          
        case(0b00000100): // diagonal //////////////////////////////////
          if (~BTN_PIN & BTN_LR) // if L/R are pressed
          {
            ControlX += (MODX_D_SHIELD_X * posX); // MODX wavedash
            ControlY += (MODX_D_SHIELD_Y * posY); 
            break;
          }
          
          // ELSE
          if (!(~CSTK_PIN & CSTK_CSTK)) // if Cstick buttons are NOT pressed
          {
            ControlX += (MODX_DIAG_X * posX); // MODX tilt
            ControlY += (MODX_DIAG_Y * posY); 
            break;
          }
          
          // ELSE
          if (~BTN_PIN & (1<<BTN_B)) // if B is held for extended angles
          {
            if (~CSTK_PIN & (1<<CSTK_DOWN))
            {
              ControlX += (MODX_D_CD_B_X * posX);
              ControlY += (MODX_D_CD_B_Y * posY); 
              break;
            }
            // ELSE
            if (~CSTK_PIN & (1<<CSTK_LEFT))
            {
              ControlX += (MODX_D_CL_B_X * posX);
              ControlY += (MODX_D_CL_B_Y * posY); 
              break;
            }
            // ELSE
            if (~CSTK_PIN & (1<<CSTK_UP))
            {
              ControlX += (MODX_D_CU_B_X * posX);
              ControlY += (MODX_D_CU_B_Y * posY); 
              break;
            }
            // ELSE
            if (~CSTK_PIN & (1<<CSTK_RIGHT))
            {
              ControlX += (MODX_D_CR_B_X * posX);
              ControlY += (MODX_D_CR_B_Y * posY); 
              break;
            }
            
          }

          if (~CSTK_PIN & (1<<CSTK_DOWN))
          {
            ControlX += (MODX_D_CD_X * posX);
            ControlY += (MODX_D_CD_Y * posY); 
            break;
          }
          // ELSE
          if (~CSTK_PIN & (1<<CSTK_LEFT))
          {
            ControlX += (MODX_D_CL_X * posX);
            ControlY += (MODX_D_CL_Y * posY); 
            break;
          }
          // ELSE
          if (~CSTK_PIN & (1<<CSTK_UP))
          {
            ControlX += (MODX_D_CU_X * posX);
            ControlY += (MODX_D_CU_Y * posY); 
            break;
          }
          // ELSE
          if (~CSTK_PIN & (1<<CSTK_RIGHT))
          {
            ControlX += (MODX_D_CR_X * posX);
            ControlY += (MODX_D_CR_Y * posY); 
            break;
          }
      }
      if (posCX)
        {
          CstickX = NEUTRAL + (posCX * MODX_FSMASH_X);
          CstickY = NEUTRAL + (posY * MODX_FSMASH_Y);
        }
      return;
            
    case 0b00000001: // mody pressed
      //modkey = 'y';
      switch(Direction) // check direction
      {
        case(0b00000001): // horizontal /////////////////////////////////
          if (~BTN_PIN & 0b00000010) // if B is pressed
          {
            ControlX += (MODX_H_B_X * posX); // side-b nerf
            return;
          }
          // ELSE
          ControlX += (MODX_H_X * posX); 
          return;
          
        case(0b00000010): // vertical /////////////////////////////////
          if (~BTN_PIN & (1<<BTN_B)) // if B is pressed
          {
            ControlY += (MODX_V_B_Y * posY); // side-b nerf
            return;
          }
          // ELSE
          ControlY += (MODX_V_Y * posY); 
          return;
        case(0b00000100): // diagonal //////////////////////////////////
          if (~BTN_PIN & BTN_LR) // if L/R are pressed
          {
            ControlX += (MODY_D_SHIELD_X * posX); // MODY wavedash
            ControlY += (MODY_D_SHIELD_Y * posY); 
            return;
          }
          
          // ELSE
          if (!(~CSTK_PIN & CSTK_CSTK)) // if Cstick buttons are NOT pressed
          {
            ControlX += (MODY_DIAG_X * posX); // MODY tilt
            ControlY += (MODY_DIAG_Y * posY); 
            return;
          }
          
          // ELSE
          if (~BTN_PIN & (1<<BTN_B)) // if B is held for extended angles
          {
            if (~CSTK_PIN & (1<<CSTK_DOWN))
            {
              ControlX += (MODY_D_CD_B_X * posX);
              ControlY += (MODY_D_CD_B_Y * posY); 
              return;
            }
            // ELSE
            if (~CSTK_PIN & (1<<CSTK_LEFT))
            {
              ControlX += (MODY_D_CL_B_X * posX);
              ControlY += (MODY_D_CL_B_Y * posY); 
              return;
            }
            // ELSE
            if (~CSTK_PIN & (1<<CSTK_UP))
            {
              ControlX += (MODY_D_CU_B_X * posX);
              ControlY += (MODY_D_CU_B_Y * posY); 
              return;
            }
            // ELSE
            if (~CSTK_PIN & (1<<CSTK_RIGHT))
            {
              ControlX += (MODY_D_CR_B_X * posX);
              ControlY += (MODY_D_CR_B_Y * posY); 
              return;
            }
            
          }

          if (~CSTK_PIN & (1<<CSTK_DOWN))
          {
            ControlX += (MODY_D_CD_X * posX);
            ControlY += (MODY_D_CD_Y * posY); 
            return;
          }
          // ELSE
          if (~CSTK_PIN & (1<<CSTK_LEFT))
          {
            ControlX += (MODY_D_CL_X * posX);
            ControlY += (MODY_D_CL_Y * posY); 
            return;
          }
          // ELSE
          if (~CSTK_PIN & (1<<CSTK_UP))
          {
            ControlX += (MODY_D_CU_X * posX);
            ControlY += (MODY_D_CU_Y * posY); 
            return;
          }
          // ELSE
          if (~CSTK_PIN & (1<<CSTK_RIGHT))
          {
            ControlX += (MODY_D_CR_X * posX);
            ControlY += (MODY_D_CR_Y * posY); 
            return;
          }
          
  
      }
      return;
      
    case 0b00000000: // both pressed
      //modkey = 'b';
      dPad = true;
  }
  
  ControlX = NEUTRAL + (MAXOFFSET * posX);
  ControlY = NEUTRAL + (MAXOFFSET * posY);
}

inline void GCDAC::CStickDAC()
{
  CstickX = NEUTRAL + (MAXOFFSET * SOCD_TwoIPNoR((CSTK_PIN & CSTK_HORIZ), &CStk_SOCD_X));
  CstickY = NEUTRAL + (MAXOFFSET * SOCD_TwoIPNoR((CSTK_PIN & CSTK_VERT)>>2, &CStk_SOCD_Y));
}

inline void GCDAC::TriggersDAC()
{
  AnalogR = 0;
  if (~CSTK_PIN & (1<<CSTK_MS))
  {
    AnalogR = SHIELD_MID;
    return;
  }
  if (~CSTK_PIN & (1<<CSTK_LS))
  {
    AnalogR = SHIELD_LIGHT;
    return;
  }
}

uint8_t GCDAC::Cstick2Dpad(uint8_t Stick)
{
  Stick = ~Stick;
  uint8_t Pad = (Stick & 0b00000101)<<1;
  Stick = (Stick & 0b00001010)>>1;
  return (Pad | Stick);
}

inline short int GCDAC::SOCD_TwoIPNoR(uint8_t input, uint8_t *SOCD)// input uses bits 0 and 1. 0 for Right/Up and 1 for Left/Down. // Activated inputs are low (e.g. 10 could be an 'up' input and 00 means both opposite inputs are pressed.)
{                                               // SOCD uses bits 0, 1, 2 and 3. 0 and 1 to check what inputs were pressed; 3 and 4 to check if inputs are locked.
                                                // this code is a bit difficult to understand because of the binary, but it is very similar to SOCD code found in other open-source box firmwares such as the Crane Firmware: https://github.com/Crane1195/CL-FW
  
    if (input == 0) // both opposite inputs are pressed 
    { 
        if (*SOCD & 0b00000001) // if R/U input was previously pressed
        {
            *SOCD |= 0b00000100; // lock R/U input
            return -1;          // return L/D input
        }
        if (*SOCD & 0b00000010) // if L/D input was previously pressed
        {
            *SOCD |= 0b00001000; // lock L/D
            return 1;           // return R/U
        }
    }
    
    if (input == 0b00000010 && !(*SOCD & 0b00000100)) // R/U input is pressed and not locked
    { 
        *SOCD = 0b00000001; // R/U was pressed, all is unlocked
        return 1; //return R/U
    }
    
    if (input == 0b00000001 && !(*SOCD & 0b00001000)) 
    {
        *SOCD = 0b00000010; // L/D was pressed, all is unlocked
        return -1; //return L/D
    }
    
    if (input == 0b00000011) 
    {
        *SOCD = 0; // nothing is pressed, all is unlocked
        return 0; //return neutral
    }
    
    return 0; //when in doubt, return neutral 
}
