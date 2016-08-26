#include "TileNode.h"
#include "logic/Point.h"
#include "logic/Utils.h"
#include <random>       // std::default_random_engine
#include <chrono>
#include <cstdlib>
#include <Colors.h>
SpriteLoader::SpriteLoader()
{
	spritePaths[3] = unique_ptr<SpriteSheetData>{new SpriteSheetData(
			"tri_paths2.png",{7.,7.},{177.,233.},6 )};
	spritePaths[4] = unique_ptr<SpriteSheetData>{new SpriteSheetData(
			"sqr_paths2.png",{0.,0.},{168.,168.},8 )};
	spritePaths[6] = unique_ptr<SpriteSheetData>{new SpriteSheetData(
			"hex_paths2.png",{0.,0.},{204.,240.},12 )};
	spritePaths[8] = unique_ptr<SpriteSheetData>{new SpriteSheetData(
			"oct_paths2.png",{0.,0.},{218.5,221.},16 )};
	spritePaths[12] = unique_ptr<SpriteSheetData>{new SpriteSheetData(
			"twl_paths22.png",{0.,0.},{171.25,171.},24)};

	auto spritecache = SpriteFrameCache::getInstance();
	spritecache->addSpriteFramesWithFile("twlist.plist");
	spritecache->addSpriteFramesWithFile("sqlist.plist");
	flipAngleOffsets[4]=0;
	flipAngleOffsets[3]=-60;
	flipAngleOffsets[6]= 60;
	flipAngleOffsets[8]=90;
	flipAngleOffsets[12]=120;
	//colors = {{255,0,0}, {255,204,0}, {64,255,217}, {128,128,255}, {255,128,196}, {255,162,128},
	//		  {229,255,128}, {128,213,255}, {89,64,255}, {255,64,89}, {255,166,64}, {140,255,64}};
	//colors ={{255,89,64}, {89,255,64}, {64,191,255}, {255,64,217}, {255,166,64}, {64,255,166}, {64,140,255},
	//		{255,64,140}, {255,191,64}, {64,255,242}, {64,89,255}, {255,64,89}, {217,255,64}, {64,217,255}, {191,64,255}};
	colors = ColorLoader::getInstance().getTileColors();
			//{{189,0,0}, {189,94,0}, {189,157,0}, {157,189,0}, {63,189,0}, {0,189,126}, {0,189,189}, {0,157,189},
			//{0,126,189}, {0,94,189}, {0,63,189}, {31,0,189}, {157,0,189}, {189,0,126}, {189,0,63}};

	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
	shuffle (colors.begin(), colors.end(), std::default_random_engine(seed));
}

SpriteLoader & SpriteLoader::getInstance() {
	static SpriteLoader instance;
	return instance;

}

Sprite * SpriteLoader::getSprite(int sheetNum, int spriteNum){
	if(sheetNum == 12){
		string spritecode ="Tw0" + myUtils::Utils::itos(spriteNum)+".png";
		//cocos2d::log("%s",spritecode.c_str());
		auto spr = Sprite::createWithSpriteFrameName(spritecode);
		return spr;
	}
	if(sheetNum == 4){
		string spritecode ="Sq0" + myUtils::Utils::itos(spriteNum)+".png";
				//cocos2d::log("%s",spritecode.c_str());
				auto spr = Sprite::createWithSpriteFrameName(spritecode);
				return spr;
	}
	double left= spritePaths[sheetNum]->offset.X()
							+ spritePaths[sheetNum]->spriteSize.X()* spriteNum, top =spritePaths[sheetNum]->offset.Y(),
							width =  spritePaths[sheetNum]->spriteSize.X(), height = 	spritePaths[sheetNum]->spriteSize.Y();
	auto spr =Sprite::create(spritePaths[sheetNum]->path, Rect( left, top, width, height));
	if(sheetNum==3) spr->setAnchorPoint( Vec2(0.6667,0.5));

	return spr;
}
SpriteSheetData::SpriteSheetData(string _path, logic::Point< double > _offset, logic::Point< double > _spriteSize,int _len):
		path(_path), offset(_offset), spriteSize(_spriteSize ), len(_len)
{

}


