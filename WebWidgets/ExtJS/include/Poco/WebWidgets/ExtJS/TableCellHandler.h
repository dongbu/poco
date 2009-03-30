//
// TableCellHandler.h
//
// $Id: //poco/Main/WebWidgets/ExtJS/include/Poco/WebWidgets/ExtJS/TableCellHandler.h#1 $
//
// Library: ExtJS
// Package: Core
// Module:  TableCellHandler
//
// Definition of the TableCellHandler class.
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


#ifndef ExtJS_TableCellHandler_INCLUDED
#define ExtJS_TableCellHandler_INCLUDED


#include "Poco/WebWidgets/ExtJS/Utility.h"
#include "Poco/WebWidgets/ExtJS/AbstractTableCellHandler.h"
#include "Poco/WebWidgets/ExtJS/CellInitializer.h"
#include "Poco/WebWidgets/ImageButtonCell.h"
#include "Poco/WebWidgets/DateFieldCell.h"
#include "Poco/NumberFormatter.h"
#include <vector>
#include <map>
#include <ostream>


namespace Poco {
namespace WebWidgets {
namespace ExtJS {



template <typename Class>
class AbstractFunction
{
public:
	AbstractFunction(){}
	virtual ~AbstractFunction(){}
	virtual void writeData(const Class* pObj, std::ostream& out) const = 0;
	virtual AbstractFunction* clone() const = 0;
};


template <typename T>
inline void write(const T& t, std::ostream& out)
{
	out << t;
}


inline void write(const std::string& t, std::ostream& out)
{
	out << "'" << Utility::safe(t) << "'";
}


template <typename Class, typename Ret>
class Function: public AbstractFunction<Class>
{
public:
	typedef Ret (Class::*Func)() const;

	Function(Func func):_func(func)
	{
	}

	void writeData(const Class* pObj, std::ostream& out) const
	{
		write<Ret>((pObj->*_func)(), out);
	}

	AbstractFunction<Class>* clone() const
	{
		return new Function(_func);
	}

private:
	Func         _func;
};


template <typename Class, typename Ret>
class Function<Class, const Ret&>: public AbstractFunction<Class>
{
public:
	typedef const Ret& (Class::*Func)() const;

	Function(Func func):_func(func)
	{
	}

	void writeData(const Class* pObj, std::ostream& out) const
	{
		write<Ret>((pObj->*_func)(), out);
	}

	AbstractFunction<Class>* clone() const
	{
		return new Function(_func);
	}

private:
	Func         _func;
};


template <typename Class>
class StaticContentFunction: public AbstractFunction<Class>
{
public:
	StaticContentFunction(const std::string& str):_str(str)
	{
	}

	void writeData(const Class*, std::ostream& out) const
	{
		out << _str;
	}

