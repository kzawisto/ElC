/*
 * Utils.cpp
 *
 *  Created on: Oct 13, 2015
 *      Author: krystian892
 */

#include <logic/Utils.h>
namespace myUtils{
Utils::Utils() {
	// TODO Auto-generated constructor stub

}

Utils::~Utils() {
	// TODO Auto-generated destructor stub
}


string Utils::merge(vector<string> tab, string deli) {
    string s =tab[0];
    for(int i =1;i< tab.size();++i){
      s.append(deli);
      s.append(tab[i]);
    }
    return s;
  }
template<typename T>
string Utils::stringifyVector(vector<T> vec,string delimiter)
{
    string out=itos<T>(vec[0]);
    for(int i =1; i< vec.size();++i){
      out+= delimiter;
      out+= itos<T>(vec[i]);
    }
    return out;
  }
vector<string>  Utils::slice(string text, string deli){
    vector<string> vec;
    int start =0,result;
    while((result = text.find(deli,start))!= string::npos){

	vec.push_back(text.substr(start,result-start));
	start = result+1;
    }
    vec.push_back(text.substr(start));
    return vec;
}
template<class T>
vector<T> Utils::sliceAny(string text, string deli){
  vector<T> vec;
  vector<string> vec1 = slice(text,deli);
  for(string s: vec1) vec.push_back(stoi<T>(s));
  return vec;
}



}
