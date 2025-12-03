
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
using namespace std;

// Partition function (similar to quicksort partition)
int partition(vector<int>& arr, int l, int r) {
    int pivot = arr[r];
    int i = l - 1;
    for (int j = l; j < r; j++) {
        if (arr[j] <= pivot) {
            swap(arr[++i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[r]);
    return i + 1;
}

// Randomized partition
int randomizedPartition(vector<int>& arr, int l, int r) {
    int randomIndex = l + rand() % (r - l + 1);
    swap(arr[randomIndex], arr[r]); // put random pivot at the end
    return partition(arr, l, r);
}

// Randomized select algorithm
int randomizedSelect(vector<int>& arr, int l, int r, int i) {
    if (l == r)
        return arr[l];
    int q = randomizedPartition(arr, l, r);
    int k = q - l + 1; // number of elements in left partition including pivot
    if (i == k)
        return arr[q];
    else if (i < k)
        return randomizedSelect(arr, l, q - 1, i);
    else
        return randomizedSelect(arr, q + 1, r, i - k);
}

int main() {
    srand(time(0)); // seed random

    int n, i;
    cout << "Enter number of elements: ";
    cin >> n;

    vector<int> arr(n);
    cout << "Enter array elements: ";
    for (int j = 0; j < n; j++)
        cin >> arr[j];

    cout << "Enter i (to find i-th smallest element): ";
    cin >> i;

    if (i < 1 || i > n) {
        cout << "Invalid i!" << endl;
        return 0;
    }

    int result = randomizedSelect(arr, 0, n - 1, i);
    cout << "The " << i << "-th smallest element is: " << result << endl;

    return 0;
}
