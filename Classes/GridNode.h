/*
 * GridNode.h
 *
 *  Created on: Oct 12, 2015
 *      Author: krystian892
 */

#ifndef CLASSES_GRIDNODE_H_
#define CLASSES_GRIDNODE_H_

#include"cocos2d.h"
#include<vector>
#include"logic/Point.h"
#include"TileNode.h"
#include"logic/SingularGrid.h"
#include<map>
#include<string>
#include <algorithm>
#include <memory>
#include <functional>

USING_NS_CC;
using namespace std;
typedef logic::SingularGrid SinGrid;
class GridNode : public Node {
public:
	PI size;
	PD position, spacing;
	double angleOffsetSprite=0;
	shared_ptr<SinGrid> singularGrid;
	vector<TileNode*> tileNodes;
	GridNode(PI _size,  PD _spacing);
	TileNode * get(int i,int j);
	static GridNode *createOctGridOld(double size);


	static GridNode * createOctGrid(PD position, double size, PD spacing,PI howMany);
	static GridNode * createTwGrid(PD position, double size, PD spacing,PI howMany);
	pair<double, PI> parseCoordinate(PD coord);
	static GridNode * createTriGrid(PD position, double size, PD spacing,PI howMany, int direction=true);
	static GridNode * createHexGrid(PD position, double size, PD spacing,PI howMany);
	void drawConnections(int i, int j,DrawNode *d);
	static GridNode *createSqrGridOld(double size,double angleOffsetDeg);
	static GridNode *createSqrGrid(PD position, double size, PD spacing, PI howMany, double angleOffset=0);
	void createTileNodes();
	void createTileNodesEx();
	virtual ~GridNode();
};
class ButtonFactory{
 static void f(int i){}
public:
  static MenuItem * createButton(std::function<void (Ref*)> func,std::string labelText, Vec2 pos, double fontsize=24);
};
namespace myUtils{
void scheduleOnce(std::function<void(float)> f,void *ptr, float delay,string key ="sth");

}
#endif /* CLASSES_GRIDNODE_H_ */
