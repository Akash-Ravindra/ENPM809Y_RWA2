/**
 * @file main.cpp
 * @author Akash Ravindra (aravind2@umd.edu)
 * @brief
 * @version 0.1
 * @date 2021=11=09
 *
 * @copyright Copyright (c) 2021
 *
 */

#include <array>
#include <iostream>
#include <string>

#include "../include/mouse/mouse.h"

int main() {
  rwa2::Mouse mouse; // Create an object of class Mouse. Contains all the
                     // methods that is required to traverse the maze
  mouse.log("Running...");
  mouse.display_walls(NULL); // Display the initial walls of the maze, i.e; all
                             // the boundry walls and set all the others to zero
  mouse.reset_mouse(); // Return the mouse to the home position and set heading
                       // to NORTH
  mouse.set_goal_position({7, 7});
  if (mouse.search_maze(
          mouse.get_home_node())) { // If a path was avaiable starting from
                                    // home_node to the goal_position
    mouse.display_path(); // Highlight the traversed path in green and set the
                          // test on the goal
    mouse.log("============================\n         Starting RUN!");
    mouse.maze_runner(
        mouse.get_nodeStack()); // Move the mouse along the newly found path
    mouse.log("             DONE!\n============================");
  } else // Maze does not have a path from home to goal
    mouse.log("Maze can not be solved");
}