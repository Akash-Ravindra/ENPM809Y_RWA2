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
  while (1) {
    mouse.search_maze({0, 0});
  }
}

// #include "../include/api/api.h"
// #include <iostream>
// #include <string>

// void log(const std::string& text) {
//     std::cerr << text << std::endl;
// }

// int main(int argc, char* argv[]) {
//     log("Running...");
//     API::setColor(0, 0, 'G');
//     API::setText(0, 0, "abc");
//     while (true) {
//         if (!API::wallLeft()) {
//             API::turnLeft();
//         }
//         while (API::wallFront()) {
//             API::turnRight();
//         }
//         API::moveForward();
//     }
// }