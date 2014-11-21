#include "../Headers/unode.h"
#include "../Headers/edge.h"
#include "../Headers/path.h"
#include "../Headers/lees.h"
#include "../Headers/newgrid.h"
#include "../Headers/problem_object.h"
#include <time.h>
#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <list>



NewGrid::NewGrid(Utilities::ProblemObject& problem){
    
    fflush(stdout);
    for(int y = 0; y < problem.get_height(); y++) {
		  vector<UNode*> temp_row;
	      for(int x = 0;x < problem.get_height(); x++) {

      fflush(stdout);
			  UNode* new_node = new UNode(x,y);
			  temp_row.push_back(new_node);
          }
          this->grid.push_back(temp_row);
      }
      fflush(stdout);
      vector<Blocker> temp = problem.get_blockers();
      for(int k = 0; k<temp.size(); ++k){
        grid.at(temp[k].location.y).at(temp[k].location.x)->set_obstacle(true);
        for(int i = 0; i< temp[k].width; ++i){
            for( int j = 0; j< temp[k].height; ++j){
                printf("%d,%d\n",i,j);
                grid.at(temp[k].location.y+i).at(temp[k].location.x+j)->set_obstacle(true);
               }
        }
    
      fflush(stdout);
       }
       }
NewGrid::~NewGrid() {
      int width = this->grid.size();
      int height = this->grid.at(0).size();
      for(int x = 0; x < width; x++) {
            for(int y = 0; y < width; y++) {
                  delete grid.at(y).at(x);
            }
      }
}
vector<Path*> NewGrid::run_lees(Utilities::ProblemObject& problem, bool intersection){
    vector<Connection> connections =problem.get_connections();
    vector<Path*> results;
    for(int i=0; i< connections.size(); ++i){
        lees_expand(grid.at(connections[i].source.x).at(connections[i].source.y),grid.at(connections[i].sink.x).at(connections[i].sink.y),grid);
        print_graph();

        fflush(stdout);
        results.push_back(traceback(grid.at(connections[i].source.x).at(connections[i].source.y),grid.at(connections[i].sink.x).at(connections[i].sink.y),grid,intersection));
        reset_costs(grid);
        }
    return results;
    }
    
void NewGrid::print_graph(){
   for(int i=0; i<grid.size(); ++i){
		for(int j = 0; j<grid.size(); ++j){
			if(grid.at(j).at(i)->is_obstacle()){
				cout<< "** ";
				continue;
			}
			cout << std::setfill('0') << std::setw(2) << grid.at(j).at(i)->get_cost()<< " ";
		}
	    cout <<endl;
	}
    cout <<endl;
    }