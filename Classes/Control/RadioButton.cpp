#include "RadioButton.h"


RadioButton::RadioButton()
	: _selected(0)
{
	_radios = new std::vector<EasyButton*>;
}


RadioButton::~RadioButton()
{
	delete _radios;
}

RadioButton* RadioButton::createRadioButton(EasyButton* i, ...)
{
	auto tmpRadioButton = new RadioButton();
	/*可变参数读取*/
	va_list argPtr; //定义可变参数指针
	va_start(argPtr, i);
	//EasyButton* p = va_arg(argPtr, EasyButton*); //获取
	EasyButton* p = i;
	int subscript = 0;
	while (p != nullptr){
		//dosomething.
		log("subscript = %d", ++subscript);
		p->touchEventWithInt = CC_CALLBACK_0(RadioButton::touchEvent, tmpRadioButton, subscript);
		tmpRadioButton->_radios->push_back(p);
		tmpRadioButton->addChild(p);
		p = va_arg(argPtr, EasyButton*);
	}
	va_end(argPtr);

	return tmpRadioButton;
}

void RadioButton::touchEvent(int i)
{
	log("Test : %d", i);
}
/*
void RadioButton::touchEvent()
{
	log("Test!");
}
*/