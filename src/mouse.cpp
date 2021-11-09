#include "../include/mouse/mouse.h"
#include "../include/api/api.h"
#include "../include/util/util.h"
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
bool rwa2::Mouse::search_maze(int x, int y) {
  Node current_node{m_maze.at(x).at(y)};
  Node next_node;
  if (!(x == 7 || x == 8) && (y == 7 || y == 8)) {
    if (stack_of_nodes.empty())
      stack_of_nodes.push(current_node);
  } else {
    return true;
  }
  if (std::find(list_of_nodes.begin(), list_of_nodes.end(), current_node) !=
      list_of_nodes.end()) {
    list_of_nodes.push_back(current_node);
    look_around(current_node);
  }
  if (m_maze.at(x).at(y).is_wall(direction::NORTH)) {

  }
}
void rwa2::Mouse::look_around(Node check_node) {
  check_node.set_wall(direction::NORTH, API::wallFront());
  check_node.set_wall(direction::WEST, API::wallLeft());
  check_node.set_wall(direction::EAST, API::wallRight());
  check_node.set_wall(direction::SOUTH, false);
}
void rwa2::Mouse::turn_left() {}
void rwa2::Mouse::turn_right() {}
void rwa2::Mouse::move_forward() {}