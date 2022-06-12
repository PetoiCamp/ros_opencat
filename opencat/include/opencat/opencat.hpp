/**
 * @brief opencat header
 * @file
 * @author C.C
 * @date 2022.05.24
 **/
#ifndef OPENCAT_H_
#define OPENCAT_H_
#include "opencat/srv/base_task.hpp"
#include "rclcpp/rclcpp.hpp"
#include <cstdint>
#include <vector>
using std::vector;

namespace OpenCat
{
using namespace opencat::srv;
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
    PLAY_MELODY,              // play built-in melody
    PLAY_CUSTOM_SOUND,        // play the cutom provided sound

    /** Gaits */
    STEPPING,    // stepping on the same spot
    BACK,        // going back
    BACK_LEFT,   // going back and left
    BACK_RIGHT,  // going back and right
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

// alias for command arguments
using TaskArgs = vector<int16_t>;

/**
 * @brief task structure defining a task
 * @param cmd: %Command enum type specifying command
 * @param arguments: %vector storing possible parameter
 * @param delay: delay in seconds after finishing command
 **/
struct Task
{
    Task(Command _cmd) : cmd(_cmd), arguments{}, delay(0){};
    Task(Command _cmd, float _delay) : cmd(_cmd), arguments{}, delay(_delay){};
    Task(Command _cmd, TaskArgs _args, float _delay)
        : cmd(_cmd), arguments{_args.begin(), _args.end()}, delay(_delay){};
    Command cmd;
    TaskArgs arguments;
    float delay;
};

class ServiceClient
{
  public:
    ServiceClient();
    /**
     * @brief send task by calling service
     * @param task: %Task to send
     **/
    void SendTask(const Task &task);

    /**
     * @brief send multiple tasks
     * @param tasks: %vector of %task
     **/
    void SendMultipleTasks(const vector<Task> &tasks);

  protected:
    std::shared_ptr<rclcpp::Node> node;
    rclcpp::Client<BaseTask>::SharedPtr send_task;
};
} // namespace OpenCat
#endif // OPENCAT_H_
