#include "UIMainMenuLayer.h"


UIMainMenuLayer::UIMainMenuLayer()
{
	CCLOG("NEW");
}

UIMainMenuLayer::~UIMainMenuLayer()
{
	CCLOG("death");
}

Scene* UIMainMenuLayer::scene()
{
	Scene* scene = NULL;

	do 
	{

		scene = Scene::create();

		CC_BREAK_IF(!scene);

		UIMainMenuLayer *layer = UIMainMenuLayer::create();

		CC_BREAK_IF(!layer);


		scene->addChild(layer);
	} while (0);


	return scene;
}

bool UIMainMenuLayer::init()
{
	bool bRet = false;

	do 
	{
		CC_BREAK_IF(!Layer::init());

		bRet = true;
	} while (0);


	timeID = 180;

	//m_pBtnStartGame = SpriteButton::

	return true;
}