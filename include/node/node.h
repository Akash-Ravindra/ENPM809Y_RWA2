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

#include <array>
#include <vector>

namespace rwa2 {
    /**
     * @brief Class to represent a node (cell) in a maze.
     *
     *A node is just a space delimited by 4 walls
     *
     */
    class Node
    {
    public:
        Node() {
            for (int i = 0; i < 4; i += 1) {
                m_walls[i] = false;
            }
        }
        std::array<int ,2> get_coords(){
            return m_coordinates;
        }
        std::array<int,2> set_coords(std::array<int,2> cords){
            m_coordinates = cords;
        }
        /**
         * @brief Set the wall of a cell
         *
         * @param direction NORTH, EAST, SOUTH, or WEST
         * @param is_wall true if there is a wall, otherwise false
         */
        void set_wall(int direction, bool is_wall);
        /**
         * @brief Return whether or not there is a wall in a cell
         *
         * @param direction Direction to set for wall (NORTH, EAST, SOUTH, or WEST)
         * @return true There is a wall in the given direction in the cell
         * @return false There is no wall in the given direction in the cell
         */
        bool is_wall(int direction) const;
        /**
         * @brief Compute the number of walls surrounding a node
         * 
         * @return int Number of walls surrounding a node
         */
        int compute_number_of_walls() const;

    private:
        std::array<bool, 4> m_walls; //all four walls in a cell
        std::array<int, 2>m_coordinates;// Coordinates of node

    };
}
#endif
