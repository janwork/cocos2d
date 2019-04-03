#ifndef __MENU_SCENE_H__
#define __MENU_SCENE_H__

#include "cocos2d.h"
#include "AppCommon.h"

class MenuScene :public Layer{
public:
	static Scene* createScene();

	virtual bool init(); 

	void menuBeginCallback(Ref * pSender);
	void menuExitCallback(Ref * pSender);

	CREATE_FUNC(MenuScene);
};


#endif // !1


