#include "UILoadingGameLayer.h"
#include "cocos-ext.h"
#include "UISetLayer.h"
#include "UIMainMenuLayer.h"

UILoadingGameLayer::UILoadingGameLayer() : m_nLoadingProgress(-1), bgSp(NULL)
{

}

UILoadingGameLayer::~UILoadingGameLayer()
{

}

bool UILoadingGameLayer::init()
{
	bool bRet = false;
	do{

		CC_BREAK_IF(!LayerColor::initWithColor(ccc4(0, 0, 0, 255)));

		Size size = Director::getInstance()->getWinSize();

		bgSp = Sprite::create("fengmianzi5.png");
		bgSp->setPosition(Vec2(size.width /2, 240));
		this->addChild(bgSp, 1);
		scheduleUpdate();
		bRet = true;

	} while (0);

	return bRet;

}

void UILoadingGameLayer::update(float dt)
{
	m_nLoadingProgress++;
	Sprite *bgSP = NULL;


	switch (m_nLoadingProgress)
	{
	case 1:
		break;
	case 2:
		UISetLayer::shared();
		break;
	case 3:
		break;
	case 4:
		break;
	case 5:

		Scene* m_pMainMenu = Scene::create();
		m_pMainMenu->addChild(UIMainMenuLayer::create());

		TransitionScene * ss = TransitionScene::create(0.8f, m_pMainMenu);
		Director::getInstance()->replaceScene(ss);
		break;
	}
}

void UILoadingGameLayer::sendXinXi()
{

}