
#include "../Headers/grid.h"
#include "../Headers/problem_object.h"
#include "../Headers/lees.h"
#include "../Headers/lees_3bit.h"
#include "../Headers/unode.h"
#include "../Headers/newgrid.h"
#include <time.h>
#include <cstdlib>
#include <iostream>

using std::cerr;
using std::cout;
using std::endl;

int main(int argc,char* argv[]) {

	// DO NOT CHANGE THIS SECTION OF CODE
	if(argc < 2) { 
		cout << "Usage: ./grid_router <test_file> " << endl; 
		exit(1);
	}
	Utilities::ProblemObject* first_problem = new Utilities::ProblemObject(std::string(argv[1]));
	// EDIT FROM HERE DOWN
     if(argc < 4) { 
		cout << "Usage: ./grid_router <test_file> <intersect y/n> <lee's type normal/3bit/2bit>" << endl; 
		exit(1);
	}
    bool intersect = true;
    if(argv[2][0]=='y'){
        intersect = false;
        }
    else if(argv[2][0]=='n'){
        intersect = true;
        }
    else{
        cout << "Usage: ./grid_router <test_file> <intersect y/n> <lee's type normal/3bit/2bit>" << endl; 
		exit(1);
     }
   
	//Create your problem map object (in our example, we use a simple grid, you should create your own)
    NewGrid g(*first_problem);
    g.print_graph();

	/*
	Note: we do not take into account the connections or blockers that exist in the Project Object
	You should be accouting for these in your problem map objects (you should not be using Grid). You
	should be using both the Node and Edge classes as the background for whatever problem map object
	you create.
	*/

	/*
	Run your algorithm after creating your problem map object. You should be returning from your algorithm 
	either a Path or a Netlist

	Path: a series of straight line segments, with a single source and a single sink
	Netlist: a series of stright line segments, with a single source and more than one sink
	*/

	//Note, we create random paths just as an example of how to create paths, netlists are created similarly
	vector<Path*> paths;
    bool minturn;
    if(argv[3][0]=='n'){
        if(argv[4][0]=='y'){
             minturn = true;
         }
         else{
            minturn = false;
            }
        paths = g.run_lees(*first_problem,intersect,minturn);
         
    }
    else if(argv[3][0]=='3'){
        paths = g.run_lees_3bit(*first_problem,intersect);
    }
    //TODO: ADD 2bit option
   /* else if(argv[3][0]=='2'){
        paths = g.run_lees_2bit(*first_problem,intersect);
    }*/
    else{
        cout << "Usage: ./grid_router <test_file> <intersect y/n> <lee's type normal/3bit/2bit>" << endl; 
		exit(1);
     }
        
	g.print_graph();

	//Print the paths/netlists that you return from your algorithm
	for(unsigned i = 0; i < paths.size(); i++) {
		cout << "Path " << i << ": ";
		paths.at(i)->print();
		Path* temp = paths.at(i);
		delete temp;
	}


	paths.clear();

	delete first_problem;

	return 0;
}
