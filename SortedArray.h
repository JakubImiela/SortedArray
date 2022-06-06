#ifndef SORTED_ARRAY_JXJ
#define SORTED_ARRAY_JXJ

#include <iostream>
#include <initializer_list>
#include <cassert>

template <typename T, int capacity>
class SortedArray
{
private:
    T* m_data{nullptr};
    const int m_capacity;
    int m_length;

public:
    SortedArray()
        :m_capacity{capacity}
        ,m_length{0}
    {
        m_data = new T[capacity];
    }


    SortedArray(std::initializer_list<T> list)
    :m_capacity{capacity}
    ,m_length{0}
    {
        assert(static_cast<int>(list.size()) < m_capacity && "declared capacity too low");

        m_data = new T[capacity];

        for(T x : list)
            insert(x);

    }

    SortedArray(const SortedArray& array)
    :m_capacity{capacity}
    ,m_length{array.length()}
    {
        m_data = new T[m_capacity];
        for(int i{0}; i < array.length(); ++i)
            {
                m_data[i] = array[i];
            }
    }


    operator=  (const SortedArray& array)
    {
        delete[] m_data;
        m_data = new T[array.length()];
        for(int i{0}; i < array.length(); ++i)
            {
                m_data[i] = array[i];
            }
        return *this;
    }

    ~SortedArray()
    {
        delete[] m_data;
    }

    void insert(T var)
    {
        auto push {[this](int newVariableIndex)
        {
            int copyFrom{m_length - 1};
            int destination{m_length};
            while( newVariableIndex < destination )
            {
                m_data[destination] = m_data[copyFrom];
                destination--;
                copyFrom--;
            }
        }};

        auto add {[this, var](int adress)
        {
             m_data[adress] = var;
            ++m_length;
        }};
        assert(m_length < m_capacity && "out of scope insertion attempt");

        if(m_length == 0)
        {
            add(0);
            return;
        }

        int position(findAprox(var));


        //decide if we should insert new value to the right
        //or to the left of its closest element
        if( var > m_data[position] )
        {
            //insert value to the right
            push(position + 1);
            add(position +1);
        }
        else
        {
            //insert value to the left
            push(position);
            add(position);
        }
    }
    //finds approximate position of variable in table
    //returns -1 if used on empty table
    int findAprox(T var)
    {
        int left{0};
        int right{m_length - 1};
        int mid{right - (right - left) / 2};
        while(left < right)
        {
            if(var < m_data[mid])
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

    void remove(T var)
    {
        int found(findAprox(var));

        if( var == m_data[found])
        {

        while(found < m_length - 1)
        {
            m_data[found] = m_data[found + 1];
            found++;
        }
        --m_length;
        }
    }
    int length () const
    {
        return m_length;
    }

    T& operator[] (int index) const
    {
        return m_data[index];
    }
    template <typename U, int>
    friend std::ostream& operator<<(std::ostream& out, const SortedArray<U, capacity>& array);


};
template<typename T, int capacity>
std::ostream& operator<<(std::ostream& out, const SortedArray<T, capacity>& array)
    {

        out << "Array elements:";
        for(int i{}; i < array.length(); ++i)
            {
                out << ' ' << array[i];
            }
    return out;
    }

#endif
