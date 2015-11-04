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
	/*�ɱ������ȡ*/
	va_list argPtr; //����ɱ����ָ��
	va_start(argPtr, i);
	//EasyButton* p = va_arg(argPtr, EasyButton*); //��ȡ
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