
#include "../Headers/grid.h"
#include "../Headers/problem_object.h"
#include "../Headers/lees.h"
#include "../Headers/lees_2bit.h"
#include "../Headers/lees_3bit.h"
#include "../Headers/lees_rubins.h"
#include "../Headers/lees_korns.h"
#include "../Headers/unode.h"
#include "../Headers/newgrid.h"
#include "../Headers/hadlocks.h"
#include <time.h>
#include <cstdlib>
#include <iostream>

using std::cerr;
using std::cout;
using std::endl;
void print_usage_instructions_and_exit() {
	cout << "Usage: ./grid_router <test_file> <algorithm> ..." << endl;
	cout << "Algorithms: " << endl;
	cout << "    n <y/n intersect> <y/n minimize turns> <y/n optimize expansion>" << endl;
	cout << "                    Normal Lee's algorithm" << endl;
	cout << "    2               Lee's algorithm with 2-bit encoding" << endl;
	cout << "    3               Lee's algorithm with 3-bit encoding" << endl;
	cout << "    r               Lee's algorithm with Rubin's improvements" << endl;
	cout << "    k               Lee's algorithm with Korn's improvements" << endl;
	cout << "    h               Hadlock's algorithm" << endl;
	cout << endl;
	cout << "Examples:" << endl;
	cout << "./grid_router ./Tests/test_sample.json n n y n" << endl;
	cout << "    Use normal Lee's algorithm, no intersections, minimize terms," << endl;
	cout << "    do not optimize expansion" << endl;
	cout << "./grid_router ./Tests/hadlocks.json h" << endl;
	cout << "    Run Hadlock's algorithm" << endl;
	exit(1);
}
int main(int argc,char* argv[]) {
	bool intersect = false;
	// DO NOT CHANGE THIS SECTION OF CODE
	if(argc < 2) { 
		cout << "Usage: ./grid_router <test_file> " << endl; 
		exit(1);
	}
	Utilities::ProblemObject* first_problem = new Utilities::ProblemObject(std::string(argv[1]));
	// EDIT FROM HERE DOWN
    if(argc < 3) { 
		print_usage_instructions_and_exit();
	}
   
	vector<Path*> paths;
    NewGrid g(*first_problem);
    bool minturn;
    bool recentexpand;
    
    // Normal Lee's algorithm
    if(argv[2][0]=='n' || argv[2][0]=='N' || argv[2][0]=='1'){
        if(argc < 6){
            print_usage_instructions_and_exit();
        }
		if(argv[3][0]=='y'){
			intersect = false;
		}
		else if(argv[3][0]=='n'){
			intersect = true;
		}
		else{
			print_usage_instructions_and_exit();
		}
		 
        if(argv[4][0]=='y'){
            minturn = true;
        }
        else if(argv[4][0]=='n'){
            minturn = false;
        }
        else{
            print_usage_instructions_and_exit();
        }
        
        if(argc < 6){
            print_usage_instructions_and_exit();
        }
        if(argv[5][0]=='y'){
            recentexpand = true;
        }
        else if(argv[5][0]=='n'){
            recentexpand = false;
        }
        else{
            print_usage_instructions_and_exit();
        } 
        paths = g.run_lees(*first_problem,intersect,minturn,recentexpand);
         
    }
    
    // Lee's algorithm with 2-bit encoding
    else if(argv[2][0]=='2'){
        paths = g.run_lees_2bit(*first_problem,intersect);
    }
    
    // Lee's algorithm with 3-bit encoding
    else if(argv[2][0]=='3'){
        paths = g.run_lees_3bit(*first_problem,intersect);
    }
    
    // Lee's algorithm with Rubin's improvements
    else if(argv[2][0]=='r' || argv[2][0]=='R' || argv[2][0]=='4'){
        paths = g.run_lees_rubins(*first_problem,intersect);
    }
    
    // Lee's algorithm with Korn's improvements
    else if(argv[2][0]=='k' || argv[2][0]=='K' || argv[2][0]=='5'){
        paths = g.run_lees_korns(*first_problem,intersect);
    }
    
    // Hadlock's algorithm
    else if(argv[2][0]=='h' || argv[2][0]=='H' || argv[2][0]=='6'){
        paths = g.run_hadlocks(*first_problem,intersect,false);
    }
    
    // invalid input
    else{
        print_usage_instructions_and_exit();
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
