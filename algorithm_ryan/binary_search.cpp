#if 0

#include <iostream>
#include <vector>
#include <math.h>
using namespace std;

int binary_search(const vector<int>& vec, int element)
{
    int minIndex = 0;
    int maxIndex = vec.size();
    int curElement = 0;

    while (minIndex < maxIndex)
    {
        /* code */
        int midIndex = floor((minIndex + maxIndex) / 2);
        curElement = vec.at(midIndex);

        if(curElement < element)
        {
            cout << "go right for search..." << endl;
            minIndex = midIndex + 1;
        }
        else if (curElement > element)
        {
            cout << "go left for search..." << endl;
            maxIndex = maxIndex - 1;
        }
        else 
        {
            cout << "Found the element: " << element << ", index: " << midIndex << endl;
            return midIndex;
        }
    }

    return -1;
}

int main()
{
    cout << "hello world" <<endl;
    int index = binary_search(vector{1,2,3,4,5,6,7,8}, 6);
    cout << "Index callback: " << index << endl;

    return 0;
}

#endif