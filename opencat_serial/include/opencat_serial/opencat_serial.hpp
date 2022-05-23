/**
 * @brief Serial library for opencat
 * @file
 * @author C.C
 * @date 2022.05.22
 **/
#ifndef OPENCAT_SERIAL_H_
#define OPENCAT_SERIAL_H_
#include "opencat_serial/serial.hpp"
#include <chrono>
#include <string>
#include <thread>
#include <vector>

using std::vector;

namespace OpenCat
{
/**
 * @brief list all commands available
 **/
enum Command : uint8_t
{
    /** Control Commands */
    SHUT_DOWN,                // rest and shutdown all servos
    SWITCH_GYRO,              // switch whether to use IMU data
    PAUSE_MOTION,             // TODO: difference between shutdown?
    CALIBRATE,                // Calibration mode
    SWITCH_RECOVERING,        // TODO: check if this can be disabled
    REPEAT_SKILL,             // repeat last called skill
    PLAY_CUSTOM_SKILL,        // play custom defined skill
    MOVE_JOINT_SEQUENCE,      // move joints in sequence
    MOVE_JOINTS_SIMULTANEOUS, // move joints all at once
    SET_JOINTS,               // set all joints at once

    /** Gaits */
    STEPPING,     // stepping on the same spot
    BACK,        // going back
    BACK_LEFT,   // TODO: add description
    BACK_RIGHT,  // TODO: add description
    CRAWL,       // crawl forward
    CRAWL_LEFT,  // crawl left
    CRAWL_RIGHT, // crawl right
    WALK,        // walk forward
    WALK_LEFT,   // walk left
    WALK_RIGHT,  // walk right
    TROT,        // trot forward
    TROT_LEFT,   // trot left
    TROT_RIGHT,  // trot right
    BOUND,       // not recommended

    /** Postures */
    BALANCE,    // balancing mode
    BUTT_UP,    // raise hip
    CALIB_POSE, // Calibration pose, make easy to calibrate joints
    REST,       // rest mode TODO: difference between SHUT_DOWN
    SIT,
    SLEEP,
    STRETCH,
    ZERO, // template for designing new posture

    /** Behavior */
    CHECK_AROUND,
    GREETING,
    PEE,
    PUSH_UP,
    MIMIC_DEATH,
    BACK_FLIP
};

const vector<std::string> command_name{
    /** Control Commands */
    "d",   // SHUT_DOWN
    "g",   // SWITCH_GYRO
    "p",   // PAUSE_MOTION
    "c",   // CALIBRATE
    "krc", // RECOVERING
    "T",   // REPEAT_SKILL
    "K",   // PLAY_CUSTOM_SKILL
    "M",   // MOVE_JOINT_SEQUENCE
    "I",   // MOVE_JOINTS_SIMULTANEOUS
    "L",   // SET_JOINTS

    /** Gaits */
    "kvt",  // STEPPING
    "kbk",  // BACK
    "kbkL", // BACK_LEFT
    "kbkR", // BACK_RIGHT
    "kcrF", // CRAWL
    "kcrL", // CRAWL_LEFT
    "kcrR", // CRAWL_RIGHT
    "kwkF", // WALK
    "kwkL", // WALK_LEFT
    "kwkR", // WALK_RIGHT
    "ktrF", // TROT
    "ktrL", // TROT_LEFT
    "ktrR", // TROT_RIGHT
    "kbdF", // BOUND

    /** Postures */
    "kbalance", // BALANCE
    "kbuttUp",  // BUTT_UP
    "kcalib",   // CALIB_POSE
    "krest",    // REST
    "ksit",     // SIT
    "ksleep",   // SLEEP
    "kstr",     // STRETCH
    "kzero",    // ZERO

    /** Behavior */
    "kck",  // CHECK_AROUND
    "khi",  // GREETING
    "kpee", // PEE
    "kpu",  // PUSH_UP
    "kpd",  // MIMIC_DEATH
    "kbf"   // BACK_FLIP
};

struct Task
{
    Task(Command _cmd) : cmd(_cmd), arguments{}, delay(0){};
    Task(Command _cmd, float _delay) : cmd(_cmd), arguments{}, delay(_delay){};
    Command cmd;
    vector<int8_t> arguments;
    float delay;
};

/**
 * @brief wrapper class to communicate with OpenCat robot
 * @inherit ::Serial::Serial, protected as we don't need to send arbitrary data
 **/
class Robot : protected ::Serial::Serial
{
  public:
    /**
     * @brief default constructor
     * @param serial_port: serial port to connect the dog
     **/
    Robot(string serial_port);

    /**
     * @brief send task to robot
     * @param task: %Task data pack
     * @return response message from robot
     **/
    std::string SendTask(const Task task);

  protected:
    static const speed_t BAUD_RATE = B115200;
};
} // namespace OpenCat

#endif // OPENCAT_SERIAL_H_
