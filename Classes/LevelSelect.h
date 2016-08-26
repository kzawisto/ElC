/*
 * LevelSelect.h
 *
 *  Created on: Oct 18, 2015
 *      Author: krystian892
 */
#ifndef LevelSelect_H
#define LevelSelect_H
#include"cocos2d.h"
#include<functional>
#include<string>
#include "ui/UIScale9Sprite.h"
#include<vector>
class FullGrid;
USING_NS_CC;
using namespace std;
class LevelSelect: public cocos2d::Layer
{
public:
   static cocos2d::Scene* createScene();
   // EventObserver eventObserver = new EventObserver();
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    Size visibleSize;
    Vec2 origin;
    vector<string> levelNames;
    vector<double> sizes;
    vector<Sprite*> stars;
    vector<Color3B> starColors;
    int vec_iter=0;
    FullGrid * grid=nullptr;
    vector<Label*> challengeLabels;
    void updateChallenges();
    void menuCloseCallback(Ref* pSender);
    void refreshGrid();
    void menuLeft(Ref* pSender);
    void menuRight(Ref* pSender);
    void menuStart(Ref* pSender);
    void menuBack(Ref* pSender);
    CREATE_FUNC(LevelSelect);
};



#endif // LevelSelect_H
