#include <iostream>
#include "SortedArray.h"



int main()
{
    SortedArray<int, 20> arr{1,2,3,4,5,6,7,8,9};
    std::cout << arr << '\n';
    arr.insert(0);
    arr.insert(1);
    arr.remove(5);
    std::cout << arr << '\n';



    return 0;
}
