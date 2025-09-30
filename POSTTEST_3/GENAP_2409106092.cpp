#include <iostream>
#include <string>
using namespace std;

// WARNA TERBATAS
const string RED = "\033[31m";
const string BLUE = "\033[34m";
const string YELLOW = "\033[33m";
const string RESET = "\033[0m";
const string BOLD = "\033[1m";

const string NAMA = "Muhammad Farras Arhab Ince";
const string NIM  = "2409106092";
const string LAST3 = NIM.substr(NIM.size() - 3); // "092"
const int lastDigit = NIM.back() - '0';          // 2
const int insertPosition = (lastDigit == 0) ? (0 + 2) : (lastDigit + 1);

struct Flight {
    string kodePenerbangan;
    string tujuan;
    string status;
};

struct Node {
    Flight data;
    Node* next;
    Node* prev;
};

Node* head = nullptr;
Node* tail = nullptr;
int kodeCounter = 0;

// Fungsi header menu
void headerMenu() {
    const int width = 60;
    string title = BOLD + BLUE + "FLIGHT SCHEDULE SYSTEM" + RESET;
    string identitas = BOLD + BLUE + "[ " + NAMA + " - " + NIM + " ]" + RESET;

    cout << BLUE << "+" << string(width - 2, '-') << "+\n" << RESET;
    int titleLen = 24; 
    cout << BLUE << "|" << RESET
         << string((width - 2 - titleLen) / 2, ' ')
         << title
         << string((width - 2 - titleLen + 1) / 2, ' ')
         << BLUE << "  |\n" << RESET;
    int identLen = NAMA.size() + NIM.size() + 5;
    cout << BLUE << "|" << RESET
         << string((width - 2 - identLen) / 2, ' ')
         << identitas
         << string((width - 2 - identLen + 1) / 2, ' ')
         << BLUE << "|\n" << RESET;
    cout << BLUE << "+" << string(width - 2, '-') << "+" << RESET << endl;
}

// Fungsi buat kode penerbangan otomatis
string generateKode() {
    if (kodeCounter == 0) {
        kodeCounter++;
        return "JT-" + LAST3;
    } else {
        return "JT-" + LAST3 + "-" + to_string(kodeCounter++);
    }
}

// Tambah jadwal di akhir
void tambahJadwal() {
    Node* newNode = new Node;
    newNode->data.kodePenerbangan = generateKode();
    cout << BOLD << BLUE << "\n== Tambah Jadwal Penerbangan ==\n" << RESET;
    cout << "[ Tujuan Penerbangan ]\n";
    cout << YELLOW << "Masukkan tujuan penerbangan: " << RESET;
    getline(cin >> ws, newNode->data.tujuan);
    cout << "\n[ Contoh status penerbangan ] \n- Tepat waktu\n- Terlambat\n- Boarding\n";
    cout << YELLOW << "Masukkan status penerbangan: " << RESET;
    getline(cin >> ws, newNode->data.status);

    newNode->next = nullptr;
    newNode->prev = tail;

    if (head == nullptr) {
        head = tail = newNode;
    } else {
        tail->next = newNode;
        tail = newNode;
    }

    cout << BLUE << "Jadwal berhasil ditambahkan dengan kode " << newNode->data.kodePenerbangan << "!\n" << RESET;
}

// Sisipkan jadwal
void sisipJadwal() {
    Node* newNode = new Node;
    newNode->data.kodePenerbangan = generateKode();
    cout << BOLD << BLUE << "\n== Sisipkan Jadwal Penerbangan ==\n" << RESET;
    cout << "[ Tujuan Penerbangan ]\n";
    cout << YELLOW << "Masukkan tujuan penerbangan: " << RESET;
    getline(cin >> ws, newNode->data.tujuan);
    cout << "\n[ Contoh status penerbangan ] \n- Tepat waktu\n- Delayed\n- Boarding..\n";
    cout << YELLOW << "Masukkan status penerbangan: " << RESET;
    getline(cin >> ws, newNode->data.status);

    if (head == nullptr || insertPosition <= 1) {
        newNode->next = head;
        newNode->prev = nullptr;
        if (head) head->prev = newNode;
        head = newNode;
        if (tail == nullptr) tail = newNode;
    } else {
        Node* temp = head;
        int pos = 1;
        while (temp->next != nullptr && pos < insertPosition - 1) {
            temp = temp->next;
            pos++;
        }
        newNode->next = temp->next;
        newNode->prev = temp;
        if (temp->next) temp->next->prev = newNode;
        temp->next = newNode;
        if (newNode->next == nullptr) tail = newNode;
    }

    cout << BLUE << "Jadwal berhasil disisipkan di posisi " << insertPosition 
         << " dengan kode " << newNode->data.kodePenerbangan << "!\n" << RESET;
}

// Hapus jadwal paling awal
void hapusAwal() {
    if (head == nullptr) {
        cout << RED << "Tidak ada jadwal untuk dihapus.\n" << RESET;
        return;
    }
    Node* temp = head;
    head = head->next;
    if (head) head->prev = nullptr;
    else tail = nullptr;

    cout << BLUE << "Jadwal dengan kode " << temp->data.kodePenerbangan << " berhasil dihapus.\n" << RESET;
    delete temp;
}

