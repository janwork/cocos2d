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

	//m_pBtnStartGame = SpriteButton::createWithFrame(SpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("kaishi2.png"), NULL, NULL);
	
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("pic/text_ui1.plist", "pic/text_ui1.png");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("pic/text_ui2.plist", "pic/text_ui2.png");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("pic/commonPic.plist", "pic/commonPic.png");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("pic/pic_In_gameUI.plist", "pic/pic_In_gameUI.png");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("pic/picInGame_fullScreen.plist", "pic/picInGame_fullScreen.png");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("pic/picInGameBlood.plist", "pic/picInGameBlood.png");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("pic/picInGameJinBi.plist", "pic/picInGameJinBi.png");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("pic/picInGameSun.plist", "pic/picInGameSun.png");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("pic/text_common.plist", "pic/text_common.png");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("pic/text_game.plist", "pic/text_game.png");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("pic/ui_store1.plist", "pic/ui_store1.png");

	Sprite* bgSprite = Sprite::create("pic/fengmianbeijMainmenu.jpg");
	bgSprite->setPosition(Vec2(400, 240));
	this->addChild(bgSprite, -100);

	Sprite* qianghun = Sprite::createWithSpriteFrameName("fengmianzi1.png");
	qianghun->setPosition(Vec2(613.5, 372));
	this->addChild(qianghun, 1);
	qianghun->setScale(0.001);

	CallFuncN* down1 = CallFuncN::create(this, callfuncN_selector(UIMainMenuLayer::biaotiActionCallBack));
	qianghun->runAction(Sequence::create(ScaleTo::create(0.3f, 1.3f), ScaleTo::create(0.2f, 0.95f), ScaleTo::create(0.1f, 1), down1, NULL));

	playBg = Sprite::createWithSpriteFrameName("kaishi1.png");
	playBg->setPosition(Vec2(650.5, -124));
	playBg->addChild(playBg, 1);

	shou = Sprite::createWithSpriteFrameName("gebo1.png");
	shou->setPosition(Vec2(335.5, 40));
	this->addChild(shou, 1);

	return true;
}

void UIMainMenuLayer::biaotiActionCallBack(Node* node)
{
	CallFuncN* down1 = CallFuncN::create(this, callfuncN_selector(UIMainMenuLayer::playBgDoneCallBack));
	playBg->setScale(0.9f);
	playBg->runAction(Sequence::create(Spawn::create(ScaleTo::create(0.4f, 1.0f), EaseBackInOut::create(MoveTo::create(0.4f, Vec2(650.5, 94.5))), NULL), down1,NULL));


	this->runAction(Sequence::create(
		MoveTo::create(0.25f, Vec2(this->getPositionX(), this->getPositionY() + 2)),
		MoveTo::create(0.05f, Vec2(this->getPositionX(), this->getPositionY() - 2)),
		NULL));


	ParticleSystem * mypat = ParticleSystemQuad::create("particle/uimainmanu_unearth2.plist");
	mypat->setAutoRemoveOnFinish(true);
	mypat->setPosition(Vec2(480, -20));
	this->addChild(mypat, 10);

}

void UIMainMenuLayer::playBgDoneCallBack(Node* node)
{

}