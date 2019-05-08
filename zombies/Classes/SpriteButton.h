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

	//virtual void registerWithTouchDispatcher();
	virtual bool onTouchBegan(Touch *touch, Event *pEvent);
	virtual void onTouchMoved(Touch *touch, Event *pEvent);
	virtual void onTouchEnded(Touch *touch, Event *pEvent);
	virtual void onTouchCancelled(Touch *touch, Event *pEvent);

	virtual void setPressDownHandler(Ref* object, SEL_MenuHandler handle);
	virtual void setPressUpHandler(Ref* object, SEL_MenuHandler handle);
	virtual void setPressMoveInsideHandler(Ref* object, SEL_MenuHandler handle);
	virtual void setPressMoveOutsideHandler(Ref* object, SEL_MenuHandler handle);

	//RBGAProtocol
	CC_PROPERTY(GLubyte, m_cOpacity, Opacity);
	CC_PROPERTY_PASS_BY_REF(Color3B, m_tColor, Color);


	bool m_bIsOpacityModifyRGB;
	virtual bool isOpacityModifyRGB()const;
	virtual void setOpacityModifyRGB(bool bOpacityModifyRGB);

	virtual GLubyte getDisplayedOpacity() const;
	virtual void updateDisplayedOpacity(GLubyte parentOpacity);
	virtual bool isCascadeOpacityEnabled() const;
	
	virtual const Color3B& getDisplayedColor() const;
	virtual void updateDisplayedColor(const Color3B& parentColor);
	virtual bool isCascadeColorEnabled() const;

	virtual  void setCascadeColorEnabled(bool cascadeColorEnabled);
	virtual  void setCascadeOpacityEnabled(bool cascadeOpacityEnabled);


	// frame getter
	virtual void setNormalFrame(SpriteFrame* frame);
	virtual SpriteFrame* getNormalFrame();
	virtual void setHighlightFrame(SpriteFrame* frame);
	virtual SpriteFrame* getHighlightFrame();
	virtual void setDisableFrame(SpriteFrame* frame);
	virtual SpriteFrame* getDisableFrame();

	CC_PROPERTY(bool, m_bZoomInOnHighlight, ZoomInOnHighlight);

	virtual void cleanup();

	CC_PROPERTY(bool, m_bEnable, Enable);
	CC_PROPERTY(Color3B, m_cUnableColor, UnableColor);

	CREATE_FUNC(SpriteButton);

	

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
	bool m_bSpriteMode;

	bool isSpriteMode();
	bool isTouchInside(Touch* pTouch);
	Sprite* m_pSprite;
	SpriteFrame* m_pFrameNormal;
	SpriteFrame* m_pFrameHighlight;
	SpriteFrame* m_pFrameDisable;
	virtual void initWithFrame(SpriteFrame * frameNormal, SpriteFrame* frameHightlight, SpriteFrame* frameDisable);
	virtual void initWithSprite(Sprite* sprite);

	

};

#endif // !SpriteButton_h

