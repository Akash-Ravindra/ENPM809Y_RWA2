/**
 * @file node.h
 * @author Alvina Alex (alvina@umd.edu)
 * @brief
 * @version 0.1
 * @date 2021-11-08
 *
 * @copyright Copyright (c) 2021
 *
 */

#ifndef NODE_H
#define NODE_H

#include "../util/util.h"
#include <array>
namespace rwa2 {
/**
 * @brief Class to represent a node (cell) in a maze.
 *
 *A node is just a space delimited by 4 walls
 *
 */
class Node {
public:
  Node() {
    for (int i = 0; i < 4; i += 1) {
      m_walls[i] = false;
    }
  }
  /**
   * @brief Get the cords object
   * @details Gets the x,y of m_coords
   * @return const std::array<int, 2> 
   */
  const std::array<int, 2> get_cords() { return m_cords; }
  /**
   * @brief Set the cords object
   * @details Sets the x,y of new m_cords
   * @param new_cords 
   */
  void set_cords(std::array<int, 2> *new_cords) { m_cords = *new_cords; }
  void set_cords(std::array<int, 2> new_cords) { m_cords = new_cords; }
  /**
   * @brief Get the visited object
   * @details Checks if the object is visited or not
   * @return true 
   * @return false 
   */
  const bool get_visited() { return m_visited; }
  /**
   * @brief Set the visited object
   * @details Sets if an object is visited as true;
   * @param state 
   */
  void set_visited(bool state) { m_visited = state; }
  /**
   * @brief Set the wall of a cell
   *
   * @param direction NORTH, EAST, SOUTH, or WEST
   * @param is_wall true if there is a wall, otherwise false
   */
  void set_wall(direction direction, bool is_wall);
  /**
   * @brief Return whether or not there is a wall in a cell
   *
   * @param direction Direction to set for wall (NORTH, EAST, SOUTH, or WEST)
   * @return true There is a wall in the given direction in the cell
   * @return false There is no wall in the given direction in the cell
   */
  bool is_wall(direction direction) const;
  /**
   * @brief Compute the number of walls surrounding a node
   *
   * @return int Number of walls surrounding a node
   */
  int compute_number_of_walls() const;

private:
  std::array<bool, 4> m_walls; // all four walls in a cell
  std::array<int, 2> m_cords{};//x y position of the node
  bool m_visited{false};// if the node is previously visited or not; default set to false initially
};
} // namespace rwa2
#endif
