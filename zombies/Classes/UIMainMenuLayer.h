#include "cocos2d.h"
#include "SpriteButton.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

USING_NS_CC;
using namespace cocos2d::ui;
using namespace cocostudio;


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

	void onStartGamePressed(Object* pSender);
	void menuCloseCallback(Object* pSender);
	void setGamePressed(Object* obj);
	void aboutPressed(Object* obj);
	void helpPressed(Object* obj);
	void huodongPressed(Object* obj);

	void biaotiActionCallBack(Node* node);
	void playBgDoneCallBack(Node* node);
	void TanChuLibao();


	//SpriteButton* m_pBtnStartGame;
	Button* m_pBtnStartGame;
	//Sprite* m_pBtnStartGame;
	Sprite* playBg;
	Sprite* shou;
	


};