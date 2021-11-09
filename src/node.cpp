/**
 * @file node.cpp
 * @author Akash Ravindra (aravind2@umd.edu)
 * @brief 
 * @version 0.1
 * @date 2021-11-09
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#include "../include/node/node.h"
#include "../include/util/util.h"

void rwa2::Node::set_wall(direction direction, bool is_wall) {
  m_walls.at(direction) = is_wall;
}

bool rwa2::Node::is_wall(direction direction) const {
  return m_walls.at(direction);
}

int rwa2::Node::compute_number_of_walls() const {
  int weight{0};
  int weight_n{0};
  int weight_s{0};
  int weight_e{0};
  int weight_w{0};
  if (is_wall(direction::NORTH))
    weight_n = 1;
  if (is_wall(direction::EAST))
    weight_s = 1;
  if (is_wall(direction::SOUTH))
    weight_e = 1;
  if (is_wall(direction::WEST))
    weight_w = 1;
  return weight + weight_n + weight_s + weight_e + weight_w;
}