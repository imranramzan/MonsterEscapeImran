/*
 Touch Gestures Functionality
 AllienEscape (c) BrainLogix
 Written by: Zeeshan Ali
 */


#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "CCScrollView.h"
#include "CCLayerPanZoom.h"
#include "CharacterHuman.h"
#include "CharacterHumanDelegateClass.h"

using namespace cocos2d;
using namespace extension;

class HelloWorld : public CCLayerPanZoom,CharacterHumanDelegateClas
{
    
    CCScrollView *gamePlayBGScrollView;
    
    CharacterHuman *human1;
    CharacterHuman *human2;
    CharacterHuman *human3;

    
    bool shouldMove;

public:
    // Method 'init' in cocos2d-x returns bool, instead of 'id' in cocos2d-iphone (an object pointer)
    virtual bool init();

    // there's no 'id' in cpp, so we recommend to return the class instance pointer
    static cocos2d::CCScene* scene();
    
    // a selector callback
    void menuCloseCallback(CCObject* pSender);

    // preprocessor macro for "static create()" constructor ( node() deprecated )
    CREATE_FUNC(HelloWorld);
    cocos2d::CCPoint getPointsWithDistanceAtAngle(int angle, int distance, float x, float y);
    void executings();
    void getUpdatedPoints(cocos2d::CCSprite *sprite);
    
    CCPoint getISOCoord(CCPoint point);
    bool isColiedable(CCPoint tileCoord);
    bool isExit(CCPoint tileCoord);
    
    void allienInHumanBoundary(CharacterHuman *human, bool inBoundary);
    
    virtual void characterTouchMove (CCPoint touchPoint, CharacterHuman *human);
    virtual void humanCurrentPosition (CCPoint pos, CharacterHuman *human) ;
    
private:
    cocos2d::CCSprite* pSprite;
    cocos2d::CCTMXTiledMap *_map;
    cocos2d::CCArray* animFrames;
    CCTMXLayer *_hurdle;
    
    bool flag;
};

#endif // __HELLOWORLD_SCENE_H__
