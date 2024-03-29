#include "vector.h"
#include "../ds_routines.h"
#include <cstdlib>
#include <cstring>

namespace structures {

	Vector::Vector(size_t size) :
		memory_(calloc(size, 1)),
		size_(size)
	{
	}

	Vector::Vector(const Vector& other) :
		Vector(other.size_)
	{
		memory_ = memcpy(memory_, other.memory_, size_);
	}

	Vector::~Vector()
	{
		free(memory_);
		memory_ = nullptr;
		size_ = 0;
	}

	Structure* Vector::clone() const
	{
		return new Vector(*this);
	}

	size_t Vector::size() const
	{
		return size_;
	}

	Structure & Vector::operator=(const Structure & other)
	{
		if (this != &other)
		{
			*this = dynamic_cast<const Vector&>(other);
		}
		return *this;
	}

	Vector& Vector::operator=(const Vector& other)
	{
		if (this != &other)
		{
			size_ = other.size_;
			memory_ = realloc(memory_, other.size_);
			memory_ = memcpy(memory_, other.memory_, size_);
		}
		return *this;
	}

	bool Vector::operator==(const Vector& other) const
	{
		return this == &other || (size_ == other.size_ && 0 == memcmp(memory_, other.memory_, size_));
		/*if (size_ != other.size_)
			return false;
		return (0 == memcmp(memory_, other.memory_, size_));*/
	}

	byte& Vector::operator[](const int index)
	{
		DSRoutines::rangeCheckExcept(index, size_, "OutOfRangeException");
		return *(static_cast<byte*>(memory_) + index);
	}

	byte Vector::operator[](const int index) const
	{
		DSRoutines::rangeCheckExcept(index, size_, "OutOfRangeException");
		return *(static_cast<byte*>(memory_) + index);
	}

	byte& Vector::readBytes(const int index, const int count, byte& dest)
	{
		DSRoutines::rangeCheckExcept(index + count, size_ + 1, "OutOfRangeException");

		if (count < 0)
			throw std::exception("Count is negative");

		memcpy(&dest, getBytePointer(index), count);
		return dest;
	}

	void Vector::copy(const Vector& src, const int srcStartIndex, Vector& dest, const int destStartIndex, const int length)
	{
		if (length < 0)
			throw std::exception("Length is negative");

		DSRoutines::rangeCheckExcept(srcStartIndex, src.size_, "OutOfRangeException");
		DSRoutines::rangeCheckExcept(destStartIndex, dest.size_, "OutOfRangeException");
		DSRoutines::rangeCheckExcept(srcStartIndex + length, src.size_ + 1, "OutOfRangeException");
		DSRoutines::rangeCheckExcept(destStartIndex + length, dest.size_ + 1, "OutOfRangeException");

		if (src == dest && (srcStartIndex + length <= destStartIndex || destStartIndex + length <= srcStartIndex))
			memmove(src.getBytePointer(destStartIndex), src.getBytePointer(srcStartIndex), length);
		else
			memcpy(dest.getBytePointer(destStartIndex), src.getBytePointer(srcStartIndex), length);
	}

	byte* Vector::getBytePointer(const int index) const
	{
		DSRoutines::rangeCheckExcept(index, size_, "OutOfRangeException");
		return reinterpret_cast<byte*>(memory_) + index;
	}

}