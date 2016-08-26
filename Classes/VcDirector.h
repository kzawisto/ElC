/*
 * VcDirector.h
 *
 *  Created on: Oct 18, 2015
 *      Author: krystian892
 */
#ifndef VCEDIRECTOR_H
#define VCEDIRECTOR_H
#include <logic/Challenges.h>
#include"EventObserver.h"
#include "cocos2d.h"
#include<string>
#include <map>
#include <vector>
USING_NS_CC;
using namespace std;
class VcDirector : public Receiver{
public:
    Scene * scene;

    void sendEvent(MyEvent & e);
	virtual ~VcDirector();
    static VcDirector * get();
};

class SettingsContainer{
};
class AchievementsObserver{
	ChallengesContainer all_challenges, my_records;
public:
	AchievementsObserver();
	~AchievementsObserver();
	map<string,Challenge> retrieveChallengesForRange(string from, string to);
	vector<string> getChallengeTypes(string grid);
	int retrieveRecordLevel(string record);
	static AchievementsObserver & getInstance();
	Challenge get(string key);

	vector<string> sendResult(string grid, double points, int moves, int length);
};
#endif // VCEDIRECTOR_H
