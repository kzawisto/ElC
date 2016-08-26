/*
 * ScoresLayer.h
 *
 *  Created on: Oct 23, 2015
 *      Author: krystian892
 */

#ifndef CLASSES_SCORESLAYER_H_
#define CLASSES_SCORESLAYER_H_

#include"cocos2d.h"
#include<functional>
#include<string>
#include<vector>
#include "ui/UIScale9Sprite.h"

USING_NS_CC;
using namespace std;
class ScoresLayer: public cocos2d::Layer
{
public:
   static cocos2d::Scene* createScene();
   // EventObserver eventObserver = new EventObserver();
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    void menuCloseCallback(Ref* pSender);
    vector< vector< Label*> > labels;
    void menuNewGame(Ref* pSender);
    void menuSettings(Ref* pSender);
    void menuScoreboards(Ref* pSender);
    void menuInfo(Ref* pSender);
    void initializeRow(vector<string> str,vector<double> rowAlign, float hpos);
    CREATE_FUNC(ScoresLayer);
};


#endif // ScoresLayer_H
