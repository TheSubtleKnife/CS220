
/* Filename: <lees_2bit.cc>
* Author:Ryan Bissiri/James Robinson
* Date:11/20/14
* Description: Implementation for lee's expansion and traceback algorithms
*/
#include "../Headers/lees_2bit.h"
#include "../Headers/claim.h"
int costTo2Bit(int cost) {
    cost = cost % 4;
    switch (cost) {
        case 1: return 0;
        case 2: return 0;
        case 3: return 1;
        case 0: return 1;
    }
    return -1; //error; shouldn't ever happen
}
/*
*Inputs: Unode* Source to expand from
         Unode* Sink to find
         grid containing all nodes
 Modifies: vector<vector<UNode*> >& grid
 Returns: Void
 Runs the Breadth-First Search expansion portion of lee's algorithm
 */
 using Utilities::claim;
void lees_2bit_expand(UNode* source, UNode* sink, vector<vector<UNode*> >& grid){
    //initial source node
    int cost = 0;
    source->set_cost(1); //expansion starts with "0 0 1 1", so source
							//should be 1 to continue this pattern
    source->set_visit(true);
    //BFS queue. Switching back and forth between these for each cost
    list<UNode*> queue0;
	list<UNode*> queue1;
    queue0.push_back(source);
    while(!(queue0.empty() && queue1.empty()))
    {
        //Check if the current queue is empty. If so, switch to other (by incrementing cost)
        if (cost % 2 == 0 && queue0.empty()) {
            cost++;
		}
		else if (cost % 2 == 1 && queue1.empty()) {
            cost++;
		}
        //Pop current queue
        if (cost % 2 == 0) {
            source = queue0.front();
            queue0.pop_front();
		}
		else {
            source = queue1.front();
            queue1.pop_front();
		}
        //check if left neighbour node is valid/not visited/not obstacle
        if((source->get_x()-1)>=0&&!grid.at(source->get_y()).at(source->get_x()-1)->is_visited()&&
            !grid.at(source->get_y()).at(source->get_x()-1)->is_obstacle()){
                //grid.at(source->get_y()).at(source->get_x()-1)->set_cost((source->get_cost())+1); //increment cost
                grid.at(source->get_y()).at(source->get_x()-1)->set_cost(costTo2Bit(cost+1)); //increment cost
                grid.at(source->get_y()).at(source->get_x()-1)->set_visit(true);//
                if(grid.at(source->get_y()).at(source->get_x()-1)==sink) { //if sink node found, end search
                    sink->set_cost(cost+1);//Save the cost from source to sink
                        //Note: I am saving it here to avoid modifying the framework. However,
                            //it could also be stored as a separate int variable somewhere else
                    break;
                }
                if (cost % 2 == 0) {
                    queue1.push_back(grid.at(source->get_y()).at(source->get_x()-1));//add discovered new node to other BFS queue
                }
                else {
                    queue0.push_back(grid.at(source->get_y()).at(source->get_x()-1));//add discovered new node to other BFS queue
                }
        }
        //check if right neighbour node is valid/not visited/not obstacle
        if((source->get_x()+1)<grid.size()&&!grid.at(source->get_y()).at(source->get_x()+1)->is_visited()&&
            !grid.at(source->get_y()).at(source->get_x()+1)->is_obstacle()){
                grid.at(source->get_y()).at(source->get_x()+1)->set_cost(costTo2Bit(cost+1)); //increment cost
                grid.at(source->get_y()).at(source->get_x()+1)->set_visit(true);
                if(grid.at(source->get_y()).at(source->get_x()+1)==sink) {
                    sink->set_cost(cost+1);//Save the cost from source to sink
                    break;
                }
                if (cost % 2 == 0) {
                    queue1.push_back(grid.at(source->get_y()).at(source->get_x()+1));//add discovered new node to other BFS queue
                }
                else {
                    queue0.push_back(grid.at(source->get_y()).at(source->get_x()+1));//add discovered new node to other BFS queue
                }
        }
        //check if up neighbour node is valid/not visited/not obstacle
        if((source->get_y()-1)>=0&&!grid.at(source->get_y()-1).at(source->get_x())->is_visited()&&
            !grid.at(source->get_y()-1).at(source->get_x())->is_obstacle()){
                grid.at(source->get_y()-1).at(source->get_x())->set_cost(costTo2Bit(cost+1)); //increment cost
                grid.at(source->get_y()-1).at(source->get_x())->set_visit(true);
                if(grid.at(source->get_y()-1).at(source->get_x())==sink) {
                    sink->set_cost(cost+1);//Save the cost from source to sink
                    break;
                }
                if (cost % 2 == 0) {
                    queue1.push_back(grid.at(source->get_y()-1).at(source->get_x()));//add discovered new node to other BFS queue
                }
                else {
                    queue0.push_back(grid.at(source->get_y()-1).at(source->get_x()));//add discovered new node to other BFS queue
                }
        }
        //check if down neighbour node is valid/not visited/not obstacle
        if((source->get_y()+1)<grid.at(0).size()&&!grid.at(source->get_y()+1).at(source->get_x())->is_visited()&&
            !grid.at(source->get_y()+1).at(source->get_x())->is_obstacle()){
				grid.at(source->get_y()+1).at(source->get_x())->set_cost(costTo2Bit(cost+1)); //increment cost
				grid.at(source->get_y()+1).at(source->get_x())->set_visit(true);
				if(grid.at(source->get_y()+1).at(source->get_x())==sink) {
                    sink->set_cost(cost+1);//Save the cost from source to sink
					break;
                }
				if (cost % 2 == 0) {
                    queue1.push_back(grid.at(source->get_y()+1).at(source->get_x()));//add discovered new node to other BFS queue
                }
                else {
                    queue0.push_back(grid.at(source->get_y()+1).at(source->get_x()));//add discovered new node to other BFS queue
                }
        }

    }
}
/*
*Inputs: Unode* Source to connect from
         Unode* Sink to connect to
         grid containing all nodes
         bool intersections set the nodes along path as an obstacle or not
 Modifies: vector<vector<UNode*> >& grid
 Returns: Path* containing path from Source to Sink
 Runs the Breadth-First Search expansion portion of lee's algorithm
 */
