#pragma once

#include <cstdint>
#include <functional>

namespace Library
{
	template <typename T>
	class Vector
	{
	public:
		Vector();
		Vector(const Vector<T>&);
		Vector<T>& operator=(const Vector<T>&);
		Vector<T>& operator[](const Vector<T>&);

		void PushBack(const T& data);
		void PopBack();

		Vector<T>& operator==(const Vector<T>&);
		Vector<T>& operator!=(const Vector<T>&);

		void Reserve(std::function<std::uint32_t(std::uint32_t, std::uint32_t)>);
		void Resize();

		std::uint32_t Size() const;
		bool IsEmpty() const;
		~Vector();
	private:
		T* buffer;
		std::uint32_t size;
		std::uint32_t capacity;
	};
}

#include "Vector.inl"
