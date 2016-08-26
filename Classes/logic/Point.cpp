#include "logic/Point.h"
#include<algorithm>
#include<valarray>
#include <ctype.h>
#include <functional>
#include <cmath> 
using namespace std;
namespace logic {
//template< class T, unsigned int N > Point<T,N>::Point(initializer_list< T >  list): arr(list)
//{
//
//}
//
//template< class T, unsigned int N >Point<T,N>::Point() : arr(N)
//{
//
//}
//template< class T, unsigned int N >PointD<T,N>::PointD(){}
//
//template< class T, unsigned int N >PointD<T,N>::PointD(const Point <T,N> & old) : Point<T,N>(old){}
//
//template< class T, unsigned int N >PointD<T,N>::PointD(initializer_list< T >  list)
//: Point<T,N>(list){}
//
//template< class T, unsigned int N >PointD<T,N>::PointD(Point <T,N> && old)
//noexcept : Point<T,N>(old){}
//
//template <typename T, unsigned int N>
//string Point <T, N>::getTypename ()
//                        {
////       return to_string("Point<")+to_string(typeid(T).name())+
////       to_string(" ,")+to_string(N)+ to_string(">");
//			  return string("point");
//    }
//
//
//
//template <typename T, unsigned int N>
//Point<T, N> Point <T, N>::operator- (const Point<T,N> & second) const
//                                        {
//      Point<T,N> ret { (*this)};
//      //std::transform(ret.arr.begin(), ret.arr.end(), ret.arr.begin(), second.arr.begin(),std::minus<T>());
//        for(unsigned i =0;i<N;++i) ret.arr[i] -= second.arr[i];
//      return ret;
//    }
//template <typename T, unsigned int N>
//Point <T, N>::Point (const Point <T,N> & old){
//       #ifdef VERBOSE
//        cout<<getTypename()<<" copy constructor\n";
//      #endif
//      arr=old.arr;
//     // for(T & a:arr ) cout<< " "<<a;
//    }
//
//
//template <typename T, unsigned int N>
//Point <T, N>::Point (Point <T,N> && old) noexcept{
//
//       arr = std::move(old.arr);
//    }
//template <typename T, unsigned int N>
//double Point <T, N>::cross(Point <T,N> &a1, Point <T,N> & a2){
//	Point<T,N> i1 = a1 - (*this);
//	Point<T,N> i2 = a2 - (*this);
//	return i1.X() * i2.Y() - i1.Y() * i2.X();
//}
//
//template <typename T, unsigned int N>
//Point<T, N> & Point <T, N>::operator= (const Point <T,N> & old){
//
//
//      arr=old.arr;
//      return *this;
//    }
//
//template <typename T, unsigned int N>
//Point<T, N> & Point <T, N>::operator+= (const Point <T,N> & second){
//      arr=arr+second.arr;
//      return *this;
//    }
//template <typename T, unsigned int N>
//Point<T, N> & Point <T, N>::operator*= (const T & second){
//      arr*=second;
//      return *this;
//    }
//template <typename T, unsigned int N>
//Point<T, N>  Point <T, N>::operator* (const T & second){
//      Point<T,N> ret(*this);
//		ret*=second;
//      return ret;
//    }
//template <typename T, unsigned int N>
//Point<T, N> & Point <T, N>::operator-= (const Point <T,N> & second){
//      arr=arr-second.arr;
//      return *this;
//    }
//template <typename T, unsigned int N>
//Point<T, N> Point <T, N>::operator+ (const Point<T,N> & second) const {
//      Point<T,N> ret = *this;
//      //std::transform(ret.arr.begin(), ret.arr.end(), ret.arr.begin(), second.arr.begin(),std::plus<T>());
//      for(unsigned i =0;i<N;++i) ret.arr[i] += second.arr[i];
//      return ret;
//    }
//
//template <typename T, unsigned int N>
//T Point <T, N>::operator* (Point<T,N> & second)  { return (arr*second.arr).sum();  }
//template <typename T, unsigned int N>
//T Point <T, N>::distance (Point<T,N> & second)  {
//      auto arr2 = pow(arr - second.arr,2);
//      return sqrt(arr2.sum());
//    }
//
//
//template <typename T, unsigned int N>
//T & Point <T, N>::X ()
//          { return arr[0]; }
//template <typename T, unsigned int N>
//T & Point <T, N>::Y ()
//          {return arr[1];}
//template <typename T, unsigned int N>
//T & Point <T, N>::Z ()
//          {   return arr[2];}
//template <typename T, unsigned int N>
//  PointD<T,N> PointD<T,N>::sqrt(){
//    PointD<T,N> p;
//    p.arr = std::sqrt(this->arr);
//    return p;
//}
//template <typename T, unsigned int N>
//Point< T, N > Point<T,N>::rotateZ(T angle){
//  T cos1 =cos(angle), sin1 = sin(angle);
//  return { cos1* this->X() - sin1* this->Y(), sin1 * this->X() + cos1*this->Y()};
//
//}
//template <typename T, unsigned int N>
//Point< T, N > Point<T,N>::rotateZAround(T angle, const Point<T,N> & center){
//
//    return ( *this-center).rotateZ(angle)  + center;
//}
//
//
//template class Point<int>;
//
//template class Point<long double,5>;
//
//template class Point<double>;
//
//template class PointD<double>;
}