	AbstractFunction<Class>* clone() const
	{
		return new StaticContentFunction(_str);
	}

private:
	std::string _str;
};


template <typename Class, typename Ret>
static AbstractFunction<Class>* function(Ret (Class::*Func)() const)
{
	return new Function<Class, Ret>(Func);
};


template<typename Class>
class TableCellHandler: public AbstractTableCellHandler
	/// TableCellHandler
{
public:
	typedef typename Poco::AutoPtr<TableCellHandler> Ptr;
	typedef typename std::vector<AbstractFunction<Class>*> Functions;
	typedef typename Functions::const_iterator ConstIterator;
	typedef typename Functions::iterator Iterator;
	typedef typename std::map<std::string, StaticContentFunction<Class>* > CodeGen; /// Maps a var name to a string generating function
	typedef typename CodeGen::iterator CodeIterator;
	typedef typename CodeGen::const_iterator CodeConstIterator;

	TableCellHandler(const std::string& className, bool useEditor, bool useRenderer):
		AbstractTableCellHandler(useEditor, useRenderer),
		_className(className)
	{
	}

	void addFixed(const std::string& name, const std::string& fixedContent)
		/// Adds a variable with a given fixed string content. The content will not be wrapped
		/// with ' ' but will be written as is
	{
		_code.insert(std::make_pair(name, new StaticContentFunction<Class>(fixedContent)));
	}

	template <typename Ret>
	void addDynamic(const std::string& name, Ret (Class::*Function)() const)
		/// Adds a variable to be initialized from a Store
		/// This requires us to generate the column as part of the store data array (simply call addData)
		/// and we have to map the varName to an index
	{
		//FIXME: multiple dynamic data support: write val[i]
		static const std::string var("val");
		addData<Ret>(Function);
		addFixed(name, var);
	}

	template <typename Ret>
	void addDynamic(const char* pName, Ret (Class::*Function)() const)
		/// Overload for char*. Forwards to the call using std::string.
	{
		addDynamic<Ret>(std::string(pName), Function);
	}

	void writeData(const void* pAny, std::ostream& out)
		/// Writes the content of the table used to dynamically
		/// initialize Table Columns
	{
		const Class* pObj = reinterpret_cast<const Class*>(pAny);
		ConstIterator it = _functions.begin();
		//FIXME: only one dynamic column
		if (it != _functions.end())
		{
			if (it != _functions.begin())
				out << ",";
			(*it)->writeData(pObj, out);
		}
	}

	void writeDynamicData(std::ostream& out)
	{
		out << "function (val){";
		out << "var tmp = new " << _className;
		out << "({renderTo:'" << Utility::getTmpID() << "'";
		CodeConstIterator it = _code.begin();
		for (; it != _code.end(); ++it)
		{
			out << ",";
			out << it->first << ":";
			it->second->writeData(0, out);
		}
		out << "});";
		out << "var html = Ext.get('tmp').dom.innerHTML;";
		out << "Ext.destroy(tmp);";
		out << "return html;}";
	}

	AbstractTableCellHandler* clone() const
	{
		return new TableCellHandler(*this);
	}

	void init(const Cell* pCell)
	{
		const Class* pClass = dynamic_cast<const Class*>(pCell);
		poco_check_ptr (pClass);
		AbstractTableCellHandler* pHandler = this;
		cellInitializer(pClass, pHandler);
	}

protected:
	virtual ~TableCellHandler()
		/// Destroys the TableCellHandler.
	{
		{
			CodeIterator it = _code.begin();
			for (; it != _code.end(); ++it)
			{
				delete it->second;
			}
		}
		{
			Iterator it = _functions.begin();
			for (; it != _functions.end(); ++it)
			{
				delete *it;
			}
		}
	}

	template <typename Ret>
	void addData(Ret (Class::*Function)() const)
	{
		if (_functions.size() > 0)
			throw NotImplementedException("More than one dynamic column is not supported by table");
		_functions.push_back(function<Class, Ret>(Function));
	}

	TableCellHandler(const TableCellHandler& other):
		AbstractTableCellHandler(other.useEditor(), other.useRenderer()),
		_className(other._className),
		_functions(),
		_code()
	{
		{
			ConstIterator it = other._functions.begin();
			for (; it != other._functions.end(); ++it)
			{
				_functions.push_back((*it)->clone());
			}
		}
		{
			CodeConstIterator it = other._code.begin();
			for (; it != other._code.end(); ++it)
			{
				_code.insert(std::make_pair(it->first, static_cast<StaticContentFunction<Class>* >(it->second->clone())));
			}
		}
	}

private:
	std::string _className;
	Functions   _functions;
	CodeGen     _code;
};



template<>
class TableCellHandler<ImageButtonCell>: public AbstractTableCellHandler
	/// TableCellHandler
{
public:
	TableCellHandler(bool useEditor, bool useRenderer):
		AbstractTableCellHandler(useEditor, useRenderer)
	{
	}


	void addFixed(const std::string& name, const std::string& fixedContent)
		/// Adds a variable with a given fixed string content. The content will not be wrapped
		/// with ' ' but will be written as is
	{
	}


	void writeData(const void* pAny, std::ostream& out)
		/// Writes the content of the table used to dynamically
		/// initialize Table Columns
	{
	}

	void writeDynamicData(std::ostream& out)
	{
		Image::Ptr ptrImg = _pClass->getImage();
		bool hasImg = ptrImg && !ptrImg->getURI().empty();
		bool showTxt = _pClass->getShowText() || !hasImg;

		out << "function (val){return ";
		out << "'<div>";
		out << "<div>";
		out << "<input src=\"' + val + '\"";
		if (!ptrImg->getName().empty())
			out << " name=\"" << ptrImg->getName() << "\"";
		if (ptrImg->getWidth() > 0)
		out << " width=\"" << ptrImg->getWidth() << "\"";
		if (ptrImg->getHeight() > 0)
		out << " height=\"" << ptrImg->getHeight() << "\"";
		std::string tooltip = ptrImg->getToolTip();
		if (!tooltip.empty())
			out << " alt=\"" << Utility::safe(tooltip) << "\"";
		out << " type=\"image\"/>";
		out << "</div>";
		if (showTxt && !_pClass->getValue().empty())
			out << "<div>" << Utility::safe(_pClass->getString()) << "</div>";
		out << "</div>';}";
	}

	AbstractTableCellHandler* clone() const
	{
		return new TableCellHandler(*this);
	}

	void init(const Cell* pCell)
	{
		_pClass = dynamic_cast<const ImageButtonCell*>(pCell);
		poco_check_ptr (_pClass);
	}

protected:
	virtual ~TableCellHandler()
		/// Destroys the TableCellHandler.
	{
	}


	TableCellHandler(const TableCellHandler& other):
		AbstractTableCellHandler(other.useEditor(), other.useRenderer()),
		_pClass(other._pClass)
	{
	}

private:
	const ImageButtonCell* _pClass;
};



template<>
class TableCellHandler<DateFieldCell>: public AbstractTableCellHandler
	/// TableCellHandler
{
public:
	TableCellHandler(bool useEditor, bool useRenderer):
		AbstractTableCellHandler(useEditor, useRenderer)
	{
	}


	void addFixed(const std::string& name, const std::string& fixedContent)
		/// Adds a variable with a given fixed string content. The content will not be wrapped
		/// with ' ' but will be written as is
	{
	}


	void writeData(const void* pAny, std::ostream& out)
		/// Writes the content of the table used to dynamically
		/// initialize Table Columns
	{
	}

	void writeDynamicData(std::ostream& out)
	{
		out << "Ext.util.Format.dateRenderer('";
		const std::string& pocoDateFormat = _pClass->getFormat();
		out << Utility::convertPocoDateToPHPDate(pocoDateFormat) << "')";
	}

	AbstractTableCellHandler* clone() const
	{
		return new TableCellHandler(*this);
	}

	void init(const Cell* pCell)
	{
		_pClass = dynamic_cast<const DateFieldCell*>(pCell);
		poco_check_ptr (_pClass);
	}

protected:
	virtual ~TableCellHandler()
		/// Destroys the TableCellHandler.
	{
	}


	TableCellHandler(const TableCellHandler& other):
		AbstractTableCellHandler(other.useEditor(), other.useRenderer()),
		_pClass(other._pClass)
	{
	}

private:
	const DateFieldCell* _pClass;
};


} } } // namespace Poco::WebWidgets::ExtJS


#endif // ExtJS_TableCellHandler_INCLUDED
