#include <stdexcept>
#include <iostream>
#include "todolist.h"
using namespace std;


DailyTodoList::DailyTodoList()
{
    data_ = new Item * [5];
    cap_ = 5;
    priorityHead_ = NULL;
    // [TO BE COMPLETED]
    //===========================
    // Add any addition code here

    for(size_t i = 0; i < cap_; i++)
    {
        data_[i] = NULL;
    }
    
    numP_ = 0;
}

DailyTodoList::~DailyTodoList()
{
    Item* temp;
    Item* rItem;
    for(size_t i = 0; i < cap_; i++)
    {
        rItem = data_[i];
        while(rItem)
        {
            temp = rItem->nextItem;
            delete rItem;
            rItem = temp;
        }
    }
    delete data_;
}

void DailyTodoList::push_back(size_t dayIndex, const std::string& val, bool highPriority)
{
    if (dayIndex < cap_)
    {
        this->insert(dayIndex, this->numItemsOnDay(dayIndex), val, highPriority);
    }
    else
    {
        this->insert(dayIndex, 0, val, highPriority);
    }
    
}

void DailyTodoList::insert(size_t dayIndex, size_t loc, const std::string& val, bool highPriority)
{
    //resize array if dayIndex is larger than array
    if(dayIndex > cap_)
    {
        resize(dayIndex*2);
    }
    
    Item* newItem;
    Item* temp = data_[dayIndex];
    
    //Edge case 1: location 0
    if(loc == 0)
    {
        //if no items in list
        if(temp == NULL)
        {
            newItem = new Item(val, NULL, 0);
            data_[dayIndex] = newItem;
        }
        else
        {
            newItem = new Item(val, temp, 0);
            data_[dayIndex] = newItem;
        }
    }
    else {
        for(size_t i = 0; i < loc-1; i++)
        {
            if(temp->nextItem == NULL)
            {
                throw std::out_of_range("Cannot insert in this location");
            }
            else
            {
                temp = temp->nextItem;
            }
        }
        newItem = new Item(val, temp->nextItem, 0);
        temp->nextItem = newItem;
    }
    
    //Deal with high priority
    if(highPriority == true)
    {
        if(priorityHead_ == NULL)
        {
            priorityHead_ = newItem;
            newItem->nextPriorityItem = NULL;
        }
        else
        {
            Item* iterator = priorityHead_;
            while(iterator->nextPriorityItem != NULL)
            {
                iterator = iterator->nextPriorityItem;
            }
            iterator->nextPriorityItem = newItem;
            newItem->nextPriorityItem = NULL;
        }
        numP_++;
    }
    else
    {
        newItem->nextPriorityItem = NULL;
    }
    
}

void DailyTodoList::remove(size_t dayIndex, size_t loc)
{
    //check for range exception + no list exists
    if(dayIndex > cap_ || data_[dayIndex] == NULL)
    {
        throw std::out_of_range("Cannot remove from this location");
    }
    
    Item* iterator1 = data_[dayIndex];
    Item* temp;
    if(loc == 0)
    {
        if(iterator1->nextItem == NULL)
        {
            data_[dayIndex] = NULL;
        }
        else
        {
            data_[dayIndex] = iterator1->nextItem;
        }
        temp = iterator1;
    }
    else
    {
    
        for(size_t i = 0; i < loc-1; i++)
        {
            if(iterator1->nextItem == NULL)
            {
                throw std::out_of_range("Cannot remove from this location");
            }
            else
            {
                iterator1 = iterator1->nextItem;
            }
        }
        //set list in correct order
        temp = iterator1->nextItem;
        iterator1->nextItem = iterator1->nextItem->nextItem;
    }

    //delete from priority
    Item* iterator2 = priorityHead_;
    //base case (first item)
    if(iterator2 == temp)
    {
        //only item in list
        if(iterator2->nextPriorityItem == NULL)
        {
            priorityHead_ = NULL;
        }
        else
        {
            priorityHead_ = iterator2->nextPriorityItem;
        }
        numP_--;
    }
    else
    {
        while(iterator2 != NULL)
        {
            if(iterator2->nextPriorityItem == temp)
            {
                iterator2->nextPriorityItem = temp->nextPriorityItem;
                numP_--;
            }
            else
            {
                iterator2 = iterator2->nextPriorityItem;
            }
        }
    }
    delete temp;
    
}

size_t DailyTodoList::numDays() const
{
    return cap_;
}

size_t DailyTodoList::numItemsOnDay(size_t dayIndex) const
{
    
    if(empty(dayIndex))
    {
        return 0;
    }
    else
    {
        Item* temp = data_[dayIndex];
        int count = 0;
        while(temp)
        {
            count++;
            temp = temp->nextItem;
        }
        return count;
    }
}

bool DailyTodoList::empty(size_t dayIndex) const
{
    return data_[dayIndex] == NULL;
}

//DONE
const std::string& DailyTodoList::getNormalVal(size_t dayIndex, size_t loc) const
{
    Item* temp = data_[dayIndex];
    
    for(size_t i = 0; i < loc; i++)
    {
        if(temp == NULL)
        {
            throw std::out_of_range("SYSTEM ERROR: bad memory access");
        }
        else
        {
            temp = temp->nextItem;
        }
    }
    return temp->val;
}

//DONE
std::string& DailyTodoList::getNormalVal(size_t dayIndex, size_t loc)
{
    Item* temp = data_[dayIndex];
    
    for(size_t i = 0; i < loc; i++)
    {
        if(temp == NULL)
        {
            throw std::out_of_range("SYSTEM ERROR: bad memory access");
        }
        else
        {
            temp = temp->nextItem;
        }
    }
    return temp->val;
}

//DONE
size_t DailyTodoList::numPriorityItems() const
{
    return numP_;
}

//DONE
const std::string& DailyTodoList::getPriorityVal(size_t priorityLoc) const
{
    if(numPriorityItems() < priorityLoc)
    {
        throw std::out_of_range("SYSTEM ERROR: bad memory access");
    }
    
    Item* temp = priorityHead_;
    
    for(size_t i = 0; i < priorityLoc; i++)
    {
        if(temp == NULL) 
        {
            throw std::out_of_range("SYSTEM ERROR: bad memory access");
        }
        else
        {
        temp = temp->nextPriorityItem;
        }
    }
    return temp->val;
}

void DailyTodoList::resize(int newSize)
{
    //allocates new memory
    Item** newArray = new Item*[newSize];
    for(int i = newSize -1; i >= 0; i--)
    {
        newArray[i] = NULL;
        if(i < (int)cap_)
        {
            //if pointer to todolist exists
            //copies data to newArray
            if(data_[i] != NULL)
            {
                newArray[i] = data_[i];
                
            }
            
        }
        
    }
    //deletes data_
    delete [] data_;
    cap_ = newSize;
    data_ = newArray;
}


