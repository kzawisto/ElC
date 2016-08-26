/*
 * GridNode.cpp
 *
 *  Created on: Oct 12, 2015
 *      Author: krystian892
 */

#include <GridNode.h>
#include "logic/LogicalGrid.h"
#include <cstdlib>
GridNode::GridNode(PI size, PD spacing) :
		size(size), spacing(spacing), tileNodes(size.Y() * size.X(), nullptr) {
	//setPosition(position.X(), position.Y());

}

void GridNode::createTileNodes() {
	for (int i = 0; i < size.Y(); ++i) {
		for (int j = 0; j < size.X(); ++j) {

			tileNodes[i * size.X() + j] = TileNode::create(
					singularGrid->get(j, i), angleOffsetSprite);
			addChild(tileNodes[i * size.X() + j]);
		}
	}
}
void GridNode::createTileNodesEx() {
	for (int i = 0; i < size.Y(); ++i) {
		for (int j = 0; j < size.X(); ++j) {

			tileNodes[i * size.X() + j] = TileNode::create(this,
					singularGrid->get(j, i), angleOffsetSprite);
			addChild(tileNodes[i * size.X() + j]);
		}
	}
}

void GridNode::drawConnections(int i, int j, DrawNode *d) {
	get(i, j)->drawConnections(d);
}
GridNode* GridNode::createSqrGridOld(double size1, double angleOffset) {

	double op = (1.0 + sqrt(2.0)) * size1;

	shared_ptr<SinGrid> singularGrid { new logic::SingularGrid(4, { 6, 5 }, {
			op, op }, { size1 / sqrt(2.0), 0 }, { 0, 0 }) };
	GridNode * gn = new GridNode(singularGrid->size, singularGrid->spacing);
	gn->singularGrid = singularGrid;
	gn->angleOffsetSprite = angleOffset;
	gn->createTileNodes();
	return gn;
}

GridNode* GridNode::createSqrGrid(PD position, double size1, PD spacing,
		PI howMany, double angleOffset) {
	PD first = { size1 / 2, size1 / 2 };
	first=first.rotateZ(-angleOffset * M_PI / 180);
	shared_ptr<SinGrid> singularGrid { new logic::SingularGrid(4, howMany,
			spacing, first, position) };
	GridNode * gn = new GridNode(singularGrid->size, singularGrid->spacing);
	gn->singularGrid = singularGrid;
	gn->angleOffsetSprite = angleOffset;
	gn->createTileNodes();
	return gn;
}

GridNode::~GridNode() {
	// TODO Auto-generated destructor stub
}

TileNode* GridNode::get(int j, int i) {
	return tileNodes[i * size.X() + j];
}

GridNode* GridNode::createTwGrid(PD position, double size1, PD spacing,
		PI howMany) {
	//double op = (1.0 + sqrt(2.0))*size1;

	shared_ptr<SinGrid> singularGrid { new logic::SingularGrid(12, howMany,
			spacing, { size1, size1 * tan(M_PI / 12) }, position) };
	GridNode * gn = new GridNode(singularGrid->size, singularGrid->spacing);
	gn->singularGrid = singularGrid;
	gn->createTileNodes();
	return gn;
}

GridNode* GridNode::createTriGrid(PD position, double side, PD spacing,
		PI howMany, int direction) {
	PD first { side / 2, side * sqrt(3) / 6 };
	double angleOffset = 30;
	if (direction == 0) {
		first = {0, side * sqrt(3)/3};
		angleOffset =-30;
	}
	if (direction == 2) {
		first = {sqrt(3)/6* side,side/2};
		angleOffset=0;
	}
	if (direction == 3) {
		first = {sqrt(3)/3* side,0};
		angleOffset = 60;
	}
	shared_ptr<SinGrid> singularGrid { new logic::SingularGrid(3, howMany,
			spacing, first, position) };
	GridNode * gn = new GridNode(singularGrid->size, singularGrid->spacing);
	gn->singularGrid = singularGrid;
	gn->angleOffsetSprite = angleOffset;
	gn->createTileNodes();
	return gn;

}

