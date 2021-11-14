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

void rwa2::Mouse::display_walls(Node *currentNode) {
  if (currentNode != NULL) { // Check if a specific node was provided to work on
    if (currentNode->is_wall(direction::NORTH)) // check the status of the wall
                                                // and update simulator
      API::setWall(currentNode->get_cords().at(0),
                   currentNode->get_cords().at(1), 'n');
    if (currentNode->is_wall(direction::EAST)) // check the status of the wall
                                               // and update simulator
      API::setWall(currentNode->get_cords().at(0),
                   currentNode->get_cords().at(1), 'e');
    if (currentNode->is_wall(direction::SOUTH)) // check the status of the wall
                                                // and update simulator
      API::setWall(currentNode->get_cords().at(0),
                   currentNode->get_cords().at(1), 's');
    if (currentNode->is_wall(direction::WEST)) // check the status of the wall
                                               // and update simulator
      API::setWall(currentNode->get_cords().at(0),
                   currentNode->get_cords().at(1), 'w');
    API::setText(
        currentNode->get_cords().at(0), currentNode->get_cords().at(1),
        std::to_string(
            m_maze.at(currentNode->get_cords().at(0))
                .at(currentNode->get_cords().at(1))
                .compute_number_of_walls())); // check the number of walls at
                                              // the node and update the text in
                                              // the simulator

  } else { // If no specific node was provided, color all the visited nodes in
           // BLUE and set text based on the number of walls in each node
    for (int x = 0; x < m_maze_width; x += 1) {
      for (int y = 0; y < m_maze_height; y += 1) {
        if (m_maze.at(x)
                .at(y)
                .get_visited()) // Color all non visited node with a diff color
        {
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
              x, y,
              std::to_string(m_maze.at(x).at(y).compute_number_of_walls()));
          // color All visited cells in blue
          API::setColor(x, y, 'b');
        }
      }
    }
  }
}
bool rwa2::Mouse::search_maze(Node *current_node) {
  // Coordinates of the current node
  int x{current_node->get_cords().at(0)};
  int y{current_node->get_cords().at(1)};
  // coordinates of the next node
  std::array<int, 2> next_node{{0, 0}};

  // If current node is not the goal
  if (!((m_goal_position.at(0) == x) && (m_goal_position.at(1) == y))) {
    if (m_stack_of_nodes.empty())
      m_stack_of_nodes.push(current_node);
  } // If current node is one of the goals
  else {
    m_stack_of_nodes.push(current_node);
    return true;
  }

  // Check if this node is in the list
  if (!current_node->get_visited()) { // then check if vector to see..
                                      // UNECESSARY BUT KEPT
    if (!(std::find(m_list_of_nodes.begin(), m_list_of_nodes.end(),
                    current_node->get_cords()) != m_list_of_nodes.end())) {
      // log("First Visit");
      m_list_of_nodes.push_back(current_node->get_cords()); // Add to vector
      look_around(current_node); // Find all surrounding walls
      current_node->set_visited(true);
    }
  }
  display_walls(current_node);
  // Check if it can go NORTH based on wall and visited
  if (!m_maze.at(x).at(y).is_wall(direction::NORTH) &&
      !is_neighbor_visited(current_node, direction::NORTH)) {
    // SET next Node and move forward
    log("Going North");
    next_node = {x, y + 1};
    if (m_stack_of_nodes.top() !=
        current_node) // To prevent double addition of junction nodes during
                      // backtrack
      m_stack_of_nodes.push(current_node);
    turn_until_direction(direction::NORTH);
    move_forward();
  }
  // Check if it can go EAST based on wall and visited
  else if (!m_maze.at(x).at(y).is_wall(direction::EAST) &&
           !is_neighbor_visited(current_node, direction::EAST)) {
    log("Going East");
    next_node = {x + 1, y};
    if (m_stack_of_nodes.top() != current_node)
      m_stack_of_nodes.push(current_node);
    turn_until_direction(direction::EAST);
    move_forward();
  }
  // Check if it can go SOUTH based on wall and visited
  else if (!m_maze.at(x).at(y).is_wall(direction::SOUTH) &&
           !is_neighbor_visited(current_node, direction::SOUTH)) {
    log("Going South");
    next_node = {x, y - 1};
    if (m_stack_of_nodes.top() != current_node)
      m_stack_of_nodes.push(current_node);
    turn_until_direction(direction::SOUTH);
    move_forward();
  }
  // Check if it can go WEST based on wall and visited
  else if (!m_maze.at(x).at(y).is_wall(direction::WEST) &&
           !is_neighbor_visited(current_node, direction::WEST)) {
    log("Going West");
    next_node = {x - 1, y};
    if (m_stack_of_nodes.top() != current_node)
      m_stack_of_nodes.push(current_node);
    turn_until_direction(direction::WEST);
    move_forward();
  }
  // The node is a deadend
  else { // check if you can backtrack
    if (!m_stack_of_nodes.empty()) {
      log("No Path");
      if (m_stack_of_nodes.top() ==
          current_node) // prevent double removal of node when a deadend is
                        // reached
        m_stack_of_nodes.pop();
      next_node =
          m_stack_of_nodes.top()
              ->get_cords(); // copy the node that second to last on the stack
      move_to(current_node,
              m_stack_of_nodes.top()); // Move to the node that is specified by
                                       // the stack from the current node
    } else
      return false; // backtracking resulted in no path
  }
  if (!m_stack_of_nodes.empty()) {
    log("Exploring");
    search_maze(&m_maze.at(next_node.at(0))
                     .at(next_node.at(1))); // start search from the next node
    return true;
  } else
    return false; // If no path can be found!
}
void rwa2::Mouse::look_around(Node *cn) {
  // using the lookup table to set the walls based on the m_direction. Example,
  // if m_direction is east, lookuptable for left would correspond to North
  cn->set_wall(m_look_up_table.at(m_direction).at(0),
               API::wallFront()); // The front of the mouse
  cn->set_wall(m_look_up_table.at(m_direction).at(1),
               API::wallRight()); // the right side of the mouse
  cn->set_wall(m_look_up_table.at(m_direction).at(3),
               API::wallLeft()); // the left side of the mouse
  if (cn->get_cords() !=
      get_home_node()->get_cords()) // Make sure that the first node isnt
                                    // considered for this
    cn->set_wall(m_look_up_table.at(m_direction).at(2),
                 false); // The backside of the mouse is always false as that is
                         // how it entered the node
}
void rwa2::Mouse::turn_left() // Turns the mouse left
{
  m_direction =
      m_direction > 0
          ? m_direction -= 1
          : direction::WEST; // Update the m_direction by -1 and handle rollover
  API::turnLeft();
}
void rwa2::Mouse::turn_right() 
{
  // Turns the mouse right
  m_direction =
      m_direction < 3
          ? m_direction += 1
          : direction::NORTH; // Update the m_direction by 1 and handle rollover
  API::turnRight();
}
void rwa2::Mouse::turn_until_direction(
    direction heading) 
{
  // Turns the m_direction until it reaches the direction 'heading'
  // log(std::to_string(heading));// Prints the specified direction to turn
  // towards.
  // log(std::to_string(m_direction));
  if (heading ==
      m_direction) // if mouse direction is the same as specified direction
    return;
  if ((heading - m_direction) < 0) // if heading is greater than mouse direction the turn left
    turn_left();
  else//else turn right
    turn_right();
    turn_until_direction(heading);
}
void rwa2::Mouse::flip_around() 
{// Turns the mouse 180 degree
  turn_right();
  turn_right();
}
void rwa2::Mouse::move_forward() {
  API::moveForward();// Moves the mouse forward
} 
void rwa2::Mouse::move_to(Node *start,
                          Node *end) // Moves the mouse backward
{
  direction heading;

  /////////////////DEBUGGING/////////////
  // log(std::to_string(start->get_cords().at(0)) + "," +
  //     std::to_string(start->get_cords().at(1)) + ":" +
  //     std::to_string(end->get_cords().at(0)) + "," +
  //     std::to_string(end->get_cords().at(1)));
  /////////////////DEBUGGING/////////////
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
bool rwa2::Mouse::is_neighbor_visited(
    Node *cn, direction h) 
{
  // Checks if the neighbor node is visited 
  int x{cn->get_cords().at(0)};
  int y{cn->get_cords().at(1)};
  switch (h) {
  case 0:                                          // North
    return {m_maze.at(x).at(y + 1).get_visited()}; // Checks north neighbour
                                                   // node
    break;
  case 1:                                          // East
    return {m_maze.at(x + 1).at(y).get_visited()}; // Checks east neighbour node
    break;
  case 2:                                          // South
    return {m_maze.at(x).at(y - 1).get_visited()}; // Checks south neighbour
                                                   // node
    break;
  case 3:                                          // West
    return {m_maze.at(x - 1).at(y).get_visited()}; // Checks west neighbour node
    break;
  default:
    return {
        m_maze.at(x).at(y).get_visited()}; // Checks if current node is visited
    break;
  }
}
void rwa2::Mouse::reset_mouse() {
  // Resets the mouse in the sim and also the m_direction
  m_direction = direction::NORTH;
  API::ackReset();
} 

void rwa2::Mouse::display_path() 
{
  // Displays the final path found using DFS. Color is set to the path.
  std::stack<Node *> son{m_stack_of_nodes};
  if (son.empty())
    return;
  while (!son.empty()) {
    API::setColor(son.top()->get_cords().at(0), son.top()->get_cords().at(1),
                  'g');
    son.pop();
  }
  API::setText(m_goal_position.at(0), m_goal_position.at(1), "G1");
}

void rwa2::Mouse::maze_runner(std::stack<Node *> maze_stack) {
  //Used to run the mouse through the path that was discovered
  reset_mouse();
  std::vector<Node *> flippedStack = std::vector<Node *>();
  while (!maze_stack.empty()) {
    Node *d = maze_stack.top();
    flippedStack.push_back(d);
    maze_stack.pop();
  }//Copy stack into vector to allow for backtracking from home position(flip the stack)

  Node *Current_node = flippedStack.back();
  flippedStack.pop_back();//Pop the home position off the stack

  while (!flippedStack.empty()) {
    API::setColor(Current_node->get_cords().at(0),
                  Current_node->get_cords().at(1), 'G');//Set the color of the current node 
    move_to(Current_node, flippedStack.back());//move to the next node based on the current node
    Current_node = flippedStack.back();//update the current node
    flippedStack.pop_back();//pop off the current node
  }
}