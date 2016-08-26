/*
 * LogicalGrid.cpp
 *
 *  Created on: Oct 12, 2015
 *      Author: krystian892
 */

#include <logic/LogicalGrid.h>
namespace logic{
LogicalGrid::LogicalGrid() {
	// TODO Auto-generated constructor stub

}

LogicalGrid::~LogicalGrid() {
	// TODO Auto-generated destructor stub
	for(int i =0;i< grids.size();++i)
		delete grids[i];
}



void LogicalGrid::createOctSqGrid() {
	SingularGrid* ptSq {new SingularGrid(4,{3,3},{3.0,3.0},{1.0,0.0}, {0.0,0.0})};
	SingularGrid* ptOct{new SingularGrid(8, {3,3},{3.0,3.0},{1.5,0.5},{1.5,1.5})};
	grids.push_back(ptSq);
	grids.push_back(ptOct);

}

}

logic::GridConnectionResolver::GridConnectionResolver(
		vector<shared_ptr<SingularGrid> > &_grids) :grids(_grids) {
		vector<Point<int>> vec { {0,0},{1,0},{1,1},{0,1},{0,2},{2,0},{2,1},{1,2},{2,2}};
		for(shared_ptr<SingularGrid>  grid: _grids){
			for(auto v: vec)
			tiles.push_back(grid->get(v.X(),v.Y()));
		}
		for(int i =0; i < tiles.size();++i){
			for(int j =i+1; j < tiles.size();++j){

				int k1=tiles[i]->testNeighbourhood(*tiles[j],1),
				k2=tiles[j]->testNeighbourhood(*tiles[i],1);
				if(k1 != -1 && k2 != -1){
					//cout<<"Resolver"<< i <<" "<<j<<" "<<k1 <<" "<<k2 <<"\n";
					tiles[i]->connections[k1] = tiles[j];
					tiles[j]->connections[k2] = tiles[i];
					tiles[i]->connections_num[k1]=k2;
					tiles[j]->connections_num[k2]=k1;
				}
			}
		}


}

void logic::GridConnectionResolver::propagateConnections() {
	for(auto grid : grids) grid->propagateConnections();
}
