/*
 * VcDirector.cpp
 *
 *  Created on: Oct 18, 2015
 *      Author: krystian892
 */

#include <base/CCDirector.h>
#include <CCFileUtils.h>
#include <GameLayer.h>
#include <logic/Utils.h>
#include <LevelSelect.h>
#include <MainMenu.h>
#include <ScoresLayer.h>
#include <VcDirector.h>
#include <vector>

using namespace std;
void VcDirector::sendEvent(MyEvent& e) {
	if (e.str == "GAME_SELECT") {
		scene = LevelSelect::createScene();
		Director::getInstance()->replaceScene(scene);
	}
	if (e.str == "MAIN_MENU") {
		scene = MainMenu::createScene();
		Director::getInstance()->replaceScene(scene);
	}
	if (e.str.find("START_SCOREBOARDS") != string::npos) {
		scene = ScoresLayer::createScene();
		Director::getInstance()->replaceScene(scene);
	}
	if (e.str.find("START_NEW_GAME") != string::npos) {
		vector<string> str = myUtils::Utils::slice(e.str, ":");
		scene = GameLayer::createScene(str[1]);
		Director::getInstance()->replaceScene(scene);
	}
//    if(e.str == "START_SCOREBOARDS"){
//      scoreboards.initialize();
//       scene = ScoresLayer::createScene(&scoreboards);
//    Director::getInstance()->replaceScene(scene);
//   }
//   if(e.str == "START_SETTINGS"){
//       scene = SettingsLayer::createScene();
//    Director::getInstance()->replaceScene(scene);
//   }
}

VcDirector* VcDirector::get() {
	static VcDirector dir;
	return &dir;

}

VcDirector::~VcDirector() {
	// TODO Auto-generated destructor stub
}

AchievementsObserver& AchievementsObserver::getInstance() {
	static AchievementsObserver instance;
	return instance;
}

AchievementsObserver::AchievementsObserver() :
		all_challenges(
				FileUtils::getInstance()->sharedFileUtils()->fullPathForFilename(
						"challenges")), my_records(
				FileUtils::getInstance()->getWritablePath() + "my_records") {

}

AchievementsObserver::~AchievementsObserver() {
	my_records.serialize(
			FileUtils::sharedFileUtils()->getWritablePath() + "my_records");
}

vector<string> AchievementsObserver::sendResult(string grid, double points,
		int moves, int length) {
	vector<string> str;
	auto vec = all_challenges.findByGrid(grid);
	auto vec2 = my_records.findByGrid(grid);
	auto it = vec.begin();
	while (it != vec.end()) {
		int lvl = 1;
		if (not vec2.empty()) {
			auto it1 = vec2.upper_bound(
					grid + "_" + it->second.type + char(127));
			it1--;
			if (it1->second.type == it->second.type)
				lvl = it1->second.level + 1;
		}
		string key = grid + "_" + it->second.type + "_"
				+ myUtils::Utils::itos<int>(lvl);
		auto it2 = vec.find(key);
		while (it2 != vec.end()) {
			ChallengeLogic * cl = ChallengeLogic::get(it2->second);
			if (cl->parseResult(points, moves, length)) {
				str.push_back(key);
				my_records.challenges[key] = all_challenges.challenges[key];
			}
			lvl++;
			key = grid + "_" + it->second.type + "_"
					+ myUtils::Utils::itos<int>(lvl);
			it2 = vec.find(key);
		}
		it = vec.upper_bound(grid + "_" + it->second.type + char(127));
	}
	return str;

}

map<string, Challenge> AchievementsObserver::retrieveChallengesForRange(
		string from, string to) {
	map<string, Challenge> partial { all_challenges.challenges.lower_bound(
			from), all_challenges.challenges.upper_bound(to) };
	return partial;
}

int AchievementsObserver::retrieveRecordLevel(string pref) {
	int ret = 0;
	map<string, Challenge> partial { my_records.challenges.lower_bound(pref),
			my_records.challenges.upper_bound(pref + char(127)) };
	for (auto m : partial)
		if (m.second.level > ret)
			ret = m.second.level;
	return ret;
}

vector<string> AchievementsObserver::getChallengeTypes(string grid) {
	return all_challenges.getChallengeTypes(grid);
}

Challenge AchievementsObserver::get(string key) {
	return all_challenges.challenges[key];
}
