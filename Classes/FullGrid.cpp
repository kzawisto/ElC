/*
 * FullGrid.cpp
 *
 *  Created on: Oct 15, 2015
 *      Author: krystian892
 */

#include "FullGrid.h"
#include "logic/LogicalGrid.h"
FullGrid::FullGrid() {
	// TODO Auto-generated constructor stub
	time =0;
	moves =0;
	observer = &dummyObserver;
	dnode= nullptr;
	start_grid=nullptr;

}

void FullGrid::setMetrics() {
	observer->setMoves(moves);
	observer->setLenght(main_path.vec.size());
	observer->setPoints((double)main_path.vec.size()*10 - moves);
	observer->sendChallengesNotification((double)main_path.vec.size()*10 - moves,moves,main_path.vec.size());
}
void FullGrid::onClick(const cocos2d::Vec2 & coord1) {
	if(clickLocked==true) return;
	pair<double, PI> p { 1e10, { -10, -10 } }, p1;

	PD coord { coord1.x, coord1.y };
	GridNode * chosen_grid;
	for (auto mygrid : grids) {
		p1 = mygrid->parseCoordinate(coord);
		if (p1.first < p.first) {
			p = p1;
			chosen_grid = mygrid;
		}
	}
	if (chosen_grid->singularGrid->check(p.second.X(), p.second.Y())
			&& p.first <= 1.0) {
		clickLocked= true;
		moves++;
		observer->setMoves(moves);
		int i = main_path.findLogicalTile(chosen_grid->get(p.second.X(), p.second.Y())->lt);
		main_path.deletePath(i);
		chosen_grid->get(p.second.X(), p.second.Y())->rotate(1);
		//main_path.startPathFrom(pathStart.first, pathStart.second->lt);
		//auto sh = Director::getInstance()->getScheduler();
		myUtils::scheduleOnce([&](float dt)
				{
			main_path.deletePath(0);
			main_path.startPathFrom(pathStart.first, pathStart.second->lt);

			setMetrics();
			clickLocked=false;

				},this,0.3f);
//		sh->schedule([&](float dt)
//		{
//			clickLocked=false;
//		    log("callback");
//		}, this, 1.0f, 0, 1.0f, false, "myCallbackKey");

	}
}


void FullGrid::addGridsToRoot() {
	for (auto g : grids) {
				addChild(g);
			}
}



void FullGrid::fillGrids(double size) {
}
void FullGrid::finishConstruction() {
		for (auto g : grids)
			vec.push_back(g->singularGrid);
		logic::GridConnectionResolver resolver(vec);
		resolver.propagateConnections();
		main_path.startPathFrom(pathStart.first, pathStart.second->lt);
}

FullGrid* FullGrid::finalize(FullGrid* grid) {
		grid->autorelease();
		grid->finishConstruction();
		return grid;
}

FullGrid::~FullGrid() {
	// TODO Auto-generated destructor stub
}

TwSqTriFullGrid::TwSqTriFullGrid() {
//	double size =50, sideSize = 2 * size * tan(M_PI / 12);
//	//auto grid = GridNode::createSqrGrid(size,45);
//	PD spacing = { 2  * size, 2 * size };
//	PI howMany = { 8, 6 };
//	auto grid = GridNode::createTwGrid( { 0, 0 }, size, spacing, howMany);
//	auto gridTri1 = GridNode::createTriGrid(
//			{ size, sideSize * (0.5 + sqrt(3) / 3) }, sideSize, spacing,
//			howMany - PI { 1, 0 });
//	auto gridTri2 = GridNode::createTriGrid(
//			{ size, -sideSize * (0.5 + sqrt(3) / 3) }, sideSize, spacing,
//			howMany - PI { 1, 0 }, 0);
//	auto gridTri3 = GridNode::createTriGrid( { -sideSize * (0.5 + sqrt(3) / 3),
//			size }, sideSize, spacing, howMany - PI { 0, 1 }, 3);
//	auto gridTri4 = GridNode::createTriGrid( { sideSize * (0.5 + sqrt(3) / 3),
//			size }, sideSize, spacing, howMany - PI { 0, 1 }, 2);
//	auto gridsqr = GridNode::createSqrGrid( { size, size }, sideSize, spacing,
//			howMany - PI { 1, 1 });
//	 //{grid->singularGrid, grid2->singularGrid};
//	grids= {grid,gridTri1,gridTri2,gridTri3,gridTri4,gridsqr}; //,grid2,,gridTri11,gridTri21};
//	pathStart= {10, grid->get(0,1)};

}

