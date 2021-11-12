#include "../include/mouse/mouse.h"  
#include "../include/api/api.h"  
#include "../include/util/util.h"
#include <string>

void rwa2::Mouse::display_walls() {
    for (int x = 0; x < m_maze_width; x += 1) {
        for (int y = 0; y < m_maze_height; y += 1) {
            if (m_maze.at(x).at(y).is_wall(direction::NORTH)) {
                //display this wall in the simulator
                API::setWall(x, y, 'n');
            }
                
            if (m_maze.at(x).at(y).is_wall(direction::EAST)) {
                //display this wall in the simulator
                API::setWall(x, y, 'e');
            }
                
            if (m_maze.at(x).at(y).is_wall(direction::SOUTH)) {
                //display this wall in the simulator
                API::setWall(x, y, 's');
            }
                
            if (m_maze.at(x).at(y).is_wall(direction::WEST)) {
                //display this wall in the simulator
                API::setWall(x, y, 'w');
            }
            //display the number of walls surrounding the current node
            API::setText(x, y, std::to_string(m_maze.at(x).at(y).compute_number_of_walls()));
        }
    }
}
void rwa2::Mouse::move_forward(int s=1){
    API::moveForward(s);
}

void rwa2::Mouse::turn_left(){
    //update m_direction
    API::turnLeft();
}
void rwa2::Mouse::turn_right(){
    //update m_direction
    API::turnRight();
}
void rwa2::Mouse::move_backward(){
    turn_left();
    turn_left();
    move_forward();
}
void rwa2::Mouse::turn_until(direction heading){
 //compare heading and m_direction
 //check if already true


 //turn in direction
 //check again 
 //if false run turn_until
 //else return
}