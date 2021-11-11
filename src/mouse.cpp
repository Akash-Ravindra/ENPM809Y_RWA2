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

void rwa2::Mouse::display_walls()
{
  for (int x = 0; x < m_maze_width; x += 1)
  {
    for (int y = 0; y < m_maze_height; y += 1)
    {
      if (m_maze.at(x).at(y).get_visited()) //Color all non visited node with a diff color
      {
        if (m_maze.at(x).at(y).is_wall(direction::NORTH))
        {
          // display this wall in the simulator
          API::setWall(x, y, 'n');
        }

        if (m_maze.at(x).at(y).is_wall(direction::EAST))
        {
          // display this wall in the simulator
          API::setWall(x, y, 'e');
        }

        if (m_maze.at(x).at(y).is_wall(direction::SOUTH))
        {
          // display this wall in the simulator
          API::setWall(x, y, 's');
        }

        if (m_maze.at(x).at(y).is_wall(direction::WEST))
        {
          // display this wall in the simulator
          API::setWall(x, y, 'w');
        }
        // display the number of walls surrounding the current node
        API::setText(
            x, y, std::to_string(m_maze.at(x).at(y).compute_number_of_walls()));
        //color All visited cells in blue
        API::setColor(x, y, 'b');
      }
    }
  }
}
bool rwa2::Mouse::search_maze(Node *current_node)
{
  //Coordinated of the current node
  int x{current_node->get_cords().at(0)};
  int y{current_node->get_cords().at(1)};
  //coordinated of the next node
  std::array<int, 2> next_node{{0,0}};

  //If current node is not the goal
  if (!((x == 7 || x == 8) && (y == 7 || y == 8)))
  {
    if (m_stack_of_nodes.empty())
      m_stack_of_nodes.push(current_node);
  } //If current node is one of the goals
  else
  {
    m_stack_of_nodes.push(current_node);
    return true;
  }

  //Check if this node is in the list
  if (!current_node->get_visited())
  {//then check if vector to see.. UNECESSARY BUT KEPT
    if (!(std::find(m_list_of_nodes.begin(), m_list_of_nodes.end(),
                    current_node->get_cords()) != m_list_of_nodes.end()))
    {
      // log("First Visit");
      m_list_of_nodes.push_back(current_node->get_cords());// Add to vector
      look_around(current_node);//Find all surrounding walls
      current_node->set_visited(true);
    }
  }
  //Check if it can go NORTH based on wall and visited
  if (!m_maze.at(x).at(y).is_wall(direction::NORTH) &&
      !is_neighbor_visited(current_node, direction::NORTH))
  {
    //SET next Node and move forward
    log("Going North");
    next_node = {x, y + 1};
    if (m_stack_of_nodes.top() != current_node)//To prevent double addition of junction nodes
      m_stack_of_nodes.push(current_node);
    turn_until_direction(direction::NORTH);
    move_forward();
  }
  //Check if it can go EAST based on wall and visited
  else if (!m_maze.at(x).at(y).is_wall(direction::EAST) &&
           !is_neighbor_visited(current_node, direction::EAST))
  {
    log("Going East");
    next_node = {x + 1, y};
    if (m_stack_of_nodes.top() != current_node)
      m_stack_of_nodes.push(current_node);
    turn_until_direction(direction::EAST);
    move_forward();
  }
  //Check if it can go SOUTH based on wall and visited
  else if (!m_maze.at(x).at(y).is_wall(direction::SOUTH) &&
           !is_neighbor_visited(current_node, direction::SOUTH))
  {
    log("Going South");
    next_node = {x, y - 1};
    if (m_stack_of_nodes.top() != current_node)
      m_stack_of_nodes.push(current_node);
    turn_until_direction(direction::SOUTH);
    move_forward();
  }
  //Check if it can go WEST based on wall and visited
  else if (!m_maze.at(x).at(y).is_wall(direction::WEST) &&
           !is_neighbor_visited(current_node, direction::WEST))
  {
    log("Going West");
    next_node = {x - 1, y};
    if (m_stack_of_nodes.top() != current_node)
      m_stack_of_nodes.push(current_node);
    turn_until_direction(direction::WEST);
    move_forward();
  }
  //The node is a deadend
  else
  {//check if you can backtrack
    if (!m_stack_of_nodes.empty())
    {
      log("No Path");
      if (m_stack_of_nodes.top() == current_node)//make double removal cuz of deadends
        m_stack_of_nodes.pop();
      next_node = m_stack_of_nodes.top()->get_cords();
      move_backward(current_node, m_stack_of_nodes.top());
    }
    else
      return false;
  }
  if (!m_stack_of_nodes.empty())
  {
    log("Going Deeper");
    search_maze(&m_maze.at(next_node.at(0)).at(next_node.at(1)));
    return true;
  }
  else
    return false;
}
void rwa2::Mouse::look_around(Node *cn)
{
  cn->set_wall(m_look_up_table.at(m_direction).at(0), API::wallFront());
  cn->set_wall(m_look_up_table.at(m_direction).at(1), API::wallRight());
  cn->set_wall(m_look_up_table.at(m_direction).at(3), API::wallLeft());
  cn->set_wall(m_look_up_table.at(m_direction).at(2), false);
}
void rwa2::Mouse::turn_left()
{
  m_direction = m_direction > 0 ? m_direction -= 1 : direction::WEST;
  API::turnLeft();
}
void rwa2::Mouse::turn_right()
{
  m_direction = m_direction < 3 ? m_direction += 1 : direction::NORTH;
  API::turnRight();
}
void rwa2::Mouse::turn_until_direction(direction heading)
{
  log(std::to_string(heading));
  // log(std::to_string(m_direction));
  if (heading == m_direction)
    return;
  if ((heading - m_direction) < 0)
    turn_left();
  else
    turn_right();
  if (heading != m_direction)
    turn_until_direction(heading);
}
void rwa2::Mouse::flip_around()
{
  turn_right();
  turn_right();
}
void rwa2::Mouse::move_forward() { API::moveForward(); }
void rwa2::Mouse::move_backward(Node *start, Node *end)
{
  direction heading;
  log(std::to_string(start->get_cords().at(0)) + "," +
      std::to_string(start->get_cords().at(1)) + ":" +
      std::to_string(end->get_cords().at(0)) + "," +
      std::to_string(end->get_cords().at(1)));
  if ((start->get_cords().at(0) - end->get_cords().at(0)) == 1)
    heading = direction::WEST;
  else if ((start->get_cords().at(0) - end->get_cords().at(0)) == -1)
    heading = direction::EAST;
  if (((start->get_cords().at(1) - end->get_cords().at(1)) == -1))
    heading = direction::NORTH;
  else if ((start->get_cords().at(1) - end->get_cords().at(1)) == 1)
    heading = direction::SOUTH;
  turn_until_direction(heading);
  move_forward();
}
bool rwa2::Mouse::is_neighbor_visited(Node *cn, direction h)
{
  int x{cn->get_cords().at(0)};
  int y{cn->get_cords().at(1)};
  switch (h)
  {
  case 0: // North
    return {m_maze.at(x).at(y + 1).get_visited()};
    break;
  case 1: // East
    return {m_maze.at(x + 1).at(y).get_visited()};
    break;
  case 2: // South
    return {m_maze.at(x).at(y - 1).get_visited()};
    break;
  case 3: // West
    return {m_maze.at(x - 1).at(y).get_visited()};
    break;
  default:
    return {m_maze.at(x).at(y).get_visited()};
    break;
  }
}
void rwa2::Mouse::reset_mouse() { API::ackReset(); }
std::array<int, 2> rwa2::Mouse::my_neighbor_cords(std::array<int, 2> cords,
                                                  direction heading)
{
  switch (heading)
  {
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
void rwa2::Mouse::display_path()
{
  if (m_stack_of_nodes.empty())
    return;
  while (!m_stack_of_nodes.empty())
  {
    API::setColor(m_stack_of_nodes.top()->get_cords().at(0), m_stack_of_nodes.top()->get_cords().at(1), 'g');
    m_stack_of_nodes.pop();
  }
}