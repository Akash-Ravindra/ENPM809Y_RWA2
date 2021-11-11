/**
 * @file main.cpp
 * @author Akash Ravindra (aravind2@umd.edu)
 * @brief
 * @version 0.1
 * @date 2021-11-09
 *
 * @copyright Copyright (c) 2021
 *
 */

#include <array>
#include <iostream>
#include <string>

#include "../include/mouse/mouse.h"

void log(const std::string &text) { std::cerr << text << std::endl; }
int main() {
  log("Running...");
  rwa2::Mouse mouse;
  mouse.display_walls();
  mouse.reset_mouse();
  // mouse.move_forward();
  if(mouse.search_maze(mouse.get_home_node())){
    mouse.display_walls();
    mouse.display_path();
  }
}