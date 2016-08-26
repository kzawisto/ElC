/*
 * ScoresLayer.cpp
 *
 *  Created on: Oct 23, 2015
 *      Author: krystian892
 */

#include <ScoresLayer.h>


#include "ScoresLayer.h"
#include "GridNode.h"
#include "EventObserver.h"
#include <fstream>
using namespace std;
bool ScoresLayer::init()
{
     if ( !Layer::init() )
    {
        return false;
    }


    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
     // add a "close" icon to exit the progress. it's an autorelease object
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(ScoresLayer::menuCloseCallback, this));
    double menuSize=40;
	closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
                                origin.y + closeItem->getContentSize().height/2));

     auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    vector<double> rowAlign{0.22, 0.44,0.66,0.8,0.9};
    initializeRow({"Place", "Name","Points", "Length","Moves"},rowAlign,0.9);
    initializeRow({"1", "Tom","1000", "100","10"},rowAlign,0.8);
    initializeRow({"2", "Bart","900", "90","10"},rowAlign,0.7);
    initializeRow({"3", "Shane","800", "90","10"},rowAlign,0.6);
    this->addChild(menu, 1);
    ParticleSystem *ps = ParticleSystemQuad::create("colored_rain.plist");
   // ps->initWithFile("cloud.plist");
  ps->setSourcePosition(Vec2(0,0));
    // ps->initWithFile("cloud.plist");
  // Scoreboards boo;
   this->addChild(ps,0);
   return true;
}
void ScoresLayer::menuNewGame(Ref* pSender)
{
	MyEvent event("GAME_SELECT", 0);
   EventObserver::get().sendEvent(event);
}
void ScoresLayer::menuSettings(Ref* pSender)
{
//  MyEvent event("START_SETTINGS", 0);
//    EventObserver::get().sendEvent(event);
}
void ScoresLayer::menuScoreboards(Ref* pSender)
{
//   MyEvent event("START_SCOREBOARDS", 0);
//    EventObserver::get().sendEvent(event);
}

void ScoresLayer::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->end();
  //  Layer::menuCloseCallback(pSender);
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
void ScoresLayer::menuInfo(Ref* pSender)
{

}
Scene* ScoresLayer::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();

    // 'layer' is an autorelease object
    auto layer = ScoresLayer::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

void ScoresLayer::initializeRow(vector<string> str,vector<double> rowAlign, float hpos) {

    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
	labels.push_back(vector<Label*>());
	for(int i =0; i <str.size();++i){
		Label * label  =Label::createWithTTF(str[i],"fonts/Marker Felt.ttf",24);
		label->setPosition(origin.x + visibleSize.width* rowAlign[i],origin.y + visibleSize.height* hpos);
		labels.back().push_back(label);
		addChild(label);
	}
}
