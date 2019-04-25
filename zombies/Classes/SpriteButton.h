#pragma once
#include "cocos2d.h"

#ifndef SPRITEBUTTON_H
#define SPRITEBUTTON_H




USING_NS_CC;
class SpriteButton :public Layer, public RGBAProtocol
{
public:
	SpriteButton();
	virtual ~SpriteButton();
	virtual bool init();
	static SpriteButton* createWithFrame(SpriteFrame * frameNormal, SpriteFrame* frameHightlight, SpriteFrame* frameDisable);
	static SpriteButton* createWithSprite(Sprite* sprite);
	CREATE_FUNC(SpriteButton);

	//virtual void registerWithTouchDispatcher();
	virtual bool onTouchBegan(Touch *touch, Event *pEvent);
	virtual void onTouchMoved(Touch *touch, Event *pEvent);
	virtual void onTouchEnded(Touch *touch, Event *pEvent);
	virtual void onTouchCancelled(Touch *touch, Event *pEvent);

	virtual void setPressDownHandler(Ref* object, SEL_MenuHandler handle);
	virtual void setPressUpHandler(Ref* object, SEL_MenuHandler handle);
	virtual void setPressMoveInsideHandler(Ref* object, SEL_MenuHandler handle);
	virtual void setPressMoveOutsideHandler(Ref* object, SEL_MenuHandler handle);

	CC_SYNTHESIZE(GLubyte, m_cOpacity, Opacity);
	CC_PROPERTY_PASS_BY_REF(Color3B, m_tColor, Color);
	//CC_PROPERTY_PASS_BY_REF(Color3B, m_tColor, Color);

	bool m_bIsOpacityModifyRGB;
	bool isOpacityModifyRGB();
	void setOpacityModifyRGB(bool bOpacityModifyRGB);

	virtual void setNormalFrame(SpriteFrame* frame);
	virtual SpriteFrame* getNormalFrame();

	virtual void setHighlightFrame(SpriteFrame* frame);
	virtual SpriteFrame* getHighlightFrame();

	virtual void setDisableFrame(SpriteFrame* frame);
	virtual SpriteFrame* getDisableFrame();

	CC_SYNTHESIZE(bool, m_bZoomInOnHighlight, ZoomInOnHighlight);

	virtual void cleanup();

	CC_SYNTHESIZE(bool, m_bEnable, Enable);
	CC_SYNTHESIZE(Color3B, m_cUnableColor, UnableColor);

protected:

	virtual void onPressedDown();
	virtual void onPressedUp();
	virtual void onPressedMoveInside();
	virtual void onPressedMoveOutside();
	virtual void onPressedCancel();

	virtual bool isAllParentVisible();

	SEL_MenuHandler m_pPressedDownHandle;
	Ref* m_pPressedDownHandleObject;

	SEL_MenuHandler  m_pPressedUpHandle;
	Ref* m_pPressedUpHandleObject;

	SEL_MenuHandler m_pPressedMoveInsideHandle;
	Ref* m_pPressedMoveInsideHandleObject;

	SEL_MenuHandler m_pPressedMoveOutsideHandle;
	Ref* m_pPressedMoveOutsideHandleObject;

	SEL_MenuHandler m_pPressedCancelHandle;
	Ref* m_pPressedCancelHandleObject;

	bool m_bTouched;
	SpriteFrame* m_pFrameNormal;
	SpriteFrame* m_pFrameHighlight;
	SpriteFrame* m_pFrameDisable;
	Sprite* m_pSprite;
	bool m_bSpriteMode;

	bool isSpriteMode();
	bool isTouchInside(Touch* pTouch);
	virtual void initWithFrame(SpriteFrame * frameNormal, SpriteFrame* frameHightlight, SpriteFrame* frameDisable);
	virtual void initWithSprite(Sprite* sprite);

	

};

#endif // !SpriteButton_h

