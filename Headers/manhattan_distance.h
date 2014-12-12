/* Filename: <manhattan_distance.h>
* Author:James Robinson
* Date:12/09/14
* Description: Header file for manhattan distance
*/
#ifndef _MANHATTAN_H_
#define _MANHATTAN_H_

#include "../Headers/unode.h"
#include <cstdlib>
#include <cmath>        // std::abs

using std::abs;
using Utilities::Node;
using Utilities::UNode;

/*
 Inputs: Unode* node1
 Unode* node2
 Modifies: none
 Returns: int containing manhattan distance from node1 to node2
 Calculates the manhattan distance between two nodes
 */
int manhattan_distance(UNode* node1, UNode* node2);

#endif
