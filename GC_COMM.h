#ifndef GC_COMM
#define GC_COMM

#include "Arduino.h"
#include "GC_SETUP.h"


#ifdef UCSR1A // if Serial '1" registers are defined (e.g. Arduino Mega2560, Lenoardo, ATMega2560, ATMega32U4)

// if defined
// register names
# define BAUD_HIGH UBRR1H
# define BAUD_LOW UBRR1L
# define UART_CTRL_A UCSR1A
# define UART_CTRL_B UCSR1B
# define UART_CTRL_C UCSR1C
# define UART_DATA UDR1
# define EXT_INT_CTRL EICRA
# define EXT_INT_MASK EIMSK
# define RX_INT_VECTOR INT0_vect
// bit names
# define RX_COMPLETE RXC1
# define TX_COMPLETE TXC1
# define TX_READY UDRE1
# define RX_INTERRUPT INT0
# define UART_DOUBLE U2X1
# define RX_ENABLE RXEN1
# define TX_ENABLE TXEN1
# define WORD_SIZE0 UCSZ10
# define WORD_SIZE1 UCSZ11
# define INTERRUPT0 ISC00
# define INTERRUPT1 ISC01

#else // if Serial1 doesn't exist:

# ifdef UCSR0A // if Serial "0" registers are defined (e.g. Arduino uno, ATMega328p)

#   define BAUD_HIGH UBRR0H
#   define BAUD_LOW UBRR0L
#   define UART_CTRL_A UCSR0A
#   define UART_CTRL_B UCSR0B
#   define UART_CTRL_C UCSR0C
#   define UART_DATA UDR0
#   define EXT_INT_CTRL EICRA
#   define EXT_INT_MASK EIMSK
#   define RX_INT_VECTOR INT0_vect

#   define RX_COMPLETE RXC0
#   define TX_COMPLETE TXC0
#   define TX_READY UDRE0
#   define RX_INTERRUPT INT0
#   define UART_DOUBLE U2X0
#   define RX_ENABLE RXEN0
#   define TX_ENABLE TXEN0
#   define WORD_SIZE0 UCSZ00
#   define WORD_SIZE1 UCSZ01
#   define INTERRUPT0 ISC00
#   define INTERRUPT1 ISC01

# else
#   error "Current board not supported!" // if Serial 0 and 1 are not defined
# endif

#endif

class GCComm
{
  public:
    GCComm(); // sets up serial port
    void SendPollResponse();
    void SendOrigin();
    inline void SendInputs(); // sends
    void InitDataLine();
    void ReceiveCommand();

    volatile uint8_t  StYXBA =    0x00;
    volatile uint8_t  LRZDpad =   0x80;
    volatile uint8_t  ControlX =  128;
    volatile uint8_t  ControlY =  128;
    volatile uint8_t  CstickX =   128;
    volatile uint8_t  CstickY =   128; 
    volatile uint8_t  AnalogL =   0;
    volatile uint8_t  AnalogR =   0;
    volatile uint8_t  DPad =      0;
    
    volatile uint8_t  rumble =    0;
    
  private:
    inline void SendByte(uint8_t dataByte);
    inline uint8_t ReceiveByte();
    inline uint8_t ReceiveRumbleByte();
    inline void SendPair(uint8_t sent);
    inline uint8_t ReceivePair();
    inline uint8_t Byte2GC(uint8_t dataByte);
    inline uint8_t GC2Byte(uint8_t dataByte);
    inline void SendStopBit();
    inline void FlushReceiveBuffer();
    inline void SetFrameSize6();
    inline void SetFrameSize8();
    inline void SetRumble(uint8_t command);
};

#endif
