/*
 * Colors.h
 *
 *  Created on: Oct 25, 2015
 *      Author: krystian892
 */

#ifndef CLASSES_COLORS_H_
#define CLASSES_COLORS_H_

#include <map>
#include <string>
#include <vector>

#include"cocos2d.h"
using std::map;
using std::string;
using std::vector;
USING_NS_CC;
class ColorAggregate{
public:
	string pk;
	int r,g,b;
	operator Color3B(){
		return Color3B(r,g,b);
	}
	operator Color4B(){
			return Color4B(r,g,b,255);
	}
	operator Color4F(){
				return Color4F(r/255.f,g/255.f,b /255.f,1.0f);
	}
	void parseVector(vector<string> ss);
	vector<string> serializeToVector();

};
class ColorLoader{
	map<string,ColorAggregate> colors;

public:
	static ColorLoader & getInstance(){
		static ColorLoader instance;
		return instance;
	}
	ColorLoader();
	vector<Color3B> getTileColors();

	ColorAggregate &  getColor(string s);
};

#endif /* CLASSES_COLORS_H_ */
