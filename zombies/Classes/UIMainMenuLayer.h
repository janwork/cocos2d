#include "cocos2d.h"

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



	


};