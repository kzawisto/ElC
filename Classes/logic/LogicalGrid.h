/*
 * LogicalGrid.h
 *
 *  Created on: Oct 12, 2015
 *      Author: krystian892
 */

#ifndef CLASSES_LOGIC_LOGICALGRID_H_
#define CLASSES_LOGIC_LOGICALGRID_H_
#include<vector>
#include<memory>
//haslo cent2015
//centrym@wz.uw.edu.pl
#include"logic/SingularGrid.h"
using namespace std;
namespace logic{
class LogicalGrid {
public:
	vector<SingularGrid*> grids;

	LogicalGrid();
	virtual ~LogicalGrid();
	void createOctSqGrid();
};
class GridConnectionResolver{
public:
	vector<shared_ptr<SingularGrid>> grids;
	vector<shared_ptr<LogicalTile>> tiles;
	GridConnectionResolver(vector<shared_ptr<SingularGrid>> & grids);
	void propagateConnections();
};

}
#endif /* CLASSES_LOGIC_LOGICALGRID_H_ */
