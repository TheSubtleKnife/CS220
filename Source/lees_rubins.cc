
/* Filename: <lees_rubins.cc>
* Author:Ryan Bissiri/James Robinson
* Date:11/20/14
* Description: Implementation for lee's expansion and traceback algorithms
* 	(using Rubin's cost optimization)
*/
#include "../Headers/lees_rubins.h"
#include "../Headers/claim.h"
using Utilities::claim;
/* documentation goes here
 */
int manhattan_distance(UNode* node1, UNode* node2) {
	return abs(node1->get_x() - node2->get_x()) + abs(node1->get_y() - node2->get_y());
}

/*
*Inputs: Unode* Source to expand from
         Unode* Sink to find
         grid containing all nodes
 Modifies: vector<vector<UNode*> >& grid
 Returns: Void
 Runs the Breadth-First Search expansion portion of lee's algorithm
 */
void lees_rubins_expand(UNode* source, UNode* sink, vector<vector<UNode*> >& grid){
    //initial source node
    int cost = 0;
    source->set_cost(cost);
    source->set_visit(true);
    source->set_rubins_cost(manhattan_distance(source, sink));
    //BFS priority queue
    int max_priority = grid.size() * grid.at(0).size(); //theoretical worst case rubin's cost of a  
    list<UNode*> queue[max_priority]; //priority queue
    int current_priority = source->get_rubins_cost(); //we'll never expand to a cell with a lower Rubin's cost than its predecessor
    queue[current_priority].push_back(source);
    while(true)
    {
        while (current_priority < max_priority && queue[current_priority].empty()) {
			current_priority++;
		}
        if (current_priority >= max_priority) {
			break;
		}
        source = queue[current_priority].front();
        queue[current_priority].pop_front();
        //check if left neighbour node is valid/not visited/not obstacle
      if((source->get_x()-1)>=0&&!grid.at(source->get_y()).at(source->get_x()-1)->is_visited()&&
            !grid.at(source->get_y()).at(source->get_x()-1)->is_obstacle()){
                grid.at(source->get_y()).at(source->get_x()-1)->set_cost((source->get_cost())+1); //increment cost 
                grid.at(source->get_y()).at(source->get_x()-1)->set_visit(true);//
                if(grid.at(source->get_y()).at(source->get_x()-1)==sink)//if sink node found, end search
                    break;
                int neighbor_priority = (source->get_cost()) + 1 + manhattan_distance(grid.at(source->get_y()).at(source->get_x()-1),sink);
                queue[neighbor_priority].push_back(grid.at(source->get_y()).at(source->get_x()-1));//add discovered new node to BFS queue
        }
        //check if right neighbour node is valid/not visited/not obstacle
        if((source->get_x()+1)<grid.size()&&!grid.at(source->get_y()).at(source->get_x()+1)->is_visited()&&
            !grid.at(source->get_y()).at(source->get_x()+1)->is_obstacle()){
                grid.at(source->get_y()).at(source->get_x()+1)->set_cost((source->get_cost())+1); //increment cost 
                grid.at(source->get_y()).at(source->get_x()+1)->set_visit(true);
                if(grid.at(source->get_y()).at(source->get_x()+1)==sink)
                    break;
                int neighbor_priority = (source->get_cost()) + 1 + manhattan_distance(grid.at(source->get_y()).at(source->get_x()+1),sink);
                queue[neighbor_priority].push_back(grid.at(source->get_y()).at(source->get_x()+1));
        }
        //check if up neighbour node is valid/not visited/not obstacle
        if((source->get_y()-1)>=0&&!grid.at(source->get_y()-1).at(source->get_x())->is_visited()&&
            !grid.at(source->get_y()-1).at(source->get_x())->is_obstacle()){
                grid.at(source->get_y()-1).at(source->get_x())->set_cost((source->get_cost())+1); //increment cost 
                grid.at(source->get_y()-1).at(source->get_x())->set_visit(true);
                if(grid.at(source->get_y()-1).at(source->get_x())==sink)
                    break;
                int neighbor_priority = (source->get_cost()) + 1 + manhattan_distance(grid.at(source->get_y()-1).at(source->get_x()),sink);
                queue[neighbor_priority].push_back(grid.at(source->get_y()-1).at(source->get_x()));
            
        }
        //check if down neighbour node is valid/not visited/not obstacle
        if((source->get_y()+1)<grid.at(0).size()&&!grid.at(source->get_y()+1).at(source->get_x())->is_visited()&&
            !grid.at(source->get_y()+1).at(source->get_x())->is_obstacle()){
            grid.at(source->get_y()+1).at(source->get_x())->set_cost((source->get_cost())+1); //increment cost 
            grid.at(source->get_y()+1).at(source->get_x())->set_visit(true);
            if(grid.at(source->get_y()+1).at(source->get_x())==sink)
                break;
                int neighbor_priority = (source->get_cost()) + 1 + manhattan_distance(grid.at(source->get_y()+1).at(source->get_x()),sink);
            queue[neighbor_priority].push_back(grid.at(source->get_y()+1).at(source->get_x()));

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
Path* traceback_rubins(UNode* source, UNode* sink,vector<vector<UNode*> > &grid,bool intersections){
    Path* new_path = new Path();
    int count = 0;
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
            (grid.at(sink->get_y()).at(sink->get_x()-1)->get_cost()+1) == (sink->get_cost())) {
                Point head(sink->get_x(),sink->get_y());//	
                Point tail(grid.at(sink->get_y()).at(sink->get_x()-1)->get_x(),
                    grid.at(sink->get_y()).at(sink->get_x()-1)->get_y());
                PathSegment* new_segment = new PathSegment(head, tail);//traced segment to add to path
                new_path->add_segment(new_segment);
                sink = grid.at(sink->get_y()).at(sink->get_x()-1);//move to next node along path
                goto next;

        }
        //check if right neighbour was visited, and costs less
        else if((sink->get_x()+1)<grid.at(0).size()&&grid.at(sink->get_y()).at(sink->get_x()+1)->is_visited()&&
            (grid.at(sink->get_y()).at(sink->get_x()+1)->get_cost()+1) == sink->get_cost()){
               Point head(sink->get_x(),sink->get_y());	
                Point tail(grid.at(sink->get_y()).at(sink->get_x()+1)->get_x(),
                    grid.at(sink->get_y()).at(sink->get_x()+1)->get_y());
                PathSegment* new_segment = new PathSegment(head, tail);
                new_path->add_segment(new_segment);
                sink = grid.at(sink->get_y()).at(sink->get_x()+1);
                goto next;

        }
        //check if down neighbour was visited, and costs less
        else if((sink->get_y()+1)<grid.size()&&grid.at(sink->get_y()+1).at(sink->get_x())->is_visited()&&
            (grid.at(sink->get_y()+1).at(sink->get_x())->get_cost()+1) == sink->get_cost()){
               Point head(sink->get_x(),sink->get_y());	
                Point tail(grid.at(sink->get_y()+1).at(sink->get_x())->get_x(),
                    grid.at(sink->get_y()+1).at(sink->get_x())->get_y());
               PathSegment* new_segment = new PathSegment(head, tail);
                new_path->add_segment(new_segment);
                sink = grid.at(sink->get_y()+1).at(sink->get_x());
                goto next;

        }
        //check if up neighbour was visited, and costs less
       //check if up neighbour was visited, and costs less
        else if((sink->get_y()-1)>=0&&grid.at(sink->get_y()-1).at(sink->get_x())->is_visited()&&
            (grid.at(sink->get_y()-1).at(sink->get_x())->get_cost()+1) == sink->get_cost()){
                Point head(sink->get_x(),sink->get_y());	
                Point tail(grid.at(sink->get_y()-1).at(sink->get_x())->get_x(),
                    grid.at(sink->get_y()-1).at(sink->get_x())->get_y());
                PathSegment* new_segment = new PathSegment(head, tail);
                new_path->add_segment(new_segment);
                sink = grid.at(sink->get_y()-1).at(sink->get_x());
                goto next;
        }
        next:
        ++count;
    }
    return new_path;
}
