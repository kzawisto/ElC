/*
 * Challenges.cpp
 *
 *  Created on: Oct 23, 2015
 *      Author: krystian892
 */

#include <logic/Challenges.h>
#include <logic/Utils.h>
#include<iostream>
using namespace myUtils;
void Challenge::parseVector(vector<string> ss) {
	pk =ss[0];
	args = ss[1];
	int i = pk.find("_");
	grid = pk.substr(0,i);
	int j = pk.find("_",i+1);
	type = pk.substr(i+1,j-i-1);
	level = myUtils::Utils::stoi<int>(pk.substr(j+1));
}

vector<string> Challenge::serializeToVector() {
	vector<string> ss{pk,args};
	return ss;
}

ChallengesContainer::ChallengesContainer(string _path) {
	challenges=myUtils::Utils::loadColumnMap<string,Challenge>(_path,":");
}

void ChallengesContainer::serialize(string writepath) {
	Utils::serializeMap(writepath, ":",challenges);
}

bool ChallengesContainer::hasKey(string key) {
	return challenges.find(key)!= challenges.end();
}

map<string,Challenge> ChallengesContainer::findByGrid(string grid) {
	map<string,Challenge> partial { challenges.lower_bound(grid), challenges.upper_bound(grid + char(127))};
	return partial;

}

vector<Challenge> ChallengesContainer::findByType(string type) {
	vector<Challenge> vec;
	iterateMap<string,Challenge>(challenges, [&](Challenge & c){
		if(c.type == type) vec.push_back(c);
	});
	return vec;
}

void ChallengesContainer::add(const Challenge& c) {
	challenges[c.pk]=c;
}

vector<Challenge> ChallengesContainer::findByLevel(int level) {
	vector<Challenge> vec;
	iterateMap<string,Challenge>(challenges, [&](Challenge & c){
		if(c.level == level) vec.push_back(c);
	});
	return vec;
}

void ChallengesContainer::loadFile(string _path) {
	challenges=myUtils::Utils::loadColumnMap<string,Challenge>(_path,":");
}

ChallengeLogic* ChallengeLogic::get(Challenge& c) {
	if(c.type=="PT") return new PointsChallengeLogic(c);
	if(c.type == "LN") return new LengthChallengeLogic(c);
	if(c.type == "MV") return new MovesChallengeLogic(c);
}

ChallengeLogic::ChallengeLogic(Challenge& _c) : c(_c) {

}

ChallengeLogic::~ChallengeLogic() {
}

bool LengthChallengeLogic::parseResult(double points, int moves, int length) {
	int len = Utils::stoi<int> (c.args);
	return length >= len;
}

LengthChallengeLogic::~LengthChallengeLogic() {

}

bool PointsChallengeLogic::parseResult(double points, int moves, int length) {
	double pt = Utils::stoi<double> (c.args);
		return points >= pt;
}

PointsChallengeLogic::~PointsChallengeLogic() {
}

bool MovesChallengeLogic::parseResult(double points, int moves, int length) {
	auto v =Utils::slice(c.args, ",");
	int mvs = Utils::stoi<int> (v[0]);
	int len = Utils::stoi<int> (v[1]);
	return moves <= mvs && len <= length;
}

MovesChallengeLogic::~MovesChallengeLogic() {
}

string ChallengeLogic::getMessage() {
	return "";
}

string LengthChallengeLogic::getMessage() {
	string s = "Construct ";
	s+=Utils::itos<double>(Utils::stoi<double>(c.args));
	s+=" segments long path.";
	return s;
}

string PointsChallengeLogic::getMessage() {
	string s = "Score ";
		s+=Utils::itos<double>(Utils::stoi<double>(c.args));
		s+=" points.";
	return s;
}

string MovesChallengeLogic::getMessage() {
	auto v =Utils::slice(c.args, ",");
	int mvs = Utils::stoi<int> (v[0]);
	int len = Utils::stoi<int> (v[1]);
	string s = "Construct ";
		s+=Utils::itos<int>(len);
		s+=" segments long path in no more than ";
		s+=Utils::itos<int>(mvs)+ " moves.";
	return s;
}

vector<string> ChallengesContainer::getChallengeTypes(string grid) {
	vector<string> vec;
	auto it =challenges.lower_bound(grid);
	auto it1 =challenges.upper_bound(grid+char(127));
	while(it != it1){
		vec.push_back(grid + "_" + it->second.type);
		it = challenges.upper_bound(grid + "_" + it->second.type+char(127));
	}
	return vec;
}