TwSqTriFullGrid* TwSqTriFullGrid::create(bool dummy) {
	TwSqTriFullGrid * tstg = new TwSqTriFullGrid();
	tstg->autorelease();
	tstg->fillGrids(50);
	tstg->addGridsToRoot();
	tstg->name="TwSqTri";
	if(!dummy)
	tstg->finishConstruction();
	return tstg;
}

HexFullGrid::HexFullGrid() {
//	double size = 50, sq32 = sqrt(3) / 2 * size;
//	PD spacing = { sq32 * 2, 3 * size };
//	PI howMany = { 8, 4 };
//	auto grid = GridNode::createHexGrid( { 0, 0 }, size, spacing, howMany);
//	auto grid2 = GridNode::createHexGrid(spacing * 0.5, size, spacing, howMany);
//	grids = {grid,grid2};
//	pathStart= {5, grid->get(0,1)};
}

HexFullGrid* HexFullGrid::create(bool dummy) {
	auto * hfg = new HexFullGrid();
	hfg->autorelease();
	hfg->fillGrids(50);
	hfg->addGridsToRoot();
	hfg->name="Hex";
	if(!dummy)
		hfg->finishConstruction();
	return hfg;
}

SqFullGrid::SqFullGrid() {
//	double size = 50;
//	PD spacing = { size, size };
//	PI howMany = { 14, 10 };
//	auto grid = GridNode::createSqrGrid( { 0, 0 }, size, spacing, howMany);
//	grids = {grid};
//	pathStart= {3, grid->get(0,1)};

}

SqFullGrid* SqFullGrid::create(bool dummy) {
	auto * hfg = new SqFullGrid();
	hfg->fillGrids(50);
	hfg->addGridsToRoot();
	hfg->name="Sq";
	if(!dummy)
	hfg->finishConstruction();
	hfg->autorelease();
	return hfg;
}

OctSqFullGrid::OctSqFullGrid() {
//	double size1 = 50;
//	double op = (1.0 + sqrt(2.0)) * size1;
//	PI howMany ={ 6, 5 };
//	PD spacing = {op, op }, first ={ size1 / sqrt(2.0), 0 };
//	  auto grid = GridNode::createSqrGrid({0,0},size1,spacing,howMany,45);
//	  auto grid2 = GridNode::createOctGrid(spacing*0.5,size1,spacing,howMany);
//	grids={grid,grid2};
//	pathStart= {3, grid->get(0,1)};

}

OctSqFullGrid* OctSqFullGrid::create(bool dummy) {
	auto * hfg = new OctSqFullGrid();
		hfg->autorelease();
		hfg->fillGrids(50);
		hfg->addGridsToRoot();
		hfg->name="OctSq";
		if(!dummy)
			hfg->finishConstruction();
		return hfg;
}

TwTriFullGrid::TwTriFullGrid() {
//	double size = 45, sideSize = 2 * size * tan(M_PI/12);
//    //auto grid = GridNode::createSqrGrid(size,45);
//    	PD spacing ={2*size,size * 2* sqrt(3)};
//    	PI howMany = {8,4};
//    auto grid2 = GridNode::createTwGrid({0,0},size,spacing,howMany);
//    auto grid =GridNode::createTwGrid({size,size*sqrt(3)},size,spacing,howMany);
//    auto gridTri1 = GridNode::createTriGrid({size,sideSize*(0.5 + sqrt(3)/3)},sideSize,spacing,howMany);
//    auto gridTri2 = GridNode::createTriGrid({size,-sideSize*(0.5 + sqrt(3)/3)},sideSize,spacing,howMany,0);
//    auto gridTri11 = GridNode::createTriGrid({0,size*sqrt(3)+sideSize*(0.5 + sqrt(3)/3)},sideSize,spacing,howMany);
//    auto gridTri21 = GridNode::createTriGrid({0,size*sqrt(3)-sideSize*(0.5 + sqrt(3)/3)},sideSize,spacing,howMany,0);
//    grids= {grid,grid2,gridTri1,gridTri2,gridTri11,gridTri21};
//   	pathStart= {10, grid->get(0,1)};
}

TwTriFullGrid* TwTriFullGrid::create(bool dummy) {
	auto * hfg = new TwTriFullGrid();
			hfg->autorelease();
			hfg->fillGrids(50);
			hfg->addGridsToRoot();
			hfg->name="TwTri";
			if(!dummy)
				hfg->finishConstruction();
			return hfg;
}

MyGridFactory::MyGridFactory() {
	creators["Sq"] =SqFullGrid::create;
	creators["Hex"] =HexFullGrid::create;
	creators["OctSq"] =OctSqFullGrid::create;
	creators["TwTri"] =TwTriFullGrid::create;
	creators["TwSqTri"]=TwSqTriFullGrid::create;
}

