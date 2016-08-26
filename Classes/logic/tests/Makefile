IDIR = -I../..
OBJDIR = ../obj

_OBJS = Point.o

OBJS = $(patsubst %,$(OBJDIR)/%,$(_OBJS))

test1: test1.o Point.o LogicalTile.o
	g++ -o test1 -std=c++11 $(IDIR) -g $^ -lboost_unit_test_framework
test2: test2.o Point.o LogicalTile.o SingularGrid.o
	g++ -o test2 -std=c++11 $(IDIR) -g $^ -lboost_unit_test_framework


test1.o: test1.cpp
	g++ -o $@ $(IDIR) -std=c++11 -g -c $^
test2.o: test2.cpp
	g++ -o $@ $(IDIR) -std=c++11 -g -c $^
Point.o: ../Point.cpp
	g++ -o $@  $(IDIR) -std=c++11 -g -c $^
LogicalTile.o: ../LogicalTile.cpp
	g++ -o $@  $(IDIR) -std=c++11 -g -c $^
%.o : ../%.cpp
	g++ -o $@  $(IDIR) -std=c++11 -g -c $^
.PHONY: clean
clean:
	rm -f *.o