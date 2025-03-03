#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <chrono>
using namespace std;
using namespace chrono;

// Function to generate a random array
vector<double> generateRandomArray(int size) {
    vector<double> arr(size);
    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<> dis(0.0, 10000.0);
    for (int i = 0; i < size; i++) {
        arr[i] = dis(gen);
    }
    return arr;
}

// Function to generate a sorted array
vector<double> generateSortedArray(int size) {
    vector<double> arr(size);
    for (int i = 0; i < size; i++) {
        arr[i] = i;
    }
    return arr;
}

// Function to generate a reverse sorted array
vector<double> generateReverseSortedArray(int size) {
    vector<double> arr(size);
    for (int i = 0; i < size; i++) {
        arr[i] = size - i;
    }
    return arr;
}

// QuickSort algorithm
int partition(vector<double>& arr, int low, int high) {
    int mid = low + (high - low) / 2; // Calculate the middle index
    double pivot = arr[mid]; // Take the middle element as pivot
    swap(arr[mid], arr[high]); // Move pivot to the end for processing
    int i = low - 1;

    for (int j = low; j < high; j++) {
        if (arr[j] <= pivot) { // Move elements smaller than pivot to the left
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]); // Place pivot in the correct position
    return i + 1; // Return the position of pivot
}

// QuickSort function with middle element as pivot
void quickSort(vector<double>& arr, int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high); // Partition the array
        quickSort(arr, low, pi - 1); // Sort the left part
        quickSort(arr, pi + 1, high); // Sort the right part
    }
}

// HeapSort algorithm
void heapify(vector<double>& arr, int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;
    if (left < n && arr[left] > arr[largest])
        largest = left;
    if (right < n && arr[right] > arr[largest])
        largest = right;
    if (largest != i) {
        swap(arr[i], arr[largest]);
        heapify(arr, n, largest);
    }
}

void heapSort(vector<double>& arr) {
    int n = arr.size();
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i);
    for (int i = n - 1; i >= 0; i--) {
        swap(arr[0], arr[i]);
        heapify(arr, i, 0);
    }
}

// MergeSort algorithm
void merge(vector<double>& arr, int l, int m, int r) {
    int n1 = m - l + 1;
    int n2 = r - m;
    vector<double> L(n1), R(n2);
    for (int i = 0; i < n1; i++) L[i] = arr[l + i];
    for (int i = 0; i < n2; i++) R[i] = arr[m + 1 + i];
    int i = 0, j = 0, k = l;
    while (i < n1 && j < n2) arr[k++] = (L[i] <= R[j]) ? L[i++] : R[j++];
    while (i < n1) arr[k++] = L[i++];
    while (j < n2) arr[k++] = R[j++];
}

void mergeSort(vector<double>& arr, int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;
        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);
        merge(arr, l, m, r);
    }
}

// Function to measure execution time
template <typename Func>
void measureTime(vector<double> arr, Func sortFunc, const string& sortName, const string& arrayType) {
    auto start = high_resolution_clock::now();
    sortFunc(arr);
    auto end = high_resolution_clock::now();
    cout << sortName << " on " << arrayType << ": "
         << duration_cast<milliseconds>(end - start).count() << " ms" << endl;
}

// Main program
int main() {
    const int dataSize = 1000000;

    // Generate datasets
    vector<double> sortedArray = generateSortedArray(dataSize);
    vector<double> reverseSortedArray = generateReverseSortedArray(dataSize);
    vector<vector<double>> randomArrays(8);
    for (int i = 0; i < 8; i++) {
        randomArrays[i] = generateRandomArray(dataSize);
    }

    // Compare sorting algorithms
    cout << "Comparison of execution times:\n";

    // QuickSort
    measureTime(sortedArray, [](vector<double>& arr) { quickSort(arr, 0, arr.size() - 1); }, "QuickSort", "ascending array");
    measureTime(reverseSortedArray, [](vector<double>& arr) { quickSort(arr, 0, arr.size() - 1); }, "QuickSort", "descending array");
    for (int i = 0; i < 8; i++) {
        measureTime(randomArrays[i], [](vector<double>& arr) { quickSort(arr, 0, arr.size() - 1); }, "QuickSort", "random array");
    }

    // HeapSort
    measureTime(sortedArray, heapSort, "HeapSort", "ascending array");
    measureTime(reverseSortedArray, heapSort, "HeapSort", "descending array");
    for (int i = 0; i < 8; i++) {
        measureTime(randomArrays[i], heapSort, "HeapSort", "random array");
    }

    // MergeSort
    measureTime(sortedArray, [](vector<double>& arr) { mergeSort(arr, 0, arr.size() - 1); }, "MergeSort", "ascending array");
    measureTime(reverseSortedArray, [](vector<double>& arr) { mergeSort(arr, 0, arr.size() - 1); }, "MergeSort", "descending array");
    for (int i = 0; i < 8; i++) {
        measureTime(randomArrays[i], [](vector<double>& arr) { mergeSort(arr, 0, arr.size() - 1); }, "MergeSort", "random array");
    }

    return 0;
}
