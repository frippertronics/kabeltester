#ifndef I2C_H
#define I2C_H
/************************************************************************* 
* Title:    C include file for the I2C master interface 
*           (i2cmaster.S or i2cmaster.c)
* Author:   Peter Fleury <pfleury@gmx.ch>
* File:     $Id: i2cmaster.h,v 1.12 2015/09/16 09:27:58 peter Exp $
* Software: AVR-GCC 4.x
* Target:   any AVR device
* Usage:    see Doxygen manual
**************************************************************************/

/**
 @file
 @defgroup pfleury_ic2master I2C Master library
 @code #include <i2cmaster.h> @endcode
  
 @brief I2C (TWI) Master Software Library

 Basic routines for communicating with I2C slave devices. This single master 
 implementation is limited to one bus master on the I2C bus. 

 This I2c library is implemented as a compact assembler software implementation of the I2C protocol 
 which runs on any AVR (i2cmaster.S) and as a TWI hardware interface for all AVR with built-in TWI hardware (i2cmaster.c).
 Since the API for these two implementations is exactly the same, an application can be linked either against the
 software I2C implementation or the hardware I2C implementation.

 Use 4.7k pull-up resistor on the SDA and SCL pin.
 
 Adapt the SCL and SDA port and pin definitions and eventually the delay routine in the module 
 i2cmaster.S to your target when using the software I2C implementation ! 
 
 Adjust the  CPU clock frequence F_CPU in i2cmaster.c or in the Makfile when using the TWI hardware implementaion.

 @note 
    The module i2cmaster.S is based on the Atmel Application Note AVR300, corrected and adapted 
    to GNU assembler and AVR-GCC C call interface.
    Replaced the incorrect quarter period delays found in AVR300 with 
    half period delays. 
    
 @author Peter Fleury pfleury@gmx.ch  http://tinyurl.com/peterfleury
 @copyright (C) 2015 Peter Fleury, GNU General Public License Version 3
 
 @par API Usage Example
  The following code shows typical usage of this library, see example test_i2cmaster.c

 @code

 #include <i2cmaster.h>


 #define Dev24C02  0xA2      // device address of EEPROM 24C02, see datasheet

 int main(void)
 {
     unsigned char ret;

     I2C_Init();                             // initialize I2C library

     // write 0x75 to EEPROM address 5 (Byte Write) 
     I2C_StartWait(Dev24C02+I2C_WRITE);     // set device address and write mode
     I2C_Write(0x05);                        // write address = 5
     I2C_Write(0x75);                        // write value 0x75 to EEPROM
     I2C_Stop();                             // set stop conditon = release bus


     // read previously written value back from EEPROM address 5 
     I2C_StartWait(Dev24C02+I2C_WRITE);     // set device address and write mode

     I2C_Write(0x05);                        // write address = 5
     I2C_RepStart(Dev24C02+I2C_READ);       // set device address and read mode

     ret = I2C_ReadNak();                    // read one byte from EEPROM
     I2C_Stop();

     for(;;);
 }
 @endcode

*/


/**@{*/

#if (__GNUC__ * 100 + __GNUC_MINOR__) < 304
#error "This library requires AVR-GCC 3.4 or later, update to newer AVR-GCC compiler !"
#endif

#include <avr/io.h>

/** defines the data direction (reading from I2C device) in I2C_Start(),I2C_RepStart() */
#define I2C_READ    1

/** defines the data direction (writing to I2C device) in I2C_Start(),I2C_RepStart() */
#define I2C_WRITE   0

#define NUM_I2C_PINS (2U)

/**
 @brief initialize the I2C master interace. Need to be called only once 
 @return none
 */
extern void I2C_Init(void);


/** 
 @brief Terminates the data transfer and releases the I2C bus 
 @return none
 */
extern void I2C_Stop(void);


/** 
 @brief Issues a start condition and sends address and transfer direction 
  
 @param    addr address and transfer direction of I2C device
 @retval   0   device accessible 
 @retval   1   failed to access device 
 */
extern unsigned char I2C_Start(unsigned char addr);


/**
 @brief Issues a repeated start condition and sends address and transfer direction 

 @param   addr address and transfer direction of I2C device
 @retval  0 device accessible
 @retval  1 failed to access device
 */
extern unsigned char I2C_RepStart(unsigned char addr);


/**
 @brief Issues a start condition and sends address and transfer direction 
   
 If device is busy, use ack polling to wait until device ready 
 @param    addr address and transfer direction of I2C device
 @return   none
 */
extern void I2C_StartWait(unsigned char addr);

 
/**
 @brief Send one byte to I2C device
 @param    data  byte to be transfered
 @retval   0 write successful
 @retval   1 write failed
 */
extern unsigned char I2C_Write(unsigned char data);


/**
 @brief    read one byte from the I2C device, request more data from device 
 @return   byte read from I2C device
 */
extern unsigned char I2C_ReadAck(void);

/**
 @brief    read one byte from the I2C device, read is followed by a stop condition 
 @return   byte read from I2C device
 */
extern unsigned char I2C_ReadNak(void);

/** 
 @brief    read one byte from the I2C device
 
 Implemented as a macro, which calls either @ref I2C_ReadAck or @ref I2C_ReadNak
 
 @param    ack 1 send ack, request more data from device<br>
               0 send nak, read is followed by a stop condition 
 @return   byte read from I2C device
 */
extern unsigned char I2C_read(unsigned char ack);
#define I2C_read(ack)  (ack) ? I2C_ReadAck() : I2C_ReadNak(); 



/**@}*/
#endif
