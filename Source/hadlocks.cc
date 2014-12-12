/* Filename: <hadlocks.cc>
* Author:Ryan Bissiri
* Date:11/18/14
* Description: Implementation for hadlocks's expansion and traceback algorithms
*/
#include "../Headers/hadlocks.h"
#include "../Headers/claim.h"

using Utilities::claim;


//Comparison class needed for priority queue of UNode*
class CompareNode{
    public:
        bool operator()(UNode* x, UNode* y){
            if(x->get_detour() >= y->get_detour()){
                return true;
            }
            else{
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
 
void hadlocks_expand(UNode* source, UNode* sink, vector<vector<UNode*> >& grid){
    //initial source node
    int cost = 0;
    source->set_cost(cost);
    source->set_visit(true);
    int init_detour = man_dist(source, sink);
    //priority queue ussed in order to visit lower detour nodes first
    std::priority_queue<UNode*,vector<UNode*>, CompareNode> queue;
    queue.push(source);
    while(!queue.empty())
    {
        source = queue.top();
        queue.pop();

        //check if left neighbour node is valid/not visited/not obstacle
        if((source->get_x()-1)>=0&&!grid.at(source->get_y()).at(source->get_x()-1)->is_visited()&&
            !grid.at(source->get_y()).at(source->get_x()-1)->is_obstacle()){
                grid.at(source->get_y()).at(source->get_x()-1)->set_cost(source->get_cost()+1); //increment cost
                //if node is a detour, add 1 to detour number
                if(man_dist(source,sink)<man_dist(grid.at(source->get_y()).at(source->get_x()-1),sink)){
              
                    grid.at(source->get_y()).at(source->get_x()-1)->set_detour(grid.at(source->get_y())
                        .at(source->get_x())->get_detour() +1);
                }
                //if not a detour, update node with the same detour number
                else{
                     grid.at(source->get_y()).at(source->get_x()-1)->set_detour(grid.at(source->get_y())
                        .at(source->get_x())->get_detour());
                }
                grid.at(source->get_y()).at(source->get_x()-1)->set_visit(true);//
                if(grid.at(source->get_y()).at(source->get_x()-1)==sink)//if sink node found, end search
                    break;
                queue.push(grid.at(source->get_y()).at(source->get_x()-1));//add discovered new node to BFS queue
        }
        //check if right neighbour node is valid/not visited/not obstacle
        if((source->get_x()+1)<grid.at(0).size()&&!grid.at(source->get_y()).at(source->get_x()+1)->is_visited()&&
            !grid.at(source->get_y()).at(source->get_x()+1)->is_obstacle()){
                grid.at(source->get_y()).at(source->get_x()+1)->set_cost(source->get_cost()+1);
                if(man_dist(source,sink)<man_dist(grid.at(source->get_y()).at(source->get_x()+1),sink)){
                   
                    grid.at(source->get_y()).at(source->get_x()+1)->set_detour(grid.at(source->get_y())
                        .at(source->get_x())->get_detour() +1);
                }
                 else{
                     grid.at(source->get_y()).at(source->get_x()+1)->set_detour(grid.at(source->get_y())'
                        .at(source->get_x())->get_detour());
                }
                grid.at(source->get_y()).at(source->get_x()+1)->set_visit(true);
                if(grid.at(source->get_y()).at(source->get_x()+1)==sink)
                    break;
                queue.push(grid.at(source->get_y()).at(source->get_x()+1));
        }
        //check if up neighbour node is valid/not visited/not obstacle
        if((source->get_y()-1)>=0&&!grid.at(source->get_y()-1).at(source->get_x())->is_visited()&&
            !grid.at(source->get_y()-1).at(source->get_x())->is_obstacle()){
                grid.at(source->get_y()-1).at(source->get_x())->set_cost(source->get_cost()+1);
                if(man_dist(source,sink)<man_dist(grid.at(source->get_y()-1).at(source->get_x()),sink)){
                   
                    grid.at(source->get_y()-1).at(source->get_x())->set_detour(grid.at(source->get_y())
                        .at(source->get_x())->get_detour() +1);
                }
                 else{
                     grid.at(source->get_y()-1).at(source->get_x())->set_detour(grid.at(source->get_y())
                        .at(source->get_x())->get_detour());
                }
                grid.at(source->get_y()-1).at(source->get_x())->set_visit(true);
                if(grid.at(source->get_y()-1).at(source->get_x())==sink)
                    break;
                queue.push(grid.at(source->get_y()-1).at(source->get_x()));
            
        }
        //check if down neighbour node is valid/not visited/not obstacle
        if((source->get_y()+1)<grid.size()&&!grid.at(source->get_y()+1).at(source->get_x())->is_visited()&&
            !grid.at(source->get_y()+1).at(source->get_x())->is_obstacle()){
            grid.at(source->get_y()+1).at(source->get_x())->set_cost(source->get_cost()+1);
            if(man_dist(source,sink)<man_dist(grid.at(source->get_y()+1).at(source->get_x()),sink)){

                    grid.at(source->get_y()+1).at(source->get_x())->set_detour(grid.at(source->get_y())
                        .at(source->get_x())->get_detour() +1);
                }
             else{
                     grid.at(source->get_y()+1).at(source->get_x())->set_detour(grid.at(source->get_y())
                        .at(source->get_x())->get_detour());
                }
            grid.at(source->get_y()+1).at(source->get_x())->set_visit(true);
            if(grid.at(source->get_y()+1).at(source->get_x())==sink)
                break;
            queue.push(grid.at(source->get_y()+1).at(source->get_x()));
            
        }
    }
}
/*
*Inputs: Unode* Source to connect from
         Unode* Sink to connect to
         grid containing all nodes
         bool intersections set the nodes along path as an obstacle or not
         bool minturns try to minimize turns
 Modifies: vector<vector<UNode*> >& grid
 Returns: Path* containing path from Source to Sink
 Runs the Breadth-First Search expansion portion of lee's algorithm
 */
Path* hadlocks_traceback(UNode* source, UNode* sink,vector<vector<UNode*> > &grid,bool intersections,bool minturns){
    Path* new_path = new Path();
    int count = 0;
    while(1){
        //last direction taken
        enum directions {left,right,up,down,any};
        directions direction;
        direction = any;
    
        if(count>grid.size()*grid.at(0).size()){
            claim("There is no valid path, routing failed", Utilities::kError);
            }
        //determines if path will become obstacle for next iteration
        if(intersections){
            sink->set_obstacle(true);
        }  
        //if traced to source, end
        if(source->get_x()==sink->get_x()&&source->get_y()==sink->get_y())
            break;
        //check if left neighbour was visited, and costs less 
        if(minturns){
            if((sink->get_x()-1)>=0&&grid.at(sink->get_y()).at(sink->get_x()-1)->is_visited()&&
                grid.at(sink->get_y()).at(sink->get_x()-1)->get_cost()<sink->get_cost()&&direction==left){
                
                    Point head(sink->get_x(),sink->get_y());//	
                    Point tail(grid.at(sink->get_y()).at(sink->get_x()-1)->get_x(),
                        grid.at(sink->get_y()).at(sink->get_x()-1)->get_y());
                    PathSegment* new_segment = new PathSegment(head, tail);//traced segment to add to path
                    new_path->add_segment(new_segment);
                    sink = grid.at(sink->get_y()).at(sink->get_x()-1);//move to next node along path
                    goto next;
                
            }
            //check if right neighbour was visited, and costs less
            else if((sink->get_x()+1)<grid.size()&&grid.at(sink->get_y()).at(sink->get_x()+1)->is_visited()&&
                grid.at(sink->get_y()).at(sink->get_x()+1)->get_cost()<sink->get_cost()&&direction==right){
                   
                    Point head(sink->get_x(),sink->get_y());	
                    Point tail(grid.at(sink->get_y()).at(sink->get_x()+1)->get_x(),
                        grid.at(sink->get_y()).at(sink->get_x()+1)->get_y());
                    PathSegment* new_segment = new PathSegment(head, tail);
                    new_path->add_segment(new_segment);
                    sink = grid.at(sink->get_y()).at(sink->get_x()+1);
                    goto next;
                
            }
            //check if down neighbour was visited, and costs less
            else if((sink->get_y()+1)<grid.at(0).size()&&grid.at(sink->get_y()+1).at(sink->get_x())->is_visited()&&
                grid.at(sink->get_y()+1).at(sink->get_x())->get_cost()<sink->get_cost()&&direction==down){
                   
                    Point head(sink->get_x(),sink->get_y());	
                    Point tail(grid.at(sink->get_y()+1).at(sink->get_x())->get_x(),
                        grid.at(sink->get_y()+1).at(sink->get_x())->get_y());
                   PathSegment* new_segment = new PathSegment(head, tail);
                    new_path->add_segment(new_segment);
                    sink = grid.at(sink->get_y()+1).at(sink->get_x());
                    goto next;
                
            }
            //check if up neighbour was visited, and costs less
            else if((sink->get_y()-1)>=0&&grid.at(sink->get_y()-1).at(sink->get_x())->is_visited()&&
                grid.at(sink->get_y()-1).at(sink->get_x())->get_cost()<sink->get_cost()&&direction==up){
                
                    Point head(sink->get_x(),sink->get_y());	
                    Point tail(grid.at(sink->get_y()-1).at(sink->get_x())->get_x(),
                        grid.at(sink->get_y()-1).at(sink->get_x())->get_y());
                    PathSegment* new_segment = new PathSegment(head, tail);
                    new_path->add_segment(new_segment);
                    sink = grid.at(sink->get_y()-1).at(sink->get_x());
                    goto next;
            }
        }
        //if direction needs to change
        
        //check if left neighbour was visited, and costs less
        if((sink->get_x()-1)>=0&&grid.at(sink->get_y()).at(sink->get_x()-1)->is_visited()&&
            grid.at(sink->get_y()).at(sink->get_x()-1)->get_cost()<sink->get_cost()){
            
                Point head(sink->get_x(),sink->get_y());//	
                Point tail(grid.at(sink->get_y()).at(sink->get_x()-1)->get_x(),
                    grid.at(sink->get_y()).at(sink->get_x()-1)->get_y());
                PathSegment* new_segment = new PathSegment(head, tail);//traced segment to add to path
                new_path->add_segment(new_segment);
                sink = grid.at(sink->get_y()).at(sink->get_x()-1);//move to next node along path
                direction = left;
                goto next;
            
        }
        //check if right neighbour was visited, and costs less
        else if((sink->get_x()+1)<grid.size()&&grid.at(sink->get_y()).at(sink->get_x()+1)->is_visited()&&
            grid.at(sink->get_y()).at(sink->get_x()+1)->get_cost()<sink->get_cost()){
               
                Point head(sink->get_x(),sink->get_y());	
                Point tail(grid.at(sink->get_y()).at(sink->get_x()+1)->get_x(),
                    grid.at(sink->get_y()).at(sink->get_x()+1)->get_y());
                PathSegment* new_segment = new PathSegment(head, tail);
                new_path->add_segment(new_segment);
                sink = grid.at(sink->get_y()).at(sink->get_x()+1);
                direction = right;
                goto next;
            
        }
        //check if down neighbour was visited, and costs less
        else if((sink->get_y()+1)<grid.at(0).size()&&grid.at(sink->get_y()+1).at(sink->get_x())->is_visited()&&
            grid.at(sink->get_y()+1).at(sink->get_x())->get_cost()<sink->get_cost()){
               
                Point head(sink->get_x(),sink->get_y());	
                Point tail(grid.at(sink->get_y()+1).at(sink->get_x())->get_x(),
                    grid.at(sink->get_y()+1).at(sink->get_x())->get_y());
               PathSegment* new_segment = new PathSegment(head, tail);
                new_path->add_segment(new_segment);
                sink = grid.at(sink->get_y()+1).at(sink->get_x());
                direction = down;
                goto next;
            
        }
        //check if up neighbour was visited, and costs less
        else if((sink->get_y()-1)>=0&&grid.at(sink->get_y()-1).at(sink->get_x())->is_visited()&&
            grid.at(sink->get_y()-1).at(sink->get_x())->get_cost()<sink->get_cost()){
            
                Point head(sink->get_x(),sink->get_y());	
                Point tail(grid.at(sink->get_y()-1).at(sink->get_x())->get_x(),
                    grid.at(sink->get_y()-1).at(sink->get_x())->get_y());
                PathSegment* new_segment = new PathSegment(head, tail);
                new_path->add_segment(new_segment);
                sink = grid.at(sink->get_y()-1).at(sink->get_x());
                direction = up;
                goto next;
        }
        next:
        ++count;
    }
    return new_path;
}

int man_dist(UNode* source, UNode* sink){
    return(abs(source->get_x()-sink->get_x())+abs(source->get_y()-sink->get_y()));
}
            
