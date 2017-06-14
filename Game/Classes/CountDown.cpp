#include "CountDown.h"

#include "Common.h"

//Ĭ�ϵ���ʱ������15��
const float DEFAULT_COUNTDOWN_TIMEUP = 20.0f;

bool CountDown::init()
{
	_totalSpriteNum = 2;
	_curSpriteIndex = 0;
	_countDownUp = DEFAULT_COUNTDOWN_TIMEUP;//����ʱĬ����15S
	_counting = _countDownUp;

	_callbackFunc = [](){
		cocos2d::log("CountDown Callbackfunc!");
	};

	if (initView() == false)
	{
		return false;
	}

	return true;
}

bool CountDown::initView()
{
	auto spriteFrameCache = cocos2d::SpriteFrameCache::getInstance();
	spriteFrameCache->addSpriteFramesWithFile(COUNTDOWN_IMAGE_LIST, 
		COUNTDOWN_IMAGES);

	_sprite = cocos2d::Sprite::create();
	this->addChild(_sprite, 0);
	auto spriteFrame = spriteFrameCache->getSpriteFrameByName(
		cocos2d::StringUtils::format("clock%d.png", _curSpriteIndex));
	_sprite->setSpriteFrame(spriteFrame);

	_labelAltas = cocos2d::LabelAtlas::create(cocos2d::StringUtils::format("%d", _countDownUp),
		COUNTDOWN_NUMS, 38, 37, '0');
	_labelAltas->setAnchorPoint(cocos2d::Vec2::ANCHOR_MIDDLE);
	this->addChild(_labelAltas, 1);

	return true;
}

void CountDown::countDown(float delta_)
{
	_counting -= delta_;

	//����ʱ<= 5Sʱ����ʾ��˸Ч��
	if (_counting > 0 && _counting <= 5)
	{
		_curSpriteIndex = (_curSpriteIndex + 1) % _totalSpriteNum;
		auto spriteFrameCache = cocos2d::SpriteFrameCache::getInstance();
		_sprite->setSpriteFrame(spriteFrameCache->getSpriteFrameByName(
			cocos2d::StringUtils::format("clock%d.png", _curSpriteIndex)));
	}

	//��ʱʱ���ѵ�
	if (_counting <= 0)
	{
		stopCountDown();
		_callbackFunc();
	}
	else
	{
		_labelAltas->setString(cocos2d::StringUtils::format("%d", (int)_counting));
	}
}

void CountDown::startCountDown()
{
	//��ʾ��ʱ��
	this->setVisible(true);

	//ÿ����ʾǰ��Ҫ���ü���
	this->_counting = _countDownUp;

	//ÿ0.2s����һ��countDown�����ڸ��¼�ʱ��Ϣ
	this->schedule(schedule_selector(CountDown::countDown), 0.2f);
}

void CountDown::stopCountDown()
{
	this->setVisible(false);
	//�رռ�ʱschedule
	this->unschedule(schedule_selector(CountDown::countDown));
	//�ָ�Ĭ�ϼ�ʱʱ��
	_countDownUp = DEFAULT_COUNTDOWN_TIMEUP;
}

void CountDown::setCallbackFunc(const std::function<void(void)>& func_)
{
	this->_callbackFunc = func_;
}

void CountDown::setCountDownUpper(float upper_)
{
	this->_countDownUp = upper_;
}