FullGrid* MyGridFactory::generate(string s,double size, bool dummy) {

	FullGrid* grid=  creators[s](true);
	grid->removeAllChildren();
	grid->fillGrids(size);
	grid->addGridsToRoot();
	if(not dummy)
	grid->finishConstruction();
	return grid;
}


void TwSqTriFullGrid::fillGrids(double size) {
	double  sideSize = 2 * size * tan(M_PI / 12);
		//auto grid = GridNode::createSqrGrid(size,45);
		PD spacing = { 2  * size, 2 * size };
		PI howMany = { 8, 6 };
		auto grid = GridNode::createTwGrid( { 0, 0 }, size, spacing, howMany);
		auto gridTri1 = GridNode::createTriGrid(
				{ size, sideSize * (0.5 + sqrt(3) / 3) }, sideSize, spacing,
				howMany - PI { 1, 0 });
		auto gridTri2 = GridNode::createTriGrid(
				{ size, -sideSize * (0.5 + sqrt(3) / 3) }, sideSize, spacing,
				howMany - PI { 1, 0 }, 0);
		auto gridTri3 = GridNode::createTriGrid( { -sideSize * (0.5 + sqrt(3) / 3),
				size }, sideSize, spacing, howMany - PI { 0, 1 }, 3);
		auto gridTri4 = GridNode::createTriGrid( { sideSize * (0.5 + sqrt(3) / 3),
				size }, sideSize, spacing, howMany - PI { 0, 1 }, 2);
		auto gridsqr = GridNode::createSqrGrid( { size, size }, sideSize, spacing,
				howMany - PI { 1, 1 });
		 //{grid->singularGrid, grid2->singularGrid};
		grids= {grid,gridTri1,gridTri2,gridTri3,gridTri4,gridsqr}; //,grid2,,gridTri11,gridTri21};
		pathStart= {10, grid->get(0,1)};
}

void TwTriFullGrid::fillGrids(double size) {
	double  sideSize = 2 * size * tan(M_PI/12);
    //auto grid = GridNode::createSqrGrid(size,45);
    	PD spacing ={2*size,size * 2* sqrt(3)};
    	PI howMany = {8,4};
    auto grid2 = GridNode::createTwGrid({0,0},size,spacing,howMany);
    auto grid =GridNode::createTwGrid({size,size*sqrt(3)},size,spacing,howMany);
    auto gridTri1 = GridNode::createTriGrid({size,sideSize*(0.5 + sqrt(3)/3)},sideSize,spacing,howMany);
    auto gridTri2 = GridNode::createTriGrid({size,-sideSize*(0.5 + sqrt(3)/3)},sideSize,spacing,howMany,0);
    auto gridTri11 = GridNode::createTriGrid({0,size*sqrt(3)+sideSize*(0.5 + sqrt(3)/3)},sideSize,spacing,howMany);
    auto gridTri21 = GridNode::createTriGrid({0,size*sqrt(3)-sideSize*(0.5 + sqrt(3)/3)},sideSize,spacing,howMany,0);
    grids= {grid,grid2,gridTri1,gridTri2,gridTri11,gridTri21};
   	pathStart= {10, grid->get(0,1)};
}

void HexFullGrid::fillGrids(double size) {
	double  sq32 = sqrt(3) / 2 * size;
	PD spacing = { sq32 * 2, 3 * size };
	PI howMany = { 8, 4 };
	auto grid = GridNode::createHexGrid( { 0, 0 }, size, spacing, howMany);
	auto grid2 = GridNode::createHexGrid(spacing * 0.5, size, spacing, howMany);
	grids = {grid,grid2};
	pathStart= {5, grid->get(0,1)};
}

void SqFullGrid::fillGrids(double size) {
	PD spacing = { size, size };
	PI howMany = { 14, 10 };
	auto grid = GridNode::createSqrGrid( { 0, 0 }, size, spacing, howMany);
	grids = {grid};
	pathStart= {3, grid->get(0,1)};
}

void OctSqFullGrid::fillGrids(double size1) {

	double op = (1.0 + sqrt(2.0)) * size1;
	PI howMany ={ 6, 5 };
	PD spacing = {op, op }, first ={ size1 / sqrt(2.0), 0 };
	  auto grid = GridNode::createSqrGrid({0,0},size1,spacing,howMany,45);
	  auto grid2 = GridNode::createOctGrid(spacing*0.5,size1,spacing,howMany);
	grids={grid,grid2};
	pathStart= {3, grid->get(0,1)};
}

