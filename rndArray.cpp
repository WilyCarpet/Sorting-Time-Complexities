#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>
#include <random>

using namespace std;

class InsertionSort
{
public:
    static void sort(vector<int> &arr)
    {
        int n = arr.size();
        for (int i = 1; i < n; i++)
        {
            int key = arr[i];
            int j = i - 1;

            while (j >= 0 && arr[j] > key)
            {
                arr[j + 1] = arr[j];
                j--;
            }
            arr[j + 1] = key;
        }
    }
};

class HeapSort
{
public:
    static void sort(vector<int> &arr)
    {
        int n = arr.size();

        // Build a max-heap
        for (int i = n / 2 - 1; i >= 0; i--)
        {
            maxHeapify(arr, n, i);
        }

        // Extract elements from the heap
        for (int i = n - 1; i > 0; i--)
        {
            swap(arr[0], arr[i]);
            maxHeapify(arr, i, 0);
        }
    }

private:
    static void maxHeapify(vector<int> &arr, int n, int root)
    {
        int largest = root;
        int left_child = 2 * root + 1;
        int right_child = 2 * root + 2;

        if (left_child < n && arr[left_child] > arr[largest])
            largest = left_child;

        if (right_child < n && arr[right_child] > arr[largest])
            largest = right_child;

        if (largest != root)
        {
            swap(arr[root], arr[largest]);
            maxHeapify(arr, n, largest);
        }
    }
};

void fillRandom(vector<int> &arr, int size)
{
    random_device rd;
    mt19937 gen(rd());

    for (int i = 0; i < size; i++)
    {
        arr.push_back(i + 1);
    }

    shuffle(arr.begin(), arr.end(), gen);
}

void fillSequential(vector<int> &arr, int size)
{
    for (int i = 1; i <= size; i++)
    {
        arr.push_back(i);
    }
}

int main()
{
    srand(time(nullptr));

    vector<int> sizes = {100000, 200000, 300000, 400000, 500000};

    for (int size : sizes)
    {
        vector<int> randomArray;
        vector<int> sequentialArray;

        fillRandom(randomArray, size);
        fillSequential(sequentialArray, size);

        vector<int> randomCopy = randomArray;
        vector<int> sequentialCopy = sequentialArray;

        clock_t start, end;

        // Timing Insertion Sort for random data
        start = clock();
        InsertionSort::sort(randomArray);
        end = clock();
        double insertionSortRandomTime = double(end - start) / CLOCKS_PER_SEC;

        // Timing Insertion Sort for sequential data
        start = clock();
        InsertionSort::sort(sequentialArray);
        end = clock();
        double insertionSortSequentialTime = double(end - start) / CLOCKS_PER_SEC;

        // Timing Heap Sort for random data
        start = clock();
        HeapSort::sort(randomCopy);
        end = clock();
        double heapSortRandomTime = double(end - start) / CLOCKS_PER_SEC;

        // Timing Heap Sort for sequential data
        start = clock();
        HeapSort::sort(sequentialCopy);
        end = clock();
        double heapSortSequentialTime = double(end - start) / CLOCKS_PER_SEC;

        cout << "Array Size: " << size << endl;
        cout << "Insertion Sort (Random): " << insertionSortRandomTime << " seconds" << endl;
        cout << "Insertion Sort (Sequential): " << insertionSortSequentialTime << " seconds" << endl;
        cout << "Heap Sort (Random): " << heapSortRandomTime << " seconds" << endl;
        cout << "Heap Sort (Sequential): " << heapSortSequentialTime << " seconds" << endl;
        cout << "-----------------------------------" << endl;
    }

    return 0;
}