#ifndef OBJECTPOOL_H
#define OBJECTPOOL_H

#include <vector>

template <class T> class ObjectPool {
public:
	ObjectPool() {
		init(0);
	}

	ObjectPool(int preAllocate) {
		init(preAllocate);
	}

	virtual ~ObjectPool() {
		for(auto iterator = mObjects.begin(); iterator != mObjects.end(); iterator++) {
			delete *iterator;
		}
		mObjects.clear();
	}

	void init(int preAllocate) {
		mObjects.reserve(preAllocate);

		for(int i = 0; i < preAllocate; i++) {
			mObjects.push_back(new T());
		}
	}

	T* get() {
		if(mObjects.size() > 0) {
			T* object = mObjects.back();
			mObjects.pop_back();
		}
		else {
			return new T();
		}
	}

	void release(T* object) {
		mObjects.push_back(object);
	}

private:
	std::vector<T*> mObjects;
};

#endif