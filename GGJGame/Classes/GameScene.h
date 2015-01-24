#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#define SCENE_LAYER_TAG 1


class MainUILayer;
class GameScene : public cocos2d::LayerColor
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  
    
    // implement the "static create()" method manually
    CREATE_FUNC(GameScene);

	void setMainUIVisible(bool visible);

private:
	cocos2d::Sprite* m_Black;
	MainUILayer* m_MainUILayer;
};

#endif // __HELLOWORLD_SCENE_H__
