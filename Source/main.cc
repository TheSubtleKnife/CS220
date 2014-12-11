
#include "../Headers/grid.h"
#include "../Headers/problem_object.h"
#include "../Headers/lees.h"
#include "../Headers/lees_2bit.h"
#include "../Headers/lees_3bit.h"
#include "../Headers/unode.h"
#include "../Headers/newgrid.h"
#include "../Headers/hadlocks.h"
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
    NewGrid g(*first_problem);
    bool minturn;
    bool recentexpand;
    if(argv[3][0]=='n' || argv[3][0]=='1'){
        if(argc < 5){
             cout << "Usage: ./grid_router <test_file> <intersect y/n> <lee's type normal/3bit/2bit> <minimize turns y/n>" << endl; 
            exit(1);
        }
        if(argv[4][0]=='y'){
             minturn = true;
         }
         else if(argv[4][0]=='n'){
            minturn = false;
         }
         else{
            cout << "Usage: ./grid_router <test_file> <intersect y/n> <lee's type normal/3bit/2bit> <minimize turns y/n>" << endl; 
            exit(1);
        }
        if(argc < 6){
             cout << "Usage: ./grid_router <test_file> <intersect y/n> <lee's type normal/3bit/2bit> <minimize turns y/n> <optimize expansion y/n>" << endl; 
            exit(1);
        }
        if(argv[5][0]=='y'){
             recentexpand = true;
         }
         else if(argv[5][0]=='n'){
            recentexpand = false;
         }
         else{
            cout << "Usage: ./grid_router <test_file> <intersect y/n> <lee's type normal/3bit/2bit> <minimize turns y/n> <optimize expansion y/n>" << endl; 
            exit(1);
        } 
        paths = g.run_lees(*first_problem,intersect,minturn,recentexpand);
         
    }
    else if(argv[3][0]=='3'){
        paths = g.run_lees_3bit(*first_problem,intersect);
    }
    else if(argv[3][0]=='2'){
        paths = g.run_lees_2bit(*first_problem,intersect);
    }
    else if(argv[3][0]=='h'){
        paths = g.run_hadlocks(*first_problem,intersect,false);
    }
    else{
        cout << "Usage: ./grid_router <test_file> <intersect y/n> <lee's type normal/3bit/2bit/hadlocks>" << endl; 
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
