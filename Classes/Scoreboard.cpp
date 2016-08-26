/*
 * Scoreboard.cpp
 *
 *  Created on: Oct 23, 2015
 *      Author: krystian892
 */

#include <Scoreboard.h>
namespace score{
Scoreboard::Scoreboard() {
	// TODO Auto-generated constructor stub

}

Scoreboard::~Scoreboard() {
	// TODO Auto-generated destructor stub
}


istream & operator>>(istream & input, GameScore & gameScore){
	input>>gameScore.name;
	input>>gameScore.length;
    input>>gameScore.points;

    input>>gameScore.moves;
    input>>gameScore.time;
    return input;
}
ostream & operator<<(ostream & output, const GameScore & gameScore){
	output<<gameScore.name<<" ";
		output<<gameScore.length<<" ";
	    output<<gameScore.points<<" ";
	    output<<gameScore.moves<<" ";
	    output<<gameScore.time<<" ";
    return output;
}


}

void score::ScoreContainer::add(const GameScore& gsc) {
	int pk =1;
	if(not mymap.empty()) pk += mymap.rbegin()->first;
	mymap[pk]= gsc;
	mymap[pk].pk =pk;
}


