
SRC=$(filter-out %main.cc, Source/*)
OBJ=claim.o edge.o grid.o netlist.o node.o path.o pathsegment.o problem_object.o segmentgroup.o newgrid.o lees.o unode.o lees_3bit.o lees_2bit.o lees_rubins.o hadlocks.o lees_korns.o manhattan_distance.o

vpath %.cc Source/

all: $(OBJ) main.cc
	g++ -g -o grid_router $^ Utilities/JSON_parser/json_parser.so 

test: all
	./grid_router Tests/test_sample.json
	
%.o: %.cc
	g++ -c $^

cleanup:
	rm -f *.o

clean: cleanup
	rm -f grid_router

