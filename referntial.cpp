#include <iostream>
using namespace std;

// Node class definition
class Node {
public:
    int data;
    Node* next;  // Self-referential pointer (points to another Node)

    // Constructor to initialize node with a value
    Node(int value) {
        data = value;
        next = nullptr;
    }
};

// LinkedList class definition
class LinkedList {
private:
    Node* head;  // Points to the first node in the list

public:
    // Constructor to initialize the list with an empty head
    LinkedList() {
        head = nullptr;
    }

    // Destructor to clean up the list and prevent memory leaks
    ~LinkedList() {
        while (head != nullptr) {
            deleteNode();
        }
    }

    // Method to insert a node at the end of the list
    void insertAtEnd(int value) {
        Node* newNode = new Node(value);
        if (head == nullptr) {
            head = newNode;  // If the list is empty, make the new node the head
        } else {
            Node* temp = head;
            while (temp->next != nullptr) {
                temp = temp->next;  // Traverse to the last node
            }
            temp->next = newNode;  // Insert the new node at the end
        }
        cout << "Inserted " << value << " at the end." << endl;
    }

    // Method to delete a node from the beginning of the list
    void deleteFromBeginning() {
        if (head == nullptr) {
            cout << "List is empty. Cannot delete." << endl;
            return;
        }
        Node* temp = head;
        head = head->next;  // Move the head pointer to the next node
        cout << "Deleted " << temp->data << " from the beginning." << endl;
        delete temp;  // Free the memory of the old head node
    }

    // Method to display the entire list
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

// Main function to interact with the LinkedList
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
