
/* Filename: <lees_korns.cc>
* Author:Ryan Bissiri/James Robinson
* Date:11/20/14
* Description: Implementation for lee's expansion and traceback algorithms
* 	(using Korn's cost optimization)
*/
#include "../Headers/lees_korns.h"
#include "../Headers/claim.h"
using Utilities::claim;

class CompareKorns{
    public:
        bool operator()(UNode* x, UNode* y){
            if(x->get_korns_cost() >= y->get_korns_cost()) {
                return true;
            }
            else {
                return false;
            }
        }
};

/*
*Inputs: Unode* Source to expand from
         Unode* Sink to find
         grid containing all nodes
 Modifies: vector<vector<UNode*> >& grid
 Returns: Void
 Runs the Breadth-First Search expansion portion of lee's algorithm
 */
void lees_korns_expand(UNode* source, UNode* sink, vector<vector<UNode*> >& grid){
    float A = 1.5; //Must be >=1. If A=1, you're just doing Rubin's
    //initial source node
    int cost = 0;
    source->set_cost(cost);
    source->set_visit(true);
    source->set_korns_cost(A*manhattan_distance(source, sink));
    //BFS priority queue
    std::priority_queue<UNode*,vector<UNode*>, CompareKorns> queue;
    queue.push(source);
    while(!queue.empty())
    {
        source = queue.top();
        queue.pop();
        //check if left neighbour node is valid/not visited/not obstacle
        if((source->get_x()-1)>=0&&!grid.at(source->get_y()).at(source->get_x()-1)->is_visited()&&
            !grid.at(source->get_y()).at(source->get_x()-1)->is_obstacle()){
                grid.at(source->get_y()).at(source->get_x()-1)->set_cost((source->get_cost())+1); //increment cost 
                grid.at(source->get_y()).at(source->get_x()-1)->set_visit(true);
                float neighbor_priority = (source->get_cost()) + 1 + A*manhattan_distance(grid.at(source->get_y()).at(source->get_x()-1),sink);
                grid.at(source->get_y()).at(source->get_x()-1)->set_korns_cost(neighbor_priority);
                if(grid.at(source->get_y()).at(source->get_x()-1)==sink) {//if sink node found, end search
                    break;
				}
                queue.push(grid.at(source->get_y()).at(source->get_x()-1));//add discovered new node to priority queue
        }
        //check if right neighbour node is valid/not visited/not obstacle
        if((source->get_x()+1)<grid.at(0).size()&&!grid.at(source->get_y()).at(source->get_x()+1)->is_visited()&&
            !grid.at(source->get_y()).at(source->get_x()+1)->is_obstacle()){
                grid.at(source->get_y()).at(source->get_x()+1)->set_cost((source->get_cost())+1); //increment cost 
                grid.at(source->get_y()).at(source->get_x()+1)->set_visit(true);
                float neighbor_priority = (source->get_cost()) + 1 + A*manhattan_distance(grid.at(source->get_y()).at(source->get_x()+1),sink);
                grid.at(source->get_y()).at(source->get_x()+1)->set_korns_cost(neighbor_priority);
                if(grid.at(source->get_y()).at(source->get_x()+1)==sink) {
                    break;
				}
                queue.push(grid.at(source->get_y()).at(source->get_x()+1));
        }
        //check if up neighbour node is valid/not visited/not obstacle
        if((source->get_y()-1)>=0&&!grid.at(source->get_y()-1).at(source->get_x())->is_visited()&&
            !grid.at(source->get_y()-1).at(source->get_x())->is_obstacle()){
                grid.at(source->get_y()-1).at(source->get_x())->set_cost((source->get_cost())+1); //increment cost 
                grid.at(source->get_y()-1).at(source->get_x())->set_visit(true);
                float neighbor_priority = (source->get_cost()) + 1 + A*manhattan_distance(grid.at(source->get_y()-1).at(source->get_x()),sink);
                grid.at(source->get_y()-1).at(source->get_x())->set_korns_cost(neighbor_priority);
                if(grid.at(source->get_y()-1).at(source->get_x())==sink) {
                    break;
				}
                queue.push(grid.at(source->get_y()-1).at(source->get_x()));
            
        }
        //check if down neighbour node is valid/not visited/not obstacle
        if((source->get_y()+1)<grid.size()&&!grid.at(source->get_y()+1).at(source->get_x())->is_visited()&&
            !grid.at(source->get_y()+1).at(source->get_x())->is_obstacle()){
				grid.at(source->get_y()+1).at(source->get_x())->set_cost((source->get_cost())+1); //increment cost 
				grid.at(source->get_y()+1).at(source->get_x())->set_visit(true);
				float neighbor_priority = (source->get_cost()) + 1 + A*manhattan_distance(grid.at(source->get_y()+1).at(source->get_x()),sink);
				grid.at(source->get_y()+1).at(source->get_x())->set_korns_cost(neighbor_priority);
				if(grid.at(source->get_y()+1).at(source->get_x())==sink) {
					break;
				}
				queue.push(grid.at(source->get_y()+1).at(source->get_x()));

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
Path* traceback_korns(UNode* source, UNode* sink,vector<vector<UNode*> > &grid,bool intersections){
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
