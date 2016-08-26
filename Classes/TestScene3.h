#ifndef __TEST_SCENE_3_H__
#define __TEST_SCENE_3_H__

#include "cocos2d.h"
#include "logic/LogicalTile.h"
class GridNode;
class TestScene3 : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();
    GridNode * grid;
    logic::PipePath pp;
    cocos2d::Vec2 gridOffset{100,100};
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    vector<GridNode *> vec1 ;
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    virtual bool onTouchBegan(cocos2d::Touch* t, cocos2d::Event*e);
    virtual void onTouchEnded(cocos2d::Touch* t, cocos2d::Event*e);
    virtual void onTouchMoved(cocos2d::Touch* t, cocos2d::Event*e);
    // implement the "static create()" method manually
    CREATE_FUNC(TestScene3);
};

#endif // __HELLOWORLD_SCENE_H__
