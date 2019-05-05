#include "SpriteButton.h"
#include <iostream>

//SpriteButton::SpriteButton():m_pFrameNormal(NULL), m_pFrameHighlight(NULL), m_pFrameDisable(NULL), m_bIsOpacityModifyRGB(false), m_bTouched(false), m_pPressedUpHandle(NULL), m_pPressedUpHandleObject(NULL), m_pPressedMoveInsideHandle(NULL), m_pPressedMoveInsideHandleObject(NULL), m_pPressedMoveOutsideHandle(NULL), m_pPressedMoveOutsideHandleObject(NULL), m_pPressedDownHandle(NULL), m_pPressedDownHandleObject(NULL), m_pSprite(NULL), m_bZoomInOnHighlight(false), m_bEnable(true), m_cOpacity(0), m_tColor(ccBLACK), m_bSpriteMode(false)
//{
//	Color3B color = { 128, 128, 128 };
//	//setUnableColor(color);
//}

SpriteButton::SpriteButton()
{
	Color3B color = { 128, 128, 128 };
	//setUnableColor(color);
}



SpriteButton::~SpriteButton()
{
	CCLOG("SpriteButton::~SpriteButton");
	CC_SAFE_RELEASE_NULL(m_pFrameDisable);
	CC_SAFE_RELEASE_NULL(m_pFrameHighlight);
	CC_SAFE_RELEASE_NULL(m_pFrameNormal);
}

//void SpriteButton::cleanup()
//{
//	Layer::cleanup();
//}

bool SpriteButton::init()
{
	if (!Layer::init())
		return false;
	setTouchEnabled(true);
	ignoreAnchorPointForPosition(false);
}

SpriteButton* SpriteButton::createWithFrame(SpriteFrame * frameNormal, SpriteFrame* frameHightlight, SpriteFrame* frameDisable)
{
	assert(frameNormal);

	SpriteButton* pRef = create();
	//pRef->m_bSpriteMode = false;
	pRef->initWithFrame(frameNormal, frameHightlight, frameDisable);
	return pRef;
}


SpriteButton* SpriteButton::createWithSprite(Sprite* sprite)
{
	CCAssert(sprite, "SpriteButton::createWithSprite(sprite)-sprite cannot be null!");

	SpriteButton* pRef = create();
	//pRef->m_bSpriteMode = false;
	pRef->initWithSprite(sprite);
	return pRef;
}

void SpriteButton::initWithFrame(SpriteFrame * frameNormal, SpriteFrame* frameHightlight, SpriteFrame* frameDisable)
{
	CCAssert(frameNormal, "normal frame cannot be null!");

	m_pFrameNormal = frameNormal;
	m_pFrameHighlight = frameHightlight;
	m_pFrameDisable = frameDisable;

	CC_SAFE_RETAIN(m_pFrameNormal);
	CC_SAFE_RETAIN(m_pFrameHighlight);
	CC_SAFE_RETAIN(m_pFrameDisable);

	m_pSprite = Sprite::createWithSpriteFrame(m_pFrameNormal);
	Size size = m_pSprite->getContentSize();
	setContentSize(size);

	m_pSprite->setPosition(Vec2(size.width/ 2, size.height/2));
	addChild(m_pSprite);

}

void SpriteButton::initWithSprite(Sprite* sprite)
{
	m_pSprite = sprite;
	Size size = m_pSprite->getContentSize();
	setContentSize(size);

	m_pSprite->setPosition(Vec2(size.width / 2, size.height / 2));
	addChild(m_pSprite);
}

//
//void SpriteButton::setPressDownHandler(Ref* object, SEL_MenuHandler handle)
//{
//	m_pPressedDownHandleObject = object;
//	m_pPressedDownHandle = handle;
//}

//void SpriteButton::setPressUpHandler(Ref* object, SEL_MenuHandler handle)
//{
//	m_pPressedUpHandleObject = object;
//	m_pPressedUpHandle = handle;
//}

