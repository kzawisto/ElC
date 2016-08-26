IDIR = -I../../
COMPILE_FLAGS = -std=c++11 -g
LINK_LIBRARIES = -lboost_unit_test_framework
DEPENDENCIES = Challenges.cpp 
test3 : test3.o Utils.o Challenges.o
	g++ -o $@ $^ $(COMPILE_FLAGS) $(LINK_LIBRARIES)
test4 : test4.o
	g++ -o $@ $^ $(COMPILE_FLAGS) $(LINK_LIBRARIES)
Utils.o : ../Utils.cpp
	g++ -o $@ -c $^ $(IDIR) $(COMPILE_FLAGS)
Challenges.o : ../Challenges.cpp
	g++ -o $@ -c $^ $(IDIR) $(COMPILE_FLAGS)
%.o : %.cxx
	g++ -o $@ -c $^ $(IDIR) $(COMPILE_FLAGS)