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


	Scene*	scene = Scene::create();

	//CC_BREAK_IF(!scene);

	UIMainMenuLayer *layer = UIMainMenuLayer::create();

	/*CC_BREAK_IF(!layer);*/

	scene->addChild(layer);

	return scene;
}

bool UIMainMenuLayer::init()
{

	if (!Layer::init()){
		return false;
	}


	timeID = 180;

	auto listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(false);
	CCLOG("<janlog> UIMainMenuLayer init");

	listener->onTouchBegan = [](Touch* touch, Event* event){
		CCLOG("touch began");
		return true;//一定要返回true ，否则后面的事件会监听不到
	};
	listener->onTouchMoved = [](Touch* touch, Event* event){
		CCLOG("touch moved");
		Vec2 v = touch->getLocation();
		CCLOG("%f %f", v.x, v.y);

	};
	listener->onTouchEnded = [=](Touch* touch, Event* event){
		CCLOG("touch ended");
	};

	/*listener->onTouchBegan = CC_CALLBACK_2(UIMainMenuLayer::onTouchBegan, this);
	listener->onTouchMoved = CC_CALLBACK_2(UIMainMenuLayer::onTouchMoved, this);
	listener->onTouchEnded = CC_CALLBACK_2(UIMainMenuLayer::onTouchEnded, this);
	listener->onTouchCancelled = CC_CALLBACK_2(UIMainMenuLayer::onTouchCancelled, this);*/

	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);


	this->setContentSize(Size(Director::getInstance()->getWinSize().width, Director::getInstance()->getWinSize().height));


	//this->setTouchEnabled(true);

	/*SpriteFrameCache::getInstance()->addSpriteFramesWithFile("pic/text_ui1.plist", "pic/text_ui1.png");
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

	m_pBtnStartGame = SpriteButton::createWithFrame(SpriteFrameCache::getInstance()->spriteFrameByName("kaishi2.png"), NULL, NULL);
	m_pBtnStartGame->setZoomInOnHighlight(true);
	m_pBtnStartGame->setPressUpHandler(this, menu_selector(UIMainMenuLayer::onStartGamePressed));

	SpriteButton* quitButton = SpriteButton::createWithFrame(SpriteFrameCache::getInstance()->spriteFrameByName("fanhui.png"), NULL, NULL);
	quitButton->setZoomInOnHighlight(true);
	quitButton->setPosition(Vec2(72, 40));
	quitButton->setPressUpHandler(this, menu_selector(UIMainMenuLayer::menuCloseCallback));
	addChild(quitButton, 1);


	Sprite* bgSprite = Sprite::create("pic/fengmianbeijMainmenu.jpg");
	bgSprite->setPosition(Vec2(400, 240));
	this->addChild(bgSprite, -100);

	Sprite* qianghun = Sprite::createWithSpriteFrameName("fengmianzi1.png");
	qianghun->setPosition(Vec2(613.5, 372));
	this->addChild(qianghun, 1);
	qianghun->setScale(0.001);

	playBg = Sprite::create("pic/ui_store1/kaishi1.png");
	playBg->setPosition(Vec2(650.5, -124));
	this->addChild(playBg, 1);
	

	CallFuncN* down1 = CallFuncN::create(this, callfuncN_selector(UIMainMenuLayer::biaotiActionCallBack));
	qianghun->runAction(Sequence::create(ScaleTo::create(0.3f, 1.3f), ScaleTo::create(0.2f, 0.95f), ScaleTo::create(0.1f, 1), down1, NULL));

	
	m_pBtnStartGame->setPosition(Vec2(playBg->getContentSize().width / 2 - 2, playBg->getContentSize().height / 2 + 60));
	playBg->addChild(m_pBtnStartGame);
	

	shou = Sprite::createWithSpriteFrameName("gebo1.png");
	shou->setPosition(Vec2(335.5, 40));
	this->addChild(shou, 1);


	Dictionary* dic = Dictionary::createWithContentsOfFile("stringsScript.xml");
	String* strchinese = dynamic_cast<String*>(dic->objectForKey("tel3"));
	LabelTTF* bmFont = LabelTTF::create(strchinese->getCString(), "", 18);
	bmFont->setPosition(Vec2(Director::getInstance()->getWinSize().width* 0.55, 55));
	addChild(bmFont, 22);

	String* uid = dynamic_cast<String*>(dic->objectForKey("userid"));
	LabelTTF* username = LabelTTF::create(uid->getCString(), "", 18);
	username->setPosition(Vec2(Director::getInstance()->getWinSize().width* 0.55 - 100, 35));
	addChild(username, 22);

	runAction(Sequence::create(DelayTime::create(0.5f), CallFunc::create(this, callfunc_selector(UIMainMenuLayer::TanChuLibao)), NULL));
*/


	return true;
}

