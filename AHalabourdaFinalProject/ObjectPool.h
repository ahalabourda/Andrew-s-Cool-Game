#pragma once

template<class T>
class ObjectPool
{

public:

	ObjectPool<T>() = delete;
	ObjectPool<T>(int desiredSize);
	~ObjectPool<T>();

	T* GetNextAvailable() const;
	const int GetSize() const { return mSize; }
	T* GetItems() const { return mItems; }

	void Draw() const;
	void Reset();

private:
	const int mSize;

	T* mItems;

};

#include "ObjectPool.inl"