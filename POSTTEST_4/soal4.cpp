#include <iostream>
using namespace std;

struct Node {
    int data;
    Node* next;
    Node* prev;
};

/*
 * Fungsi ini menerima referensi ke pointer head dan data yang akan disisipkan.
 * Pointer head bisa berubah jika data baru menjadi elemen terkecil.
 */
void sortedInsert(Node *&head_ref, int data) {
    Node* newNode = new Node{data, nullptr, nullptr};

    // Kasus 1: List masih kosong
    if (head_ref == nullptr) {
        newNode->next = newNode;
        newNode->prev = newNode;
        head_ref = newNode;
        return;
    }

    // Kasus 2: Data baru lebih kecil dari head (sisipkan di awal)
    if (data < head_ref->data) {
        // Sisipkan sebelum head
        Node* tail = head_ref->prev; // tail adalah node sebelum head
        
        newNode->next = head_ref;
        newNode->prev = tail;
        
        head_ref->prev = newNode;
        tail->next = newNode;
        
        head_ref = newNode; // Update head ke node baru
        return;
    }

    // Kasus 3: Cari posisi yang tepat (tengah/akhir)
    Node* current = head_ref;
    
    // Cari node terakhir yang data-nya <= data baru
    while (current->next != head_ref && current->next->data < data) {
        current = current->next;
    }
    
    // Sisipkan newNode setelah current
    newNode->next = current->next;
    newNode->prev = current;
    
    current->next->prev = newNode;
    current->next = newNode;
}

void printList(Node *head_ref)
{
    if (head_ref == nullptr)
    {
        cout << "List kosong" << endl;
        return;
    }

    Node *current = head_ref;
    do
    {
        cout << current->data << " ";
        current = current->next;
    } while (current != head_ref);
    cout << endl;
}

int main()
{
    Node *head = nullptr;

    // Test sorted insert
    sortedInsert(head, 30);
    sortedInsert(head, 10);
    sortedInsert(head, 40);
    sortedInsert(head, 20);

    cout << "Circular Doubly Linked List (sorted): ";
    // Expected output: 10 20 30 40
    printList(head);

    return 0;
}