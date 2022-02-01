#include "ObjectPool.h"

template<class T>
ObjectPool<T>::ObjectPool(int desiredSize)
	: size(desiredSize)
	, items(new T[size])
{
}

template<class T>
ObjectPool<T>::~ObjectPool()
{
}

template<class T>
T* ObjectPool<T>::GetNextAvailable() const
{
	
	for (int i = 0; i < size; i++) {
		if (items[i].GetIsActive() == false) {
			return &items[i];
		}
	}

	throw 0;

}

template<class T>
void ObjectPool<T>::Draw() const
{

	for (int i = 0; i < size; i++) {
		if (items[i].GetIsActive() == true) {
			items[i].Draw();
		}
	}

}

template<class T>
void ObjectPool<T>::Tick()
{
	for (int i = 0; i < size; i++) {
		if (items[i].GetIsActive() == true) {
			items[i].Tick();
		}
	}
}