#ifndef LOGICALTILE_H
#define LOGICALTILE_H
#include "logic/Point.h"
#include <map>
#include<vector>
#include<valarray>
#include<memory>
#include<tuple>
#include<functional>
namespace logic{
typedef logic::Point<double> PD;
typedef logic::Point<int> PI;
class SingularGrid;
class TileObserver {
public:
	virtual void lightenPath(int i)=0;
	virtual void dimPath(int i)=0;
	virtual void otherMethod(){}
	virtual ~TileObserver(){};
};
class ConsoleTileObserver : public TileObserver{
	virtual void lightenPath(int i);
		virtual void dimPath(int i);
		virtual ~ConsoleTileObserver(){};
};
class LogicalTile
{
public:
    double CircR, InsR;
    //std::function<void(int)> lightenPath, unlightenPath;
    int n;
    void rotate(int step);
    int constrainNumber(int num){
    	return (num + n* wires_per_side) % (n* wires_per_side);
    }
    double internal_angle,rotation_angle;
    map<int, shared_ptr<LogicalTile>> connections;
    map<int,int> connections_num;
    std::vector<int> internalWiring;
    SingularGrid * grid;
    TileObserver * tileObserver;
    std::vector<int> internal;
	Point<int> grid_position;
    std::vector<Point<double>> contour, centered_contour,connectionPoints;
    Point<double> position;
    int wires_per_side;
    LogicalTile();
     LogicalTile(const LogicalTile & other);
     void setRotation(double rot);
    LogicalTile(int _n, Point<double> _position, Point<double> first_vertex);
    int testNeighbourhood(LogicalTile & nei, double epsilon);
    ~LogicalTile();
    void setRandomInternalWiring(int wires_per_side);
    void setConnectionPoints();
    LogicalTile& operator=(const LogicalTile& other);
    bool operator==(const LogicalTile& other) const;
    PD connectionPointOnThis(int side, int wire);
    shared_ptr<LogicalTile> getConnectionNeighbour(int side);
    PD connectionPointOnNeighbour(int side, int wire);
	const Point<int>& getGridPosition() const {
		return grid_position;
	}

	void setGridPosition(const Point<int>& gridPosition) {
		grid_position = gridPosition;
	}
};

class PipePath{

	const int wps =2;
	pair<int,int> parseWiringNumber(int i){
		return { i/wps, i%wps};
	}
	int getWiringNumber(pair<int,int> p){
		return p.first * wps + p.second;
	}
public:
	vector<pair<int,shared_ptr<LogicalTile>>> vec;
	PipePath();
	int findLogicalTile(shared_ptr<LogicalTile> pt);
	void startPathFrom(int entry, shared_ptr<LogicalTile> tile);
	void deletePath(int begin=0);
};

}





#endif // LOGICALTILE_H
