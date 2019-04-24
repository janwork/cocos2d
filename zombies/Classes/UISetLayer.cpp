#include "UISetLayer.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;
using namespace CocosDenshion;


UISetLayer* UISetLayer::m_pSingleInstance = NULL;

bool bLogined = false;
int payIndex;

class Sp01;

UISetLayer* UISetLayer::shared()
{
	if (m_pSingleInstance == NULL)
	{
		m_pSingleInstance = new UISetLayer();
	}

	return m_pSingleInstance;
}

void UISetLayer::purgeShared()
{
	CC_SAFE_DELETE(m_pSingleInstance);
}

//void UISetLayer::setUIMainMenuLayer(UIMainMenuLayer *uim)
//{
//	UIMM = uim;
//}

UISetLayer::UISetLayer()
{
}

UISetLayer::~UISetLayer()
{

}

void UISetLayer::update(float dt)
{

}

