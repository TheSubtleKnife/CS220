/* Filename: <newgrid.cc>
* Author:Ryan Bissiri
* Date:11/18/14
* Description: Implementation of the grid class
*/
#include "../Headers/unode.h"
#include "../Headers/edge.h"
#include "../Headers/path.h"
#include "../Headers/lees.h"
#include "../Headers/lees_3bit.h"
#include "../Headers/newgrid.h"
#include "../Headers/problem_object.h"
#include "../Headers/claim.h"
#include <time.h>
#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <list>
using Utilities::claim;

/*Inputs: ProblemObject* containing sources/sinks/blockers
 Modifies: vector<vector<UNode*> >& grid
 Returns: NewGrid
 Initializes the grid size, and places the blockers
 */
NewGrid::NewGrid(Utilities::ProblemObject& problem){
    //init grid with default nodes
    for(int y = 0; y < problem.get_height(); y++) {
		  vector<UNode*> temp_row;
	      for(int x = 0;x < problem.get_width(); x++) {
			  UNode* new_node = new UNode(x,y);
			  temp_row.push_back(new_node);
          }
          this->grid.push_back(temp_row);
      }
      //add blockers
      vector<Blocker> temp = problem.get_blockers();
      for(int k = 0; k<temp.size(); ++k){
      if(temp[k].location.y < 0 || temp[k].location.x < 0 ||temp[k].location.y > problem.get_height() 
        || temp[k].location.x >  problem.get_width()){ 
            claim("Invalid placement of blocker", Utilities::kError);
         }
        grid.at(temp[k].location.y).at(temp[k].location.x)->set_obstacle(true);
        for(int i = 0; i< temp[k].width; ++i){
            for( int j = 0; j< temp[k].height; ++j){
                if(temp[k].location.y+i > problem.get_height() || temp[k].location.x+j >  problem.get_width()){
                     claim("Invalid placement of blocker", Utilities::kError);
                }
                grid.at(temp[k].location.y+i).at(temp[k].location.x+j)->set_obstacle(true);
            }
        }
    }
}

//Destructor
NewGrid::~NewGrid() {
      int width = this->grid.size();
      int height = this->grid.at(0).size();
      for(int x = 0; x < width; x++) {
            for(int y = 0; y < width; y++) {
                  delete grid.at(y).at(x);
            }
      }
}
/*Inputs: ProblemObject* containing sources/sinks
          bool decides if intersections are allowed or not
 Modifies: vector<vector<UNode*> >& grid
 Returns: vector<Path*> containing paths if valid routing could be found
 runs lee's normal algorithm
 */
vector<Path*> NewGrid::run_lees(Utilities::ProblemObject& problem, bool intersection){
    vector<Connection> connections =problem.get_connections();
    vector<Path*> results;
    for(int i=0; i< connections.size(); ++i){
        if(connections[i].source.x < 0 || connections[i].source.y < 0||connections[i].sink.x < 0 
            || connections[i].sink.y < 0 || connections[i].source.x > problem.get_width() 
            || connections[i].source.y > problem.get_height()|connections[i].sink.x > problem.get_width() 
            || connections[i].sink.y > problem.get_height()){
                claim("Source/Sink out of grid bounds", Utilities::kError); //error checking
        }
        //calling lee's BFS expansion
        lees_expand(grid.at(connections[i].source.x).at(connections[i].source.y),grid.at(connections[i].sink.x)
            .at(connections[i].sink.y),grid);
        print_graph();
        //calling lee's traceback
        results.push_back(traceback(grid.at(connections[i].source.x).at(connections[i].source.y),grid.at(connections[i].sink.x).at(connections[i].sink.y),grid,intersection));
        reset_costs();
        }
    return results;
    }
    
vector<Path*> NewGrid::run_lees_3bit(Utilities::ProblemObject& problem, bool intersection){
    vector<Connection> connections =problem.get_connections();
    vector<Path*> results;
    for(int i=0; i< connections.size(); ++i){
        if(connections[i].source.x < 0 || connections[i].source.y < 0||connections[i].sink.x < 0 
            || connections[i].sink.y < 0 || connections[i].source.x > problem.get_width() 
            || connections[i].source.y > problem.get_height()|connections[i].sink.x > problem.get_width() 
            || connections[i].sink.y > problem.get_height()){
                claim("Source/Sink out of grid bounds", Utilities::kError); //error checking
        }
        //calling lee's 3bit BFS
        lees_3bit_expand(grid.at(connections[i].source.x).at(connections[i].source.y),grid.at(connections[i].sink.x)
            .at(connections[i].sink.y),grid);
        print_graph();
        //3bit traceback
        results.push_back(traceback_3bit(grid.at(connections[i].source.x).at(connections[i].source.y),grid.at(connections[i].sink.x).at(connections[i].sink.y),grid,intersection));
        reset_costs();
        }
    return results;
    }
/*    
vector<Path*> NewGrid::run_lees_2bit(Utilities::ProblemObject& problem, bool intersection){
    vector<Connection> connections =problem.get_connections();
    vector<Path*> results;
    for(int i=0; i< connections.size(); ++i){
        if(connections[i].source.x < 0 || connections[i].source.y < 0||connections[i].sink.x < 0 
            || connections[i].sink.y < 0 || connections[i].source.x > problem.get_width() 
            || connections[i].source.y > problem.get_height()|connections[i].sink.x > problem.get_width() 
            || connections[i].sink.y > problem.get_height()){
                claim("Source/Sink out of grid bounds", Utilities::kError); //error checking
        }
        //calling lee's 2bit BFS
        lees_2bit_expand(grid.at(connections[i].source.x).at(connections[i].source.y),grid.at(connections[i].sink.x)
            .at(connections[i].sink.y),grid);
        print_graph();
        //3bit traceback
        results.push_back(traceback_2bit(grid.at(connections[i].source.x).at(connections[i].source.y),grid.at(connections[i].sink.x).at(connections[i].sink.y),grid,intersection));
        reset_costs();
        }
    return results;
    }
*/
/*
 Prints out costs and blockers in the grid
 */   
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
/*Inputs:
         
 Modifies: vector<vector<UNode*> >& grid
 Returns: 
 Resets costs and visited status of grid
 */
void NewGrid::reset_costs(){
    for(int i=0;i< grid.size();++i){
        for(int j=0; j<grid.at(0).size(); ++j){
            grid.at(i).at(j)->set_visit(false);
            grid.at(i).at(j)->set_cost(0);
            }
        }
    }