pair<double, PI> GridNode::parseCoordinate(PD coord) {
	PD rel_coord = coord - get(0, 0)->lt->position;
	int x = int(round(rel_coord.X() / spacing.X()) + 1e-6), y = int(
			round(rel_coord.Y() / spacing.Y()) + 1e-6);
	if (x < 0)
		x = 0;
	if (x >= size.X())
		x = size.X() - 1;
	if (y < 0)
		y = 0;
	if (y >= size.Y())
		y = size.Y() - 1;
	PD pos { x * spacing.X(), y * spacing.Y() };
	double dist = rel_coord.distance(pos) / get(0, 0)->lt->InsR;
	return {dist, {x,y}};

}

GridNode* GridNode::createHexGrid(PD position, double size1, PD spacing,
		PI howMany) {
	double sq32 = sqrt(3) / 2 * size1;
	shared_ptr<SinGrid> singularGrid { new logic::SingularGrid(6, howMany,
			spacing, { sq32, size1 / 2 }, position) };
	GridNode * gn = new GridNode(singularGrid->size, singularGrid->spacing);
	gn->singularGrid = singularGrid;
	gn->createTileNodes();
	return gn;
}

GridNode* GridNode::createOctGrid(PD position, double size1, PD spacing,
		PI howMany) {

	double op = (1.0 + sqrt(2.0)) * size1;
	shared_ptr<SinGrid> singularGrid { new logic::SingularGrid(8, howMany,
			spacing,{ op / 2, size1 * 0.5 }, position) };
	GridNode * gn = new GridNode(singularGrid->size, singularGrid->spacing);
		gn->singularGrid = singularGrid;
		gn->createTileNodes();
		return gn;

}
GridNode* GridNode::createOctGridOld(double size1) {

	double op = (1.0 + sqrt(2.0)) * size1;
	shared_ptr<SinGrid> singularGrid { new logic::SingularGrid(8, { 6, 5 }, {
			op, op }, { op / 2, size1 * 0.5 }, { op / 2, op / 2 }) };
	GridNode * gn = new GridNode(singularGrid->size, singularGrid->spacing);
	gn->singularGrid = singularGrid;
	gn->createTileNodes();
	return gn;
}
MenuItem * ButtonFactory::createButton(std::function<void (Ref*)> func,std::string labelText, Vec2 pos, double fontsize){
//       auto sprite2 = ui::Scale9Sprite::create("button9small.png");
//       auto sprite3 = ui::Scale9Sprite::create("button9small2.png");
//
       auto label1=Label::createWithTTF(labelText.c_str(), "fonts/Marker Felt.ttf", fontsize);
    //  auto label2=Label::createWithTTF(labelText.c_str(), "fonts/Marker Felt.ttf", 24);


      int col = rand() % getMySpriteLoader().colors.size();
      label1->setTextColor(Color4B::WHITE );
      label1->enableOutline(Color4B(getMySpriteLoader().colors[col]),5);
     // label1->enableGlow(Color4B::WHITE );
      // label1->enableShadow(Color4B::BLUE, Size(10,10),5);
      label1->setAlignment(TextHAlignment::CENTER);
     // std::function<void (int)> g=std::bind(ButtonFactory::f,0);
     /* sprite2->addChild(label1);
      sprite3->addChild(label2);
      label1->setPosition(Vec2(label1->getContentSize().width/2 + 10,label1->getContentSize().height/2 +10));
      label2->setPosition(Vec2(label1->getContentSize().width/2 + 10,label1->getContentSize().height/2 +10));
      sprite2->setContentSize(Size(label1->getContentSize().width + 20,label1->getContentSize().height +20));
      sprite3->setContentSize(Size(label1->getContentSize().width + 20,label1->getContentSize().height +20));
    */  auto buttonsprite //= MenuItemSprite::create(sprite2,sprite3,func);
	    =MenuItemLabel::create(label1,func);
      buttonsprite->setPosition(pos);
      return buttonsprite;
}
;

void myUtils::scheduleOnce(std::function<void(float)> f, void * ptr,float delay,string key) {
	auto sh = Director::getInstance()->getScheduler();
	sh->schedule(f,ptr, 1.0f, 0, delay, false,key);
}
