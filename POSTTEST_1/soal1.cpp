#include <iostream>
using namespace std;

// Fungsi untuk membalik urutan array menggunakan pointer
void balikArray(int *arr, int n) {
    int *start = arr;
    int *end = arr + n - 1;
    while (start < end) {
        int temp = *start;
        *start = *end;
        *end = temp;
        start++;
        end--;
    }
}

// Fungsi untuk menampilkan array
void tampilArray(int *arr, int n) {
    for (int i = 0; i < n; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
}

int main() {
    int prima[7] = {2, 3, 5, 7, 11, 13, 17};

    cout << "Array sebelum dibalik: ";
    tampilArray(prima, 7);

    balikArray(prima, 7);

    cout << "Array sesudah dibalik: ";
    tampilArray(prima, 7);

    return 0;
}