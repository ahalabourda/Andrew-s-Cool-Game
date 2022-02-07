#pragma once

template<class T>
ObjectPool<T>::ObjectPool(int desiredSize)
	: size(desiredSize)
	, items(new T[size])
{
}

template<class T>
ObjectPool<T>::~ObjectPool()
{

	delete[] items;
	items = nullptr;

}

template<class T>
T* ObjectPool<T>::GetNextAvailable() const
{

	for (int i = 0; i < size; i++) {
		if (items[i].GetIsActive() == false) {
			return &items[i];
		}
	}

	throw std::exception("Couldn't get a poolable object");

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