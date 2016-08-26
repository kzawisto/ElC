#include "logic/SingularGrid.h"
namespace logic{

SingularGrid::SingularGrid(int N,Point <int> _size, Point<double> _spacing, Point<double> first, Point<double> position)
: size(_size), spacing(_spacing)
{
	double posx = position.X();
	for(int a=0;a<size.Y();++a){
		position.X() = posx;
		for (int b = 0;  b < size.X(); ++ b){
			vec.push_back(shared_ptr<LogicalTile>{
				new LogicalTile(N,position,first)
			});
			vec[a*size.X()+b]->grid_position = {b,a};
			vec[a*size.X()+b]->grid=this;
			position.X() += spacing.X();
		}
		position.Y()+=spacing.Y();
	}
}
SingularGrid::SingularGrid(const SingularGrid& other)
{

}
shared_ptr<LogicalTile> SingularGrid::get(int x, int y) {
		return vec[y* size.X()+x];
}

bool SingularGrid::check(int x, int y) {
	 return x< size.X() && y< size.Y() && y >=0 && x >=0;
}

void SingularGrid::propagateConnections() {
	shared_ptr<LogicalTile> refTile =get(1,1);
	cout<<"AAA ";
	for(int i =0;i < size.Y();++i){
		for(int j =0; j < size.X();++j){

			if(j==1 && i == 1) continue;
			shared_ptr<LogicalTile> current =get(j,i);
			//auto it1 = refTile->connections_num.begin();
			for(auto it = refTile->connections.begin(); it != refTile->connections.end();++it){
				auto grid = it->second->grid;
				auto gridps = it->second->grid_position;
				if(grid->check( gridps.X() - 1 +j,gridps.Y() - 1 +i)){
					auto other = grid->get( gridps.X() - 1 +j,gridps.Y() - 1 +i);
					if(other == refTile) continue;
					current->connections[it->first] = other;
					current->connections_num[it->first] = refTile->connections_num[it->first];
					other->connections[  refTile->connections_num[it->first]] = current;
					other->connections_num[  refTile->connections_num[it->first]] = it->first;
				}
			}
		}
	}
}

}


