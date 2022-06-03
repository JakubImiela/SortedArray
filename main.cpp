#include <iostream>
#include <cassert>

class SortedArray
{
private:
    int* m_array{nullptr};
    const int m_capacity;
    int m_length;

    //add element to the array
    //increase its length
    //USE THIS FUNCTION ONLY FOR ADDING ELEMENTS
    void add(int var, int adress)
    {
        m_array[adress] = var;
        ++m_length;
    }

    //replace all elements, given index included
    //one space to the right
    void push(int newVariableIndex)
    {
        int copyFrom{m_length - 1};
        int destination{m_length};
        while( newVariableIndex < destination )
        {
            m_array[destination] = m_array[copyFrom];
            destination--;
            copyFrom--;
        }
    }

public:
    SortedArray(int capacity)
        :m_capacity{capacity}
        ,m_length{0}
    {
        m_array = new int[capacity];
    }

    SortedArray(const SortedArray&) = delete;
    operator=  (const SortedArray&) = delete;

    ~SortedArray()
    {
        delete[] m_array;
    }

    void insert(int var)
    {
        assert(m_length < m_capacity && "out of scope insertion attempt");

        if(m_length == 0)
        {
            add(var, 0);
            return;
        }

        int position(findAprox(var));


        //decide if we should insert new value to the right
        //or to the left of its closest element
        if( var > m_array[position] )
        {
            //insert value to the right
            push(position + 1);
            add(var, position +1);
        }
        else
        {
            //insert value to the left
            push(position);
            add(var, position);
        }
    }
    //finds approximate position of variable in table
    //returns -1 if used on empty table
    int findAprox(int var)
    {
        int left{0};
        int right{m_length - 1};
        int mid{right - (right - left) / 2};
        while(left < right)
        {
            if(var < m_array[mid])
            {
                right = mid - 1; //if mid is equal to right, this avoids infinite loop
            }
            else //( var >= m_array[mid]
            {
                left = mid; //mid is never equal to left
            }

            mid = right - (right - left) / 2;
        }
        return mid;
    }

    void remove(int var)
    {
        int found(findAprox(var));

        if( var == m_array[found])
        {

        while(found < m_length - 1)
        {
            m_array[found] = m_array[found + 1];
            found++;
        }
        --m_length;
        }
    }
    friend std::ostream& operator<<(std::ostream& out, const SortedArray& array);

};

std::ostream& operator<<(std::ostream& out, const SortedArray& array)
{

        out << "Array elements:";
        for(int i{}; i < array.m_length; ++i)
            {
                out << ' ' << array.m_array[i];
            }
    return out;
}


int main()
{
    SortedArray arr{10};


    arr.insert(0);
    arr.insert(10);
    arr.insert(25);
    arr.insert(5);
    arr.insert(20);
    arr.insert(5);
    arr.insert(-5);
    std::cout << arr << '\n';

    arr.remove(20);
    std::cout << arr << '\n';
    arr.remove(22);
    std::cout << arr << '\n';
    arr.remove(25);
    std::cout << arr << '\n';
    arr.remove(-5);
    std::cout << arr << '\n';


    return 0;
}
