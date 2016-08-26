#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE test1
#include <boost/test/unit_test.hpp>
#include "logic/Point.h"
#include <cmath>

BOOST_AUTO_TEST_CASE(case1)
{
    BOOST_CHECK(2+2 == 4); 
    logic::Point<int> p{1,2};
    BOOST_CHECK(p.X()==1);
    BOOST_CHECK(p.Y()==2);
    
}

BOOST_AUTO_TEST_CASE(case2)
{
  
    logic::Point<int> p{1,2};
    
    BOOST_CHECK(p.X()==1);
    BOOST_CHECK(p.Y()==2);
    logic::Point<int> p2= p;
    BOOST_CHECK_EQUAL(p2.Y(),2);
    BOOST_CHECK_EQUAL(p2.X(),1);
    p2 = p;
    
    BOOST_CHECK_EQUAL(p2.Y(),2);
    BOOST_CHECK_EQUAL(p2.X(),1);
}
BOOST_AUTO_TEST_CASE(reservation)
{
    logic::Point<int> p;
    BOOST_CHECK_EQUAL(p.arr.size(),2);
    logic::Point<long double,5> p1;
    BOOST_CHECK_EQUAL(p1.arr.size(),5);
}

BOOST_AUTO_TEST_CASE(adding_and_subtracting)
{	
   
    logic::Point<double> p1{1.0,2.0}, p2{0.5,0.5}, res = p1-p2, res1;
     res1= p1 + p2;
    BOOST_CHECK_EQUAL(p1.Y(),2.0);
    BOOST_CHECK_CLOSE(res.X(), 0.5,0.001);
    BOOST_CHECK_CLOSE(res.Y(), 1.5,0.001);
    BOOST_CHECK_CLOSE(res1.X(), 1.5,0.001);
    BOOST_CHECK_CLOSE(res1.Y(), 2.5,0.001);
    
    
}
BOOST_AUTO_TEST_CASE(distance_and_multiplication){
   logic::Point<double> p1{1.0,2.0}, p2{1.0,0.0},p3{3.0,3.0};
    BOOST_CHECK_CLOSE(p1.distance(p2),2.0,0.001);
    BOOST_CHECK_CLOSE(p3.distance(p2),sqrt(13.0),0.001);
    BOOST_CHECK_CLOSE(p1*p2,1.0,0.001);
    BOOST_CHECK_CLOSE(p1*p3,9.0,0.001);
   
}


BOOST_AUTO_TEST_CASE(rotations){
     logic::Point<double> p1{1.0,1.0}, p2{1.0,0.0},p3{3.0,3.0};
     auto p4=p2.rotateZ(M_PI/2);
     BOOST_CHECK_SMALL(p4.X(),0.001);
     BOOST_CHECK_CLOSE(p4.Y(),1.0,0.001);
     auto p5 = p1.rotateZAround(M_PI, p3);
     BOOST_CHECK_CLOSE(p5.X(),5.0,0.001);
     BOOST_CHECK_CLOSE(p5.Y(),5.0,0.001);
}


BOOST_AUTO_TEST_CASE(cross_product){
	logic::Point<double> i1{1,1}, i2{2,1},i3{1,2},i4{0,1};
	double d1 = i1.cross(i2,i3), d2 = i1.cross(i2,i4);
	BOOST_CHECK_CLOSE(d1, 1.0,0.001);
	BOOST_CHECK_SMALL(d2,0.001);
}