TileNode::TileNode(logic::Point<double> _position) {
	dn = DrawNode::create();
	addChild(dn);
	setPosition((float)_position.X(),(float)_position.Y());
	dn->drawPoint({0,0},2.0, Color4F::GREEN);
}

TileNode* TileNode::create(logic::Point<double> position) {
	TileNode* tn = new TileNode(position);
	tn->autorelease();
	return tn;
}

TileNode::TileNode(shared_ptr<LogTile> lt): lt(lt) {
	setPosition( PtoV<double>(lt->position));
	dn = DrawNode::create();
	addChild(dn);
	//setPosition((float)_position.X(),(float)_position.Y());


}
SpriteLoader & getMySpriteLoader()
{
	static SpriteLoader instance;
	return instance;
}
TileNode* TileNode::create(shared_ptr<LogTile> lt, double angleOffset) {
	TileNode* tn = new TileNode(lt);
	lt->tileObserver=tn;
	//tn->drawBeziers();
	tn->createSprites(angleOffset);
	//tn->drawFrame();
	tn->autorelease();

	return tn;
}
TileNode* TileNode::create(Node * father, shared_ptr<LogTile> lt, double angleOffset){
	TileNode* tn = new TileNode(lt);
	lt->tileObserver=tn;
	//tn->drawBeziers();
	tn->createSprites(father,angleOffset);
	//tn->drawFrame();
	tn->autorelease();

	return tn;
}

double TileNode::getDisplayScale() {
	return 0.95;
}

void TileNode::lightenPath(int i) {
	spriteContainer[i]->setColor(Color3B::WHITE);
	double scl = 1.05;
	spriteContainer[i]->setScale(scl*spriteContainer[i]->getScaleX(), scl*spriteContainer[i]->getScaleY());
}

void TileNode::dimPath(int i) {

	spriteContainer[i]->setColor(getMySpriteLoader().colors[rand() % 12]);
	double scl = 1.0/1.05;
	spriteContainer[i]->setScale(scl*spriteContainer[i]->getScaleX(), scl*spriteContainer[i]->getScaleY());
}

void TileNode::rotate(int step) {

	map<int, Sprite*> spriteCpy = spriteContainer;
	for(int i =0; i < lt->n* lt->wires_per_side;++i){
			if(i > lt->internalWiring[i] )continue;
			int i1 = lt->constrainNumber(i+step*lt->wires_per_side),
					i2 = lt->constrainNumber(lt->internalWiring[i]+step*lt->wires_per_side);
			spriteContainer[i1] = spriteCpy[i];
			spriteContainer[i2] = spriteCpy[i];
			//spriteContainer[i1]->setRotation(spriteContainer[i1]->getRotation() - step * lt->internal_angle /M_PI *180.0);
			float angle = (float)(- step *  lt->internal_angle /M_PI *180.0);
									auto action=RotateBy::create(0.3f,  angle);
									spriteContainer[i1]->runAction(action);
	}

	lt->rotate(step);
}

void TileNode::drawConnections(DrawNode * draw) {
	srand(time(0));
	//for(int i =0; i < lt->n;++i){
	for(auto it = lt->connections.begin();it != lt->connections.end();++it){
		for(int j=0; j< lt->wires_per_side;++j){
			double r = rand() %100 + 100, g= rand() % 100 + 100, b=rand() %100 + 100;
			Color4F col ( r /200, g/200, b/200, 1.0);
			Vec2 p1= PtoV<double>(lt->connectionPointOnThis(it->first,j));
			Vec2 p2= PtoV<double>(lt->connectionPointOnNeighbour(it->first,j));
			draw->drawLine(p1,p2, col);
		}
	}
	//lt->connectionPointOnThis()
	//}
}

