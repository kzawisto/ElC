#ifndef SINGULARGRID_H
#define SINGULARGRID_H
#include"logic/Point.h"
#include<memory>
#include<vector>
#include"logic/LogicalTile.h"

using namespace std;
namespace logic{

class SingularGrid
{
public:

    Point<int> size;
    Point<double>spacing;
    vector<shared_ptr<LogicalTile>> vec;
    SingularGrid(int N,Point <int> _size, Point<double> spacing, Point<double> first, Point <double> position);
    SingularGrid(const SingularGrid& other);
    shared_ptr<LogicalTile> get(int x, int y);
    bool check(int x, int y);
    void propagateConnections();


};
}
#endif // SINGULARGRID_H
