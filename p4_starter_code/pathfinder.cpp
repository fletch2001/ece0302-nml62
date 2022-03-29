#include <iostream>

#include "image.h"
#include "deque.hpp"

struct coord{
  unsigned int i;
  unsigned int j;
};

struct exit_path {
  unsigned int steps;
  coord c;
};

bool find_start(Image<Pixel> &, coord &);
void search(Image<Pixel> &, Image<Pixel> &, const coord &, std::string);
coord previousRow(coord);
coord nextRow(coord);
coord previousColumn(coord);
coord nextColumn(coord);
void exit_handler(Image<Pixel> &);

int nodes = 0;

int main(int argc, char *argv[])
{
  Image<Pixel> map = readFromFile(argv[1]); // read map in from file to Image object
  Image<Pixel> explored = map; // explored map to keep track of explored coordinates

  std::string outputfile = argv[2];

  unsigned width, height;
  
  width = map.width(); // get width
  height = map.height(); // get height

  coord start;

//*** i is row
//*** j is column

  // finding start point (red sqaure)
  if(find_start(map, start)) {
    std::cout << start.i << " " << start.j << std::endl;
    //std::cout << map(start.j, start.i).alpha << std::endl << map(start.i, start.j).blue << std::endl << map(start.i, start.j).green << std::endl << map(start.i, start.j).red << std::endl;
    std::cout << (map(start.i, start.j) == RED) <<"\n\n\n\n";

    search(map, explored, start, outputfile);
  }
}

// takes a coordinate by reference and 
bool find_start(Image<Pixel> &map, coord &c) {
  for(unsigned j = 0; j < map.height(); j++) {
      for(unsigned i = 0; i < map.width(); i++) {
        if(map(i, j) == RED) { // start search here
          c = {i, j};
          return true; // exit from search if found
        }
      }
    }
    return false;
}

void search(Image<Pixel> &map, Image<Pixel> &explored, const coord & c, std::string outputfile) {
  //if(map(c.i, c.j) == WHITE) map(c.i, c.j) = BLUE;
  if(map(c.i, c.j) == BLACK) std::cout << c.j << " " << c.i << " B\n";
  if(map(c.i, c.j) == WHITE) std::cout << c.j << " " << c.i << " W\n";
    //std::cout << map(c.i, c.j).alpha << std::endl << map(c.i, c.j).blue << std::endl << map(c.i, c.j).green << std::endl << map(c.i, c.j).red << std::endl;

  // if(c.i == 0 || c.j == 0 || c.j == map.width() - 1 || c.i == map.height() - 1 && (map(c.i, c.j) == WHITE)) { // case when exit is found
  //   std::clog << "EXIT FOUND\n\n";
  //   map(c.i, c.j) = GREEN; // print exit
  //   writeToFile(map, outputfile);
  //   exit_handler(map); // go to exit handler
  //   return;
  // }

  //explored(c.i, c.j) = BLUE; // set explored node to blue
  
  Deque<coord> frontier;

/*

pR
nR
pC
nC

*/

  //explored(c.i, c.j) = BLUE;

  if(c.i >= 1) {
    if(map(c.i - 1, c.j) == WHITE && explored(c.i - 1, c.j) == WHITE) {
      std::cout << "q:" << frontier.isEmpty() << "\n";
      frontier.pushFront(previousRow(c)); // add previous row to frontier
      //explored(c.i, c.j + 1) = Pixel{0, 0, static_cast<uint8_t>(120 + nodes), 255};
      writeToFile(explored, "explored.png");
    }
  }

  if(c.i < map.height() - 1) {
    if(map(c.i + 1, c.j) == WHITE && explored(c.i + 1, c.j) == WHITE) {
      std::cout << "q:" << frontier.isEmpty() << "\n";
      frontier.pushFront(nextRow(c));
      //explored(c.i, c.j + 1) = Pixel{0, 0, static_cast<uint8_t>(120 + nodes), 255};
      writeToFile(explored, "explored.png");
    } 
  }

  if(c.j >= 1) {
    if(map(c.i, c.j - 1) == WHITE && explored(c.i, c.j - 1) == WHITE) {
      std::cout << "q:" << frontier.isEmpty() << "\n";
      frontier.pushFront(previousColumn(c));
      //explored(c.i, c.j + 1) = Pixel{0, 0, static_cast<uint8_t>(120 + nodes), 255};
      //explored(c.i, c.j + 1) = Pixel{0, 0, 120, 255};
      writeToFile(explored, "explored.png");
    } 
  }

  if(c.j < map.width() - 1) {
    if(map(c.i, c.j + 1) == WHITE && explored(c.i, c.j + 1) == WHITE) {
      std::cout << "q:" << frontier.isEmpty() << "\n";
      frontier.pushFront(nextColumn(c));
      //explored(c.i, c.j + 1) = Pixel{0, 0, 120, 255};
      writeToFile(explored, "explored.png");
    } 
  }
  
  // writeToFile(map, outputfile);
  

  while(frontier.isEmpty() == false) {
    std::clog << "search\n";
    //std::cout << frontier.back().i << " " << frontier.back().j << std::endl;
     //search(map, explored, frontier.back(), outputfile); // check first node in queue
    
    coord current = frontier.back;

     explored(frontier.back().i, frontier.back().j) = BLUE;

      if(c.i == 0 || c.j == 0 || c.j == map.width() - 1 || c.i == map.height() - 1 && (map(c.i, c.j) == WHITE)) { // case when exit is found
  //   std::clog << "EXIT FOUND\n\n";
  //   map(c.i, c.j) = GREEN; // print exit
  //   writeToFile(map, outputfile);
  //   exit_handler(map); // go to exit handler
  //   return;
  // }


     frontier.popBack(); // remove checked node from list
  }

  return;
}

coord previousRow(coord c) {
  return coord{c.i - 1, c.j};
}

coord nextRow(coord c) {
  return coord{c.i + 1, c.j};
}

coord previousColumn(coord c) {
  return coord{c.i, c.j - 1};
}

coord nextColumn(coord c) {
  return coord{c.i, c.j + 1};
}

void exit_handler(Image<Pixel> & map) {
  exit(EXIT_SUCCESS);
}