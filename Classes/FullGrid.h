/*
 * FullGrid.h
 *
 *  Created on: Oct 15, 2015
 *      Author: krystian892
 */

#ifndef CLASSES_FULLGRID_H_
#define CLASSES_FULLGRID_H_
#include "GridNode.h"
#include "logic/SingularGrid.h"
#include "logic/Point.h"
#include "TileNode.h"
#include <string>
#include <functional>
#include<map>
USING_NS_CC;
using namespace std;

class GridObserver{
public:
	virtual void setTime(double t)=0;
	virtual void setLenght(int len)=0;
	virtual void setPoints(double pts)=0;
	virtual void setMoves(int moves)=0;
	virtual void sendChallengesNotification(double pts, int moves,int len)=0;
	virtual ~GridObserver(){};
};
class DummyGridObserver : public GridObserver{
public:
	virtual void setTime(double t){};
	virtual void setLenght(int len){};
	virtual void setPoints(double pts){};
	virtual void setMoves(int moves){};
	virtual void sendChallengesNotification(double pts, int moves,int len){};
	virtual ~DummyGridObserver(){};
};
class FullGrid : public Node {
protected:
	 vector<GridNode *> grids;
	 vector<shared_ptr<logic::SingularGrid>> vec;
	 DrawNode *dnode;
	 DummyGridObserver  dummyObserver;

	 logic::PipePath main_path;
	 bool clickLocked= false;
	 GridNode * start_grid;
	 pair<int,TileNode *> pathStart;
public:
	FullGrid();
	 double time;
	 string name;
	 GridObserver * observer=nullptr;
	 void setMetrics();
	 int moves=0;
	void onClick(const Vec2 & coord);
	void finishConstruction();
	void addGridsToRoot();
	static FullGrid *finalize (FullGrid * grid);
	virtual ~FullGrid();
	virtual void fillGrids(double size);
};

class MyGridFactory{
	map<string, function<FullGrid*(bool)>> creators;
	MyGridFactory();
public:
	FullGrid *generate(string s,double size, bool dummy =false);
	static MyGridFactory & get(){
		static MyGridFactory grd;
		return grd;
	}
};
class TwSqTriFullGrid: public FullGrid{
public:
	TwSqTriFullGrid();
	static TwSqTriFullGrid * create(bool dummy =false);
	void fillGrids(double size);
};
class TwTriFullGrid: public FullGrid{
public:
	TwTriFullGrid();
	static TwTriFullGrid * create(bool dummy =false);
	void fillGrids(double size);
};
class HexFullGrid: public FullGrid{
public:
	HexFullGrid();
	static HexFullGrid * create(bool dummy =false);
	void fillGrids(double size);

};
class SqFullGrid: public FullGrid{
public:
	SqFullGrid();
	static SqFullGrid * create(bool dummy =false);
	void fillGrids(double size);

};
class OctSqFullGrid: public FullGrid{
public:
	OctSqFullGrid();
	static OctSqFullGrid * create(bool dummy =false);
	void fillGrids(double size);

};
#endif /* CLASSES_FULLGRID_H_ */