void TileNode::createSprites(double angleOffset) {

	int col_counter=0;
	for(unsigned b =0; b < lt->internalWiring.size();++b){
		if((int)b < lt->internalWiring[b]){
			int step = lt->internalWiring[b]- b-1;
			Sprite * sprite = b%2 ? getMySpriteLoader().getSprite(lt->n,lt->n * lt->wires_per_side -2-step):
					getMySpriteLoader().getSprite(lt->n,step);
			double scale = 2*getDisplayScale()*lt->InsR / getMySpriteLoader().spritePaths[lt->n]->spriteSize.X();
			if(lt->n ==3 ) scale = getDisplayScale()*(lt->InsR + lt->CircR)/getMySpriteLoader().spritePaths[lt->n]->spriteSize.X();
			sprite->setScale(scale,scale);
			//sprite->setRotation(-(lt->internal_angle / M_PI * 180));
			if(b%2) {
				sprite->setScaleX( -sprite->getScaleX());
				double angle= 360-(b /2) * (lt->internal_angle / M_PI * 180.0)
												+ getMySpriteLoader().flipAngleOffsets[lt->n] + angleOffset;
				if(angle > 360) angle -=360;
				if(angle<0) angle+=360;
				sprite->setRotation(angle);
			}
			else  sprite->setRotation(goodAngle(360- (b /2) * (lt->internal_angle / M_PI * 180.0)+angleOffset));
			//int cl =rand() % 12;
			sprite->setColor(getMySpriteLoader().colors[rand() % 12]);

			addChild(sprite);
			spriteContainer[b] = sprite;
			spriteContainer[lt->internalWiring[b]] = sprite;
			col_counter++;
		}
	}
}

void TileNode::createSprites(Node * father,double angleOffset) {
	int col_counter=0;
	for(unsigned b =0; b < lt->internalWiring.size();++b){
		if((int)b < lt->internalWiring[b]){
			int step = lt->internalWiring[b]- b-1;
			Sprite * sprite = b%2 ? getMySpriteLoader().getSprite(lt->n,lt->n * lt->wires_per_side -2-step):
					getMySpriteLoader().getSprite(lt->n,step);
			double scale = 2*getDisplayScale()*lt->InsR / getMySpriteLoader().spritePaths[lt->n]->spriteSize.X();
			if(lt->n ==3 ) scale = getDisplayScale()*(lt->InsR + lt->CircR)/getMySpriteLoader().spritePaths[lt->n]->spriteSize.X();
			sprite->setScale(scale,scale);
			//sprite->setRotation(-(lt->internal_angle / M_PI * 180));
			if(b%2) {
				sprite->setScaleX( -sprite->getScaleX());
				double angle= 360-(b /2) * (lt->internal_angle / M_PI * 180.0)
												+ getMySpriteLoader().flipAngleOffsets[lt->n] + angleOffset;
				if(angle > 360) angle -=360;
				if(angle<0) angle+=360;
				sprite->setRotation(angle);
			}
			else  sprite->setRotation(goodAngle(360- (b /2) * (lt->internal_angle / M_PI * 180.0)+angleOffset));
			//int cl =rand() % 12;
			sprite->setColor(getMySpriteLoader().colors[rand() % 12]);
			sprite->setPosition((float)lt->position.X(),(float) lt->position.Y());
			father->addChild(sprite);
			spriteContainer[b] = sprite;
			spriteContainer[lt->internalWiring[b]] = sprite;
			col_counter++;
		}
	}
}
void TileNode::drawBeziers() {
	int col_counter=0;
	for(unsigned a = 0; a< lt->internalWiring.size();++a){
		if((int)a > lt->internalWiring[a]) continue;
		Vec2 origin = PtoV<double>(lt->connectionPoints[a]*getDisplayScale()),
				control1 =PtoV<double>(lt->connectionPoints[a] *0.5),
				control2 =PtoV<double>(lt->connectionPoints[lt->internalWiring[a]] *0.5),
				dest =PtoV<double>(lt->connectionPoints[lt->internalWiring[a]] *getDisplayScale());
		dn->drawCubicBezier(origin,control1,control2,dest,10,Color4F(getMySpriteLoader().colors[col_counter]));
		col_counter++;
	}
}

void TileNode::drawFrame() {
	PD pos(lt->position);
	myUtils::cyclic_iterate<PD>(lt->contour, [&] (PD & a, PD & b){
		Vec2 from = PtoV<double>((a-pos)*=getDisplayScale()), to = PtoV<double>((b-pos)*=getDisplayScale());
		dn->drawLine(from, to, Color4F(0.0f,0,0.6f,0.6f));
	});

//
//	for(PD & p: lt->connectionPoints){
//		dn->drawDot(PtoV<double>(p*getDisplayScale()),1.5,Color4F::WHITE);
//	}

}
