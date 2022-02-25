import random
from math import sqrt
from cmath import rect, phase
import numpy as np
import scipy.stats
from scipy.stats import norm
from numpy import pi, cos, sin


class ParticleFilterPoseEstimator:
    def __init__(self):
        self.pose_list = []
        self.average_pose = []
        self.average_covariance = []
        self._k_d = 0.05 * 0.05
        self._time_step = 0.1
        self._k_theta = (5.0 * 5.0 / 360.0) * (pi / 180.0)
        self._k_drift = (2.0 * 2.0) / 1.0 * (pi / 180.0) ** 2

    def initialize(self, pose_from, pose_to, n=200):
        area = 3
        for i in range(0, n):
            tmp_pose = [0, 0, 0]
            tmp_pose[0] = pose_from[0] + random.uniform(-1, 1) * (area / 2)
            tmp_pose[1] = pose_from[1] + random.uniform(-1, 1) * (area / 2)

            if pose_from[2] < pose_to[2]:
                tmp_pose[2] = random.uniform(pose_from[2], pose_to[2])
            else:
                tmp_pose[2] = random.uniform(pose_to[2], pose_from[2])

            self.pose_list.append(tmp_pose)

    def integrate_movement(self, motion, sigma_motion):
        for p in self.pose_list:
            v = motion[0]
            omega = motion[1]

            # Add noise to v:
            v_noisy = v + random.gauss(0.0, sqrt(sigma_motion[0, 0]))

            # Add noise to omega:
            omega_noisy = omega + random.gauss(0.0, sqrt(sigma_motion[1, 1]))

            d = v_noisy * self._time_step
            d_theta = omega_noisy * self._time_step

            theta = p[2]
            p[0] += d * cos(theta + 0.5 * d_theta)
            p[1] += d * sin(theta + 0.5 * d_theta)
            p[2] = (theta + d_theta) % (2 * pi)

        self.get_pose()
        self.get_covariance()

    def integrate_measurement(self, dist_list, alpha_list, distant_map):
        if dist_list is None and alpha_list is None:
            return
        weights = []
        intervals = []
        tmp_weight = 0
        intervals.append(tmp_weight)
        for p in self.pose_list:
            w = self.get_particle_weight(p, dist_list, alpha_list, distant_map)
            weights.append(w)
            intervals.append(w + tmp_weight)
            tmp_weight = w + tmp_weight
        #self.resample_roulette(intervals, sum(weights))
        self.resample_spoke_wheel(weights)

    def resample_roulette(self, intervals, weights_sum):
        particles = []
        for i in range(len(self.pose_list)):
            random_number = np.random.uniform(0, weights_sum * 1.000001)
            interval_index = self.binary_search(intervals, random_number)
            particle = self.pose_list[interval_index]
            particles.append(particle)
        self.pose_list = np.array(particles)

    def binary_search(self, intervals, target):
        start = 0
        end = len(intervals) - 1
        mid = 0
        while start <= end:
            mid = (start + end) // 2
            if intervals[mid] > target:
                end = mid - 1
            elif intervals[mid] < target:
                start = mid + 1
            else:
                return mid - 1
        return mid - 1

    # Spoke wheel method
    def resample_spoke_wheel(self, weights):
        weights_sum = np.sum(weights)
        spoke_distance = weights_sum / len(weights)
        r = np.random.uniform(0, spoke_distance * 1.000001)
        counted_weights = 0
        spoke = r
        particles = []

        for i in range(len(weights)):
            counted_weights += weights[i]
            while counted_weights > spoke:
                particles.append(self.pose_list[i])
                spoke += spoke_distance

            if i == len(weights) - 1:
                while counted_weights > spoke:
                    particles.append(self.pose_list[0])
                    spoke += spoke_distance

        if len(particles) == 0:
            print()
        if len(particles) != len(self.pose_list):
            return self.pose_list
        self.pose_list = np.array(particles)

    def get_particle_weight(self, particle, dist_list, alpha_list, distant_map):
        w = 1
        for k in range(0, len(dist_list)):
            distance = dist_list[k]
            alpha = alpha_list[k]
            if distance is None:
                continue
            x = distance * np.cos(alpha + particle[2]) + particle[0]
            y = distance * np.sin(alpha + particle[2]) + particle[1]
            dist = distant_map.getValue(x, y)
            if dist is None:
                return 0
            # very accurate but very slow
            # w *= scipy.stats.norm(0.0, 0.4**2).pdf(dist)
            w *= self.norm_distribution(dist, 0.0, 0.4)
        return w

    def norm_distribution(self, x, mean, sd):
        return np.exp(-(x - mean) ** 2 / (2 * (sd ** 2))) / (2 * np.pi * (sd ** 2)) ** 0.5

    def get_covariance(self):
        x = []
        y = []
        omega = []
        for p in self.pose_list:
            x.append(p[0])
            y.append(p[1])
            omega.append(p[2])

        covariance = np.array(np.cov([x, y]))
        variance = np.cov(omega)

        average_covariance = np.zeros((3, 3))
        average_covariance[0, 0] = covariance[0, 0]
        average_covariance[0, 1] = covariance[0, 1]
        average_covariance[1, 0] = covariance[1, 0]
        average_covariance[1, 1] = covariance[1, 1]
        average_covariance[2, 2] = variance

        self.average_covariance = average_covariance
        return self.average_covariance

    def get_pose(self):
        avg_x = 0
        avg_y = 0
        omegas = []
        for p in self.pose_list:
            avg_x += p[0]
            avg_y += p[1]
            omegas.append(p[2])
        avg_x /= len(self.pose_list)
        avg_y /= len(self.pose_list)
        avg_omega = mean_angle(omegas)

        self.average_pose = [avg_x, avg_y, avg_omega]
        return self.average_pose

def mean_angle(angles):
    return phase(sum(rect(1, d) for d in angles)/len(angles))