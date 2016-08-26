/*
 * Utils.h
 *
 *  Created on: Oct 13, 2015
 *      Author: krystian892
 */

#ifndef CLASSES_LOGIC_UTILS_H_
#define CLASSES_LOGIC_UTILS_H_
#include<vector>
#include<functional>
#include<sstream>
#include<string>
#include<map>
#include<fstream>
using namespace std;

namespace myUtils{
template<typename T> void cyclic_iterate(vector<T> vec,const function<void(T&,T&)> & func ){
	for(unsigned int  a= 0;a<vec.size()-1;++a) func(vec[a],vec[a+1]);
	if(vec.size()>1) func(vec[vec.size()-1],vec[0]);
}
template<typename T,typename K> void iterateMap(map<T,K> container,const function<void(K&)> & func){
	for(auto it=container.begin();it != container.end();++it)	func( it->second);
}
class Utils {
public:
	Utils();
	virtual ~Utils();


template<class T>
  static string itos(T t1,unsigned int i =4){
    stringstream ss;
    ss.precision(i);
    ss<< t1;
    return ss.str();
  }
  template<class T>
    static T stoi(string t1);
  template<class T>
  static vector<T> sliceAny(string text, string deli);

  static vector<string>  slice(string text, string deli);
  static string merge( vector<string> tab, string deli);
  template<class T>
  static string stringifyVector(vector<T> vec,string delimiter);
  template<class K, class T>
  static map<K,T> loadColumnMap(string path, string separator);
  template<class K, class T>
  static void serializeMap(string path,string separator ,map<K,T> mymap);
};

template<class T>
T Utils::stoi(string t1){
stringstream ss;
ss<< t1;
T t2;
ss >> t2;
return t2;
}
}

template<class K, class T>
inline map<K, T> myUtils::Utils::loadColumnMap(string path, string separator) {
	fstream file;
	file.open(path.c_str(), fstream::in | fstream::out);
	string myLine;
	map<K,T> mymap;
	while(getline(file,myLine)){
		auto vec = slice(myLine, separator);
		T obj;
		obj.parseVector(vec);
		mymap[obj.pk]= obj;
	}
	file.close();
	return mymap;
}

template<class K, class T>
inline void myUtils::Utils::serializeMap(string path,string separator, map<K, T> mymap) {
	fstream file;
		file.open(path.c_str(), fstream::out);
		for(auto it = mymap.begin();it != mymap.end();++it){
			auto vec = it->second.serializeToVector();
			for(int i =0;i < vec.size()-1;++i)
				file<<vec[i]<<separator;
			file<<vec.back()<<"\n";
		}
		file.close();
}

#endif /* CLASSES_LOGIC_UTILS_H_ */
