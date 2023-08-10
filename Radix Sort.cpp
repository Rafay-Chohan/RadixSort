#include <iostream>
#include<string>
using namespace std;
template <typename T>
class Queue
{

public:
	class node
	{
		T  data;
		node* next;
		node(T d, node* p)
		{
			data = d;
			next = p;
		}
		friend class Queue<T>;
	};

	class Queueiterator
	{
	protected:
		node* current;
		friend class Queue<T>;
	public:
		//Default Constructor
		Queueiterator()
		{
			current = nullptr;
		}
		//Parameterized Constructor used in begin and end functions
		Queueiterator(node* p)
		{
			current = p;
		}
		//Dereference operation to provide access of data to user
		T& operator* () const
		{
			return current->data;
		}
		//Move forward Pre-increment
		Queueiterator& operator++ ()
		{
			if (current != nullptr)
				this->current = this->current->next;
			return *this;
		}
		//Move forward Post-increment
		Queueiterator operator++ (int)
		{
			Queueiterator old = *this;
			++(*this);
			return old;
		}
		//If two iterators point to same node
		bool operator== (const Queueiterator& rhs) const { return current == rhs.current; }
		//If two iterators point to different nodes
		bool operator!= (const Queueiterator& rhs) const { return !(*this == rhs); }
	};
	//Iterator returned that points to First Node 
	Queueiterator begin()
	{
		return front;
	}
	//Iterator returned that points to Last Node  
	Queueiterator end()
	{
		return nullptr;
	}

	//Other Functions of Link Queue
	void  printQueue();
	void  Enqueue(T value);
	void Dequeue();
	void Dequeue(T& element);
	bool isFull();
	bool isEmpty();

	Queue() { front = nullptr; rear = nullptr; }
	~Queue();
private:
	node* front;
	node* rear;
};
template <typename T>
bool Queue<T>::isFull()
{
	return false;
}
template <typename T>
bool Queue<T>::isEmpty()
{
	if (front == nullptr)
		return true;
	else
		return false;
}
//Erase
template <typename T>
void Queue<T>::Dequeue()
{
	if (front == rear)
	{
		node* curr = front;
		front = rear = NULL;
		delete curr;
		return;
	}
	node* curr = front;
	front = front->next;
	delete curr;
}
template <typename T>
void Queue<T>::Dequeue(T& element)
{
	node* curr = front;
	front = front->next;
	element = curr->data;
	delete curr;
}
//Enqueuenode at rear
template <typename T>
void Queue<T>::Enqueue(T value)
{
	node* nnode = new node(value, nullptr);
	if (front == NULL)
	{
		front = nnode;
		rear = nnode;
	}
	else
	{
		rear->next = nnode;
		rear = nnode;
	}
}
//Destructor
template <typename T>
Queue<T>::~Queue()
{
	node* temp;
	while (front != nullptr)
	{
		temp = front;
		front = front->next;
		delete temp;
	}

}

//print Queue
template <typename T>
void Queue<T>::printQueue()
{
	node* current;
	current = front;
	while (current != nullptr)
	{
		cout << current->data <<endl;
		current = current->next;
	}
	cout << "NULL" << endl<<endl;
}
void radixSort(int key,int m,Queue<int> &list)
{
	Queue<int>* arr = new Queue<int>[m];//M-1 Number of Queues M being number of possibilty
	int temp;
	int temp2;
	Queue<int>::Queueiterator x = list.begin();
	for (int i = 0; i < key; i++)
	{
		while(!(list.isEmpty()))
		{
			x = list.begin();
			temp2 = pow(10, i);
			temp = (*x) / temp2;
			temp = temp % 10;//Getting 1 single element/digit
			for (int j = 0; j < m; j++)//Loop for dequeing in arr
			{
				if (temp == j)
				{
					arr[j].Enqueue(*x);
					list.Dequeue();
				}
			}
		}
		for (int j = 0; j < m; j++)//Loop for Enqueing from arr
		{
			while(!(arr[j].isEmpty()))
			{
				arr[j].Dequeue(temp);
				list.Enqueue(temp);
			}
		}
	}

}
void radixSort(int key,int m, Queue<string>& list)
{
	Queue<string>* arr = new Queue<string>[m];//M-1 Number of Queues M being number of possibilty
	string temp;
	Queue<string>::Queueiterator x = list.begin();
	for (int i = key-1; i >=0; i--)
	{
		while (!(list.isEmpty()))
		{
			x = list.begin();
			temp = *x;
			for (int j = 1; j < m; j++)
			{
				if (temp[i] == char(j))
				{
					arr[j].Enqueue(temp);
					list.Dequeue();
					continue;
				}
			}
		}
		for (int j = 1; j < m; j++)//Loop for Enqueing from arr
		{
			while (!(arr[j].isEmpty()))
			{
				arr[j].Dequeue(temp);
				list.Enqueue(temp);
			}
		}
	}

}
int main()
{
	Queue<int> Q2;
	Q2.Enqueue(329);
	Q2.Enqueue(457);
	Q2.Enqueue(657);
	Q2.Enqueue(839);
	Q2.Enqueue(436);
	Q2.Enqueue(720);
	Q2.Enqueue(355);
	cout << "Queue Int Before Sort:\n";
	Q2.printQueue();
	radixSort(3, 10, Q2);
	cout << "Queue Int after sort:\n";
	Q2.printQueue();
	Queue<string> Q;
	Q.Enqueue("329");
	Q.Enqueue("457");
	Q.Enqueue("657");
	Q.Enqueue("839");
	Q.Enqueue("436");
	Q.Enqueue("720");
	Q.Enqueue("355");
	cout << "Queue String Before Sort:\n";
	Q.printQueue();
	radixSort(3, 128, Q);
	cout << "Queue String after sort:\n";
	Q.printQueue();
	
}