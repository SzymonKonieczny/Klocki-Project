#pragma once
#ifndef PRIORITYQUEUECUSTOM_H
#define PRIORITYQUEUECUSTOM_H

#include <queue>
enum PriorityLevel
{
	Low,
	Mid,
	Top
};


template <class T>
class PriorityQueueCustom
{
public:
	std::queue<T> TopPriority;
	std::queue<T> MidPriority;
	std::queue<T> LowPriority;
	T* pop_by_prioirty();



	
	void push_with_priority(T& Item, PriorityLevel prio);





};


#endif // !PRIORITYQUEUECUSTOM_H

template<class T>
 T* PriorityQueueCustom<T>::pop_by_prioirty()
{
	{
		T* result = nullptr;
		if (!TopPriority.empty())
		{
			result = *TopPriority.front();
		}
		else if (!MidPriority.empty())
		{
			*
				result = *MidPriority.front();
		}
		else if (!LowPriority.empty())
		{
			result = *LowPriority.front();
		}
		return result;

	}
}




template<class T>
 void PriorityQueueCustom<T>::push_with_priority(T& Item, PriorityLevel prio)
{
	switch (PriorityLevel)
	{
	case Low:
		LowPriority.push(Item)
			break;
	case Mid:
		MidPriority.push(Item)
			break;
	case Top:
		TopPriority.push(Item)
			break;
	default:
		break;
	}
}
