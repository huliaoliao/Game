#ifndef					__SINGLETON_H__
#define					__SINGLETON_H__

template<typename T>
class Singleton
{
public:
	static T& getIns();

	static T* getInstance();

private:
	Singleton() = default;

	~Singleton() = default;

private:
	Singleton(const Singleton&) = delete;

	Singleton& operator=(const Singleton&) = delete;
};

template<typename T>
T& Singleton<T>::getIns()
{
	static T s_instance;
	return s_instance;
}

template<typename T>
T* Singleton<T>::getInstance()
{
	return &getIns();
}

#endif