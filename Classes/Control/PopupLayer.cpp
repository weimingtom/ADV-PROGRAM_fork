//
//  PopuLayer.cpp
//  Karma
//
//  Created by SunnyRx on 16/7/31.
//
//

#include "PopupLayer.hpp"

PopupLayer::PopupLayer(const std::string &backgroundImage)
{
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    //初始化背景图层
    _backgroundLayer = LayerColor::create(Color4B(0, 0, 0, 64));
    this->addChild(_backgroundLayer);
    //初始化背景框
    _backgroundSprite = ui::Scale9Sprite::create(backgroundImage);
    _backgroundSprite->cocos2d::Node::setAnchorPoint(Vec2::ANCHOR_MIDDLE);
    _backgroundSprite->setPosition(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y);
    this->addChild(_backgroundSprite);
    //初始化按钮数量
    _buttonCounter = 0;
    //初始化容器
    _buttonList = new std::vector<PopupButton*>;
    //初始化Y值
    _buttonPositionY = _backgroundSprite->getContentSize().height / 2 - _backgroundSprite->getContentSize().height / 3;
    log("_backgroundSprite.height = %f, _buttonPositionY = %d", _backgroundSprite->getContentSize().height, _buttonPositionY);
    //初始化Menu
    _buttonMenu = Menu::create();
    _buttonMenu->setPosition(0, _buttonPositionY);
    this->addChild(_buttonMenu);
    //初始化对话框文字
    _popupTextFont = DEFAULT_TEXT_FONT;
    _popupTextSize = DEFAULT_TEXT_SIZE;
    _popupTextPositionX = _backgroundSprite->getContentSize().width / 2;
    _popupTextPositionY = (_backgroundSprite->getContentSize().height / 3) * 2;
    _popupText = Label::createWithSystemFont("Are you sure?", _popupTextFont, _popupTextSize);
    _popupText->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
    _popupText->setPosition(_popupTextPositionX, _popupTextPositionY);
    _backgroundSprite->addChild(_popupText);
    //阻断触碰事件
    auto *backgroundTouch = EventListenerTouchOneByOne::create();
    backgroundTouch->onTouchBegan = [=] (Touch *t, Event *e)
    {
        return true;
    };
    backgroundTouch->onTouchEnded = [=] (Touch *t, Event *e)
    {
        log("Background touched.");
        //碰到对话框以外的区域就释放整个层
        this->runAction(Sequence::create(CallFunc::create(CC_CALLBACK_0(Node::removeFromParent, this)), NULL));
    };
    backgroundTouch->setSwallowTouches(true);
    _backgroundLayer->getEventDispatcher()->addEventListenerWithSceneGraphPriority(backgroundTouch, _backgroundLayer);
    
    auto *backgroundSpriteTouch = EventListenerTouchOneByOne::create();
    backgroundSpriteTouch->onTouchBegan = [=] (Touch *t, Event *e)
    {
        if (_backgroundSprite->getBoundingBox().containsPoint(this->convertTouchToNodeSpace(t)))
        {
            return true;
        }
        return false;
    };
    backgroundSpriteTouch->setSwallowTouches(true);
    _backgroundSprite->getEventDispatcher()->addEventListenerWithSceneGraphPriority(backgroundSpriteTouch, _backgroundSprite);
}

PopupLayer::~PopupLayer()
{
    delete(_buttonList);
}

PopupLayer* PopupLayer::create(const std::string &backgroundImage)
{
    PopupLayer* popupLayer = new PopupLayer(backgroundImage);
    return popupLayer;
}

void PopupLayer::addButton(const std::string &normalImage, std::function<void (Ref *)> &callback)
{
    addButton(normalImage, normalImage, normalImage,callback);
}

void PopupLayer::addButton(const std::string &normalImage, const std::string &selectedImage, std::function<void (Ref *)> &callback)
{
    addButton(normalImage, selectedImage, selectedImage, callback);
}

void PopupLayer::addButton(const std::string &normalImage, const std::string &touchImage, const std::string &selectedImage, std::function<void (Ref *)> &callback)
{
    //待实现
}

void PopupLayer::addLabelButton(const std::string &buttonText, const ccMenuCallback& callback)
{
    //创建MenuItemFont
    auto button = MenuItemFont::create(buttonText, callback);
    //给这个按钮绑定一个事件，触发后便释放整个图层
    auto *buttonTouch = EventListenerTouchOneByOne::create();
    
    buttonTouch->onTouchBegan = [=] (Touch *t, Event *e)
    {
        //log("button began touched.");
        if (button->getBoundingBox().containsPoint(_backgroundSprite->convertTouchToNodeSpace(t)))
        {
            //log("button touched.");
            return true;
        }
        return false;
    };
    
    buttonTouch->onTouchEnded = [=] (Touch *t, Event *e)
    {
        
        //释放整个层
        //log("button end touched.");
        if (button->getBoundingBox().containsPoint(_backgroundSprite->convertTouchToNodeSpace(t)))
        {
            //log("button touched.");
            this->runAction(Sequence::create(CallFunc::create(CC_CALLBACK_0(Node::removeFromParent, this)), NULL));
        }
    };
    //buttonTouch->setSwallowTouches(true);
    button->getEventDispatcher()->addEventListenerWithSceneGraphPriority(buttonTouch, button);
    //创建PopupButton
    auto popupButton = new PopupButton;
    popupButton->button = button;
    popupButton->buttonType = PopupButton::ButtonType::FONT;
    //增加按钮输将并添加按钮到列表中
    _buttonCounter++;
    _buttonList->push_back(popupButton);
    //排列按钮的位置
    arrange();
}

void PopupLayer::arrange()
{
    //把对话框X轴分成(按钮数量+1)份，这就是按钮之间的间隔
    auto tempX = _backgroundSprite->getContentSize().width / (_buttonCounter+1);
    _buttonMenu->removeFromParent();
    _buttonMenu->removeAllChildren();
    //auto buttonVector = new std::vector<MenuItem*>;
    Vector<MenuItem*> buttonVector;
    for (int i = 0; i < _buttonCounter; i++)
    {
        _buttonList->at(i)->button->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
        _buttonList->at(i)->button->setPosition(tempX * (i+1), _buttonPositionY);
        //log("Button %d = [%f,%d]",i,tempX * (i+1), _buttonPositionY);
        buttonVector.pushBack(_buttonList->at(i)->button);
    }
    _buttonMenu = Menu::createWithArray(buttonVector);
    _buttonMenu->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
    _buttonMenu->setPosition(0, 0);
    _backgroundSprite->addChild(_buttonMenu);
}

void PopupLayer::setString(const std::string &text)
{
    _popupText->setString(text);
}