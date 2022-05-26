from enum import IntEnum, auto
import rospy
from opencat.srv import base_task
from dataclasses import dataclass


class Command(IntEnum):
    """
    available command type
    """
    "Control Commands"
    SHUT_DOWN = 0  # rest and shutdown all servos
    SWITCH_GYRO = auto()  # switch whether to use IMU data
    PAUSE_MOTION = auto()  # TODO: difference between shutdown?
    CALIBRATE = auto()  # Calibration mode
    SWITCH_RECOVERING = auto()  # TODO: check if this can be disabled
    REPEAT_SKILL = auto()  # repeat last called skill
    PLAY_CUSTOM_SKILL = auto()  # play custom defined skill
    MOVE_JOINT_SEQUENCE = auto()  # move joints in sequence
    MOVE_JOINTS_SIMULTANEOUS = auto()  # move joints all at once
    SET_JOINTS = auto()  # set all joints at once
    PLAY_MELODY = auto()  # play built-in melody
    PLAY_CUSTOM_SOUND = auto()  # play the cutom provided sound
    "Gaits"
    STEPPING = auto()  # stepping on the same spot
    BACK = auto()  # going back
    BACK_LEFT = auto()  # going back and left
    BACK_RIGHT = auto()  # going back and right
    CRAWL = auto()  # crawl forward
    CRAWL_LEFT = auto()  # crawl left
    CRAWL_RIGHT = auto()  # crawl right
    WALK = auto()  # walk forward
    WALK_LEFT = auto()  # walk left
    WALK_RIGHT = auto()  # walk right
    TROT = auto()  # trot forward
    TROT_LEFT = auto()  # trot left
    TROT_RIGHT = auto()  # trot right
    BOUND = auto()  # not recommended
    "Postures"
    BALANCE = auto()  # balancing mode
    BUTT_UP = auto()  # raise hip
    CALIB_POSE = auto()  # Calibration pose, make easy to calibrate joints
    REST = auto()  # rest mode TODO: difference between SHUT_DOWN
    SIT = auto()
    SLEEP = auto()
    STRETCH = auto()
    ZERO = auto()  # template for designing new posture
    "Behavior"
    CHECK_AROUND = auto()
    GREETING = auto()
    PEE = auto()
    PUSH_UP = auto()
    MIMIC_DEATH = auto()
    BACK_FLIP = auto()


@dataclass
class Task:
    """
    Task dataclass
    """
    cmd: Command
    arguments: list
    delay: float


class ServiceClient:
    """
    opencat ros service client wrapper
    """

    def __init__(self):
        rospy.wait_for_service('opencat_send_task')
        self.send_task = rospy.ServiceProxy('opencat_send_task', base_task)

    def SendTask(self, task: Task):
        """
        send task by calling service
        """
        self.send_task(int(task.cmd), task.arguments, task.delay)

    def SendMultipleTasks(self, tasks: list):
        """
        send multiple tasks together
        """
        for task in tasks:
            self.SendTask(task)
