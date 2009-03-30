//
// Button.cpp
//
// $Id: //poco/Main/WebWidgets/src/Button.cpp#9 $
//
// Library: WebWidgets
// Package: Controls
// Module:  Button
//
// Copyright (c) 2008, Applied Informatics Software Engineering GmbH.
// and Contributors.
//
// Permission is hereby granted, free of charge, to any person or organization
// obtaining a copy of the software and accompanying documentation covered by
// this license (the "Software") to use, reproduce, display, distribute,
// execute, and transmit the Software, and to prepare derivative works of the
// Software, and to permit third-parties to whom the Software is furnished to
// do so, all subject to the following:
// 
// The copyright notices in the Software and this entire statement, including
// the above license grant, this restriction and the following disclaimer,
// must be included in all copies of the Software, in whole or in part, and
// all derivative works of the Software, unless such copies or derivative
// works are solely in the form of machine-executable object code generated by
// a source language processor.
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE, TITLE AND NON-INFRINGEMENT. IN NO EVENT
// SHALL THE COPYRIGHT HOLDERS OR ANYONE DISTRIBUTING THE SOFTWARE BE LIABLE
// FOR ANY DAMAGES OR OTHER LIABILITY, WHETHER IN CONTRACT, TORT OR OTHERWISE,
// ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
// DEALINGS IN THE SOFTWARE.
//


#include "Poco/WebWidgets/Button.h"
#include "Poco/WebWidgets/ButtonCell.h"


namespace Poco {
namespace WebWidgets {


Button::Button(const std::string& name, const std::type_info& type, Cell::Ptr ptrCell):
	Control(name, type)
{
	init(ptrCell);
}

	
Button::Button(const std::type_info& type, Cell::Ptr ptrCell):
	Control(type)
{
	init(ptrCell);
}


Button::Button(const std::string& name, const std::type_info& type):
	Control(name, type)
{
	init();
}


Button::Button(const char* pName, const std::type_info& type):
	Control(std::string(pName), type)
{
	init();
}

	
Button::Button(const std::type_info& type):
	Control(type)
{
	init();
}


Button::Button(const std::string& name):
	Control(name, typeid(Button))
{
	init();
}


Button::Button(const char* pName):
	Control(std::string(pName), typeid(Button))
{
	init();
}


Button::Button(const std::string& name, const std::string& txt):
	Control(name, typeid(Button))
{
	init();
	setText(txt);
}


Button::Button(const char* pName, const char* pTxt):
	Control(std::string(pName), typeid(Button))
{
	init();
	setText(std::string(pTxt));
}


Button::Button():
	Control(typeid(Button))
{
	init();
}


Button::~Button()
{
}


void Button::init(Cell::Ptr ptrCell)
{
	ButtonCell::Ptr pCell = ptrCell.cast<ButtonCell>();
	poco_check_ptr (pCell);
	pCell->buttonClicked = ajaxDelegate(*this, &Button::fireButtonClicked);
	setCell(pCell);
}


void Button::init()
{
	ButtonCell* pCell = new ButtonCell(this);
	init(pCell);
}


void Button::fireButtonClicked(void* pSender, AjaxParameters& params)
{
	buttonClicked(pSender, params);
}


} } // namespace Poco::WebWidgets
