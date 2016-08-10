//
//  PopuLayer.hpp
//  Karma
//
//  Created by SunnyRx on 16/7/31.
//
//

#ifndef PopupLayer_hpp
#define PopupLayer_hpp

#include "cocos2d.h"
#include "extensions/cocos-ext.h"

USING_NS_CC;

#define DEFAULT_TEXT_FONT "微软雅黑"
#define DEFAULT_TEXT_SIZE 20

struct PopupButton
{
    MenuItem* button;
    enum ButtonType
    {
        FONT,
        IMAGE
    } buttonType;
};

class PopupLayer : public Node
{
    //背景图片，使用九宫格精灵储存
    ui::Scale9Sprite* _backgroundSprite;
    //背景层，可以用于阻挡Event传递
    LayerColor* _backgroundLayer;
    //当前按钮数量
    int _buttonCounter;
    //储存按钮的容器
    std::vector<PopupButton*> *_buttonList;
    //按钮所在的Y值
    int _buttonPositionY;
    //按钮菜单
    Menu* _buttonMenu;
    //对话框文字
    Label* _popupText;
    int _popupTextSize;
    float _popupTextPositionX;
    float _popupTextPositionY;
    std::string _popupTextFont;
    //排列按钮
    void arrange();
    
    PopupLayer(const std::string &backgroundImage);
public:
    ~PopupLayer();
    
    //创建PopupLayer的静态方法
    static PopupLayer* create(const std::string &backgroundImage);
    //无触碰图片和触发图片的按钮添加方式
    void addButton(const std::string &normalImage, std::function<void(Ref*)> &callback);
    //无触碰图片的按钮添加方式
    void addButton(const std::string &normalImage, const std::string &selectedImage, std::function<void(Ref*)> &callback);
    //完整的按钮添加方式
    void addButton(const std::string &normalImage, const std::string &touchImage, const std::string &selectedImage, std::function<void(Ref*)> &callback);
    //Label按钮的添加方式
    void addLabelButton(const std::string &buttonText, const ccMenuCallback& callback);
    //设置文本框内容
    void setString(const std::string &text);
};

#endif /* PopuLayer_hpp */