Path* traceback_2bit(UNode* source, UNode* sink,vector<vector<UNode*> > &grid,bool intersections){
    Path* new_path = new Path();
    int count = 0;
    int cost = sink->get_cost(); //# of spaces from source to that point
    while(1){
        if(count>grid.size()*grid.at(0).size()){
            claim("There is no valid path, Routing Failed", Utilities::kError);
            }
        //determines if path will become obstacle for next iteration
        if(intersections){
            sink->set_obstacle(true);
        }
        //if traced to source, end
        if(source->get_x()==sink->get_x()&&source->get_y()==sink->get_y())
            break;
        //check if left neighbour was visited, and costs less
         if((sink->get_x()-1)>=0&&grid.at(sink->get_y()).at(sink->get_x()-1)->is_visited()&&
            (grid.at(sink->get_y()).at(sink->get_x()-1)->get_cost()) == costTo2Bit(cost-1)) {
                Point head(sink->get_x(),sink->get_y());//	
                Point tail(grid.at(sink->get_y()).at(sink->get_x()-1)->get_x(),
                    grid.at(sink->get_y()).at(sink->get_x()-1)->get_y());
                PathSegment* new_segment = new PathSegment(head, tail);//traced segment to add to path
                new_path->add_segment(new_segment);
                sink = grid.at(sink->get_y()).at(sink->get_x()-1);//move to next node along path
                cost--;
                goto next;

        }
        //check if right neighbour was visited, and costs less
        else if((sink->get_x()+1)<grid.size()&&grid.at(sink->get_y()).at(sink->get_x()+1)->is_visited()&&
            (grid.at(sink->get_y()).at(sink->get_x()+1)->get_cost()) == costTo2Bit(cost-1)){
                Point head(sink->get_x(),sink->get_y());	
                Point tail(grid.at(sink->get_y()).at(sink->get_x()+1)->get_x(),
                    grid.at(sink->get_y()).at(sink->get_x()+1)->get_y());
                PathSegment* new_segment = new PathSegment(head, tail);
                new_path->add_segment(new_segment);
                sink = grid.at(sink->get_y()).at(sink->get_x()+1);
                cost--;
                goto next;

        }
        //check if down neighbour was visited, and costs less
        else if((sink->get_y()+1)<grid.at(0).size()&&grid.at(sink->get_y()+1).at(sink->get_x())->is_visited()&&
            (grid.at(sink->get_y()+1).at(sink->get_x())->get_cost()) == costTo2Bit(cost-1)){
                Point head(sink->get_x(),sink->get_y());	
                Point tail(grid.at(sink->get_y()+1).at(sink->get_x())->get_x(),
                    grid.at(sink->get_y()+1).at(sink->get_x())->get_y());
                PathSegment* new_segment = new PathSegment(head, tail);
                new_path->add_segment(new_segment);
                sink = grid.at(sink->get_y()+1).at(sink->get_x());
                cost--;
                goto next;

        }
        //check if up neighbour was visited, and costs less
       //check if up neighbour was visited, and costs less
        else if((sink->get_y()-1)>=0&&grid.at(sink->get_y()-1).at(sink->get_x())->is_visited()&&
            (grid.at(sink->get_y()-1).at(sink->get_x())->get_cost()) == costTo2Bit(cost-1)){
                Point head(sink->get_x(),sink->get_y());	
                Point tail(grid.at(sink->get_y()-1).at(sink->get_x())->get_x(),
                    grid.at(sink->get_y()-1).at(sink->get_x())->get_y());
                PathSegment* new_segment = new PathSegment(head, tail);
                new_path->add_segment(new_segment);
                sink = grid.at(sink->get_y()-1).at(sink->get_x());
                cost--;
                goto next;
        }
        next:
        ++count;
    }
    return new_path;
}
