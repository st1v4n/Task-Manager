#pragma once
#include <iostream>
//class used for the due_date, because it is optional
template <typename T>
class Optional {
public:
	void setValue(const T& newValue);
	const T& getValue() const;
	bool isValueSet() const;
private:
	T value;
	bool isSet = false;
};

template<typename T>
inline void Optional<T>::setValue(const T& newValue)
{
	//it must have operator= defined
	value = newValue; 
	isSet = true;
}

template<typename T>
inline const T& Optional<T>::getValue() const
{
	//checking if it is set, else throwing an exception
	if (isSet) {
		return value;
	}
	throw std::logic_error("Value not set!");
}

template<typename T>
inline bool Optional<T>::isValueSet() const
{
	return isSet;
}
