/*
  This is a library written for the PCA9536 4-bit I2C I/O Expander
  SparkFun sells these at its website: www.sparkfun.com
  Do you like this library? Help support SparkFun. Buy a board!
  https://www.sparkfun.com/products/TODO
  Written by Jim Lindblom @ SparkFun Electronics, May 4th, 2018
  The PCA9536 is a 4-bit I/O digital expander, which communicates via an I2C bus.
  The expander can read or write four separate I/O.
  
  This library handles the initialization of the PCA9536 and supports standard
  pinMode, digitalRead, and digitalWrite functions.
  https://github.com/sparkfunX/SparkFun_PCA9536_Arduino_Library

  Development environment specifics:
  Arduino IDE 1.8.5
  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
  GNU General Public License for more details.
  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#pragma once

#if (ARDUINO >= 100)
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#define DEBUG_PCA9536

#include <Wire.h>

typedef enum {
    PCA9536_ADDRESS = 0x41,
    PCA9536_ADDRESS_INVALID = 0xFF
} PCA9536_Address_t;

typedef enum {
    PCA9536_REGISTER_INPUT_PORT         = 0x00,
    PCA9536_REGISTER_OUTPUT_PORT        = 0x01,
    PCA9536_REGISTER_POLARITY_INVERSION = 0x02,
    PCA9536_REGISTER_CONFIGURATION      = 0x03,
    PCA9536_REGISTER_INVALID
} PCA9536_REGISTER_t;

typedef enum {
    PCA9536_ERROR_READ            = -4,
    PCA9536_ERROR_WRITE           = -3,
    PCA9536_ERROR_INVALID_ADDRESS = -2,
    PCA9536_ERROR_UNDEFINED       = -1,
    PCA9536_ERROR_SUCCESS         = 1
} PCA9536_error_t;
const PCA9536_error_t PCA9536_SUCCESS = PCA9536_ERROR_SUCCESS;

typedef enum {
    PCA9536_RETAIN,
    PCA9536_INVERT,
    PCA9536_INVERT_END
} PCA9536_invert_t;

// rgb, white LED definitions for QWIIC RGB Breakout
enum {
    PCA9536_WHITE, // 0
    PCA9536_RED,   // 1
    PCA9536_GREEN, // 2
    PCA9536_BLUE   // 3
};

class PCA9536 {
public:
    PCA9536();

    PCA9536_error_t begin(TwoWire &wirePort = Wire);

    void setDebugStream(Stream &debugPort = Serial);

    PCA9536_error_t pinMode(uint8_t pin, uint8_t mode);

    PCA9536_error_t digitalWrite(uint8_t pin, uint8_t value);
    PCA9536_error_t write(uint8_t pin, uint8_t value);

    uint8_t digitalRead(uint8_t pin);
    uint8_t read(uint8_t pin);

    PCA9536_error_t invert(uint8_t pin, PCA9536_invert_t inversion = PCA9536_INVERT);
    PCA9536_error_t revert(uint8_t pin);

private:
    TwoWire *_i2cPort; //The generic connection to user's chosen I2C hardware
    Stream * _debugPort;
    PCA9536_Address_t _deviceAddress;

// I2C Read/Write
    PCA9536_error_t readI2CBuffer(uint8_t * dest, PCA9536_REGISTER_t startRegister, uint16_t len);
    PCA9536_error_t writeI2CBuffer(uint8_t * src, PCA9536_REGISTER_t startRegister, uint16_t len);
    PCA9536_error_t readI2CRegister(uint8_t * dest, PCA9536_REGISTER_t registerAddress);
    PCA9536_error_t writeI2CRegister(uint8_t data, PCA9536_REGISTER_t registerAddress);
};