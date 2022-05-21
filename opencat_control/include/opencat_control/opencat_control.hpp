#ifndef OPENCAT_CONTROL_H_
#define OPENCAT_CONTROL_H_
#include "opencat_control/control_srv.h"
#include "serial.hpp"
#include <string>
#include <vector>
using opencat_control::control_srv;
using std::vector;

namespace OpenCat
{
/**
 * @brief list all commands available
 **/
enum Command : uint8_t
{
    /** Control Commands */
    SHUT_DOWN, // rest and shutdown all servos
    SWITCH_GYRO,
    PAUSE_MOTION,      // TODO: difference between shutdown?
    CALIBRATE,         // Calibration mode
    SWITCH_RECOVERING, // TODO: check if this can be disabled
    MOVE_JOINTS,

    /** Gaits */
    STEPING, // stepping on the same spot
    BACK,
    BACK_LEFT,
    BACK_RIGHT,
    CRAWL,
    CRAWL_LEFT,
    CRAWL_RIGHT,
    WALK,
    WALK_LEFT,
    WALK_RIGHT,
    TROT,
    TROT_LEFT,
    TROT_RIGHT,
    BOUND, // not recommended

    /** Postures */
    BALANCE, // balancing mode
    BUTT_UP,
    CALIB_POSE, // Calibration pose, make easy to calibrate joints
    REST,
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

const vector<std::string> command_name({
    /** Control Commands */
    "d",  // SHUT_DOWN
    "g",  // SWITCH_GYRO
    "p",  // PAUSE_MOTION
    "c",  // CALIBRATE
    "rc", // SWITCH_RECOVERING
    "m"   // MOVE_JOINTS

    /** Gaits */
    "kvt",  // STEPING
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
});

// serial interface
Serial serial("/dev/ttyUSB0", B115200);

/**
 * @brief handle RPC service call and send command to OpenCat
 * @param req: %Request received
 * @param res: %Response to be sent
 **/
bool send_command(control_srv::Request &req, control_srv::Response &res);
} // namespace OpenCat

#endif // OPENCAT_CONTROL_H_
