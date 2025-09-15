#include <iostream>
using namespace std;

int main() {
    int matriks[3][3] = {
        {3, 2, 4},
        {5, 1, 7},
        {8, 6, 9},
    };

    // Cetak matriks
    cout << "Matriks 3x3:" << endl;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            cout << matriks[i][j] << " ";
        }
        cout << endl;
    }

    // Hitung jumlah elemen pada baris genap (indeks 0 dan 2)
    int jumlah = 0;
    for (int i = 0; i < 3; i++) {
        if (i % 2 == 0) { 
            for (int j = 0; j < 3; j++) {
                jumlah += matriks[i][j];
            }
        }
    }

    cout << "Jumlah elemen pada baris genap: " << jumlah << endl;
}