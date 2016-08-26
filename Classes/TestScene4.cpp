#include "TestScene4.h"
#include "GridNode.h"
#include "logic/SingularGrid.h"
#include "logic/LogicalGrid.h"
#include <sys/time.h>
#include <algorithm>
USING_NS_CC;
using namespace std;
Scene* TestScene4::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();

    // 'layer' is an autorelease object
    auto layer = TestScene4::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool TestScene4::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }

    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(TestScene4::menuCloseCallback, this));

	closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
                                origin.y + closeItem->getContentSize().height/2));

    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label


  ;

    	double size = 50, sideSize = 2 * size * tan(M_PI/12), sq32 = sqrt(3)/2*size;;
    //auto grid = GridNode::createSqrGrid(size,45);
    	PD spacing ={sq32*2 ,3*size};
    	PI howMany = {8,4};

    grid = GridNode::createHexGrid({0,0},size,spacing,howMany);

    auto grid2 = GridNode::createHexGrid(spacing*0.5,size,spacing,howMany);
//    auto grid =GridNode::createTwGrid({size,size*sqrt(3)},size,spacing);
   //auto gridTri1 = GridNode::createTriGrid({size,sideSize*(0.5 + sqrt(3)/3)},sideSize,spacing,howMany-PI{1,0});
//    auto gridTri2 = GridNode::createTriGrid({size,-sideSize*(0.5 + sqrt(3)/3)},sideSize,spacing,howMany-PI{1,0},0);
//    auto gridTri3 = GridNode::createTriGrid({-sideSize*(0.5 + sqrt(3)/3),size},sideSize,spacing,howMany-PI{0,1},3);
//    auto gridTri4 = GridNode::createTriGrid({sideSize*(0.5 + sqrt(3)/3),size},sideSize,spacing,howMany-PI{0,1},2);
//    auto gridsqr = GridNode::createSqrGrid({size,size}, sideSize, spacing,howMany-PI{1,1});
//    auto gridTri11 = GridNode::createTriGrid({0,size*sqrt(3)+sideSize*(0.5 + sqrt(3)/3)},sideSize,spacing);
//    auto gridTri21 = GridNode::createTriGrid({0,size*sqrt(3)-sideSize*(0.5 + sqrt(3)/3)},sideSize,spacing,false);

    vector<shared_ptr<logic::SingularGrid>> vec;//{grid->singularGrid, grid2->singularGrid};
    vec1= {grid,grid2};//,gridTri1,gridTri2,gridTri3,gridTri4,gridsqr};//,grid2,,gridTri11,gridTri21};
    for(auto g: vec1) vec.push_back(g->singularGrid);
//    logic::GridConnectionResolver resolver(vec);
//    resolver.propagateConnections();

    DrawNode *dnode = DrawNode::create();
    this->addChild(dnode);
    dnode->setPosition(gridOffset);
//    for(int i =0; i < grid->size.X();++i)
//    	for(int j =0; j < grid->size.Y();++j){
//
//    		grid->drawConnections(i,j,dnode);
//    	}
//    for(int i =0; i < gridsqr->size.X();++i)
//        	for(int j =0; j < gridsqr->size.Y();++j){
//
//        		gridsqr->drawConnections(i,j,dnode);
//        	}
    for(auto g : vec1) {

    	g->setPosition(gridOffset);
    	addChild(g);
    }
    auto lt1 = grid->get(0,1)->lt;
    //pp.startPathFrom(10, grid->get(0,1)->lt);
    for(int i =0; i< lt1->internalWiring.size();++i){

    }
    auto touchListener = EventListenerTouchOneByOne::create();
       touchListener->onTouchBegan = CC_CALLBACK_2(TestScene4::onTouchBegan, this);
       touchListener->onTouchEnded = CC_CALLBACK_2(TestScene4::onTouchEnded, this);
       touchListener->onTouchMoved = CC_CALLBACK_2(TestScene4::onTouchMoved, this);
       _eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
       // add the sprite as a child to this layer
    //this->addChild(sprite, 0);

    return true;
}


void TestScene4::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}

bool TestScene4::onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event) {
	  Vec2 loc =touch->getLocation();
	  PD coord{loc.x- gridOffset.x, loc.y-gridOffset.y};
	  pair<double, PI> p{1e10, {-10,-10}},p1;
	  GridNode * chosen_grid;
	  for( auto mygrid : vec1){
		 p1= mygrid->parseCoordinate(coord);
		 if(p1.first < p.first){
			 p=p1;
			 chosen_grid = mygrid;;
		 }
	  }
	  if(chosen_grid->singularGrid->check(p.second.X(),p.second.Y()) && p.first <= 1.0){
		  pp.deletePath();
		  chosen_grid->get(p.second.X(),p.second.Y())->rotate(1);
		  pp.startPathFrom(10, grid->get(0,1)->lt);
	  }
	  return true;
}

void TestScene4::onTouchEnded(cocos2d::Touch* t, cocos2d::Event* e) {
}

void TestScene4::onTouchMoved(cocos2d::Touch* t, cocos2d::Event* e) {
}
