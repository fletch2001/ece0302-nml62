#include <iostream>
#include <cstdlib>

#include "image.h"
#include "deque.hpp"

struct coord{
  unsigned int i;
  unsigned int j;
};

struct metadata {
  std::string outputfile;
  Image<Pixel> map;
};

bool find_start(metadata &, coord &);
//void search(metadata &, Image<Pixel> &, const coord &);
void search(metadata &, const coord &);
coord previousRow(coord);
coord nextRow(coord);
coord previousColumn(coord);
coord nextColumn(coord);
bool checkExit(coord, Image<Pixel> *);
void exit_handler(int, metadata);
void exit_handler(std::string = "");

int nodes = 0;

int main(int argc, char *argv[])
{
  Image<Pixel> map;

  // check if map is readable
  try {
    map = readFromFile(argv[1]); // read map in from file to Image object
  } catch(std::exception e) {
    exit_handler("invalid input file/no input file found"); // catch error and go to exit handler for no map
  }

  metadata problemData{argv[2], map};
  // problemData.outputfile = argv[2];
  // problemData.map = map;

  unsigned width, height;
  
  width = map.width(); // get width
  height = map.height(); // get height

  coord start;

//*** i is row
//*** j is column

  // finding start point (red sqaure)
  if(find_start(problemData, start)) {
    //std::cout << start.i << " " << start.j << std::endl;
    //std::cout << map(start.j, start.i).alpha << std::endl << map(start.i, start.j).blue << std::endl << map(start.i, start.j).green << std::endl << map(start.i, start.j).red << std::endl;
   // std::cout << (map(start.i, start.j) == RED) <<"\n\n\n\n";

   // search(problemData, explored, start);
    search(problemData, start);
  }
}

// takes a metadata struct by reference and a coordinate by reference
bool find_start(metadata &m, coord &c) {
  // keeps track of whether a red pixel has been found
  bool start_found = 0;

  for(unsigned j = 0; j < m.map.height(); j++) {
      for(unsigned i = 0; i < m.map.width(); i++) {
        if(m.map(i, j) != BLACK && m.map(i, j) != WHITE && m.map(i, j) != RED ) {
          exit_handler("non red/white/black pixel found."); // go to error exit handler
        } else if(m.map(i, j) == RED && start_found == false) { // start search here
          c = {i, j};
          start_found = true; // exit from search if found
        } else if(m.map(i, j) == RED && start_found == true) {
          exit_handler("multiple red(start) pixels found."); // go to error exit handler
        }
      }
    }
    return true;
}