// Update status penerbangan
void updateStatus() {
    if (head == nullptr) {
        cout << RED << "Tidak ada jadwal penerbangan.\n" << RESET;
        return;
    }

    string kode;
    cout << BOLD << BLUE << "\n== Update Status Penerbangan ==\n" << RESET;
    cout << YELLOW << "Masukkan kode penerbangan yang ingin diupdate: " << RESET;
    getline(cin >> ws, kode);

    Node* temp = head;
    while (temp != nullptr) {
        if (temp->data.kodePenerbangan == kode) {
            cout << "Status saat ini: " << temp->data.status << "\n";
            cout << YELLOW << "Masukkan status baru: " << RESET;
            getline(cin >> ws, temp->data.status);
            cout << BLUE << "Status penerbangan dengan kode " << kode << " berhasil diperbarui!\n" << RESET;
            return;
        }
        temp = temp->next;
    }

    cout << RED << "Kode penerbangan tidak ditemukan.\n" << RESET;
}

// Tampilkan semua jadwal dari depan
void tampilkanJadwal() {
    if (head == nullptr) {
        cout << RED << "Tidak ada jadwal penerbangan.\n" << RESET;
        return;
    }

    cout << BOLD << "\nDaftar Jadwal Penerbangan (dari depan):\n" << RESET;
    cout << "+------------------------------------------------------------+\n";
    cout << "| " << "Kode Penerbangan" << string(3, ' ')
         << "| " << "Tujuan" << string(21, ' ')
         << "| " << "Status" << string(11, ' ') << "|\n";
    cout << "+------------------------------------------------------------+\n";

    Node* temp = head;
    while (temp != nullptr) {
        cout << "| " << temp->data.kodePenerbangan;
        cout << string(17 - temp->data.kodePenerbangan.size(), ' ');
        cout << "| " << temp->data.tujuan;
        cout << string(22 - temp->data.tujuan.size(), ' ');
        cout << "| " << temp->data.status;
        cout << string(15 - temp->data.status.size(), ' ');
        cout << "|\n";
        temp = temp->next;
    }

    cout << "+------------------------------------------------------------+\n";
}

// Tampilkan jadwal dari belakang
void tampilkanJadwalBelakang() {
    if (tail == nullptr) {
        cout << RED << "Tidak ada jadwal penerbangan.\n" << RESET;
        return;
    }

    cout << BOLD << "\nDaftar Jadwal Penerbangan (dari belakang):\n" << RESET;
    cout << "+------------------------------------------------------------+\n";
    cout << "| " << "Kode Penerbangan" << string(3, ' ')
         << "| " << "Tujuan" << string(21, ' ')
         << "| " << "Status" << string(11, ' ') << "|\n";
    cout << "+------------------------------------------------------------+\n";

    Node* temp = tail;
    while (temp != nullptr) {
        cout << "| " << temp->data.kodePenerbangan;
        cout << string(17 - temp->data.kodePenerbangan.size(), ' ');
        cout << "| " << temp->data.tujuan;
        cout << string(22 - temp->data.tujuan.size(), ' ');
        cout << "| " << temp->data.status;
        cout << string(15 - temp->data.status.size(), ' ');
        cout << "|\n";
        temp = temp->prev;
    }

    cout << "+------------------------------------------------------------+\n";
}

// Cari detail data
void cariDetail() {
    if (head == nullptr) {
        cout << RED << "Tidak ada jadwal penerbangan.\n" << RESET;
        return;
    }

    string input;
    cout << BOLD << BLUE << "\n== Cari Detail Penerbangan ==\n" << RESET;
    cout << YELLOW << "Masukkan Kode Penerbangan atau Nama Tujuan: " << RESET;
    getline(cin >> ws, input);

    Node* temp = head;
    while (temp != nullptr) {
        if (temp->data.kodePenerbangan == input || temp->data.tujuan == input) {
            cout << BOLD << "Detail Jadwal Penerbangan:\n" << RESET;
            cout << "Kode   : " << temp->data.kodePenerbangan << "\n";
            cout << "Tujuan : " << temp->data.tujuan << "\n";
            cout << "Status : " << temp->data.status << "\n";
            return;
        }
        temp = temp->next;
    }

    cout << RED << "Data tidak ditemukan.\n" << RESET;
}

// Main program
int main() {
    int pilihan;
    do {
        headerMenu();
        cout << BOLD << BLUE << " == MENU SISTEM JADWAL PENERBANGAN ==\n" << RESET;
        cout << BOLD << "  1. " << RESET << "Tambah Jadwal Penerbangan\n";
        cout << BOLD << "  2. " << RESET << "Sisipkan Jadwal Penerbangan\n";
        cout << BOLD << "  3. " << RESET << "Hapus Jadwal Paling Awal\n";
        cout << BOLD << "  4. " << RESET << "Update Status Penerbangan\n";
        cout << BOLD << "  5. " << RESET << "Tampilkan Semua Jadwal (Depan)\n";
        cout << BOLD << "  6. " << RESET << "Tampilkan Semua Jadwal (Belakang)\n";
        cout << BOLD << "  7. " << RESET << "Cari Detail Jadwal\n";
        cout << BOLD << "  0. " << RESET << "Keluar\n";
        cout << YELLOW << "Pilih menu: " << RESET;
        cin >> pilihan;

        cin.ignore();
        switch (pilihan) {
            case 1: tambahJadwal(); break;
            case 2: sisipJadwal(); break;
            case 3: hapusAwal(); break;
            case 4: updateStatus(); break;
            case 5: tampilkanJadwal(); break;
            case 6: tampilkanJadwalBelakang(); break;
            case 7: cariDetail(); break;
            case 0: cout << BLUE << "Keluar dari program...\n" << RESET; break;
            default: cout << RED << "Pilihan tidak valid.\n" << RESET;
        }
        cout << endl;
    } while (pilihan != 0);

    return 0;
}