/* Filename: <manhattan_distance.cc>
* Author:Ryan Bissiri/James Robinson
* Date:12/09/14
* Description: Compute the manhattan distance between two nodes
*/
#include "../Headers/manhattan_distance.h"

/*
 Inputs: Unode* node1
 Unode* node2
 Modifies: none
 Returns: int containing manhattan distance from node1 to node2
 Calculates the manhattan distance between two nodes
 */
int manhattan_distance(UNode* node1, UNode* node2) {
	return (abs(node1->get_x() - node2->get_x()) + abs(node1->get_y() - node2->get_y()));
}
