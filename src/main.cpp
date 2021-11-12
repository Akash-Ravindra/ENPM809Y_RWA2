#include <iostream>
#include <array>

#include "../include/mouse/mouse.h"
#include "../include/api/api.h"
#include "string"
#include "iostream"
void log(std::string display){
	std::cerr<<display<<std::endl;
}
int main() {
	rwa2::Mouse mouse;
	mouse.display_walls();
	log("Started");
	while(true)
		API::turnLeft();
}

