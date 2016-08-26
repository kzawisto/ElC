#ifndef TILENODE_H
#define TILENODE_H

#include"cocos2d.h"
#include<vector>
#include"logic/Point.h"
#include "logic/LogicalTile.h"

#include<map>
#include<string>
#include <algorithm> 
#include <memory>
typedef logic::Point<double> PD;
typedef logic::Point<int> PI;
USING_NS_CC;
using namespace std;
typedef logic::LogicalTile LogTile;

class SpriteSheetData{
public:
    string path;
    logic::Point<double> offset, spriteSize;
    int len;
    SpriteSheetData(string _path, logic::Point<double> _offset, logic::Point<double> _spriteSize, int _len);
};
class SpriteLoader {
public:
  SpriteLoader();
  SpriteLoader & getInstance();
  SpriteFrameCache * sfc;
  map<int,unique_ptr<SpriteSheetData>> spritePaths;
  map<int, double> flipAngleOffsets;
  vector<Color3B> colors;
  Sprite * getSprite(int sheetNum, int spriteNum);
};
class TileNode : public Node, public logic::TileObserver{
public:
  DrawNode * dn;
  shared_ptr<LogTile> lt;
  map<int,Sprite*> spriteContainer;
  //static const double display_scale=0.9;
  double getDisplayScale();
  void rotate(int step);
  virtual void lightenPath(int i) override;
  	virtual void dimPath(int i) override;
  TileNode(logic::Point<double> position);
  TileNode(shared_ptr<LogTile> lt);

  static TileNode * create(logic::Point<double> position);
  static TileNode * create(shared_ptr<LogTile> lt, double angleOffset=0);

  static TileNode * create(Node * father, shared_ptr<LogTile> lt, double angleOffset=0);
  void drawFrame();
  void drawBeziers();
  void createSprites(double angleOffset=0);

  void createSprites(Node * father, double angleOffset=0);
  static double goodAngle(double badAngle){
	  	return badAngle - ( (int) (badAngle /360) - (badAngle<=0)) * 360 ;
  }
 //void drawFrame();
  void drawConnections(DrawNode * draw);
};

SpriteLoader & getMySpriteLoader() ;
template <typename T,unsigned int N=2>
logic::Point<T,N> VtoP(Vec2 a){
	return logic::Point<T,N>{(T)a.x, (T) a.y};
}
template <typename T,unsigned int N=2>
Vec2 PtoV(logic::Point<T,N> a){
	return Vec2{(float)a.X(), (float) a.Y()};
}


#endif // TILENODE_H
