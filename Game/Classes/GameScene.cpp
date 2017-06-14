#include "GameScene.h"

#include "CallLandlordLayer.h"
#include "Common.h"
#include "GameController.h"
#include "HeadImageLayer.h"
#include "OverLayer.h"
#include "PokerLayer.h"
#include "ReadyStateLayer.h"
#include "ui/UIScale9Sprite.h"
#include "Util.h"

cocos2d::Scene* GameScene::createScene()
{
	auto scene = cocos2d::Scene::create();
	auto layer = GameScene::create();
	scene->addChild(layer);
		
	return scene;
}

bool GameScene::init()
{
	if (!cocos2d::Layer::init())
	{
		return false;
	}

	if (initView() == false)
	{
		return false;
	}

	if (initContent() == false)
	{
		return false;
	}

	//���������������ΪScene��û����ȫ��ʼ�������µ�ǰRunningScene
	//���Ǹ�Scene�����³���
	//this->scheduleOnce(schedule_selector(GameScene::start), 1.0f);

	return true;
}

bool GameScene::initView()
{
	auto winSize = cocos2d::Director::getInstance()->getWinSize();

	//��Ϸ��������
	auto sceneBg = cocos2d::ui::Scale9Sprite::create(GAME_SCENE_BG);
	auto sceneBgSize = sceneBg->getContentSize();
	sceneBg->setCapInsets(cocos2d::Rect(sceneBgSize.width / 4, sceneBgSize.height / 4,
		sceneBgSize.width / 4, sceneBgSize.height / 4));
	sceneBg->setContentSize(cocos2d::Size(winSize));
	sceneBg->setPosition(cocos2d::Point(winSize / 2));
	this->addChild(sceneBg);

	//��Ϸ�������ܱ߿�
	auto sceneBorder = cocos2d::ui::Scale9Sprite::create(GAME_SCENE_BORDER);
	auto sceneBorderSize = sceneBorder->getContentSize();
	sceneBorder->setCapInsets(cocos2d::Rect(sceneBorderSize.width / 4, sceneBorderSize.height / 4,
		sceneBorderSize.width / 4, sceneBorderSize.height / 4));
	sceneBorder->setContentSize(cocos2d::Size(winSize.width, winSize.height));
	sceneBorder->setPosition(cocos2d::Point(winSize / 2));
	this->addChild(sceneBorder);

	//��Ϸ�������Ͻ�Ҷ��
	auto leftLeaf = cocos2d::Sprite::create(GAME_SCENE_LEFT_LEAF);
	leftLeaf->setScale(MIDDLE_SCALE);
	leftLeaf->setAnchorPoint(cocos2d::Vec2::ANCHOR_TOP_LEFT);
	leftLeaf->setPosition(cocos2d::Point(0, winSize.height));
	this->addChild(leftLeaf);

	//��Ϸ�������Ͻ�Ҷ��
	auto rightLeaf = cocos2d::Sprite::create(GAME_SCENE_RIGHT_LEAF);
	rightLeaf->setScale(MIDDLE_SCALE);
	rightLeaf->setAnchorPoint(cocos2d::Vec2::ANCHOR_TOP_RIGHT);
	rightLeaf->setPosition(cocos2d::Point(winSize.width, winSize.height));
	this->addChild(rightLeaf);

	return true;
}

bool GameScene::initContent()
{
	//ע�����ͷ�����Ϣ
	cocos2d::NotificationCenter::getInstance()->addObserver(this,
		callfuncO_selector(GameScene::createHeadImageLayerCallback),
		CREATE_HEADIMAGE_LAYER, nullptr);

	//ע������ͷ�����Ϣ
	cocos2d::NotificationCenter::getInstance()->addObserver(this,
		callfuncO_selector(GameScene::destroyHeadImageLayerCallback),
		DESTROY_HEADIMAGE_LAYER, nullptr);

	//ע�����׼������Ϣ
	cocos2d::NotificationCenter::getInstance()->addObserver(this,
		callfuncO_selector(GameScene::createReadyLayerCallback),
		CREATE_READY_LAYER, nullptr);

	//ע������׼������Ϣ
	cocos2d::NotificationCenter::getInstance()->addObserver(this,
		callfuncO_selector(GameScene::destroyReadyLayerCallback),
		DESTROY_READY_LAYER, nullptr);

	//ע������˿˲���Ϣ
	cocos2d::NotificationCenter::getInstance()->addObserver(this,
		callfuncO_selector(GameScene::createPokerLayerCallback),
		CREATE_POKER_LAYER, nullptr);

	//ע�������˿˲���Ϣ
	cocos2d::NotificationCenter::getInstance()->addObserver(this,
		callfuncO_selector(GameScene::destroyPokerLayerCallback),
		DESTROY_POKER_LAYER, nullptr);

	//ע����ӽе�������Ϣ
	cocos2d::NotificationCenter::getInstance()->addObserver(this,
		callfuncO_selector(GameScene::createCallLandlordLayerCallback),
		CREATE_CALL_LANDLORD_LAYER, nullptr);

	//ע�������˿˲���Ϣ
	cocos2d::NotificationCenter::getInstance()->addObserver(this,
		callfuncO_selector(GameScene::destroyCallLandlordLayerCallback),
		DESTROY_CALL_LANDLORD_LAYER, nullptr);

	//ע����ӽ�������Ϣ
	cocos2d::NotificationCenter::getInstance()->addObserver(this,
		callfuncO_selector(GameScene::createOverLayerCallback),
		CREATE_OVER_LAYER,
		nullptr);

	//ע�����ٽ�������Ϣ
	cocos2d::NotificationCenter::getInstance()->addObserver(this,
		callfuncO_selector(GameScene::destroyOverLayerCallback),
		DESTROY_OVER_LAYER,
		nullptr);

	return true;
}

void GameScene::createHeadImageLayerCallback(cocos2d::Ref*)
{
	//����ͷ���
	HeadImageLayer::createLayer();
}

void GameScene::destroyHeadImageLayerCallback(cocos2d::Ref*)
{
	//����ͷ���
	HeadImageLayer::destroyLayer();
}

void GameScene::createReadyLayerCallback(cocos2d::Ref*)
{
	//����׼����
	ReadyStateLayer::createLayer();
}

void GameScene::destroyReadyLayerCallback(cocos2d::Ref*)
{
	//����׼����
	ReadyStateLayer::destroyLayer();
}

void GameScene::createPokerLayerCallback(cocos2d::Ref*)
{
	//�����˿˲�
	PokerLayer::createLayer();
}

void GameScene::destroyPokerLayerCallback(cocos2d::Ref*)
{
	//�����˿˲�
	PokerLayer::destroyLayer();
}

void GameScene::createCallLandlordLayerCallback(cocos2d::Ref*)
{
	//�����е�����
	CallLandlordLayer::createLayer();
}

void GameScene::destroyCallLandlordLayerCallback(cocos2d::Ref*)
{
	//���ٽе�����
	CallLandlordLayer::destroyLayer();
}

void GameScene::createOverLayerCallback(cocos2d::Ref*)
{
	//����������
	OverLayer::createLayer();
}

void GameScene::destroyOverLayerCallback(cocos2d::Ref*)
{
	//���ٽ�����
	OverLayer::destroyLayer();
}

