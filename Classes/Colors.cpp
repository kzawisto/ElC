/*
 * Colors.cpp
 *
 *  Created on: Oct 25, 2015
 *      Author: krystian892
 */

#include <Colors.h>

#include "logic/Utils.h"

using namespace myUtils;
ColorLoader::ColorLoader() {
	string path = FileUtils::sharedFileUtils()->fullPathForFilename("colors");
	colors=Utils::loadColumnMap<string,ColorAggregate>(path,":");

}

void ColorAggregate::parseVector(vector<string> ss) {
	pk = ss[0];
	r = myUtils::Utils::stoi<int>(ss[1]);
	g = myUtils::Utils::stoi<int>(ss[2]);
	b = myUtils::Utils::stoi<int>(ss[3]);
}

vector<string> ColorAggregate::serializeToVector() {

	vector<string> ss {pk,Utils::itos<int>(r),Utils::itos<int>(g),Utils::itos<int>(b)};
	return ss;
}

vector<Color3B> ColorLoader::getTileColors() {
	map<string, ColorAggregate> mymap(colors.lower_bound("_tile"), colors.upper_bound("_tilf"));
	vector<Color3B> colors1;
	for(auto & m:mymap){
		colors1.push_back(m.second);
	}
	return colors1;
}

ColorAggregate& ColorLoader::getColor(string s) {
	return colors[s];
}