void UIMainMenuLayer::biaotiActionCallBack(Node* node)
{
	CCCallFuncN* down1 = CCCallFuncN::create(this, callfuncN_selector(UIMainMenuLayer::playBgDoneCallBack));
	playBg->setScale(0.9f);
	playBg->runAction(CCSequence::create(CCSpawn::create(CCScaleTo::create(0.4f, 1.0f), CCEaseBackOut::create(CCMoveTo::create(0.4f, ccp(650.5, 480 - 370.5 - 15))), NULL), down1, NULL));
	this->runAction(Sequence::create(
			MoveTo::create(0.25f, Vec2(this->getPositionX(), this->getPositionY() + 2)),
			MoveTo::create(0.05f, Vec2(this->getPositionX(), this->getPositionY() - 2)),
			NULL));


	ParticleSystem *mypat = ParticleSystemQuad::create("particle/uimainmanu_unearth2.plist");
	mypat->setAutoRemoveOnFinish(true);
	mypat->setPosition(Vec2(480, -20));
	this->addChild(mypat, 10);
}

void UIMainMenuLayer::playBgDoneCallBack(Node* node)
{
	CallFunc* down2 = CallFunc::create([=]{

		CCLOG("UIMainMenuLayer::playBgDoneCallBac");
		SpriteButton* setButton = SpriteButton::createWithFrame(SpriteFrameCache::getInstance()->spriteFrameByName("an_shezhi.png"), NULL, NULL);

		setButton->setZoomInOnHighlight(true);
		setButton->setPosition(Vec2(50, 440));
		setButton->setPressUpHandler(this, menu_selector(UIMainMenuLayer::setGamePressed));
		addChild(setButton, 100);


		SpriteButton* storeButton = SpriteButton::createWithFrame(SpriteFrameCache::getInstance()->spriteFrameByName("an_gouwuche.png"), NULL, NULL);
		storeButton->setZoomInOnHighlight(true);
		storeButton->setPosition(Vec2(50, 365));
		storeButton->setPressUpHandler(this, menu_selector(UIMainMenuLayer::onStorePressed));

		addChild(storeButton, 100);
	});

	playBg->runAction(Sequence::create(Spawn::create(ScaleTo::create(0.4f, 1.0f), EaseBackOut::create(MoveTo::create(0.4f, Vec2(650.5, 94.5))), NULL), down2, NULL));

}

void UIMainMenuLayer::onStartGamePressed(Object* pSender)
{
	CCLOG("onStartGamePressed");
}

void UIMainMenuLayer::onStorePressed(Object* pSender)
{
	CCLOG("onStorePressed");
}


void  UIMainMenuLayer::menuCloseCallback(Object* pSender)
{
	CCLOG("menuCloseCallback");
}

void  UIMainMenuLayer::setGamePressed(Object* obj)
{
	CCLOG("setGamePressed");
}

void UIMainMenuLayer::TanChuLibao()
{

}

bool UIMainMenuLayer::onTouchBegan(Touch *touch, Event *pEvent)
{
	CCLOG(" UIMainMenuLayer::onTouchBegan ");

	return true;

}

void UIMainMenuLayer::onTouchMoved(Touch *touch, Event *pEvent)
{
}

void UIMainMenuLayer::onTouchEnded(Touch *touch, Event *pEvent)
{
	
}

void UIMainMenuLayer::onTouchCancelled(Touch *touch, Event *pEvent)
{
}
