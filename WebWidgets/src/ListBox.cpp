//
// ListBox.cpp
//
// $Id: //poco/Main/WebWidgets/src/ListBox.cpp#2 $
//
// Library: WebWidgets
// Package: Controls
// Module:  ListBox
//
// Copyright (c) 2007, Applied Informatics Software Engineering GmbH.
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


#include "Poco/WebWidgets/ListBox.h"
#include "Poco/WebWidgets/ListBoxCell.h"
#include "Poco/Delegate.h"


namespace Poco {
namespace WebWidgets {


ListBox::ListBox(const std::string& name, const std::type_info& type, ListBoxCell::Ptr ptrCell):
	Control(name, type)
{
	init(ptrCell);
}


ListBox::ListBox(const char* pName, const std::type_info& type, ListBoxCell::Ptr ptrCell):
	Control(std::string(pName), type)
{
	init(ptrCell);
}


ListBox::ListBox(const std::type_info& type, ListBoxCell::Ptr ptrCell):
	Control(type)
{
	init(ptrCell);
}


ListBox::ListBox(const std::string& name, const std::type_info& type):
	Control(name, type)
{
	init();
}


ListBox::ListBox(const char* pName, const std::type_info& type):
	Control(std::string(pName), type)
{
	init();
}


ListBox::ListBox(const std::type_info& type):
	Control(type)
{
	init();
}


ListBox::ListBox(const std::string& name):
	Control(name, typeid(ListBox))
{
	init();
}


ListBox::ListBox(const char* pName):
	Control(std::string(pName), typeid(ListBox))
{
	init();
}
	
	
ListBox::ListBox():
	Control(typeid(ListBox))
{
	init();
}

	
ListBox::~ListBox()
{
}


void ListBox::init()
{
	_pLBCell = new ListBoxCell(this);
	_pLBCell->afterLoad = delegate(*this, &ListBox::fireAfterLoad);
	_pLBCell->beforeLoad += Poco::delegate(this, &ListBox::fireBeforeLoad);
	_pLBCell->rowDeselected += Poco::delegate(this, &ListBox::fireRowDeselected);
	_pLBCell->rowSelected += Poco::delegate(this, &ListBox::fireRowSelected);
	_pLBCell->selectionChanged += Poco::delegate(this, &ListBox::fireSelectionChange);
	setCell(_pLBCell);
}


void ListBox::init(Cell::Ptr ptrCell)
{
	ListBoxCell::Ptr ptr = ptrCell.cast<ListBoxCell>();
	poco_check_ptr (ptr);
	_pLBCell = ptr;
	_pLBCell->afterLoad = delegate(*this, &ListBox::fireAfterLoad);
	_pLBCell->beforeLoad += Poco::delegate(this, &ListBox::fireBeforeLoad);
	_pLBCell->rowDeselected += Poco::delegate(this, &ListBox::fireRowDeselected);
	_pLBCell->rowSelected += Poco::delegate(this, &ListBox::fireRowSelected);
	_pLBCell->selectionChanged += Poco::delegate(this, &ListBox::fireSelectionChange);
	setCell(ptrCell);
}


void ListBox::fireBeforeLoad(std::pair<ListBoxCell*, Poco::Net::HTTPServerResponse*>& data)
{
	beforeLoad(this, data.second);
}


void ListBox::fireAfterLoad(void* pSender)
{
	ListBox* pThis = this;
	afterLoad(this, pThis);
}


void ListBox::fireRowSelected(int& pos)
{
	rowSelected(this, pos);
}


void ListBox::fireRowDeselected(int& pos)
{
	rowDeselected(this, pos);
}


void ListBox::fireSelectionChange(const std::set<int>& sel)
{
	selectionChanged(this, sel);
}


} } // namespace Poco::WebWidgets
