#include "ObjectPool.h"
#pragma once

template<class T>
ObjectPool<T>::ObjectPool(int pDesiredSize)
	: mSize(pDesiredSize)
	, mItems(new T[mSize])
{
}

template<class T>
ObjectPool<T>::~ObjectPool()
{
	delete[] mItems;
	mItems = nullptr;
}

template<class T>
T* ObjectPool<T>::GetNextAvailable() const
{

	for (int i = 0; i < mSize; i++) {
		if (mItems[i].GetIsActive() == false) {
			return &mItems[i];
		}
	}

	throw std::exception("Couldn't get a poolable object");

}

template<class T>
void ObjectPool<T>::Draw() const
{

	for (int i = 0; i < mSize; i++) {
		if (mItems[i].GetIsActive() == true) {
			mItems[i].Draw();
		}
	}

}

template<class T>
inline void ObjectPool<T>::Reset()
{
	for (int i = 0; i < mSize; i++) {
		mItems[i].Deactivate();
	}
}