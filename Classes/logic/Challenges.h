/*
 * Challenges.h
 *
 *  Created on: Oct 23, 2015
 *      Author: krystian892
 */

#ifndef CLASSES_LOGIC_CHALLENGES_H_
#define CLASSES_LOGIC_CHALLENGES_H_

#include <map>
#include <string>
#include <vector>

using namespace std;

class Challenge{
public:
	string pk, grid, type;
	int level;
	string args;
	void parseVector(vector<string> ss);
	vector<string> serializeToVector();
};

class ChallengesContainer{
	string path;
public:
	map<string,Challenge> challenges;
	ChallengesContainer(string _path);
	void loadFile(string _path);
	void serialize(string writepath);
	bool hasKey(string key);
	void add(const Challenge & c);
	map<string,Challenge> findByGrid(string grid);
	vector<Challenge> findByType(string type);
	vector<Challenge> findByLevel(int level);
	vector<string> getChallengeTypes(string grid);

};
class ChallengeLogic{
protected:
	Challenge & c;
public:
	static ChallengeLogic * get(Challenge &c);
	ChallengeLogic(Challenge &c);
	virtual bool parseResult( double points, int moves,
			int length)=0;
	virtual string getMessage();
	virtual ~ChallengeLogic();
};

class LengthChallengeLogic : public ChallengeLogic{
public:
	using ChallengeLogic::ChallengeLogic;
	virtual bool parseResult( double points, int moves,
			int length);
	virtual string getMessage();
	virtual ~LengthChallengeLogic();
};
class PointsChallengeLogic: public ChallengeLogic{
public:
	using ChallengeLogic::ChallengeLogic;
	virtual bool parseResult( double points, int moves,int length);
	virtual string getMessage();
	virtual ~PointsChallengeLogic();
};
class MovesChallengeLogic: public ChallengeLogic{
public:
	using ChallengeLogic::ChallengeLogic;
	virtual bool parseResult( double points, int moves,
				int length);
	virtual string getMessage();
	virtual ~MovesChallengeLogic();
};
#endif /* CLASSES_LOGIC_CHALLENGES_H_ */
