//
// Label.h
//
// $Id: //poco/Main/WebWidgets/include/Poco/WebWidgets/Label.h#7 $
//
// Library: WebWidgets
// Package: Views
// Module:  Label
//
// Definition of the Label class.
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
// works are solely in the form of machine-execuLabel object code generated by
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


#ifndef WebWidgets_Label_INCLUDED
#define WebWidgets_Label_INCLUDED


#include "Poco/WebWidgets/View.h"


namespace Poco {
namespace WebWidgets {


class WebWidgets_API Label: public View
	/// A Label displays static text.
{
public:
	typedef Poco::AutoPtr<Label> Ptr;

	Label();
		/// Creates an anonymous Label.

	Label(const std::string& name);
		/// Creates a Label with the given name.

	explicit Label(const char* pName);
		/// Creates a Label with the given name.

	Label(const std::string& name, const std::string& text);
		/// Creates a Label with the given name and text.

	Label(const char* pName, const char* pText);
		/// Creates a Label with the given name and text.

	// View
	void setText(const std::string& text);

	std::string getText() const;
	
	const std::string& getLabelText() const;
		/// Same as getText but instead of getText which must return a copy
		/// due to the View interface this returns a reference
	
protected:
	Label(const std::string& name, const std::type_info& type);
		/// Creates a Label and assigns it the given name.

	explicit Label(const char* pName, const std::type_info& type);
		/// Creates a Label and assigns it the given name.

	Label(const std::type_info& type);
		/// Creates a Label.

	~Label();
		/// Destroys the Label.

private:
	std::string _text;
};


inline const std::string& Label::getLabelText() const
{
	return _text;
}


} } // namespace Poco::WebWidgets


#endif // WebWidgets_Label_INCLUDED
