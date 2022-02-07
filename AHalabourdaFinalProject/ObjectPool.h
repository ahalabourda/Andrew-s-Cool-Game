#pragma once

template<class T>
class ObjectPool
{

public:

	ObjectPool<T>() = delete;
	ObjectPool<T>(int desiredSize);
	~ObjectPool<T>();

	T* GetNextAvailable() const;
	const int GetSize() const { return size; }
	T* GetItems() const { return items; }

	void Draw() const;

private:
	const int size;

	T* items;

};

#include "ObjectPool.inl"