//
// Buffer.h
//
// $Id: //poco/1.4/Foundation/include/Poco/Buffer.h#2 $
//
// Library: Foundation
// Package: Core
// Module:  Buffer
//
// Definition of the Buffer class.
//
// Copyright (c) 2006, Applied Informatics Software Engineering GmbH.
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


#ifndef Foundation_Buffer_INCLUDED
#define Foundation_Buffer_INCLUDED


#include "Poco/Foundation.h"
#include <cstring>
#include <cstddef>


namespace Poco {


template <class T>
class Buffer
	/// A very simple buffer class that allocates a buffer of
	/// a given type and size in the constructor and
	/// deallocates the buffer in the destructor.
	///
	/// This class is useful everywhere where a temporary buffer
	/// is needed.
{
public:
	Buffer(std::size_t capacity):
		_capacity(capacity),
		_used(capacity),
		_ptr(new T[capacity])
		/// Creates and allocates the Buffer.
	{
	}
	
	~Buffer()
		/// Destroys the Buffer.
	{
		delete [] _ptr;
	}
	
	void resize(std::size_t newCapacity, bool preserveContent = true)
		/// Resizes the buffer. If preserveContent is true,
		/// the content of the old buffer is copied over to the
		/// new buffer. The new capacity can be larger or smaller than
		/// the current one, but it must not be 0.
	{
		poco_assert(newCapacity);

		if (newCapacity > _capacity)
		{
			T* ptr = new T[newCapacity];
			if (preserveContent)
				std::memcpy(ptr, _ptr, newCapacity);

			delete [] _ptr;
			_ptr  = ptr;
			_capacity = newCapacity;
		}
		
		_used = newCapacity;
	}

	std::size_t capacity() const
		/// Returns the allocated memory size.
	{
		return _capacity;
	}

	std::size_t size() const
		/// Returns the used size of the buffer.
	{
		return _used;
	}
	
	T* begin()
		/// Returns a pointer to the beginning of the buffer.
	{
		return _ptr;
	}
	
	const T* begin() const
		/// Returns a pointer to the beginning of the buffer.
	{
		return _ptr;
	}

	T* end()
		/// Returns a pointer to end of the buffer.
	{
		return _ptr + _used;
	}
	
	const T* end() const
		/// Returns a pointer to the end of the buffer.
	{
		return _ptr + _used;
	}
	
	T& operator [] (std::size_t index)
	{
		poco_assert (index < _used);
		
		return _ptr[index];
	}

	const T& operator [] (std::size_t index) const
	{
		poco_assert (index < _used);
		
		return _ptr[index];
	}

private:
	Buffer();
	Buffer(const Buffer&);
	Buffer& operator = (const Buffer&);

	std::size_t _capacity;
	std::size_t _used;
	T*          _ptr;
};


} // namespace Poco


#endif // Foundation_Buffer_INCLUDED
