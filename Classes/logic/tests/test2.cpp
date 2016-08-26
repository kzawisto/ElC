#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE test2
#include <boost/test/unit_test.hpp>
#include "logic/Point.h"
#include "logic/LogicalTile.h"
#include "logic/SingularGrid.h"
#include <cmath>
using namespace logic;
BOOST_AUTO_TEST_CASE(tile_contour) {
	LogicalTile diamond(4,1.0, { 0.0, 0.0 }, { 1.0, 0.0 });
	BOOST_CHECK_CLOSE(diamond.contour[0].X(), 1.0, 0.001);
	BOOST_CHECK_SMALL(diamond.contour[0].Y(), 0.001);
	BOOST_CHECK_CLOSE(diamond.contour[1].Y(), 1.0, 0.001);
	BOOST_CHECK_SMALL(diamond.contour[1].X(), 0.001);
	BOOST_CHECK_CLOSE(diamond.contour[2].X(), -1.0, 0.001);
	BOOST_CHECK_SMALL(diamond.contour[2].Y(), 0.001);
	BOOST_CHECK_CLOSE(diamond.contour[3].Y(), -1.0, 0.001);
	BOOST_CHECK_SMALL(diamond.contour[3].X(), 0.001);
}
BOOST_AUTO_TEST_CASE(rotate_this_one) {
	LogicalTile diamond(4,1.0, { 1.0, 0.0 }, { 1.0, 0.0 });
	BOOST_CHECK_CLOSE(diamond.contour[0].X(), 2.0, 0.001);
	BOOST_CHECK_SMALL(diamond.contour[0].Y(), 0.001);
	BOOST_CHECK_CLOSE(diamond.contour[1].Y(), 1.0, 0.001);
	BOOST_CHECK_CLOSE(diamond.contour[1].X(), 1, 0.001);
	BOOST_CHECK_SMALL(diamond.contour[2].X(), 0.001);
	BOOST_CHECK_SMALL(diamond.contour[2].Y(), 0.001);
	BOOST_CHECK_CLOSE(diamond.contour[3].Y(), -1.0, 0.001);
	BOOST_CHECK_CLOSE(diamond.contour[3].X(), 1, 0.001);
	diamond.setRotation(M_PI/2);
	BOOST_CHECK_CLOSE(diamond.contour[3].X(), 2.0, 0.001);
	BOOST_CHECK_SMALL(diamond.contour[3].Y(), 0.001);
	BOOST_CHECK_CLOSE(diamond.contour[0].Y(), 1.0, 0.001);
	BOOST_CHECK_CLOSE(diamond.contour[0].X(), 1, 0.001);
	BOOST_CHECK_SMALL(diamond.contour[1].X(), 0.001);
	BOOST_CHECK_SMALL(diamond.contour[1].Y(), 0.001);
	BOOST_CHECK_CLOSE(diamond.contour[2].Y(), -1.0, 0.001);
	BOOST_CHECK_CLOSE(diamond.contour[2].X(), 1, 0.001);
}
BOOST_AUTO_TEST_CASE(singular_grids){
	SingularGrid grid(4,{4,4},{3.0,2.0},{1.0,1.0},{0,0});
	auto l1 =grid.get(1,2);
	BOOST_CHECK_CLOSE(l1->position.X(), 3.0, 0.001);
	BOOST_CHECK_CLOSE(l1->position.Y(), 4.0, 0.001);

}
BOOST_AUTO_TEST_CASE(neighbourhood){
	double op = 1.0 + sqrt(2.0);
	SingularGrid grid(4,{4,4},{op,op},{1.0,0},{0,0});
	SingularGrid grid1(8, {4,4},{op,op},{op/2,0.5},{op/2,op/2});
	//cout<<"\n"<<grid.get(0,0)->position.X()<<" "<<grid.get(0,0)->position.Y()<<"\n";
	for(int a=0;a < grid.get(0,0)->n-1;++a){
		//cout<<a<<" "<<grid.get(0,0)->contour[a].X()<<" "<<grid.get(0,0)->contour[a].Y()<<" "
		//		<< grid.get(0,0)->position.cross( grid.get(0,0)->contour[a],grid.get(0,0)->contour[a+1])<<"\n";
		BOOST_CHECK( grid.get(0,0)->position.cross( grid.get(0,0)->contour[a],grid.get(0,0)->contour[a+1])>0);
	}
	cout<<grid.get(0,0)->testNeighbourhood( *(grid1.get(0,0)),0.01);
}
