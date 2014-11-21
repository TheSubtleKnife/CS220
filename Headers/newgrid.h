#ifndef _NEWGRID_H_
#define _NEWGRID_H_

#include "../Headers/unode.h"
#include "../Headers/edge.h"
#include "../Headers/path.h"
#include "../Headers/lees.h"
#include "../Headers/problem_object.h"
#include <time.h>
#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <list>
class ProblemObject;
class NewGrid{
    private:
        vector<vector<UNode*> > grid;
    public:
         NewGrid(Utilities::ProblemObject& problem);
         ~NewGrid();
        vector<Path*> run_lees(Utilities::ProblemObject& problem, bool intersection );
        void print_graph();
};
#endif