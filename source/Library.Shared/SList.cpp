#include "Pch.h"
#include "SList.h"

namespace Library
{
	SList::SList() : mData(0)
	{}

	void SList::Insert(int data)
	{
		mData = data;
	}

	int SList::Pop() const
	{
		return mData;
	}
}
