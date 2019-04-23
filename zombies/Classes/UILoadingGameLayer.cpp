#include "UILoadingGameLayer.h"
#include "cocos-ext.h"

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
		bgSp = Sprite::create("fengmianzi5.png");
		bgSp->setPosition(ccp(400, 480 -240));
		this->addChild(bgSp, 0);


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
		break;
	case 3:
		break;
	case 4:
		break;
	case 5:

	default:
		break;
	}
}

void UILoadingGameLayer::sendXinXi()
{

}