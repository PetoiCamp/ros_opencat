/**
 * @brief unimportant data for opencat lib
 * @author C.C
 * @date 2022.05.23
 **/
#ifndef OPENCAT_SERIAL_DATA_H_
#define OPENCAT_SERIAL_DATA_H_
#include <string>
#include <vector>

namespace OpenCat
{
const std::vector<std::string> command_name{
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
    "o",   // PLAY_MELODY
    "B",   // PLAY_CUSTOM_SOUND

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

const std::vector<std::string> command_description{
    /** Control Commands */
    "shut down",            // SHUT_DOWN
    "switch IMU",           // SWITCH_GYRO
    "pause motion",         // PAUSE_MOTION
    "calibrate",            // CALIBRATE
    "recovering",           // RECOVERING
    "repeat custom skill",  // REPEAT_SKILL
    "play custom skill",    // PLAY_CUSTOM_SKILL
    "move joint sequence",  // MOVE_JOINT_SEQUENCE
    "index and set joints", // MOVE_JOINTS_SIMULTANEOUS
    "set all joints",       // SET_JOINTS
    "play built-in melody", // PLAY_MELODY
    "play custom melody",   // PLAY_CUSTOM_SOUND

    /** Gaits */
    "stepping",             // STEPPING
    "going back",           // BACK
    "going back and left",  // BACK_LEFT
    "going back and right", // BACK_RIGHT
    "crawl",                // CRAWL
    "crawl left",           // CRAWL_LEFT
    "crawl right",          // CRAWL_RIGHT
    "walk",                 // WALK
    "walk left",            // WALK_LEFT
    "walk right",           // WALK_RIGHT
    "trot",                 // TROT
    "trot left",            // TROT_LEFT
    "trot right",           // TROT_RIGHT
    "bound",                // BOUND

    /** Postures */
    "balance",          // BALANCE
    "butt up",          // BUTT_UP
    "calibration pose", // CALIB_POSE
    "rest",             // REST
    "sit",              // SIT
    "sleep",            // SLEEP
    "stretch",          // STRETCH
    "zero",             // ZERO

    /** Behavior */
    "check around", // CHECK_AROUND
    "greeting",     // GREETING
    "pee",          // PEE
    "push up",      // PUSH_UP
    "mimic death",  // MIMIC_DEATH
    "back flip"     // BACK_FLIP
};
} // namespace OpenCat

#endif // OPENCAT_SERIAL_DATA_H_
