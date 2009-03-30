//
// DateField.h
//
// $Id: //poco/Main/WebWidgets/include/Poco/WebWidgets/DateField.h#4 $
//
// Library: WebWidgets
// Package: Controls
// Module:  DateField
//
// Definition of the DateField class.
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


#ifndef WebWidgets_DateField_INCLUDED
#define WebWidgets_DateField_INCLUDED


#include "Poco/WebWidgets/TextField.h"


namespace Poco {

	class DateTime;

namespace WebWidgets {


class WebWidgets_API DateField: public TextField
	/// A DateField picker
{
public:
	typedef Poco::AutoPtr<DateField> Ptr;

	DateField();
		/// Creates an anonymous DateField  with a simple Y-m-d format

	DateField(const std::string& name);
		/// Creates a named DateField  with a simple Y-m-d format

	explicit DateField(const char* pName);
		/// Creates a named DateField  with a simple Y-m-d format

	void setFormat(const std::string& dateFormat);
		/// Sets a format string as defined in Poco::DateFormat, Poco::DateFormatter

	const std::string& getFormat() const;
		/// Returns the format

	void setDate(const Poco::DateTime& dt);
		/// Sets the date

	const Poco::DateTime& getDate() const;
		/// returns the date if set, otherwise an exception, use getValue().empty() to check if it is valid

protected:
	DateField(const std::string& name, const std::type_info& type);
		/// Creates a DateField and assigns it the given name.


	explicit DateField(const char* pName, const std::type_info& type);
		/// Creates a DateField and assigns it the given name.

	DateField(const std::type_info& type);
		/// Creates a DateField.

	~DateField();
		/// Destroys the DateField.
};


} } // namespace Poco::WebWidgets


#endif // WebWidgets_DateField_INCLUDED
