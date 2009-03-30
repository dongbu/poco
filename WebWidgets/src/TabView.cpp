//
// TabView.cpp
//
// $Id: //poco/Main/WebWidgets/src/TabView.cpp#4 $
//
// Library: WebWidgets
// Package: Views
// Module:  TabView
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


#include "Poco/WebWidgets/TabView.h"


#define NO_VIEW_SELECTED 0xffffffffu


namespace Poco {
namespace WebWidgets {


const ContainerView::ViewVec::size_type TabView::NONE_SELECTED(NO_VIEW_SELECTED);


TabView::TabView():
	ContainerView(typeid(TabView)),
	_activeView(NO_VIEW_SELECTED)
{
}


TabView::TabView(const std::string& name):
	ContainerView(name, typeid(TabView)),
	_activeView(NO_VIEW_SELECTED)
{
}


TabView::TabView(const char* pName):
	ContainerView(std::string(pName), typeid(TabView)),
	_activeView(NO_VIEW_SELECTED)
{
}


TabView::TabView(const std::string& name, const std::type_info& type):
	ContainerView(name, type),
	_activeView(NO_VIEW_SELECTED)
{
}


TabView::TabView(const char* pName, const std::type_info& type):
	ContainerView(std::string(pName), type),
	_activeView(NO_VIEW_SELECTED)
{
}


TabView::TabView(const std::type_info& type):
	ContainerView(type),
	_activeView(NO_VIEW_SELECTED)
{
}


TabView::~TabView()
{
}


void TabView::setActiveView(ContainerView::ViewVec::size_type pos)
{
	if (pos >= size())
		throw RangeException("pos too large");

	_activeView = pos;
}


} } // namespace Poco::WebWidgets
