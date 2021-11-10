/**
 * @file mouse.cpp
 * @author Akash Ravindra (aravind2@umd.edu)
 * @brief
 * @version 0.1
 * @date 2021-11-09
 *
 * @copyright Copyright (c) 2021
 *
 */
#include "../include/mouse/mouse.h"
#include "../include/api/api.h"
#include <algorithm>
#include <string>

void rwa2::Mouse::display_walls() {
  for (int x = 0; x < m_maze_width; x += 1) {
    for (int y = 0; y < m_maze_height; y += 1) {
      if (m_maze.at(x).at(y).is_wall(direction::NORTH)) {
        // display this wall in the simulator
        API::setWall(x, y, 'n');
      }

      if (m_maze.at(x).at(y).is_wall(direction::EAST)) {
        // display this wall in the simulator
        API::setWall(x, y, 'e');
      }

      if (m_maze.at(x).at(y).is_wall(direction::SOUTH)) {
        // display this wall in the simulator
        API::setWall(x, y, 's');
      }

      if (m_maze.at(x).at(y).is_wall(direction::WEST)) {
        // display this wall in the simulator
        API::setWall(x, y, 'w');
      }
      // display the number of walls surrounding the current node
      API::setText(
          x, y, std::to_string(m_maze.at(x).at(y).compute_number_of_walls()));
    }
  }
}
bool rwa2::Mouse::search_maze(std::array<int, 2> current_node) {
  int x{current_node.at(0)};
  int y{current_node.at(1)};
  std::array<int, 2> next_node{};
  std::array<int, 2> previous_node{};
  if (!m_stack_of_nodes.empty())
    previous_node = m_stack_of_nodes.top();
  log("Entered Node");
  if (!((x == 7 || x == 8) && (y == 7 || y == 8))) {
    m_stack_of_nodes.push(current_node);
  } else {
    m_stack_of_nodes.push(current_node);
    return true;
  }
  if (!(std::find(m_list_of_nodes.begin(), m_list_of_nodes.end(),
                  current_node) != m_list_of_nodes.end())) {
    log("First Visit");
    m_list_of_nodes.push_back(current_node);
    look_around(&current_node);
  }
  if (!m_maze.at(x).at(y).is_wall(direction::NORTH) &&
      previous_node != my_neighbor_cords(current_node, direction::NORTH)) {
    log("No wall North");
    next_node = {x, y + 1};
    // m_stack_of_nodes.push(next_node);
    turn_until_direction(direction::NORTH);
    move_forward();
    if (search_maze(next_node))
      return true;
  }
  if (!m_maze.at(x).at(y).is_wall(direction::EAST) &&
      previous_node != my_neighbor_cords(current_node, direction::EAST)) {
    log("No wall East");
    next_node = {x + 1, y};
    // m_stack_of_nodes.push(next_node);
    turn_until_direction(direction::EAST);
    move_forward();
    if (search_maze(next_node))
      return true;
  }
  if (!m_maze.at(x).at(y).is_wall(direction::SOUTH) &&
      previous_node != my_neighbor_cords(current_node, direction::SOUTH)) {
    log("No wall South");
    next_node = {x, y - 1};
    // m_stack_of_nodes.push(next_node);
    turn_until_direction(direction::SOUTH);
    move_forward();
    if (search_maze(next_node))
      return true;
  }
  if (!m_maze.at(x).at(y).is_wall(direction::WEST) &&
      previous_node != my_neighbor_cords(current_node, direction::WEST)) {
    log("No wall West");
    next_node = {x - 1, y};
    // m_stack_of_nodes.push(next_node);
    turn_until_direction(direction::WEST);
    move_forward();
    if (search_maze(next_node))
      return true;
  }
  if (!m_stack_of_nodes.empty()) {
    m_stack_of_nodes.pop();
    move_backward();
    return false;
  }
  return false;
}
void rwa2::Mouse::look_around(std::array<int, 2> *cn) {
  Node *check_node = &m_maze.at(cn->at(0)).at(cn->at(1));
  check_node->set_wall(m_look_up_table.at(m_direction).at(0), API::wallFront());
  check_node->set_wall(m_look_up_table.at(m_direction).at(1), API::wallRight());
  check_node->set_wall(m_look_up_table.at(m_direction).at(3), API::wallLeft());
  check_node->set_wall(m_look_up_table.at(m_direction).at(2), false);
}
void rwa2::Mouse::turn_left() {
  m_direction = m_direction > 0 ? m_direction -= 1 : direction::WEST;
  API::turnLeft();
}
void rwa2::Mouse::turn_right() {
  m_direction = m_direction < 3 ? m_direction += 1 : direction::NORTH;
  API::turnRight();
}
void rwa2::Mouse::turn_until_direction(direction heading) {
  log(std::to_string(heading));
  log(std::to_string(m_direction));
  if (heading == m_direction)
    return;
  if ((heading - m_direction) < 0)
    turn_left();
  else
    turn_right();
  if (heading != m_direction)
    turn_until_direction(heading);
}
void rwa2::Mouse::flip_around() {
  turn_right();
  turn_right();
}
void rwa2::Mouse::move_forward() { API::moveForward(); }
void rwa2::Mouse::move_backward() {
  flip_around();
  API::moveForward();
  flip_around();
}
void rwa2::Mouse::reset_mouse() { API::ackReset(); }
std::array<int, 2> rwa2::Mouse::my_neighbor_cords(std::array<int, 2> cords,
                                                  direction heading) {
  switch (heading) {
  case 0: // North
    return {cords.at(0), cords.at(1) + 1};
    break;
  case 1: // East
    return {cords.at(0) + 1, cords.at(1)};
    break;
  case 2: // South
    return {cords.at(0), cords.at(1) - 1};
    break;
  case 3: // West
    return {cords.at(0) - 1, cords.at(1)};
    break;
  default:
    return {cords.at(0), cords.at(1)};
    break;
  }
}