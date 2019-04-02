#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "cocos2d.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

using namespace CocosDenshion;


class SceneGame;

class Player : public Sprite
{
public:
	static Player* create(std::string name, int score, bool isHero);
	
	virtual bool init(std::string name, int score, bool isHero);

	void updateCards();

	void clearCards();

	void setDiZhu();
	bool getIsDiZhu(){ return _isDiZhu; };

	//void FaPai(SceneGame * scene, PokeInfo info);

	//void  ChuPai(SceneGame* scene, bool isFollow, CARD_TYPE cardType, unsigned int count, unsigned int value);

	void BuChu();

	void ChaiPai();

	void PlayEffectForCards(std::vector<int> & vec);

	//void ShowTipInfo();

	bool IsQiangDiZhu();

	std::string GetName();

	void SetPlayerID(size_t id);

	size_t GetPlayerID();

	int GetScore();

	std::string GetScoreString();

	void Score(int delta_score);




protected:

	size_t _id;
	bool _isHero;
	bool _isDiZhu;

	std::string  _name;
	int  _score;

	Sprite* _cardsManager;
	Label* _labelName;
	Label* _labelScore;
	Label* _labelPokeCount;

	//std::vector<PokeInfo> _vecPokeInfo;
	std::vector<int>  _vecFindFollowCards;
	//std::vector<PokeInfo> _vecOutCards;
		
	Label* _labelTipInfo;
	int m_intArray[15];


};

#endif // !__PLAYER_
