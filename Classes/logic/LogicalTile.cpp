#include "logic/LogicalTile.h"

#include "SingularGrid.h"
#include <random>       // std::default_random_engine
#include <chrono>  
#include<algorithm>
#include<cmath>
#include "logic/Utils.h"
namespace logic{
using namespace std;

LogicalTile::LogicalTile(int _n, Point<double> _position, Point<double> first_vertex)
: internal(_n),n(_n), position(_position),  internal_angle(2*M_PI/_n)
{

	CircR = sqrt(pow(first_vertex.X(),2) + pow(first_vertex.Y(),2));
	InsR = CircR * cos(internal_angle/2);
	rotation_angle= 0;
  for(int  a =0;a < n;++a) internal[a]= a;

   unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
  shuffle (internal.begin(), internal.end(), std::default_random_engine(seed));
   contour.push_back(first_vertex+position);
   centered_contour.push_back(first_vertex);

  for(int a =1;a<n;++a) {
      first_vertex = first_vertex.rotateZ(internal_angle);
     contour.push_back(first_vertex+ position);
     centered_contour.push_back(first_vertex);
   }
  setRandomInternalWiring(2);
  setConnectionPoints();
}
LogicalTile::LogicalTile(const LogicalTile& other)
{

}
LogicalTile::~LogicalTile()
{

}
LogicalTile& LogicalTile::operator=(const LogicalTile& other)
{
  return *this;
}

int LogicalTile::testNeighbourhood(LogicalTile& nei,double epsilon) {
	//Point<double> d = position + nei.position;
	double d = position.distance(nei.position);
	//cout<<"CircR  "<<CircR<<" "<< nei.CircR<<"\n";
	if(abs(d - InsR - nei.InsR )> epsilon ) return -1;
	int a =0;
	bool broken =false;
	for(; a< n-1;++a)if( position.cross( contour[a], nei.position) >0
			&&  position.cross( nei.position, contour[a+1]) >0) {
		broken = true;
		break;
	}
	if(a == n-2 && broken == false) {
		if( position.cross( contour[a], nei.position) >0
			&&  position.cross( nei.position, contour[0]) >0) a= n-1;

		else a =-1;
	}
	return a;
//	return -1;
//	for(; b< nei.n-1;++b)	if( nei.position.cross( nei.contour[b], position) >0 &&
//			nei.position.cross(  position,nei.contour[b+1]) >0)break;
//	if(b == nei.n-1) {
//		if( nei.position.cross( nei.contour[b], position) >0 &&
//			nei.position.cross(  position,nei.contour[b+1]) >0 ) b= nei.n;
//
//	}
}


bool LogicalTile::operator==(const LogicalTile& other) const
{
  return true;
}
LogicalTile::LogicalTile() {

}

void LogicalTile::setRotation(double rot) {
	double new_rot = rot-rotation_angle;
	for(auto it = contour.begin();it != contour.end();++it ){
		*it = (*it).rotateZAround(new_rot, position);
	}
	rotation_angle =rot;
}
void LogicalTile::setRandomInternalWiring(int wires_per_side) {
	this->wires_per_side = wires_per_side;
	internalWiring.resize(n* wires_per_side);
	vector<int> vec;
	vec.reserve(n* wires_per_side);
	for(int a =0; a< n* wires_per_side;++a) {
		vec.push_back(a);
	}
	 unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
	 shuffle (vec.begin(), vec.end(), std::default_random_engine(seed));
	 for(unsigned a =0;a< vec.size();a+=2){
		 internalWiring[vec[a]] = vec[a+1];
		 internalWiring[vec[a+1]] = vec[a];
	 }

}
void LogicalTile::setConnectionPoints() {
	myUtils::cyclic_iterate<PD>(centered_contour, [&] (PD & a, PD & b){
		for(int i =1;i<wires_per_side+1;++i){
			PD p=(a+ ((b-a)* ((double) i /(double)(wires_per_side+1))));
			connectionPoints.push_back( p);
		}
	});
}


//template class LogicalTile<4>;

PD LogicalTile::connectionPointOnThis(int side, int wire) {
	return (connectionPoints[side * wires_per_side + wire]*0.85)+ position;
}

PD LogicalTile::connectionPointOnNeighbour(int side, int wire) {
	//cout<< connections_num[side] + (wires_per_side-1 -wire)<<" "<<
		//	connections[side]->connectionPoints.size()<<"\n";
	auto it = connections.find(side);
	if(it == connections.end()) return {0.0, 0.0};
	if( connections_num.find(side)== connections_num.end()) return {0.0, 0.0};
	return ((connections[side]->connectionPoints[connections_num[side]* wires_per_side + (wires_per_side-1 -wire)])*0.85)
			+connections[side]->position;
}

shared_ptr<LogicalTile> LogicalTile::getConnectionNeighbour(int side) {
	return connections[side];
}
void ConsoleTileObserver::lightenPath(int i) {
	cout<<"\n Lightening path"<<i;
}

void ConsoleTileObserver::dimPath(int i) {
	cout<<"\n Dimming path"<<i;
}
PipePath::PipePath() {

}

void PipePath::startPathFrom(int entry, shared_ptr<LogicalTile> tile) {

	vec.push_back({entry, tile});
	shared_ptr<LogicalTile> current_tile=tile, tmp_tile;
	pair<int,int> wiring = parseWiringNumber(entry);
	while(true){
		current_tile->tileObserver->lightenPath(entry);
		int next = current_tile->internalWiring[entry];
		wiring = parseWiringNumber(next);
		if(current_tile->connections.find(wiring.first) == current_tile->connections.end()) break;
		entry = getWiringNumber({current_tile->connections_num[wiring.first], wps - 1 -wiring.second});
		vec.push_back( {entry,current_tile->connections[wiring.first]}) ;
		current_tile = vec.back().second;
	}
}

void PipePath::deletePath(int begin) {
	for(int i =begin; i <vec.size();++i){
		vec[i].second->tileObserver->dimPath(vec[i].first);
	}
	vec.erase(vec.begin()+begin, vec.end());
}

void LogicalTile::rotate(int step) {
	vector<int> vec=internalWiring;
	vector<PD> vecPoints =connectionPoints;
	for(int i =0; i < n* wires_per_side;++i){
		if(i > vec[i] )continue;
		int i1 = constrainNumber(i+step*wires_per_side), i2 = constrainNumber(vec[i]+step*wires_per_side);
		internalWiring[i1]=i2;
		internalWiring[i2]=i1;
//		connectionPoints[i1] = vecPoints[i];
//		connectionPoints[i2] = vecPoints[vec[i]];
	}
}
int PipePath::findLogicalTile(shared_ptr<LogicalTile> pt) {
	for(int i= 0;i< vec.size();++i){
		if(pt ==vec[i].second) return i;

	}
	return vec.size();
}
}


