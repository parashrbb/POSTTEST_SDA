#include <iostream>
#include <algorithm>
using namespace std;

struct Mahasiswa {
    string nama;
    string nim;
    float ipk;
};

int main() {
    Mahasiswa mhs[4];
    string temp;

    for (int i = 0; i < 4; i++) {
        cout << "Mahasiswa ke-" << i+1 << endl;
        cout << "Nama: ";
        getline(cin, mhs[i].nama);
        cout << "NIM: ";
        getline(cin, mhs[i].nim);
        cout << "IPK: ";
        getline(cin, temp);     
        mhs[i].ipk = stof(temp); 
    }

    sort(mhs, mhs+4, [](Mahasiswa a, Mahasiswa b) {
        return a.ipk < b.ipk;
    });

    cout << "\nData Mahasiswa setelah diurutkan berdasarkan IPK:\n";
    for (int i = 0; i < 4; i++) {
        cout << "Nama: " << mhs[i].nama << endl;
        cout << "NIM: " << mhs[i].nim << endl;
        cout << "IPK: " << mhs[i].ipk << endl;
        cout << "---------------------\n";
    }

    return 0;
}