//void SpriteButton::setPressMoveInsideHandler(Ref* object, SEL_MenuHandler handle)
//{
//	m_pPressedMoveInsideHandleObject = object;
//	m_pPressedMoveInsideHandle = handle;
//}

//void SpriteButton::setPressMoveOutsideHandler(Ref* object, SEL_MenuHandler handle)
//{
//	m_pPressedMoveOutsideHandleObject = object;
//	m_pPressedMoveOutsideHandle = handle;
//}

//bool SpriteButton::onTouchBegan(Touch *touch, Event *pEvent)
//{
//	m_bTouched = false;
//
//	if (!m_bEnable)
//		return false;
//	if (!isVisible())
//		return false;
//	if (!isAllParentVisible())
//		return false;
//	if (!isTouchInside(touch))
//		return false;
//
//	m_bTouched = true;
//
//	onPressedDown();
//
//	if (m_bZoomInOnHighlight)
//	{
//		ScaleTo* action = ScaleTo::create(0.1, 0.1);
//		runAction(action);
//	}
//
//	return true;
//
//}

//void SpriteButton::onTouchMoved(Touch *touch, Event *pEvent)
//{
//	if (!m_bTouched)
//		return;
//
//	bool inside = isTouchInside(touch);
//
//	if (inside)
//	{
//		onPressedMoveInside();
//	}
//	else
//	{
//		onPressedMoveOutside();
//	}
//}

//void SpriteButton::onTouchEnded(Touch *touch, Event *pEvent)
//{
//	if (m_bTouched)
//		return;
//
//	onPressedUp();
//
//	if (m_bZoomInOnHighlight || getScale() > 1)
//	{
//		ScaleTo* action = ScaleTo::create(0.1, 1.0);
//		runAction(action);
//	}
//}

//void SpriteButton::onTouchCancelled(Touch *touch, Event *pEvent)
//{
//	if (!m_bTouched)
//		return;
//	onPressedCancel();
//}

//bool SpriteButton::isTouchInside(Touch* pTouch)
//{
//	Vec2 touchLocation = pTouch->getLocation();
//
//	touchLocation = this->getParent()->convertToNodeSpace(touchLocation);
//
//	Rect bBox = boundingBox();
//	return bBox.containsPoint(touchLocation);
//}

//void SpriteButton::onPressedDown()
//{
//	if (!m_bSpriteMode && m_pFrameHighlight)
//	{
//		m_pSprite->setDisplayFrame(m_pFrameHighlight);
//	}
//
//	if (m_pPressedDownHandleObject)
//	{
//		(m_pPressedDownHandleObject->*m_pPressedDownHandle)(this);
//	}
//}

//void SpriteButton::onPressedMoveInside()
//{
//	if (m_pPressedMoveInsideHandleObject)
//	{
//		(m_pPressedMoveInsideHandleObject->*m_pPressedMoveInsideHandle)(this);
//	}
//}

//void SpriteButton::onPressedMoveOutside()
//{
//	if (m_pPressedMoveOutsideHandleObject)
//	{
//		(m_pPressedMoveOutsideHandleObject->*m_pPressedMoveOutsideHandle)(this);
//	}
//}

//void SpriteButton::onPressedUp()
//{
//	if (!m_bSpriteMode)
//		m_pSprite->setDisplayFrame(m_pFrameNormal);
//
//	if (m_pPressedUpHandleObject)
//	{
//		(m_pPressedUpHandleObject->*m_pPressedUpHandle)(this);
//	}
//}

//void SpriteButton::onPressedCancel()
//{
//	m_bTouched = false;
//	if (!m_bSpriteMode)
//		m_pSprite->setDisplayFrame(m_pFrameNormal);
//	setScale(1.0);
//}

//void SpriteButton::setZoomInOnHighlight(bool var)
//{
//	m_bZoomInOnHighlight = var;
//}


//bool SpriteButton::getZoomInOnHighlight()
//{
//	return m_bZoomInOnHighlight;
//}

