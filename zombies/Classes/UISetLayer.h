#ifndef UISETLAYER_H
#define UISETLAYER_H
#include "cocos2d.h"
#include <iostream>

USING_NS_CC;


class UIMainMenuLayer;

class UISetLayer : public Layer
{
private:
	

	//CC_SYNTHESIZE(bool, m_bShowEquipJiaTL, m_bShowEquipJiaTL);
	//CC_SYNTHESIZE(bool, m_bUpdateUIStore, m_bUpdateUIStore);
	//CC_SYNTHESIZE(bool, m_bIsShowGameTask, m_bIsShowGameTask);
	//CC_SYNTHESIZE(bool, m_bStoreBtnEnable, m_bStoreBtnEnable);
	//CC_SYNTHESIZE(double, m_dLastStackTime, LastStackTime);
	//CC_SYNTHESIZE(bool, m_bStopSp01Move, StopSp01Move);


public:
	static UISetLayer* shared();
	static void purgeShared();

	//void updateTime(float dt);

	int userID;
	bool shuaxin;
	//void getUserID(int ID);
	std::string _IMEI;
	std::string _IMSI;
	std::string _ICCID;
	std::string FileMD5;
	std::string SingelCode;
	/*
		void setIMEI(std::string str);
		void setIMSI(std::string str);
		void setICCID(std::string str);
		void setFileMD5(std::string str);
		void setSingnelCode(std::string str);*/

	UIMainMenuLayer *UIMM;
	/*void setUIMainMenuLayer(UIMainMenuLayer *uim);
	void replaceToMainMenu();
	void replaceToGaming();
	void replaceToPause();
	void replaceToUIStore();
	void replaceToLoading();
	void runMainMenu();
	void replaceToBigLevelUI();
	void replaceToLittleLevelUI();
	void runBeforeGameCG_1();
	void replaceToGameCG_1();
	void replaceToGameCG_2();
	void replaceToGameCG_3();
	void replaceToGameCG_4();*/

	/*void sendXinxi();
	void onHttpRequestCompleted(Ref* sender, void *data);

	void runHelloWorld();
	void runUILoadingGameLayer();*/
	//static Scene* makeScene(Layer *layer);

	/*void payforBuy(int index);
	void payOrderSdk(int index);
	char payname[10];
	void iapResultSuccess(int shopIndex);
	void iapResultYiJie(int shopIndex);
	void iapResultFailed(int shopIndex);
	void iapResultCancel(int shopIndex);
	void getComJhtcCf(std::string name);
	void requestMusic(bool b);
	void exitGame();
	void retainCCSpriteFrameCache_Game2UI();
	void releaseAndRetainCCSpriteFrameCache_UI2Game();
	void releaseAndRetainCCSpriteFrameCache_Game2UI();
	void retainCGCCSpriteFrameCache();
	void updateBoom();

	void OpenWindows();*/

	int m_nLianJiNum;
	float PAYID_BUYJIATELIN_TIME;
	float PAYID_BUYREBIRTH_TIME;
	float PAYID_BUY35000COINS_TIME;
	float PAYID_BUG160000COINS_TIME;
	float PAYID_BUYGIFTCHOUJIANG_TIME;
	float PAYID_BUY60DIAMOND_TIME;
	float PAYID_BUY240DIAMOND_TIME;
	float PAYID_BUYXIJIN_TIME;
	float PAYID_BOMB_TIME;
	float PAYID_FROZON_TIME;
	float PAYID_BUYCOINSFULI_TIME;
	float PAYID_BUY240DIAMOND_time;
	float PAYID_BUYGIFTJINGBAO_TIME;
	float PAYID_BUYGIFTZHANHUO_TIME;


	bool buyType;
	bool TanChuBoom;
	bool TanchuBing;
	bool BossFirstAtt;
	bool TanchuFuhuo;
	bool butFuhuoType;
	bool isErciTan;

	bool sdkStype_one;
	bool sdkStype_two;
	bool sdkStype_three;
	bool sdkStype_four;
	bool buyStype;
	int buyOrder;
	bool Validata;
	bool BackPoint;
	int sdkOneOrder;
	int sdkTworder;
	int sdkThreeOrder;
	int sdkFourOrder;
	int sdkFiveOrder;
	int sdkOrderArr[5];
	float anKouSdk_time;

	int m_nCurGameView;
	int m_nShowUIStoreType;


	//void setWinSpriteFromHeroHurt(Sprite* node, int hurtNum);

	int m_nGamingMode;

	int bigLevelInfo[3][6][2];

	int difficultyLevelInfo[3][1];

	int m_nCurBigLevelID;

	int m_nCurSmallLevelID;

	int m_nCurChooseDifficult;

	int smallLevelInfo[3][6][8][3];

	int openWIndow;

	int playerInfoAll[10];

	int goodsInfo[6];

	int giftInfo[4];

	long m_lLastGetTaskDayTime;

	int todayTask[5][6];

	int playInfo[2];

	bool m_bHasGiveLianTongGift;

	void update(float dt);

	/*bool isLittleLevelUnClock(int difficulty, int bigLevelID, int smallLevelID);

	void unClockLittleLevel(int difficulty, int bigLevelID, int smallLevelID);

	void setLettleLevelHeroHurtNum(int difficulty, int bigLevelID, int smallLevelID, int info);

	int getHeroHurtNumOfLittleLevel(int difficulty, int bigLevelID, int smallLevelID);

	void unClockBigLevel(int difficulty, int bigLevelID);

	void unClockDifficultLevel(int difficulty);

	bool isDifficultLevelUnClock(int difficulty);

	bool isBigLevelUnClock(int difficulty, int bigLevelID);

	int getNearestBigLevelID(int difficulty);

	int getNearestSmallLevelID(int difficulty, int bigLevelID);

	bool isLittleLevelHasGiveJiangli(int difficulty, int bigLevelID, int smallLevelID);

	void setLittleLevelHasGiveJiangli(int difficulty, int bigLevelID, int smallLevelID);
*/
	//float getValueOfGunAttribute(GunType guntype, int attribute, int secondAttribute);

	//const CString* getValueOfGunAttributeCString(GunType guntype, int attribute, int secondAttribute);

	//int getGradeOfGunAttribute(GunType guntype, int attribute);

	//void updateGunAttribute(GunType guntype, int attribute);

	//void paddingGunAttribute();


	//void alterCoinsNum(int num, bool record);
	//void alterZuanShiNum(int num);

	//void unClockGunNeedLevelM(GunType type, int *diff, int *bigL, int*smallL);

private:

	UISetLayer();
	~UISetLayer();
	static UISetLayer *m_pSingleInstance;
	//void initGameData();
	//void unClockAndBuyAllGun();
	//void unClockAllLevel();


};


//#define CHECK_IAP_BTN \
//if (!UISetLayer::shared()->getm_bStoreBtnEnable() ) \
//{ \
//	return;\
//}else\
//{\
//	UISetLayer::shared()->setm_bStoreBtnEnable(false);\
//}


#endif // !UISETLAYER_H
