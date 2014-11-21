/* Filename: <unode.h>
* Author:Ryan Bissiri
* Date:11/18/14
* Description: Header file adding additional member variables to Node class
*/
#ifndef _UNODE_H_
#define _UNODE_H_

#include "../Headers/node.h"

namespace Utilities{
    class UNode: public Node{
        private:
            bool obstacle;
            bool visited;
        public:
            //constructors
            UNode(int x, int y, int cost=0);
            UNode(Point coord, int cost=0);
            //accessors
            bool is_visited();
            bool is_obstacle();
            //mutators
            void set_visit(bool visit);
            void set_obstacle(bool obstacle);
        
    };
}	
#endif 