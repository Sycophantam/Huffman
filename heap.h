#ifndef HEAP_H
#define HEAP_H

#include <iostream>

using namespace std;

template <typename E, typename C>               // element and comparator
class Heap
{
public:
    /******************************
    **        CONSTRUCTOR        **
    ******************************/
    Heap();                                	// default constructor

    Heap(const Heap& source);     			// copy constructor
    Heap& operator=(const Heap& source);    // overloaded assignment operator
    ~Heap();                               	// destructor

    /*******************
    **    MUTATORS    **
    *******************/
    void insert(E value);       			// insert new data
    E remove();              				// remove root data

    /************************
    **      ACCESSORS      **
    ************************/
    E peek();								// retrieve but don't remove root data
    int size() const;
    bool is_empty() const;
    void printHeap();

private:
    void expand();							//resize the array
    void upheap_bubbling(int index);
    void downheap_bubbling(int index);
    void print(int index);

    //private member variables
    E* _data;
    int _size;
    int _capacity;
};

/******************************
**        CONSTRUCTOR        **
******************************/
/***************************************************************
* Heap()
* Constructor; Initialize _data to empty array.
*
* Parameters: none
* Return: none
***************************************************************/
template <typename E, typename C>
Heap<E,C>::Heap()
{
    _capacity = 10;
    _data = new E[10];
    _size = 0;
}

/***************************************************************
* Heap(const Heap& source)
* Copy Constructor; Initialize this Heap according to source Heap
*
* Parameters: source(Heap): the heap that this heap is initialized to
* Return: none
***************************************************************/
template <typename E, typename C>
Heap<E,C>::Heap(const Heap& source)
{
    _capacity = source._capacity;
    _size = source._size;
    _data = new E [_capacity];
    for (int i=0; i<_size; i++)
    {
        _data[i] = source._data[i];
    }
}


/***************************************************************
* Heap& operator=(const Heap& source)
* Copy Assignment operator; Set this Heap to be the same as
*                           source Heap
*
* Parameters: source(Heap): the heap that this heap is set to be the same as.
* Return: a reference to this heap
***************************************************************/
template <typename E, typename C>
Heap<E, C>& Heap<E,C>::operator=(const Heap& source)
{
    if (&source == source)
        return *this;

    if (_data != nullptr)
        delete[] _data;

    _capacity = source._capacity;
    _size = source._size;
    _data = new E [_capacity];

    for (int i=0; i<_size; i++)
    {
        _data[i] = source._data[i];
    }

    return *this;
}



/***************************************************************
* ~Heap()
* Destructor; destroys this heap.
*
* Parameters: none
* Return: none
***************************************************************/
template <typename E, typename C>
Heap<E,C>::~Heap()
{
    delete[] _data;
    _data = nullptr;
}


/*******************
**    MUTATORS    **
*******************/
/***************************************************************
* void insert(E value)
* inserts the given value into the heap
*
* Parameters: value(E): the value to be inserted into the heap
* Return: none
***************************************************************/
template <typename E, typename C>
void Heap<E,C>::insert(E value)
{
    if(_size == _capacity)
        expand();

    _data[_size] = value;
    _size++;

    upheap_bubbling(_size - 1);
}


/***************************************************************
* E remove()
* removes the root of the heap
*
* Parameters: none
* Return: the value removed.
***************************************************************/
template <typename E, typename C>
E Heap<E,C>::remove()
{
    E temp = _data[0];
    _size--;
    _data[0] = _data[_size];

    downheap_bubbling(0);
    return temp;
}


/************************
**      ACCESSORS      **
************************/
/***************************************************************
* E peek()
* returns the value of the root of the heap.
*
* Parameters: none
* Return: the value of the root of the heap
***************************************************************/
template <typename E, typename C>
E Heap<E,C>::peek()
{
    assert(!is_empty());
    return _data[0];
}


/***************************************************************
* int size()
* returns the size of the heap
*
* Parameters: none
* Return: the size of the heap
***************************************************************/
template <typename E, typename C>
int Heap<E,C>::size() const
{
    return _size;
}


/***************************************************************
* bool is_empty()
* returns true if _data is empty
*
* Parameters: none
* Return: true if _data is empty. false otherwise
***************************************************************/
template <typename E, typename C>
bool Heap<E,C>::is_empty() const
{
    return _size < 1;
}


/***************************************************************
* void expand()
* double the value of _capacity and reallocate space for _data
*
* Parameters: none
* Return: none
***************************************************************/
template <typename E, typename C>
void Heap<E,C>::expand()
{
    _capacity *= 2;
    E* deleter = _data;
    _data = new E[_capacity];
    for(int i = 0; i < _size; i++)
    {
        _data[i] = deleter[i];
    }
    delete[] deleter;
}


/***************************************************************
* void upheap_bubbling(int index)
* rebuild the heap from the bottom upward to follow the order of
* the comparator
*
* Parameters: index(int): the index to begin the rebuild
* Return: none
***************************************************************/
template <typename E, typename C>
void Heap<E,C>::upheap_bubbling(int index)
{
    if (index == 0)
    {
        return;
    }
    //If the index is odd
    else if (index % 2)
    {
        if (C()(_data[index], _data[(index - 1)/2]))
        {
            E temp = _data[index];
            _data[index] = _data[(index - 1)/2];
            _data[(index - 1)/2] = temp;
            upheap_bubbling((index-1)/2);
        }
    }
    else
    {
        if (C()(_data[index], _data[index/2])){
            E temp = _data[index];
            _data[index] = _data[index/2];
            _data[index/2] = temp;
            upheap_bubbling(index/2);
        }
    }
}


/***************************************************************
* void upheap_bubbling(int index)
* rebuild the heap from root downward to follow the order of
* the comparator
*
* Parameters: index(int): the index to begin the rebuild
* Return: none
***************************************************************/
template <typename E, typename C>
void Heap<E,C>::downheap_bubbling(int index)
{
    if (index >= _size)
    {
        return;
    }
    else if (_data[index * 2 + 2] >= _size)
    {
        if (C()(_data[index * 2 + 1], _data[index]))
        {
            E temp = _data[index];
            _data[index] = _data[index * 2 + 1];
            _data[index * 2 + 1] = temp;
        }
    }
    else
    {
        int swap_index;
        if (C()(_data[index * 2 + 1], _data[index * 2 + 2]))
        {
            swap_index = index * 2 + 1;
        }
        else
        {
            swap_index = index * 2 + 2;
        }
        if (C()(_data[swap_index], _data[index]))
        {
            E temp = _data[index];
            _data[index] = _data[swap_index];
            _data[swap_index] = temp;
            downheap_bubbling(swap_index);
        }
    }
}
/***************************************************************
* void print()
* prints the values in _data to the console
*
* Parameters: index(int): the index to start printing at
* Return: none
***************************************************************/
template <typename E, typename C>
void Heap<E,C>::print(int index)
{
    cout << _data[index] << " ";
    if(2 * index + 1 < _size)
    {
        print(2 * index + 1);
    }

    if(2 * index + 2 < _size)
    {
        print(2 * index + 2);
    }
}


template<typename E, typename C>
void Heap<E,C>::printHeap()
{
    print(0);
    cout << endl;
}


#endif // HEAP_H
