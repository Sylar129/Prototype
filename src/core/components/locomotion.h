// Copyright (c) 2025 Sylar129. All rights reserved

#pragma once

#include "glm/glm.hpp"

namespace prototype {

class SpiralMotion {
 public:
  /**
   * @brief 构造函数：初始化光源球体的参数和初始状态。
   * @param radius R
   * @param center Pc
   * @param omegaTheta ω_θ
   * @param omegaPhi ω_φ
   * @param thetaInitial 初始角度 θ0
   * @param phiInitial 初始角度 φ0
   */
  SpiralMotion(double radius, const glm::vec3& center, double omegaTheta,
           double omegaPhi, double thetaInitial, double phiInitial)
      : radius(radius),
        center(center),
        omegaTheta(omegaTheta),
        omegaPhi(omegaPhi),
        currentTheta(thetaInitial),
        currentPhi(phiInitial) {
    // 初始化完成后，立即计算初始位置
    calculatePositionFromAngles();
  }

  /**
   * @brief 更新光源的位置信息，这是通过增量时间驱动的核心函数。
   * * @param deltaTime 自上次更新以来经过的时间 (Δt)。
   */
  void updatePosition(double deltaTime) {
    // 1. 更新当前角度状态 (增量运动)

    // θ_new = θ_old + ω_θ * Δt
    currentTheta += omegaTheta * deltaTime;

    // φ_new = φ_old + ω_φ * Δt
    currentPhi += omegaPhi * deltaTime;

    // 可选：将水平角限制在 [0, 2*PI) 范围内，以保持数值稳定
    currentTheta = std::fmod(currentTheta, 2.0 * M_PI);

    // 2. 根据新的角度状态计算新的笛卡尔坐标位置
    calculatePositionFromAngles();
  }

  // 成员变量 - 存储当前状态和参数
  glm::vec3 position;

  // --- 常量参数 ---
  glm::vec3 center;   // 球心/目标点 (Pc)
  double radius;      // 旋转半径 (R)
  double omegaTheta;  // 水平角速度 (ω_θ)
  double omegaPhi;    // 垂直角速度 (ω_φ)

 private:
  /**
   * @brief 私有方法：根据 currentTheta 和 currentPhi 重新计算 position 变量。
   */
  void calculatePositionFromAngles() {
    // R * sin(phi) 是半径在 XZ-平面上的投影
    double rProjection = radius * std::sin(currentPhi);

    // x = xc + R * sin(phi) * cos(theta)
    position.x = center.x + rProjection * std::cos(currentTheta);

    // y = yc + R * cos(phi)  (假设 Y 轴是垂直轴)
    position.y = center.y + radius * std::cos(currentPhi);

    // z = zc + R * sin(phi) * sin(theta)
    position.z = center.z + rProjection * std::sin(currentTheta);
  }

  // --- 状态变量 ---
 private:
  double currentTheta;  // 当前水平角度
  double currentPhi;    // 当前垂直角度
};

}  // namespace prototype
