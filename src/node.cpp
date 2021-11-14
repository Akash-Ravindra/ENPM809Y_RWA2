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

void rwa2::Node::set_wall(
    direction direction,
    bool is_wall) // Sets the wall in the specified direction if there is a
                  // preexisting wall
{
  m_walls.at(direction) = is_wall;
}

bool rwa2::Node::is_wall(direction direction)
    const // Checks if there is a wall in the specified 'directtion'
{
  return m_walls.at(direction);
}

int rwa2::Node::compute_number_of_walls() const {
  int weight{0}; // All weights initialised to zero
  int weight_n{0};
  int weight_s{0};
  int weight_e{0};
  int weight_w{0};
  if (is_wall(direction::NORTH)) // checks if there is a wall in the north
    weight_n = 1;                // if true a weight is increased
  if (is_wall(direction::EAST))  // checks if there is a wall in the east
    weight_s = 1;                // if true a weight is increased
  if (is_wall(direction::SOUTH)) // checks if there is a wall in the south
    weight_e = 1;                // if true a weight is increased
  if (is_wall(direction::WEST))  // checks if there is a wall in the west
    weight_w = 1;                // if true a weight is increased
  return weight + weight_n + weight_s + weight_e + weight_w;
}