// Keshav Yanamandra
// COMSC-210-5293, Fall 2026
// Lab 21

#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>

using namespace std;

const int MIN_LS = 5, MAX_LS = 20;

class Goat {
    private:
        int age;
        string name;
        string color;

        //using AI I created these strings---
        string names[15] = {
            "Billy", "Charlie", "Daisy", "Rocky", "Max",
            "Luna", "Buddy", "Coco", "Rosie", "Milo",
            "Pepper", "Sunny", "Ruby", "Oscar", "Nala"
        };

        string colors[15] = {
            "White", "Black", "Brown", "Gray", "Tan",
            "Cream", "Red", "Gold", "Silver", "Beige",
            "Spotted", "Black and White", "Brown and White",
            "Gray and White", "Golden Brown"
        };
    public:
        Goat() {
            age = rand() % 20 + 1;
            name = names[rand() % 15];
            color = colors[rand() % 15];
        }

        Goat(int a, string n, string c) {
            age = a;
            name = n;
            color = c;
        }

        void print() {
            cout << "    " << name << " (" << color << ", " << age << ")" << endl;
        }
};

class DoublyLinkedList {
private:
    struct Node {
        //int data;
        //guessing I need to use goat here
        Goat data;
        Node* prev;
        Node* next;

        // Node(int val, Node* p = nullptr, Node* n = nullptr) {
        //     data = val; 
        //     prev = p;
        //     next = n;
        // }
        
        Node(Goat val, Node* p = nullptr, Node* n = nullptr) {
            data = val; 
            prev = p;
            next = n;
        }

    };

    Node* head;
    Node* tail;

public:
    // constructor
    DoublyLinkedList() { head = nullptr; tail = nullptr; }

    void push_back(Goat value) {
        Node* newNode = new Node(value);
        if (!tail)  // if there's no tail, the list is empty
            head = tail = newNode;
        else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
    }

    void push_front(Goat value) {
        Node* newNode = new Node(value);
        if (!head)  // if there's no head, the list is empty
            head = tail = newNode;
        else {
            newNode->next = head;
            head->prev = newNode;
            head = newNode;
        }
    }

    void insert_after(Goat value, int position) {
        if (position < 0) {
            cout << "Position must be >= 0." << endl;
            return;
        }

        Node* newNode = new Node(value);
        if (!head) {
            head = tail = newNode;
            return;
        }

        Node* temp = head;
        for (int i = 0; i < position && temp; ++i)
            temp = temp->next;

        if (!temp) {
            cout << "Position exceeds list size. Node not inserted.\n";
            delete newNode;
            return;
        }

        newNode->next = temp->next;
        newNode->prev = temp;
        if (temp->next)
            temp->next->prev = newNode;
        else
            tail = newNode; // Inserting at the end
        temp->next = newNode;
    }


    //updating print functions
    void print() {
        Node* current = head;

        if (!current) {
            cout << "List is empty" << endl;
            return;
        }

        while (current) {
            current->data.print();
            current = current->next;
        }
    }
    void print_reverse() {
        Node* current = tail;

        if (!current) {
            cout << "List is empty" << endl;
            return;
        }

        while (current) {
            current->data.print();
            current = current->prev;
        }
    }
    ~DoublyLinkedList() {
        while (head) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }
};

// Driver program
int main() {
    srand(time(0));

    DoublyLinkedList list;
    int size = rand() % (MAX_LS-MIN_LS+1) + MIN_LS;

    for (int i = 0; i < size; ++i) {
        Goat g;
        list.push_back(g);
    }

    cout << "Forward:" << endl;
    list.print();

    cout << "Backward:" << endl;
    list.print_reverse();

    cout << "Deleting list, then trying to print.\n";
    list.~DoublyLinkedList();
    cout << "List forward: ";
    list.print();

    return 0;
}
