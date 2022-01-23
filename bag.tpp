#include "bag.hpp"

// empty implementation                                                                                                     

/** default constructor
 * creates new bag object
 * sets current size (bagSize) to 0
 * sets maxSize (size before memory is reallocated) to 10
 * dynamically allocates a new array to hold bag items
*/
template <typename T> Bag<T>::Bag() 
{ 
    max_size_increment = 10;
    bagSize = 0;
    maxSize = 10;
    items = new T[maxSize];
}

/** destructor
 * deletes dynamically allocated array of items
 * sets items pointer to nullptr
 */
template <typename T> Bag<T>::~Bag() 
{
    delete [] items;
    items = nullptr;
}

//returns size of bag
template <typename T> std::size_t Bag<T>::getCurrentSize() const { return bagSize; }

//returns true when bagSize == 0
template <typename T> bool Bag<T>::isEmpty() const { return (bagSize==0); }

/** adds item to bag
 * takes entry of type T
 * increases bagSize by 1
 * if bagSize is less than or equal to the max bag size (maxSize),
 *  add entry to bag
 * otherwise, reallocate bag to size of maxSize + max_size_increment
 * returns true when the last item in the bag is the new item
 */
template <typename T> bool Bag<T>::add(const T& entry) 
{ 
    bagSize++;

    if(bagSize <= maxSize)
    {
        items[bagSize-1] = entry;
    } else {
        //reallocation case (when array has reached max size)
        T* temp = new T[maxSize + max_size_increment];
        for(int i = 0; i < maxSize; i++)
        {
            temp[i] = items[i];
        }
        
        maxSize += max_size_increment;
        
        delete[] items;

        items = temp;
        temp = nullptr;

        items[bagSize -1 ] = entry;
    }
    return(items[bagSize - 1] == entry); 
}

/** removes item entry from bag
 * finds where the first instance of a given item is in the bag
 * copies items array to a temp array except for the remove item
 * decreases bagSize
 * deletes items array and reassigns temp array to items pointer
 * returns true when complete, otherwise returns false
 */
template <typename T> bool Bag<T>::remove(const T& entry) 
{ 
    int removeIndex;
    for(int i = 0; i < bagSize; i++)
    {
        if(items[i] == entry)
        {
            removeIndex = i;

            //decreases max bag size when possible
            if(bagSize-1 <= maxSize-max_size_increment) maxSize-=max_size_increment;

            T* temp = new T[maxSize];
            
            for(int i = 0, j = 0; i < bagSize-1; i++)
            {
                if(i == removeIndex) j++;
                temp[i] = items[j];
                j++;
            }
            bagSize -= 1;
            delete[] items;
            items = temp;

            temp = nullptr;

            return true;
        }
    }
    return false; 
}

//clears bag
template <typename T> void Bag<T>::clear() 
{
    delete [] items;
    bagSize = 0;
    maxSize = max_size_increment;
    items = new T[maxSize];
}

//returns frequency of a given item
template <typename T> std::size_t Bag<T>::getFrequencyOf(const T& entry) const 
{ 
    unsigned int freq = 0;

    for(unsigned int i = 0; i < bagSize; i++)
    {
        if(items[i] == entry) freq++;
    }

    return freq;
}

//returns whether the bag contains a given item
template <typename T> bool Bag<T>::contains(const T& entry) const 
{ 
    for(int i = 0; i < bagSize; i++)
    {
        if(items[i] == entry)
        {
            return true;
        }
    }
    return false; 
}