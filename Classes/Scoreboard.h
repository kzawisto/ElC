/*
 * Scoreboard.h
 *
 *  Created on: Oct 23, 2015
 *      Author: krystian892
 */

#ifndef CLASSES_SCOREBOARD_H_
#define CLASSES_SCOREBOARD_H_
#include <string>
#include<map>
#include<iostream>
using namespace std;
namespace score{
class Scoreboard {
public:
	Scoreboard();
	virtual ~Scoreboard();
};
struct GameScore{
	int pk;
	string name;
	int length;
	double points;
	int moves;
	double time;
	//GameScore(int _pk, string _name, int _length, double _points, int _moves, double _time);
};

class ScoreContainer{
	map<int, GameScore> mymap;
	void add(const GameScore & gsc);
};

}
#endif /* CLASSES_SCOREBOARD_H_ */
