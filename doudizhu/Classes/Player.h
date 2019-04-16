#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "cocos2d.h"
#include "SimpleAudioEngine.h"
#include "Poke.h"

USING_NS_CC;

using namespace CocosDenshion;

//����

enum CARD_TYPE
{
	SINGLE_CARD = 1,		//����
	DOUBLE_CARD,			//����
	THREE_CARD,				//3����
	BOMB_CARD,				//ը��
	MISSILE_CARD,			//���
	THREE_ONE_CARD,			//3��1
	THREE_TWO_CARD,			//3��2
	BOMB_TWO_CARD,			//4��2����
	BOME_TWOOO_CARD,		//4��2��
	CONNECT_CARD,			//���� ˳��
	COMPANY_CARD,			//����
	AIRCRAFT_CARD,			//�ɻ�����
	AIRCRAFT_SINGLE_CARD,	//�ɻ�������
	AIRCRAFT_DOUBLE_CARD,	//�ɻ�������
	ERROR_CARD				//��������
};


// ÿ���Ƶ���Ϣ
struct CARDS_DATA{
	std::vector<int>	_cards;
	CARD_TYPE			_type;
	unsigned int		_value;
};

class PokeExhibitionZone : public Sprite{

public:

	static PokeExhibitionZone* create()
	{
		PokeExhibitionZone *sprite = new (std::nothrow) PokeExhibitionZone();
		if (sprite && sprite->init()){
			sprite->autorelease();
			return sprite;
		}

		CC_SAFE_DELETE(sprite);
		return nullptr;
	}


	virtual bool init(){

		if (!Sprite::init()){

			return false;
		}

		return true;
	}

	void chuPai(std::vector<PokeInfo> arrayIndexs)
	{

		if (arrayIndexs.empty()){
			auto label_buchu = Sprite::create("buchu.png");
			addChild(label_buchu);
		}


		for (int i = 0; i < arrayIndexs.size(); ++i)
		{
			auto card = Poke::create(arrayIndexs.at(i));
			card->setScale(0.5);
			this->addChild(card, 100 - arrayIndexs.at(i)._num);
		}

		sortAllChildren();

		int count = _children.size();


		for (int i = 0; i < _children.size(); i++){
			Poke* card = dynamic_cast<Poke*>(_children.at(i));
			if (card != NULL){
				card->setPosition(i * 30, 0);
			}
		}


	}
};


class GameScene;

class Player : public Sprite
{
public:
	static Player* create(std::string name, int score, bool isHero);
	
	virtual bool init(std::string name, int score, bool isHero);

	void updateCards();
	void clearCards();

	void setDiZhu();
	bool getIsDiZhu(){ return _isDiZhu; };

	void FaPai(GameScene * scene, PokeInfo info);
	void ChuPai(GameScene* scene, bool isFollow, CARD_TYPE cardType, unsigned int count, unsigned int value);
	void BuChu();
	void ChaiPai();

	void PlayEffectForCards(std::vector<int> & vec);

	void ShowTipInfo(bool isFollow, CARD_TYPE cardType, unsigned int count, unsigned int value);

	bool IsQiangDiZhu();

	std::string GetName();
	void SetPlayerID(size_t id);
	size_t GetPlayerID();

	int GetScore();

	std::string GetScoreString();

	void Score(int delta_score);

	std::vector<int>& FindFollowCards(CARD_TYPE cardType, unsigned int count, unsigned int value);

	std::vector<int>& FindOutCards();

	std::vector<PokeInfo>& GetOutCards();



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

	std::vector<PokeInfo> _vecPokeInfo;
	std::vector<int>  _vecFindFollowCards;
	std::vector<PokeInfo> _vecOutCards;

	PokeExhibitionZone* _exhibitionZone; 
	std::vector<CARDS_DATA> _allCardGroups;
		
	Label* _labelTipInfo;
	int m_intArray[15];


};

#endif // !__PLAYER_
