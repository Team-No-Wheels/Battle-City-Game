#pragma once

namespace Library
{
	/** A single linked list implementation
	*/
	class SList
	{
	public:
		/** Constructs a new single linked list
		*/
		explicit SList();
		void Insert(int data);
		int Pop() const;
	private:
		int mData;
	};
}
