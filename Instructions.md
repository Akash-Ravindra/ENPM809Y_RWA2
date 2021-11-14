# Instructions
## Build Command
- The directory would be the root of the project folder ( Same as where this file is placed)
- The following would be the build command 
    - `g++ src/main.cpp src/mouse.cpp src/node.cpp src/api.cpp `
- The run command would be
    - `./a.out`

## Other comments
- The usual behavious of the code is
    - The mouse travels through the maze discovering walls as it enters each node
    - It updates the wall color and the text at each node
    - On finding the goal (set goal position using mouse method executed in main) the path is highlighted in green
    - The mouse begins to traverse through the maze along the same path
-   There are privte member  functions in Class `Mouse` that dont show up in the doxygen HTML output
