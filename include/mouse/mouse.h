/**
 * @file mouse.h
 * @author Zeid Kootbally (zeidk@umd.edu)
 * @brief The file contains the Mouse class
 * @version 0.1
 * @date 2021-10-24
 *
 * @copyright Copyright (c) 2021
 *
 */

 /*! \mainpage Maze search algorithm
  *
  * This project consists of searching a path in a maze
  * and then task a mouse (robot) to follow the path.
  * - \subpage searchingPathPage "Searching a path"
  *
  * - \subpage followingPathPage "Following a path"
  *
  */

  /*! \page searchingPathPage Searching a path
   *
   * The search algorithm used for searching a path in a maze relies on
   * the depth-first search (DFS) approach. This algorithm is implemented in rwa2::Mouse::search_maze()
   *
   */

   /*! \page followingPathPage Following a path
    *
    * To follow a path generated by DFS, methods from the class API (api/api.h) must be used to interact
    * with the micromouse simulator.
    * - Methods of the API class are documented <a href="https://github.com/mackorone/mms#summary">here</a>.
    */


#ifndef MICROMOUSE_H
#define MICROMOUSE_H

#include "../node/node.h"
#include "../util/util.h"
#include <array>

namespace rwa2 {
    /**
     * @brief This class is used to compute a path and execute the path.
     *
     */
    class Mouse {
        public:

        /**
         * @brief Construct a new MicroMouse object
         *
         * The robot is always at (0,0) and facing NORTH when the simulator starts
         */
        Mouse() :m_x{ 0 }, m_y{ 0 }, m_direction{ direction::NORTH } {
            //initialize the maze by placing around the perimeter of the maze
            for (int x = 0; x < m_maze_width; x += 1) {
                for (int y = 0; y < m_maze_height; y += 1) {
                    m_maze.at(x).at(y).set_wall(direction::NORTH, (y == m_maze_height - 1));
                    m_maze.at(x).at(y).set_wall(direction::EAST, (x == m_maze_width - 1));
                    m_maze.at(x).at(y).set_wall(direction::SOUTH, (y == 0));
                    m_maze.at(x).at(y).set_wall(direction::WEST, (x == 0));
                    m_maze.at(x).at(y).set_coords({x,y});
                }
            }
        }
        // this method visually sets the walls in the simulator
        void display_walls();
        //IMPLEMENT THE METHODS BELOW
        //Note: Come up with your own parameters and implementations
        /**
         * @brief Implement DFS to compute a path between 2 nodes in a maze
         *
         * @return true A path is found
         * @return false A path is not found
         */
        bool search_maze();
        /**
         * @brief Make the mouse move forward by s cells (Default 1 step)
         *
         */
        void move_forward(int s);
        /**
         * @brief Make the mouse rotate 90 deg CCW
         *
         */
        void turn_left();
        /**
         * @brief Make the mouse rotate 90 deg CW
         *
         */
        void turn_right();
        /**
         * @brief Make the mouse move backward i.e. 180 deg rotation
         * 
         */
        void move_backward();
        /**
         * @brief Make the mouse turn until it aligns in the specified direction
         * 
         */
        void turn_until(direction);



        private:
        static const int m_maze_width{ 16 }; //width of the maze
        static const int m_maze_height{ 16 };//height of the maze
        int m_x; //x position of the robot in the maze
        int m_y; //y position of the robot in the maze
        int m_direction; //direction of the robot in the maze
        std::array<std::array<Node, m_maze_width>, m_maze_height> m_maze; //2D array maze object
    };
}
#endif