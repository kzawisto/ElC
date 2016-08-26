#include <Colors.h>
#include "GameLayer.h"
#include "GridNode.h"
#include "logic/SingularGrid.h"
#include "logic/LogicalGrid.h"

#include <sys/time.h>
#include <algorithm>
#include <logic/Utils.h>
#include <VcDirector.h>
#include <string>
#include<valarray>
#include <vector>
USING_NS_CC;
using namespace std;
Scene* GameLayer::createScene(string levelKey)
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();

    // 'layer' is an autorelease object
    auto layer = GameLayer::create(levelKey);

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

void GameLayer::timerTick(float dt) {
	cocos2d::log("Timer tick %f",dt);
}

void GameLayer::createLabels() {
	 Size visibleSize = Director::getInstance()->getVisibleSize();
	    Vec2 origin = Director::getInstance()->getVisibleOrigin();
	  lLength =Label::createWithTTF("Length: 0","fonts/Marker Felt.ttf",32);
	    lPoints = Label::createWithTTF("Points: 0","fonts/Marker Felt.ttf",32);
	    lMoves =  Label::createWithTTF("Moves: 0","fonts/Marker Felt.ttf",32);
	    lTime= Label::createWithTTF("0","fonts/Marker Felt.ttf",24);
	    lLength->setPosition(visibleSize.width * 8/9,visibleSize.height* 2/12);
	    lLength->setColor(Color3B::RED);
	    addChild(lLength);
	    lMoves->setPosition(visibleSize.width * 8/9,visibleSize.height* 3/12);
	    lMoves->setColor(Color3B::BLUE);
	   // lMoves->enableGlow(Color4B::WHITE);
	    addChild(lMoves);
	    lPoints->setPosition(visibleSize.width * 8/9,visibleSize.height* 4/12);
	   	 lPoints->setColor(Color3B::GREEN);
	   	 addChild(lPoints);

}

GameLayer * GameLayer::create(string levelKey){
	auto g = new GameLayer();
	g->init(levelKey);
	g->autorelease();
	return g;
}
bool GameLayer::init()
{
 return true;
}
// on "init" you need to initialize your instance
bool GameLayer::init(string levelkey)
{
	 ColorLoader & cl =ColorLoader::getInstance();
	     starColors = {cl.getColor("bronze"), cl.getColor("silver"),
	    cl.getColor("gold"),  cl.getColor("white"),  cl.getColor("diamond"),
		cl.getColor("red"), cl.getColor("green"), cl.getColor("blue") };
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    this->levelkey= levelkey;
    visibleSize = Director::getInstance()->getVisibleSize();
      origin = Director::getInstance()->getVisibleOrigin();
    gridPos={100+origin.x,100+origin.y};
   std::valarray<int> arr{1,2,3}, arr2{4,5,6};
    arr+=arr2;
    logic::Point<double> p1{1.0,2.0}, p2{0.4,0.5};
    double d = p1.distance(p2);
   createLabels();
   cocos2d::log("levelkey : ");
   cocos2d::log("%s",levelkey.c_str());
  grid= MyGridFactory::get().generate(levelkey,45,false);

    		//TwTriFullGrid::create();
    		//HexFullGrid::create();
    		//TwSqTriFullGrid::create();
  grid->setPosition(gridPos);
   addChild(grid);
    grid->observer = this;
    grid->setMetrics();
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(GameLayer::menuCloseCallback, this));

	closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
                                origin.y + closeItem->getContentSize().height/2));
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);
    auto touchListener = EventListenerTouchOneByOne::create();
    touchListener->onTouchBegan = CC_CALLBACK_2(GameLayer::onTouchBegan, this);
    touchListener->onTouchEnded = CC_CALLBACK_2(GameLayer::onTouchEnded, this);
    touchListener->onTouchMoved = CC_CALLBACK_2(GameLayer::onTouchMoved, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
    //this->schedule(schedule_selector(GameLayer::timerTick),1.0f);
    return true;
}


void GameLayer::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}

bool GameLayer::onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event) {
	Vec2 loc =touch->getLocation() - gridPos;
	grid->onClick(loc);
	return true;
}

void GameLayer::onTouchEnded(cocos2d::Touch* t, cocos2d::Event* e) {
}

void GameLayer::onTouchMoved(cocos2d::Touch* t, cocos2d::Event* e) {
}

void GameLayer::setTime(double t) {
	string s = myUtils::Utils::itos(t);

}

void GameLayer::setLenght(int len) {
	string s = "Length: "+myUtils::Utils::itos(len);
	lLength->setString(s);
}

void GameLayer::setPoints(double pts) {
	string s = "Points: "+myUtils::Utils::itos(pts);
	float f = pts;
	log("points %f",f);
		lPoints->setString(s);
}
void GameLayer::sendChallengesNotification(double pts, int moves,int len){
	vector<string> s1=AchievementsObserver::getInstance().sendResult(levelkey,pts,moves,len);
	int i =0;
	for(string s: s1){

		Challenge c =AchievementsObserver::getInstance().get(s);
		Sprite * spr= Sprite::create("star.png");
		Vec2 pos {origin.x + visibleSize.width * (8.f/9.f ), origin.y + visibleSize.height /2};
		spr->setPosition(origin.x + visibleSize.width * (8.f/9.f ), origin.y + visibleSize.height /2);
		spr->setColor(starColors[c.level-1]);

		this->addChild(spr);
		spr->setVisible(false);

		myUtils::scheduleOnce([i,pos,this, spr](float dt){
			auto ac1 = FadeOut::create(2.0f);
			auto ac2= MoveBy::create(2.0f,Vec2(0, visibleSize.height /2));
			spr->setVisible(true);
			spr->runAction(ac1);
			spr->runAction(ac2);
		    ParticleSystem *ps = ParticleSystemQuad::create("spark.plist");
		    ps->setEmissionRate(ps->getEmissionRate() *0.1 *(i+1)*(i+1));
		   ps->setSourcePosition(pos);
		   this->addChild(ps);
		},this, 0.5f +1.f*i, string("challenge_completed") + char('a'+i));

	i++;
	}
}
void GameLayer::setMoves(int moves) {
	string s = "Moves: "+myUtils::Utils::itos(moves);
			lMoves->setString(s);
}
