#pragma once

#include "cocos2d.h"
#include "logic/LogicalTile.h"
#include "FullGrid.h"
class GridNode;
class GameLayer : public cocos2d::Layer, public GridObserver
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene(string levelKey);
    virtual bool init();
    bool init(string levelkey);
    string levelkey;
    Label * lPoints, * lMoves, *lTime,*lLength;
    FullGrid * grid;
    cocos2d::Vec2 gridPos;
    Size visibleSize;
    vector<Color3B> starColors;
        Vec2 origin;
    void menuCloseCallback(cocos2d::Ref* pSender);
    virtual bool onTouchBegan(cocos2d::Touch* t, cocos2d::Event*e);
    virtual void onTouchEnded(cocos2d::Touch* t, cocos2d::Event*e);
    virtual void onTouchMoved(cocos2d::Touch* t, cocos2d::Event*e);
    virtual void setTime(double t);
    virtual void setLenght(int len);
    virtual void setPoints(double pts);
    virtual void setMoves(int moves);
    virtual void sendChallengesNotification(double pts, int moves,int len);
    void createLabels();
    void timerTick(float dt);
    //CREATE_FUNC(GameLayer);
    //CREATE_FUNC(GameLayer);
    static GameLayer * create(string levelKey);
};

