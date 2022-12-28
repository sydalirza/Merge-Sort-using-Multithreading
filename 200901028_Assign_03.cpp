#include <iostream>
#include <thread>
#include <vector>

using namespace std;

void mergeSort(vector<int>& arr, int start, int end); //function declaration

int main()
{
    cout << "Enter the number of elements in the array: ";
    int no_of_elements;
    cin >> no_of_elements;

    cout << "Enter the elements: ";
    vector<int> arr(no_of_elements);
    for (int i = 0; i < no_of_elements; i++)
    {
        cin >> arr[i];
    }

    thread t1(mergeSort, ref(arr), 0, arr.size() - 1);
    t1.join();

    cout << "Sorted Array (by Merge Sort): ";
    for (int i = 0; i < no_of_elements; i++)
    {
        cout << arr[i] << " ";
    }
    cout << endl;

    return 0;
}


vector<int> merge(vector<int> left, vector<int> right)
{
    vector<int> sorted_array;
    while (left.size() > 0 && right.size() > 0)
    {
        if (left[0] < right[0])
        {
            sorted_array.push_back(left[0]);
            left.erase(left.begin());
        }
        else
        {
            sorted_array.push_back(right[0]);
            right.erase(right.begin());
        }
    }

    while (left.size() > 0)
    {
        sorted_array.push_back(left[0]);
        left.erase(left.begin());
    }

    while (right.size() > 0)
    {
        sorted_array.push_back(right[0]);
        right.erase(right.begin());
    }

    return sorted_array;
}

void mergeSort(vector<int>& arr, int start, int end)
{
    if (start < end)
    {
        int mid = (start + end) / 2;
        vector<int> left(arr.begin() + start, arr.begin() + mid + 1);
        vector<int> right(arr.begin() + mid + 1, arr.begin() + end + 1);

        thread t1(mergeSort, ref(left), 0, left.size() - 1); // One thread is assigned the left portion
        thread t2(mergeSort, ref(right), 0, right.size() - 1); // One thread is assigned the right portion

        t1.join(); //Two cores = Two threads
        t2.join();

        arr = merge(left, right); 
    }
}

