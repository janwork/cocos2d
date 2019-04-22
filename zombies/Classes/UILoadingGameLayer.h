#include "cocos2d.h"


USING_NS_CC;

class UILoadingGameLayer : public LayerColor
{
public:
	UILoadingGameLayer();
	virtual ~UILoadingGameLayer();
	virtual bool init();

	CREATE_FUNC(UILoadingGameLayer);

	void update(float dt);
	void sendXinXi();
	void onHttpRequestCompleted(Ref *pSender, void *data);


private:
	int m_nLoadingProgress;
	Sprite* bgSp;
};
