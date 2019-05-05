#include "cocos2d.h"
#include "SpriteButton.h"

USING_NS_CC;

class UIMainMenuLayer : public Layer
{
public:
	UIMainMenuLayer();
	~UIMainMenuLayer();

	virtual bool init();

	static Scene* scene();
	LabelTTF *userid;
	int timeID;

	CREATE_FUNC(UIMainMenuLayer);
	void biaotiActionCallBack(Node* node);
	void playBgDoneCallBack(Node* node);


	SpriteButton* m_pBtnStartGame;
	Sprite* playBg;
	Sprite* shou;
	


};