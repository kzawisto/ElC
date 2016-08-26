#ifndef POINT_H
#define POINT_H
#include <type_traits>
#include <valarray>
#include <iostream>
#include<algorithm>
#include<string>
#include<initializer_list>
//#define VERBOSE true

using namespace std;
namespace logic{
  template <typename T, unsigned int N = 2>
class Point
{
public:
  valarray <T> arr;
  Point (): arr(N){};
  string getTypename (){ return string("point");}
  Point (const Point <T,N> & old){arr=old.arr;}
  Point (Point <T,N> && old) noexcept  { arr = std::move(old.arr);};
 // Point & operator = (Point <T,N> && old);
  
  Point & operator = (const Point <T,N> & old){
	        arr=old.arr;
	        return *this;
	      };
  Point operator + (const Point <T,N> & second) const{
	        Point<T,N> ret = *this;
	        //std::transform(ret.arr.begin(), ret.arr.end(), ret.arr.begin(), second.arr.begin(),std::plus<T>());
	        for(unsigned i =0;i<N;++i) ret.arr[i] += second.arr[i];
	        return ret;
	      }
  Point & operator+=(const Point <T,N> & second){
      arr=arr+second.arr;
      return *this;
}
  Point & operator-=(const Point <T,N> & second){
	        arr=arr-second.arr;
	        return *this;
	      }
  Point & operator*=(const T & arg){
	        arr*=arg;
	        return *this;
	      }
  Point  operator*(const T & arg){
	        Point<T,N> ret(*this);
	  		ret*=arg;
	        return ret;
	      }
  double cross(Point <T,N> & a1, Point <T,N> & a2){
	  	Point<T,N> i1 = a1 - (*this);
	  	Point<T,N> i2 = a2 - (*this);
	  	return i1.X() * i2.Y() - i1.Y() * i2.X();
	  }
   Point<T,N> rotateZ(T  angle){
	     T cos1 =cos(angle), sin1 = sin(angle);
	     return { cos1* this->X() - sin1* this->Y(), sin1 * this->X() + cos1*this->Y()};
	   }
  Point<T,N> rotateZAround(T  angle, const Point<T,N> & center){

	      return ( *this-center).rotateZ(angle)  + center;
	  };
  T distance(Point <T,N> & second){
	       // auto arr2 = pow(arr - second.arr,2);
	       // return sqrt(arr2.sum());
	  	  	 T d = (arr[0]-second.arr[0])*(arr[0]-second.arr[0])+ (arr[1]-second.arr[1])*(arr[1]-second.arr[1]);
	  	  	  return sqrt(d);
	      }
  T operator *(Point <T,N> & second) { return (arr*second.arr).sum();  }
  
  Point (initializer_list <T> list): arr(list){};
  T & X () { return arr[0]; }
  T & Y (){ return arr[1]; };
  T & Z (){ return arr[2]; };
  Point operator-(const Point<T,N> & second) const {
	        Point<T,N> ret { (*this)};
	        //std::transform(ret.arr.begin(), ret.arr.end(), ret.arr.begin(), second.arr.begin(),std::minus<T>());
	          for(unsigned i =0;i<N;++i) ret.arr[i] -= second.arr[i];
	        return ret;
  }
};

//template <typename T,unsigned int N = 2>
//class PointD : public Point<T,N>{
//public:
//  PointD ();
//   PointD (const Point <T,N> & old);
//  PointD (Point <T,N> && old) noexcept;
//  PointD (initializer_list <T> list);
//  PointD<T,N> sqrt();
//
//};
}
typedef logic::Point<double> PD;
typedef logic::Point<int> PI;
#endif
