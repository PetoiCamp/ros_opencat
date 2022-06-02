/**
 * @brief source file for serial lib
 * @file
 * @author C.C
 * @date 2022.05.22
 **/
#include "opencat_serial/serial.hpp"
#include <cassert>

namespace Serial
{
Serial::Serial(string serial_port, speed_t baud_rate, tcflag_t data_bits,
               bool parity)
    : serial_dev{open(serial_port.c_str(), O_RDWR)} // open device
{
    // check device open
    if (this->serial_dev < 0)
    {
        printf("Error %i from open: %s\n", errno, strerror(errno));
    }
    // Read in existing settings, and handle any error
    // NOTE: This is important! POSIX states that the struct passed to
    // tcsetattr() must have been initialized with a call to tcgetattr()
    // overwise behaviour is undefined
    if (tcgetattr(serial_dev, &tty) != 0)
    {
        printf("Error %i from tcgetattr: %s\n", errno, strerror(errno));
    }
    // parity bit
    tty.c_cflag &= ~PARENB; // Clear parity bit, disabling parity (most common)
    if (parity)
        tty.c_cflag |= PARENB; // Set parity bit, enabling parity
    // stop bit, default is fine
    tty.c_cflag &= ~CSTOPB; // Clear stop field, only one stop bit used in
                            // communication (most common)
    // data bits
    tty.c_cflag &= ~CSIZE;
    tty.c_cflag |= data_bits;
    // disable canonical mode
    tty.c_lflag &= ~ICANON;
    // disable software flow control
    tty.c_iflag &= ~(IXON | IXOFF | IXANY); // Turn off s/w flow ctrl
    // disable special handling of chars
    tty.c_iflag &= ~(IGNBRK | BRKINT | PARMRK | ISTRIP | INLCR | IGNCR |
                     ICRNL); // Disable any special handling of received bytes
    // output options
    tty.c_oflag &= ~OPOST; // Prevent special interpretation of output bytes
                           // (e.g. newline chars)
    tty.c_oflag &=
        ~ONLCR; // Prevent conversion of newline to carriage return/line feed
    // Wait for up to 1s (10 deciseconds), returning as soon as any data is
    // received.
    tty.c_cc[VTIME] = 10;
    tty.c_cc[VMIN] = 0;
    // Set in/out baud rate
    cfsetspeed(&tty, baud_rate);
    // Save tty settings, also checking for error
    if (tcsetattr(serial_dev, TCSANOW, &tty) != 0)
    {
        printf("Error %i from tcsetattr: %s\n", errno, strerror(errno));
    }
}

int Serial::send(const vector<uint8_t> &msg)
{
    return write(serial_dev, &msg[0], msg.size());
}

vector<uint8_t> Serial::receive(size_t bytes)
{
    assert(bytes <= sizeof(read_buf));
    read(serial_dev, read_buf, bytes);
    return vector<uint8_t>{read_buf, read_buf + bytes};
}

std::string Serial::readline()
{
    std::string res;
    do
    {
        read_buf[0] = '\0';
        read(serial_dev, read_buf, 1);
        res.push_back((char)read_buf[0]);
    } while (res.back() != '\n');
    // remove newline chars
    while (res.back() == '\r' || res.back() == '\n')
        res.pop_back();
    return res;
}

const vector<string> ListSerialPorts()
{
    const string tty_path = "/sys/class/tty";
    DIR *dir;
    dirent *ent;
    dir = opendir(tty_path.c_str());
    vector<string> res;
    if (dir != nullptr)
    {
        while ((ent = readdir(dir)) != nullptr)
        {
            string tty_name = string(ent->d_name);
            string device_path = tty_path + "/" + tty_name + "/" + "device";
            if (access(device_path.c_str(), F_OK) == 0)
            {
                char sym_link[256] = "";
                readlink(device_path.c_str(), sym_link, 256);
                // possible that pointing to the driver
                if (string(sym_link) != "../../../serial8250")
                {
                    res.push_back("/dev/" + tty_name);
                }
            }
        }
        closedir(dir);
    }
    else
    {
        std::cerr << "Error: Getting serial ports failed" << std::endl;
    }
    return res;
}
} // namespace Serial
