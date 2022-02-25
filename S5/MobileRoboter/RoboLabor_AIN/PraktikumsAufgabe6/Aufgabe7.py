import random
from time import sleep

from matplotlib import pyplot as plt
from numpy import pi

from PoseEstimator.plotUtilities import plotPoseParticles, plotShow, plotPositions, plotPoseCovariance
from PraktikumsAufgabe6.ParticleFilterPoseEstimator import ParticleFilterPoseEstimator, mean_angle
from Robot_Simulator_V3 import simpleWorld
from Robot_Simulator_V3 import Robot
import numpy as np

robot_poses = []
particle_poses = []

def main():
    my_world = simpleWorld.buildWorld()

    my_robot = Robot.Robot()
    robot_initial_pose = [4.5, 5.5, np.deg2rad(90)]
    my_world.setRobot(my_robot, robot_initial_pose)

    # my_world.addDynObstacleLine(10, 10, 10, 12)
    # my_world.addDynObstacleLine(8, 4, 8, 7)

    my_grid = my_world.getDistanceGrid()

    particle_estimator = ParticleFilterPoseEstimator()
    particle_estimator.initialize([4.5, 5.5, np.deg2rad(110)], [4.5, 5.5, np.deg2rad(70)])

    initial_particles = np.array(particle_estimator.pose_list)
    initial_particles_pose = np.array(particle_estimator.get_pose())
    initial_particles_covariance = particle_estimator.get_covariance()

    curve_drive(my_robot, 1, 4, -180, particle_estimator, my_grid, my_world)

    final_particles = np.array(particle_estimator.pose_list)

    plt.plot([2, 16],[2,2], 'k')
    plt.plot([16, 16], [2, 12], 'k')
    plt.plot([16, 4], [12, 12], 'k')
    plt.plot( [4, 4], [12, 10], 'k')
    plt.plot( [4, 2], [10, 10], 'k')
    plt.plot( [2, 2], [10,  2], 'k')
    plotPoseCovariance(initial_particles_pose, initial_particles_covariance)
    plotPoseParticles(initial_particles, color="r")
    plotPoseParticles(final_particles, color="r")
    plotPositions(robot_poses, color="g")
    plotPositions(particle_poses)
    plotShow()

def curve_drive(robot, v, r, delta_theta, particle_estimator, distant_map, world):
    if v > robot._maxSpeed:
        v = robot._maxSpeed
    if v < -robot._maxSpeed:
        v = -robot._maxSpeed

    #print(robot._world.getTrueRobotPose())
    # Calculate the length the robot must walk on the circle
    circle_length = r * np.deg2rad(abs(delta_theta))

    # full s with speed v
    steps_full = int(circle_length/v)
    # for last step calculate Velocity ratio # to get the last missing length with reduced Velocity
    steps_rest = circle_length/v - steps_full

    #number of steps to complete length with given Velocity
    steps = steps_full / robot.getTimeStep()

    # for number of steps calculate the angle per step
    if steps_full == 0:
        angle_per_step = pi
    else:
        angle_per_step = delta_theta / steps_full

    for t in range(int(steps)):
        robot.move([v, np.deg2rad(angle_per_step)])
        robot_poses.append(world.getTrueRobotPose())
        particle_estimator.integrate_movement([v, np.deg2rad(angle_per_step)], robot.getSigmaMotion())
        particle_estimator.integrate_measurement(robot.sense(), robot.getSensorDirections(), distant_map)
        particle_poses.append(particle_estimator.get_pose())

    # complete length with reduced velocity and one last rotation
    if steps_rest != 0:
        robot.move([v * steps_rest, np.deg2rad(angle_per_step)])
        robot_poses.append(world.getTrueRobotPose())
        particle_estimator.integrate_movement([v * steps_rest, np.deg2rad(angle_per_step)], robot.getSigmaMotion())
        particle_estimator.integrate_measurement(robot.sense(), robot.getSensorDirections(), distant_map)
        particle_poses.append(particle_estimator.get_pose())


if __name__ == "__main__":
    main()

