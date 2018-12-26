#pragma once

template <typename T> class Singleton
{
protected:

	static T * s_pIntance;

	Singleton() {}
	Singleton(const Singleton&) {}
	Singleton operator =(const Singleton&) {}
	virtual ~Singleton() {}

public:

	static T * GetInstance()
	{
		if (s_pIntance == nullptr)
			s_pIntance = new T();
		return s_pIntance;
	}

	static void DestroyInstance()
	{
		if (s_pIntance)
		{
			delete s_pIntance;
			s_pIntance = nullptr;
		}
	}
};

template<typename T>
T* Singleton<T>::s_pIntance = nullptr;