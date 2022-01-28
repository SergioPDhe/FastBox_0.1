#include "GC_DAC.h"
#include "GC_COMM.h"
#include "GC_SETUP.h"

GCComm gcComm;
GCDAC gcDac;

uint8_t ctrlX = 0x80;
uint8_t ctrlY = 0x80;



int count = 0;


void setup() 
{
  gcComm.InitDataLine();
    
  DDRB = 0b00111100;
  
  BTN_DDR = 0;
  BTN_PORT = 0b11111111;
  
  CTRL_DDR = 0;
  CTRL_PORT = 0b00111111;

  CSTK_DDR = 0;
  CSTK_PORT = 0b00111111;

  RMBL_DDR = 1;
  RMBL_PORT = 0;
  
  //delay(500);
  PORTB = 0;
  Serial.begin(115200);
  Serial.println(123);
}

void loop() 
{
  gcDac.DAC();
  
  UpdateAnalog();
  
  count++;
}

void UpdateAnalog()
{
  
  gcComm.ControlX = gcDac.ControlX;
  gcComm.ControlY = gcDac.ControlY;

  if (gcDac.dPad)
  {
    gcComm.DPad = gcDac.Cstick2Dpad(CSTK_PIN & CSTK_CSTK);
  }
  else
  {
    gcComm.CstickX = gcDac.CstickX;
    gcComm.CstickY = gcDac.CstickY;
  }

  gcComm.AnalogR = gcDac.AnalogR;

}

ISR(INT0_vect) // activates when RX drops low (INT0 and RX are connected)
{
  gcComm.ReceiveCommand();
  //Serial.println(count);
  //Serial.println(gcDac.modkey);
  //Serial.println((uint8_t)CTRL_PIN);
  //Serial.println(gcDac.out);
  count=0;
}
