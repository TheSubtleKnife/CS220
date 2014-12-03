/* Filename: <unode.cc>
* Author:Ryan Bissiri
* Date:11/18/14
* Description: Implementation of unode.h
*/
#include "../Headers/unode.h"

Utilities::UNode::UNode(int x, int y, int cost):Utilities::Node::Node(x,y,cost){
      this->visited = false;
      this->obstacle = false;
}
Utilities::UNode::UNode(Point coord, int cost):Utilities::Node::Node(coord,cost){
      this->visited = false;
      this->obstacle = false;
}


bool Utilities::UNode::is_visited(){
    return this->visited;
}

bool Utilities::UNode::is_obstacle(){
    return this->obstacle;
}

void Utilities::UNode::set_visit(bool visit){
    this->visited = visit;
}
void Utilities::UNode::set_obstacle(bool obstacle){
    this->obstacle = obstacle;
}
