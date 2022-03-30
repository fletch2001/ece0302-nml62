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
void exit_handler(int, metadata);

int nodes = 0;

int main(int argc, char *argv[])
{
  Image<Pixel> map = readFromFile(argv[1]); // read map in from file to Image object
  //Image<Pixel> explored = map; // explored map to keep track of explored coordinates

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

// takes a coordinate by reference and 
bool find_start(metadata &m, coord &c) {
  bool start_found = 0;

  for(unsigned j = 0; j < m.map.height(); j++) {
      for(unsigned i = 0; i < m.map.width(); i++) {
        if(m.map(i, j) != BLACK && m.map(i, j) != WHITE && m.map(i, j) != RED ) {
          exit_handler(-2, m);
        } else if(m.map(i, j) == RED && start_found == false) { // start search here
          c = {i, j};
          start_found = true; // exit from search if found
        } else if(m.map(i, j) == RED && start_found == true) {
          exit_handler(-2, m);
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
  
  Deque<coord> frontier;
  bool explored[m.map.height()][m.map.width()];
  for(unsigned i = 0; i < m.map.height(); i++) {
    for(unsigned j = 0; j < m.map.width(); j++) {
      explored[i][j] = 0; // clear explored array
    }
  }

  frontier.pushFront(c);
/*

pR
nR
pC
nC

*/

  //explored(c.i, c.j) = BLUE;

  
  // writeToFile(map, outputfile);
  

  while(true) {
    //tstd::clog << "search\n";
    //std::cout << frontier.back().i << " " << frontier.back().j << std::endl;
     //search(map, explored, frontier.back(), outputfile); // check first node in queue
    
      if(frontier.isEmpty() == true) {
        exit_handler(-1, m);
      }

      coord current = frontier.back();
      frontier.popBack(); // remove checked node from list
      //explored(current.i, current.j) = BLUE;
      if(explored[current.i][current.j] == 1) continue; // skip to next coordinate in queue
      else{ explored[current.i][current.j] =1; path(current.i, current.j) = BLUE; }
      //explored[current.i][current.j] = 1;
      
      //writeToFile(path, "explored-1.png");

      if(current.i == 0 || current.j == 0 || current.j == map->height() - 1|| current.i == map->width()  - 1 && (map->operator()(current.i, current.j) == WHITE)) { // case when exit is found
        //std::clog << "EXIT FOUND\n\n";
        map->operator()(current.i, current.j) = GREEN; // print exit
        exit_handler(1, metadata{m.outputfile, *map}); // go to exit handler (pass in 1 for success)
      }

      if(current.i >= 1) { // check that not on edge and that map(prevrow) will not throw error
          //if(map(current.i - 1, current.j) == WHITE && explored(current.i - 1, current.j) == WHITE) {
          if(map->operator()(current.i - 1, current.j) == WHITE && explored[current.i-1][current.j] == 0) {
            //std::cout << "q:" << frontier.isEmpty() << "\n";
            frontier.pushFront(previousRow(current)); // add previous row to frontier
            // std::cout << previousRow(current).i << " " << previousRow(current).j << " pushed to queue\n";
          }
        }

        if(current.i < map->height() - 1) { // check that map() will not go out of range and throw error
          //if(map(current.i + 1, current.j) == WHITE && explored(current.i + 1, current.j) == WHITE) {
          if(map->operator()(current.i + 1, current.j) == WHITE && explored[current.i+1][current.j] == 0) {
            //std::cout << "q:" << frontier.isEmpty() << "\n";
            frontier.pushFront(nextRow(current));
            // std::cout << nextRow(current).i << " " << nextRow(current).j << " pushed to queue\n";
          } 
        }

        if(current.j >= 1) { // check that map() will not go out of range and throw error
          //if(map(current.i, current.j - 1) == WHITE && explored(current.i, current.j - 1) == WHITE) {
          if(map->operator()(current.i, current.j - 1) == WHITE && explored[current.i][current.j - 1] == 0) {
            //std::cout << "q:" << frontier.isEmpty() << "\n";
            frontier.pushFront(previousColumn(current));
            // std::cout << previousColumn(current).i << " " << previousColumn(current).j << " pushed to queue\n";
          } 
        }

        if(current.j < map->width() - 1) {
          //if(map(current.i, current.j + 1) == WHITE && explored(current.i, current.j + 1) == WHITE) {
          if(map->operator()(current.i, current.j + 1) == WHITE && explored[current.i][current.j + 1] == 0) {
            //std::cout << "q:" << frontier.isEmpty() << "\n";
            frontier.pushFront(nextColumn(current));
            // std::cout << nextColumn(current).i << " " << nextColumn(current).j << " pushed to queue\n";
          } 
        }
  }
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

void exit_handler(int e, metadata m) {
  if(e == 1) {
    writeToFile(m.map, m.outputfile); // write output to map
    std::cout << "solution found\n";
    exit(EXIT_SUCCESS);
  }
  else if(e == -1) {
    writeToFile(m.map, m.outputfile);
    std::cout << "no solution found\n";
    exit(EXIT_SUCCESS);
  }
  else if(e == -2) {
    std::cout << "start error\n";
    std::cerr << "error\n";
    writeToFile(m.map, m.outputfile);
    exit(EXIT_FAILURE);
  }
}