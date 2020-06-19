#pragma once
#include <string>
#include <sstream>


template<typename T> class WeakPointer;

class ReferenceCounter
{
	
private:
	int _ReferenceCount;
	int _WeakPointerCount;
public:

	void AddWeakPointer()
	{
		_WeakPointerCount++;
		
	}
	void RemoveWeakPointer()
	{
		_WeakPointerCount--;
	}
	void AddReference()
	{
		_ReferenceCount++;
	}
	int RemoveReference()
	{
		return --_ReferenceCount;
	}

	int ReferenceCount() const
	{
		return _ReferenceCount;
	}
    int WeakPointerCount() const
	{
		return _WeakPointerCount;
	}
};

template<typename T>
class SmartPointer
{
	friend WeakPointer < T >;
private:
	T* data;// pointer data
	ReferenceCounter* _Reference;
public:
	explicit SmartPointer() : data(0), _Reference(0)
	{
		_Reference = new ReferenceCounter();
		_Reference->AddReference();
	}
	explicit SmartPointer(T* pValue) : data(pValue), _Reference(0)
	{
		_Reference = new ReferenceCounter();
		_Reference->AddReference();
	}
	SmartPointer(const SmartPointer & I_smart_pointer) : data(I_smart_pointer.data), _Reference(I_smart_pointer._Reference)
	{
		if(_Reference)
			_Reference->AddReference();
	}

	SmartPointer(const WeakPointer<T> & i_weak_pointer) : data(i_weak_pointer.data), _Reference(i_weak_pointer._Reference)
	{
		if (_Reference)
		{
			if(_Reference->ReferenceCount()==0)
			{
				data = nullptr;
				_Reference = nullptr;
			}
			else
			{
				
			_Reference->AddReference();
			}
		}
	}
	
	~SmartPointer()
	{
		//Call it only when the reference count is 0;
		if (_Reference->RemoveReference() == 0 )
		{
			std::ostringstream os_;
			//os_ << "Game Object pointer Destroyed  " << data;
			OutputDebugStringA(os_.str().c_str());
			//TODO: Fix this! this is temp fix!
			data = nullptr;
			delete data;
			delete _Reference;
		}


	}

	int GetCount() const
	{
		return _Reference->ReferenceCount();
	}
	ReferenceCounter* GetReference()
	{
		return _Reference;
	}
	T* GetData()
	{
		
		return data;
	}

	operator bool()
	{
		return data != nullptr;
	
	}
	T& operator*()
	{
		
			return *data;
	}
	T* operator->()
	{
		
		return data;
	}

	void operator = (std::nullptr_t i_nullptr) 
	{
		if (_Reference->RemoveReference() == 0)
		{
			delete data;
			delete _Reference;
			
			 
		}
		data = nullptr;
		_Reference = new ReferenceCounter();
		_Reference->AddReference();
		
	}
	
	SmartPointer<T>& operator = (const SmartPointer<T>& i_smart_pointer)
	{
		if(this!=&i_smart_pointer)
		{
			if(_Reference->RemoveReference()==0)
			{
				
				delete data;
				delete _Reference;
			}

			data = i_smart_pointer.data;
			_Reference = i_smart_pointer._Reference;
			_Reference->AddReference();
		}
		return *this;
	}
};

template<typename T> class WeakPointer
{
	friend SmartPointer < T >;
public:
	T* data;
	ReferenceCounter* _Reference;
public:
	WeakPointer(SmartPointer <T>& i_other):
	data(i_other.GetData()),
	_Reference(i_other.GetReference())
	{
		
		_Reference->AddWeakPointer();
	}
	WeakPointer(WeakPointer <T>& i_other) :
	data(i_other.data),
	_Reference(i_other.GetCount())
	{
		_Reference->AddWeakPointer();
	}

	SmartPointer<T> Acquire()
	{
		return SmartPointer<T>(*this);
	}
	int GetCount() const
	{
		return _Reference->WeakPointerCount();
	}
	ReferenceCounter* GetReference()
	{
		return _Reference;
	}
	T* GetData()
	{
		if (data != nullptr)
			return data;
	}
	operator bool ()
	{
		return _Reference->ReferenceCount() > 0;
	}
	WeakPointer<T>& operator = (const WeakPointer<T>& i_weak_pointer)
	{
		if (this != &i_weak_pointer)
		{
			if (_Reference->RemoveReference() == 0)
			{

				delete data;
				delete _Reference;
			}

			data = i_weak_pointer.data;
			_Reference = i_weak_pointer._Reference;
			_Reference->AddWeakPointer();
		}
		return *this;
	}
};
