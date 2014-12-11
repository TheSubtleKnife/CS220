/* Filename: <hadlocks.h>
* Author:Ryan Bissiri
* Date:11/18/14
* Description: Header file for lee's expansion and traceback algorithms
*/
#ifndef _HADLOCKS_H_
#define _HADLOCKS_H_

#include "../Headers/unode.h"
#include "../Headers/edge.h"
#include "../Headers/path.h"
#include <time.h>
#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <list>
#include <queue>

using std::cerr;
using std::cout;
using std::endl;
using std::list;
using Utilities::Edge;
using Utilities::Node;
using Utilities::UNode;
using Utilities::Path;
/*
*Inputs: Unode* Source to expand from
         Unode* Sink to find
         grid containing all nodes
 Modifies: vector<vector<UNode*> >& grid
 Returns: Void
 Runs the Breadth-First Search expansion portion of lee's algorithm
 */
void hadlocks_expand(UNode* source, UNode* sink, vector<vector<UNode*> >& grid);
/*
*Inputs: Unode* Source to connect from
         Unode* Sink to connect to
         grid containing all nodes
         bool intersections set the nodes along path as an obstacle or not
 Modifies: vector<vector<UNode*> >& grid
 Returns: Path* containing path from Source to Sink
 Runs the Breadth-First Search expansion portion of lee's algorithm
 */
Path* hadlocks_traceback(UNode* source, UNode* sink ,vector<vector<UNode*> >&grid, bool intersections,bool minturns);
int man_dist(UNode* source, UNode* sink);
#endif