//void SpriteButton::setEnable(bool var)
//{
//	if (m_bEnable == var)
//		return;
//	m_bEnable = var;
//	if (m_bEnable)
//	{
//		if (!m_bSpriteMode)
//			m_pSprite->setDisplayFrame(m_pFrameNormal);
//		setColor(Color3B::WHITE);
//
//
//	}
//	else
//	{
//		if (m_pFrameDisable)
//		{
//			if (!m_bSpriteMode)
//				m_pSprite->setDisplayFrame(m_pFrameDisable);
//		}
//		else
//		{
//			Color3B color = m_cUnableColor;
//			setColor(color);
//		}
//	}
//}

//bool SpriteButton::getEnable()
//{
//	return m_bEnable;
//}

//
//void SpriteButton::setColor(Color3B color)
//{
//	m_tColor = color;
//
//	Object* child;
//	//Array* children = this->getChildren();
//
//	//CCARRAY_FOREACH(children, child)
//	//{
//	//	RGBAProtocol* pNode = dynamic_cast<RGBAProtocol*>(child);
//	//	if (pNode)
//	//	{
//	//		pNode->setColor(m_tColor);
//	//	}
//	//}
//}

//const Color3B& SpriteButton::getColor(void)
//{
//	return m_tColor;
//}

//void SpriteButton::setOpacity(GLubyte opacity)
//{
//	m_cOpacity = opacity;
//	Object* child;
//	Array* children = getChildren();
//	CCARRAY_FOREACH(children, child)
//	{
//		RGBAProtocol* pNode = dynamic_cast<RGBAProtocol*>(child);
//		if (pNode)
//		{
//			pNode->setOpacity(opacity);
//		}
//	}
//}
//
//GLubyte SpriteButton::getOpacity()
//{
//	return m_cOpacity;
//}

//void SpriteButton::setOpacityModifyRGB(bool bOpacityModifyRGB)
//{
//	m_bIsOpacityModifyRGB = bOpacityModifyRGB;
//	Object* child;
//	Array* children = getChildren();
//	CCARRAY_FOREACH(children, child)
//	{
//		RGBAProtocol* pNode = dynamic_cast<RGBAProtocol*>(child);
//		if (pNode)
//		{
//			pNode->setOpacityModifyRGB(bOpacityModifyRGB);
//		}
//	}
//}

//bool SpriteButton::isOpacityModifyRGB()
//{
//	return m_bIsOpacityModifyRGB;
//}

//void SpriteButton::setNormalFrame(SpriteFrame* frame)
//{
//	CC_SAFE_RETAIN(frame);
//	CC_SAFE_RELEASE_NULL(m_pFrameNormal);
//	m_pFrameNormal = frame;
//	m_pSprite->setDisplayFrame(m_pFrameNormal);
//}

//SpriteFrame* SpriteButton::getNormalFrame()
//{
//	return m_pFrameNormal;
//}


//void SpriteButton::setHighlightFrame(SpriteFrame *frame)
//{
//	CC_SAFE_RETAIN(frame);
//	CC_SAFE_RELEASE_NULL(m_pFrameHighlight);
//	m_pFrameHighlight = frame;
//}

//CCSpriteFrame* SpriteButton::getHighlightFrame()
//{
//	return m_pFrameHighlight;
//}
//
//void SpriteButton::setDisableFrame(SpriteFrame *frame)
//{
//	CC_SAFE_RETAIN(frame);
//	CC_SAFE_RELEASE_NULL(m_pFrameDisable);
//	m_pFrameDisable = frame;
//}
//
//CCSpriteFrame* SpriteButton::getDisableFrame()
//{
//	return m_pFrameDisable;
//}
//
//bool SpriteButton::isAllParentVisible()
//{
//	Node* parent = getParent();
//	while (parent)
//	{
//		if (parent->isVisible())
//		{
//			parent = parent->getParent();
//		}
//		else
//		{
//			return false;
//		}
//	}
//	return true;
//}

//void SpriteButton::setUnableColor(Color3B color)
//{
//	m_cUnableColor = color;
//}

//Color3B SpriteButton::getUnableColor()
//{
//	return m_cUnableColor;
//}

//bool SpriteButton::isSpriteMode()
//{
//	return m_bSpriteMode;
//}