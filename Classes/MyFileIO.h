/*
 * MyFileIO.h
 *
 *  Created on: Oct 23, 2015
 *      Author: krystian892
 */


#ifndef CLASSES_MYFILEIO_H_
#define CLASSES_MYFILEIO_H_
#include<map>
#include <fstream>
#include <iostream>
using namespace std;
class MyFileIO {
public:
	MyFileIO();
	virtual ~MyFileIO();
};
template <typename K,typename T>
class MapIO{
public:
	fstream file;
	 map<K,T>  loadFile(string filename);
	void parseMap();
	void saveFile(map<K, T> mymap, string filepath);
};
struct Person{
  string pk;
  int age;
  int height;
  bool operator==(const Person & other){
    return pk == other.pk && age== other.age && height == other.height;
  }
};
istream & operator>>(istream & input, Person & person);
ostream & operator<<(ostream & input, const Person & person);
template<typename K, typename T>
inline map<K,T> MapIO<K,T>::loadFile(string filename) {
	file.open(filename.c_str(), fstream::in | fstream::out | fstream::app);
	map<K, T> mymap;
	K key;
	for(;;){
	  file>>key;
	  if(file.fail() or file.bad() or file.eof()) break;
	  mymap[key].pk = key;
	  file>>mymap[key];
	}
	if(not file.eof())cout<<"ERROR";
	file.close();
	return mymap;
}
template<typename K,typename T>
inline void MapIO<K,T>::parseMap() {

}
template<typename K,typename T>
inline void MapIO<K,T>::saveFile(map<K, T> mymap, string filepath) {
      file.open(filepath.c_str(), fstream::trunc | fstream::out);
     for(auto it = mymap.begin();it != mymap.end();++it){
       file<<it->first<<" "<< it->second<<"\n";

     }
     file.close();
}
class MyStrings{
	map<string, string> ss;
	MyStrings(){

	}
};


#endif

