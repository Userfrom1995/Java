#include <iostream>
using namespace std;


class Node {
public:
    int data;
    Node* next;  

    
    Node(int value) {
        data = value;
        next = nullptr;
    }
};


class LinkedList {
private:
    Node* head;  

public:
    
    LinkedList() {
        head = nullptr;
    }

    
    ~LinkedList() {
        while (head != nullptr) {
            Node* temp = head;
            head = head->next;  
            delete temp;  
        }
    }

   
    void insertAtEnd(int value) {
        Node* newNode = new Node(value);
        if (head == nullptr) {
            head = newNode;  
        } else {
            Node* temp = head;
            while (temp->next != nullptr) {
                temp = temp->next;  
            temp->next = newNode;  
        }
        cout << "Inserted " << value << " at the end." << endl;
    }
    }

    
    void deleteFromBeginning() {
        if (head == nullptr) {
            cout << "List is empty. Cannot delete." << endl;
            return;
        }
        Node* temp = head;
        head = head->next;  
        cout << "Deleted " << temp->data << " from the beginning." << endl;
        delete temp;  
    }

   
    void display() {
        if (head == nullptr) {
            cout << "The list is empty." << endl;
            return;
        }
        Node* temp = head;
        cout << "List: ";
        while (temp != nullptr) {
            cout << temp->data << " ";
            temp = temp->next;
        }
        cout << endl;
    }
};


int main() {
    LinkedList list;
    int choice, value;

    while (true) {
        cout << "\n1. Insert at end" << endl;
        cout << "2. Delete from beginning" << endl;
        cout << "3. Display list" << endl;
        cout << "4. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter the value to insert: ";
                cin >> value;
                list.insertAtEnd(value);
                break;

            case 2:
                list.deleteFromBeginning();
                break;

            case 3:
                list.display();
                break;

            case 4:
                cout << "Exiting program..." << endl;
                return 0;

            default:
                cout << "Invalid choice, please try again." << endl;
        }
    }

    return 0;
}
