#ifndef SERIAL_H_
#define SERIAL_H_
#include <errno.h>
#include <fcntl.h>
#include <iostream>
#include <string.h>
#include <string>
#include <termios.h>
#include <unistd.h>
#include <vector>

using std::string;
using std::vector;

/**
 * @brief wrapper class for serial communication in linux
 **/
class Serial
{
  private:
    int serial_dev;
    uint8_t read_buf[256];
    termios tty;

  public:
    /**
     * @brief open a serial device with given settings
     * @param serial_port: path of the serial device
     * @param baud_rate: baudrate of the device
     * @param data_bits: number of bits in
     * @param parity: activate parity bit
     **/
    Serial(string serial_port, speed_t baud_rate = B9600, tcflag_t data_bits = CS8,
           bool parity = true);
    /**
     * @brief write to serial device
     * @msg vector of bytes to write
     * @return status of write
     **/
    int send(const vector<uint8_t> &msg);

    /**
     * @brief read from serial device
     * @return vector of bytes read
     **/
    vector<uint8_t> receive(size_t bytes = 1);
};

#endif // SERIAL_H_
