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
            int detour;
            int rubins_cost;
            float korns_cost;
        public:
            //constructors
            UNode(int x, int y, int cost=0);
            UNode(Point coord, int cost=0);
            //accessors
            bool is_visited();
            bool is_obstacle();
            int get_detour();
            int get_rubins_cost();
            float get_korns_cost();
            //mutators
            void set_visit(bool visit);
            void set_obstacle(bool obstacle);
            void set_detour(int detour);
			void set_rubins_cost(int rubins_cost);
			void set_korns_cost(float korns_cost);
    };
}	
#endif 