void search(metadata &m, const coord & c) {
  //std::clog << "search start\n\n";
//void search(metadata &m, Image<Pixel> &explored, const coord & c) {
  Image<Pixel> *map = &m.map; // extract map from metadata struct
  Image<Pixel> path = m.map;
  //explored(c.i, c.j) = BLUE; // set explored node to blue
  
  // check if initial space is an exit
  if(checkExit(c, map)) exit_handler(1, metadata{m.outputfile, *map});

  // double ended queue for keeping track of frontier (search space)
  Deque<coord> frontier;
  
  // 2-d array of each pixel to keep track of what has been explored
  bool explored[m.map.height()][m.map.width()];
  
  // initialize explored array to 0s
  for(unsigned i = 0; i < m.map.height(); i++) {
    for(unsigned j = 0; j < m.map.width(); j++) {
      explored[i][j] = 0; // clear explored array
    }
  }

  // add the first coordinate to the queue to start breadth-first-search
  frontier.pushFront(c);
  

  // loop runs until an exit handler is called
  while(true) {
    
      // return no solution if queue is empty -- no more possible spaces to explore
      if(frontier.isEmpty() == true) {
        exit_handler(-1, m);
      }

      coord current = frontier.back();
      frontier.popBack(); // remove checked node from list

      // checks whether coordinate has been explored already and sets to explored if it has
      if(explored[current.i][current.j] == 1) continue; // skip to next coordinate in queue
      else{ 
        explored[current.i][current.j] = 1; 
        
        // uncomment for visualization of where search is occuring
        // path(current.i, current.j) = BLUE; 
        //writeToFile(path, "path.png");
      }
      
  
      // ORIGIAL CHECKING FOR EXIT--FASTER TO CHECK IN EACH IF STATEMENT BELOW
      // if(current.i == 0 || current.j == 0 || current.j == map->height() - 1|| current.i == map->width()  - 1 && (map->operator()(current.i, current.j) == WHITE)) { // case when exit is found
      //   //std::clog << "EXIT FOUND\n\n";
      //   map->operator()(current.i, current.j) = GREEN; // print exit
      //   exit_handler(1, metadata{m.outputfile, *map}); // go to exit handler (pass in 1 for success)
      // }

      /**
       * @brief checks previousRow (i-1, j), nextRow(i+1, j), previousColumn(i, j-1), and nextColumn(i, j+1) in that order.
       * First checks if each previous/next space white, then checks if it is an exit using the checkExit() method and if 
       * not, adds it to the queue for search
       */

      if(current.i >= 1) { // check that not on edge and that map(prevrow) will not throw error
          // check that element is a white space and has not been explored
          if(map->operator()(current.i - 1, current.j) == WHITE && explored[current.i-1][current.j] == 0) {
            // check if element is an exit
            if(checkExit(previousRow(current), map)) exit_handler(1, metadata{m.outputfile, *map});
            
            // add element to queue
            frontier.pushFront(previousRow(current)); 
          }
        }

        if(current.i < map->height() - 1) { // check that map() will not go out of range and throw error
          // check that element is a white space and has not been explored
          if(map->operator()(current.i + 1, current.j) == WHITE && explored[current.i+1][current.j] == 0) {
            // check if element is an exit
            if(checkExit(nextRow(current), map)) exit_handler(1, metadata{m.outputfile, *map});
            
            // add element to queue
            frontier.pushFront(nextRow(current)); 
          } 
        }


        if(current.j >= 1) { // check that map() will not go out of range and throw error
          
          // check that element is a white space and has not been explored
          if(map->operator()(current.i, current.j - 1) == WHITE && explored[current.i][current.j - 1] == 0) {
            // check if element is an exit
            if(checkExit(previousColumn(current), map)) exit_handler(1, metadata{m.outputfile, *map});
            
            // add element to queue
            frontier.pushFront(previousColumn(current)); 
          } 
        }

        // check that element is not on edge
        if(current.j < map->width() - 1) {
          
          // check that element is a white space and has not been explored
          if(map->operator()(current.i, current.j + 1) == WHITE && explored[current.i][current.j + 1] == 0) {
            // check if element is an exit
            if(checkExit(nextColumn(current), map)) exit_handler(1, metadata{m.outputfile, *map});
            
            // add next column element to queue
            frontier.pushFront(nextColumn(current)); 
          } 
        }
  }
}

// checks if a coordinate is an exit
bool checkExit(coord current, Image<Pixel> *map) {
  if(current.i == 0 || current.j == 0 || current.j == map->height() - 1|| current.i == map->width() - 1 && (map->operator()(current.i, current.j) == WHITE)) { // case when exit is found
    map->operator()(current.i, current.j) = GREEN; // print exit
    return true; // return true
  } else {
    return false; // return false if not exit
  }
}

// return coordinate to previous row
coord previousRow(coord c) {
  return coord{c.i - 1, c.j};
}

// return coordinate to next row
coord nextRow(coord c) {
  return coord{c.i + 1, c.j};
}

// return coordinate to previous column
coord previousColumn(coord c) {
  return coord{c.i, c.j - 1};
}

// return coordinate to next column
coord nextColumn(coord c) {
  return coord{c.i, c.j + 1};
}

// handles exit routine depending on exit status (-2 for error, -1 for no solution found, 1 for solution found)
void exit_handler(int e, metadata m) {
  if(e == 1) {
    writeToFile(m.map, m.outputfile); // write output to map
    std::cout << "solution found\n";
    exit(EXIT_SUCCESS); // exit_success
  }
  else if(e == -1) {
    writeToFile(m.map, m.outputfile); // write solution to map
    std::cout << "no solution found\n";
    exit(EXIT_SUCCESS); // exit_success
  }
  else if(e == -2) {
    std::cerr << "error\n"; // write error to std_error
    writeToFile(m.map, m.outputfile); // write solution to map
    exit(EXIT_FAILURE); // exit_failure
  }
}

// default exit handler for no-map errors
void exit_handler(std::string mes) {
  std::cerr << "error"; // write error to std_error
  if(mes != "") std::cerr << ": "+mes;
  std::cerr << "\n";
  exit(EXIT_FAILURE); // exit_failure
}