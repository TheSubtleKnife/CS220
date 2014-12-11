/* Filename: <unode.cc>
* Author:Ryan Bissiri
* Date:11/18/14
* Description: Implementation of unode.h
*/
#include "../Headers/unode.h"

Utilities::UNode::UNode(int x, int y, int cost):Utilities::Node::Node(x,y,cost){
      this->visited = false;
      this->obstacle = false;
      this->detour = 0;
      this->rubins_cost = 0;
}
Utilities::UNode::UNode(Point coord, int cost):Utilities::Node::Node(coord,cost){
      this->visited = false;
      this->obstacle = false;
      this->detour = 0;
      this->rubins_cost = 0;
}


bool Utilities::UNode::is_visited(){
    return this->visited;
}

bool Utilities::UNode::is_obstacle(){
    return this->obstacle;
}

int Utilities::UNode::get_detour(){
    return this->detour;
}

int Utilities::UNode::get_rubins_cost() {
      return this->rubins_cost;
}

void Utilities::UNode::set_visit(bool visit){
    this->visited = visit;
}

void Utilities::UNode::set_obstacle(bool obstacle){
    this->obstacle = obstacle;
}

void Utilities::UNode::set_detour(int detour){
    this->detour = detour;
}

void Utilities::UNode::set_rubins_cost(int rubins_cost) {
      this->rubins_cost = rubins_cost;
}
