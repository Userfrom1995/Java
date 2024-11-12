Certainly! Let me explain the code step by step so you can fully understand how it works. Here's the breakdown:

### 1. **Imports**
```java
import java.util.Scanner;
```
- The `Scanner` class is imported from the `java.util` package to read user input from the console (e.g., matrix dimensions and elements).

### 2. **RowSumThread Class**
```java
static class RowSumThread extends Thread {
    private int[] row;
    private int rowIndex;

    public RowSumThread(int[] row, int rowIndex) {
        this.row = row;
        this.rowIndex = rowIndex;
    }

    @Override
    public void run() {
        int sum = 0;
        for (int num : row) {
            sum += num;
        }
        System.out.println("Sum of row " + rowIndex + ": " + sum);
    }
}
```
- **Class Declaration**: `RowSumThread` extends the `Thread` class, meaning it will be a thread that can run concurrently with others.
  
- **Instance Variables**:
  - `private int[] row`: This array holds the elements of a particular row in the matrix.
  - `private int rowIndex`: This variable stores the index of the row (used to print the correct row number).

- **Constructor**:
  - The constructor takes two parameters:
    - `row`: The array of integers representing a row in the matrix.
    - `rowIndex`: The index of the row (to identify which row we are processing).

- **run() Method**:
  - This method is called when the thread starts. It's where the thread performs its task (i.e., calculating the sum of a row).
  - It initializes a variable `sum` to 0.
  - Then, it loops through each element in the `row` array and adds each element to `sum`.
  - After the loop finishes, it prints the sum of the row using `System.out.println()`.

### 3. **Main Method**
```java
public static void main(String[] args) {
    Scanner scanner = new Scanner(System.in);
    
    // Read matrix dimensions
    System.out.print("Enter the number of rows (m): ");
    int m = scanner.nextInt();
    
    System.out.print("Enter the number of columns (n): ");
    int n = scanner.nextInt();
    
    // Create matrix A with m rows and n columns
    int[][] matrix = new int[m][n];
    
    // Read matrix elements
    System.out.println("Enter the elements of the matrix:");
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            matrix[i][j] = scanner.nextInt();
        }
    }
    
    // Create and start m threads to compute the row sums
    Thread[] threads = new Thread[m];
    
    for (int i = 0; i < m; i++) {
        // Create a thread for each row
        threads[i] = new RowSumThread(matrix[i], i);
        // Start the thread
        threads[i].start();
    }
    
    // Wait for all threads to finish
    try {
        for (int i = 0; i < m; i++) {
            threads[i].join();
        }
    } catch (InterruptedException e) {
        e.printStackTrace();
    }
    
    // Close the scanner
    scanner.close();
}
```

#### Key Sections in the `main()` Method:

1. **Input the Matrix Dimensions**:
   ```java
   System.out.print("Enter the number of rows (m): ");
   int m = scanner.nextInt();
   
   System.out.print("Enter the number of columns (n): ");
   int n = scanner.nextInt();
   ```
   - The program first prompts the user to enter the number of rows (`m`) and columns (`n`) of the matrix.

2. **Initialize the Matrix**:
   ```java
   int[][] matrix = new int[m][n];
   ```
   - A 2D array `matrix` of size `m x n` is created to store the matrix elements.

3. **Input Matrix Elements**:
   ```java
   System.out.println("Enter the elements of the matrix:");
   for (int i = 0; i < m; i++) {
       for (int j = 0; j < n; j++) {
           matrix[i][j] = scanner.nextInt();
       }
   }
   ```
   - The program prompts the user to enter each element of the matrix. The nested `for` loops iterate over all rows (`i`) and columns (`j`), reading each integer and storing it in the `matrix` array.

4. **Create and Start Threads**:
   ```java
   Thread[] threads = new Thread[m];
   
   for (int i = 0; i < m; i++) {
       threads[i] = new RowSumThread(matrix[i], i);
       threads[i].start();
   }
   ```
   - The program creates an array `threads` of `Thread` objects, one for each row of the matrix.
   - For each row `i`, a new `RowSumThread` is created, passing the row (`matrix[i]`) and the row index (`i`) to the constructor.
   - `start()` is called on each thread to begin its execution. Each thread will execute its `run()` method, which computes the sum of the corresponding row.

5. **Wait for All Threads to Finish**:
   ```java
   try {
       for (int i = 0; i < m; i++) {
           threads[i].join();
       }
   } catch (InterruptedException e) {
       e.printStackTrace();
   }
   ```
   - The `join()` method ensures that the main thread (the one running `main()`) waits for all the worker threads to finish before continuing. Without `join()`, the main thread might exit before the worker threads finish computing the sums.

6. **Close the Scanner**:
   ```java
   scanner.close();
   ```
   - The `Scanner` object is closed to release the resources it holds after we're done reading inputs.

### Why Use Threads?
- Each row of the matrix is independent of the others when calculating the sum, so we can use multiple threads to calculate the row sums concurrently (in parallel).
- This can speed up the computation if there are many rows and the system has multiple CPU cores to handle the threads simultaneously.

### Example Input/Output

**Input**:
```
Enter the number of rows (m): 3
Enter the number of columns (n): 4
Enter the elements of the matrix:
1 2 3 4
5 6 7 8
9 10 11 12
```

**Output** (order may vary due to threading):
```
Sum of row 0: 10
Sum of row 1: 26
Sum of row 2: 42
```

### Summary:
- **Multithreading**: Each row's sum is calculated in a separate thread. This allows multiple rows to be processed simultaneously, taking advantage of modern multi-core processors.
- **Concurrency**: Since each thread works on a different row, there is no need for synchronization, and they can run independently.
- **Thread Management**: The program creates threads dynamically, waits for all threads to finish using `join()`, and prints the results after computation.


Sure! Let's break down the program step by step to understand how it works.

### Overview of the Problem:
- We need to create two threads in Java:
  1. **OddThread**: Prints odd numbers from 1 to 50.
  2. **EvenThread**: Prints even numbers from 1 to 50.
- Both threads will run concurrently and alternately print odd and even numbers.

### 1. **Class Definitions**
```java
static class OddThread extends Thread {
    public void run() {
        for (int i = 1; i <= 50; i += 2) {
            System.out.println("Odd: " + i);
            try {
                Thread.sleep(100);  // Sleep to simulate some work and allow context switching
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }
    }
}
```
#### OddThread Class:
- **Inheritance**: `OddThread` extends the `Thread` class, meaning it is a subclass of `Thread` and can be run as a separate thread in a multithreaded environment.
- **run() Method**:
  - This method is the core of the thread. When the thread starts, it will execute the `run()` method.
  - **Loop**: The loop runs from 1 to 50, with an increment of 2 each time (`i += 2`). This ensures that only odd numbers are printed (`1, 3, 5, ..., 49`).
  - **Printing**: The thread prints the odd number along with the message `Odd: `.
  - **Thread.sleep(100)**: After printing each number, the thread sleeps for 100 milliseconds. This is done to simulate some work being done and also to give the second thread (the `EvenThread`) a chance to run and print its even numbers. Without this sleep, the `OddThread` might complete its task too quickly without allowing the `EvenThread` to print.
  
  - **Exception Handling**: If an interruption occurs while the thread is sleeping (e.g., if the thread is interrupted externally), the `InterruptedException` will be caught and printed.

```java
static class EvenThread extends Thread {
    public void run() {
        for (int i = 2; i <= 50; i += 2) {
            System.out.println("Even: " + i);
            try {
                Thread.sleep(100);  // Sleep to simulate some work and allow context switching
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }
    }
}
```
#### EvenThread Class:
- **Inheritance**: Just like `OddThread`, the `EvenThread` extends the `Thread` class.
- **run() Method**:
  - This method runs a loop from 2 to 50, incrementing by 2 (`i += 2`) to print only even numbers (`2, 4, 6, ..., 50`).
  - **Printing**: Each even number is printed with the prefix `Even: `.
  - **Thread.sleep(100)**: This is included to allow the `OddThread` a chance to run as well. If `sleep()` wasn't there, one thread could potentially monopolize the CPU and the other thread may not get a chance to execute.

### 2. **Main Method**
```java
public static void main(String[] args) {
    // Create two threads: one for odd numbers and one for even numbers
    Thread oddThread = new OddThread();
    Thread evenThread = new EvenThread();

    // Start both threads
    oddThread.start();
    evenThread.start();

    // Wait for both threads to finish
    try {
        oddThread.join();
        evenThread.join();
    } catch (InterruptedException e) {
        e.printStackTrace();
    }

    System.out.println("Both threads have finished printing numbers.");
}
```

#### Inside the `main()` Method:
- **Creating Threads**:
  ```java
  Thread oddThread = new OddThread();
  Thread evenThread = new EvenThread();
  ```
  - Two threads are created: `oddThread` and `evenThread`. These threads are instances of the `OddThread` and `EvenThread` classes, respectively. Each thread will execute its own `run()` method when started.

- **Starting Threads**:
  ```java
  oddThread.start();
  evenThread.start();
  ```
  - The `start()` method is called on both threads. This doesn't directly invoke the `run()` method; rather, it causes the JVM to schedule the threads for execution. When the threads are started, the `run()` method of both threads will be executed concurrently.

- **Waiting for Threads to Finish**:
  ```java
  try {
      oddThread.join();
      evenThread.join();
  } catch (InterruptedException e) {
      e.printStackTrace();
  }
  ```
  - The `join()` method is called on both threads. The `join()` method causes the main thread (the one executing `main()`) to wait until the specified thread has finished executing.
  - **Why `join()`?**: Without `join()`, the main thread could finish before the odd and even threads have completed their tasks, causing the program to terminate prematurely. By using `join()`, we ensure that the main thread waits for both `oddThread` and `evenThread` to finish before printing the final message.
  
- **Final Message**:
  ```java
  System.out.println("Both threads have finished printing numbers.");
  ```
  - Once both threads have completed (i.e., after `join()` returns), this message is printed to indicate that all the numbers have been printed.

### Key Concepts:
1. **Multithreading**: 
   - Threads run concurrently, meaning that `OddThread` and `EvenThread` are working at the same time. However, due to the thread scheduling of the operating system, the exact order of execution can vary.
   - `start()` and `join()` are fundamental methods for controlling thread execution: `start()` begins the thread, and `join()` makes the main thread wait until the specified thread finishes.

2. **Thread.sleep()**: 
   - By using `Thread.sleep(100)`, we allow the CPU to switch between threads. Without `sleep()`, the odd and even threads would compete for the CPU, potentially leading to one thread finishing quickly and the other thread not getting a chance to run. By adding a short delay, we simulate the threads yielding to each other, giving a more interleaved output (alternating odd and even numbers).

3. **Thread Execution Order**: 
   - Even though the threads are running concurrently, there's no guarantee of which thread will print first or how they will alternate. The actual output order can vary depending on how the operating system schedules the threads. However, in this case, both threads will finish printing their respective numbers between 1 and 50.

### Sample Output:
```text
Odd: 1
Even: 2
Odd: 3
Even: 4
Odd: 5
Even: 6
...
Odd: 49
Even: 50
Both threads have finished printing numbers.
```

### Possible Variations:
- The exact order of odd and even numbers may differ depending on the timing and scheduling of the threads by the operating system. For example, you may see something like:
  ```text
  Odd: 1
  Even: 2
  Odd: 3
  Even: 4
  ...
  ```

### Conclusion:
This program demonstrates basic multithreading in Java. It creates two threads, one for printing odd numbers and another for even numbers, and runs them concurrently. By using `Thread.sleep()` and `Thread.join()`, we control the timing of the threads and ensure that the program waits for both threads to complete their execution before finishing.

Certainly! Let's break down the code and explain the key concepts step by step. This C++ program implements a **singly linked list** using **self-referential classes**, where each `Node` object points to another `Node` object.

### Key Concepts:
1. **Self-Referential Class**:  
   A self-referential class is one in which a class contains a pointer to an instance of itself (or another instance of the same type). In this case, the `Node` class is self-referential because it contains a pointer to another `Node` object. This allows us to create linked structures like linked lists, where each node points to the next node in the list.

2. **Singly Linked List**:  
   A singly linked list is a linear collection of nodes where each node contains:
   - Data (in our case, an integer value),
   - A pointer to the next node in the list (or `nullptr` if it is the last node).
   
   The linked list starts from a `head` pointer, which points to the first node. Operations like insertion, deletion, and traversal are based on updating these node pointers.

---

### Step-by-Step Explanation of the Code:

#### 1. **Node Class Definition**:
```cpp
class Node {
public:
    int data;
    Node* next;  // Pointer to the next node in the list

    // Constructor to initialize node with a value
    Node(int value) {
        data = value;
        next = nullptr;  // Initially, the next pointer is nullptr
    }
};
```
- **Data**: Each `Node` stores an integer (`data`), which is the value stored in that node.
- **Next Pointer**: `Node* next` is a pointer to another `Node` object, which represents the link to the next node in the list. If a node is the last one, `next` will be `nullptr`.
- **Constructor**: The constructor initializes the node with a value (`data`), and the `next` pointer is initially set to `nullptr` (indicating that this node is not linked to any other node when created).

#### 2. **LinkedList Class Definition**:
```cpp
class LinkedList {
private:
    Node* head;  // Pointer to the first node in the list

public:
    // Constructor
    LinkedList() {
        head = nullptr;  // Initially, the list is empty (no nodes)
    }

    // Destructor
    ~LinkedList() {
        while (head != nullptr) {
            deleteNode();  // Deallocates memory for the nodes
        }
    }
```
- **head**: This is a pointer to the first node of the linked list. If the list is empty, `head` is `nullptr`.
- **Constructor**: The constructor initializes `head` to `nullptr`, indicating that the list starts empty.
- **Destructor**: The destructor ensures that when the `LinkedList` object is destroyed, all the dynamically allocated memory for nodes is freed by calling the `deleteNode()` method (which you can imagine as a helper function to delete nodes one by one).

#### 3. **Insert at End**:
```cpp
void insertAtEnd(int value) {
    Node* newNode = new Node(value);  // Create a new node with the given value
    if (head == nullptr) {
        head = newNode;  // If the list is empty, the new node becomes the head
    } else {
        Node* temp = head;
        while (temp->next != nullptr) {
            temp = temp->next;  // Traverse to the last node
        }
        temp->next = newNode;  // Link the new node after the last node
    }
    cout << "Inserted " << value << " at the end." << endl;
}
```
- **Creating a New Node**: A new node (`newNode`) is created with the given value. The constructor of `Node` initializes the node’s `data` and sets `next` to `nullptr`.
- **Empty List Check**: If the list is empty (i.e., `head` is `nullptr`), the new node is directly assigned to `head`.
- **Traverse to Last Node**: If the list is not empty, the program uses a `while` loop to traverse the list by following the `next` pointers until it reaches the last node (where `next` is `nullptr`).
- **Linking the New Node**: The `next` pointer of the last node is updated to point to the new node, thus inserting the new node at the end.

#### 4. **Delete from Beginning**:
```cpp
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
```
- **Empty List Check**: If the list is empty (i.e., `head` is `nullptr`), a message is printed, and the function exits.
- **Deleting the First Node**: The `head` pointer is updated to point to the next node in the list (`head = head->next`), effectively removing the first node from the list.
- **Deallocating Memory**: The old first node (pointed to by `temp`) is deleted using `delete temp`, freeing the dynamically allocated memory for that node.

#### 5. **Display the List**:
```cpp
void display() {
    if (head == nullptr) {
        cout << "The list is empty." << endl;
        return;
    }
    Node* temp = head;
    cout << "List: ";
    while (temp != nullptr) {
        cout << temp->data << " ";  // Print data of each node
        temp = temp->next;  // Move to the next node
    }
    cout << endl;
}
```
- **Empty List Check**: If the list is empty (`head == nullptr`), a message is printed.
- **Traversing the List**: If the list is not empty, a `while` loop is used to traverse the list. In each iteration, the data of the current node (`temp->data`) is printed, and `temp` is updated to the next node (`temp = temp->next`).

#### 6. **Main Function**:
```cpp
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
```
- **Menu Interface**: The main function provides a menu with options to insert a node at the end, delete from the beginning, display the list, or exit the program.
- **Loop**: A `while (true)` loop keeps the program running until the user chooses to exit. Based on the user's choice, the corresponding method is called (insert, delete, display, or exit).

### Key Operations:

1. **Insertion at the End**:  
   The program adds a new node to the end of the list. If the list is empty, the new node becomes the head; otherwise, it traverses the list to find the last node and appends the new node after it.

2. **Deletion from the Beginning**:  
   The program removes the node at the beginning of the list by updating the `head` pointer to the next node and deallocating the old head node.

3. **Display**:  
   The program traverses the list from the head to the end, printing each node's data.

### Sample Run:

```
1. Insert at end
2. Delete from beginning
3. Display list
4. Exit
Enter your choice: 1
Enter the value to insert: 10
Inserted 10 at the end.

1. Insert at end
2. Delete from beginning
3. Display list
4. Exit
Enter your choice: 1
Enter the value to insert: 20
Inserted 20 at the end.

1. Insert at end
2. Delete from beginning
3. Display list
4. Exit
Enter your choice: 3
List: 10 20

1. Insert at end
2. Delete from beginning
3. Display list
4. Exit
Enter your choice: 2
Deleted 10 from the beginning.

1. Insert at end
2. Delete from beginning
3. Display list
4. Exit
Enter your choice: 3
List: 20
```

In this run, we insert `10` and `20` into the list, display the list, delete `10` from the beginning, and then display the remaining list (`20`).

Sure! Let's break down the changes and the entire process for a clearer understanding of how the code works and why the changes were necessary.

### Understanding the Code

The code you've shared is a simple implementation of a **singly linked list** in C++, where each node contains an integer `data` and a pointer `next` that points to the next node in the list. The linked list class `LinkedList` is responsible for managing the list operations like inserting a node, deleting a node, and displaying the list.

#### Key Components:

1. **Node Class:**
   - Each `Node` holds two things:
     - `data`: the value stored in the node (in this case, an integer).
     - `next`: a pointer that points to the next `Node` in the list. If it's the last node, `next` will be `nullptr`.

   ```cpp
   class Node {
   public:
       int data;
       Node* next;

       Node(int value) {
           data = value;
           next = nullptr;  // initially points to nullptr, meaning no next node
       }
   };
   ```

2. **LinkedList Class:**
   - The `LinkedList` class manages the linked list. It contains:
     - `head`: a pointer to the first node in the list.
     - Methods to insert, delete, and display nodes in the list.

#### Problem in the Destructor

The **error** you were facing was in the **destructor** of the `LinkedList` class. Here's the original code snippet where the error occurs:

```cpp
~LinkedList() {
    while (head != nullptr) {
        deleteNode();  // Calling deleteNode(), but it's not defined
    }
}
```

The issue here is that `deleteNode()` is **not defined** anywhere in your class, so the compiler doesn’t know how to handle this call.

### Solution

#### Two Approaches to Fixing the Destructor

We can fix this in **two ways**:

### Solution 1: Directly Deleting Nodes in the Destructor (Simpler Approach)

Instead of calling a non-existent `deleteNode()` function, we can directly delete the nodes inside the destructor. We will iterate through the list, deleting each node one by one.

Here’s how we modify the destructor:

```cpp
~LinkedList() {
    while (head != nullptr) {
        Node* temp = head;
        head = head->next;  // Move the head pointer to the next node
        delete temp;  // Delete the old head node
    }
}
```

#### Explanation of this Code:
- **While Loop**: The loop will continue as long as there are nodes in the list (`head != nullptr`).
- **Node* temp = head**: We store the current `head` node in a temporary pointer `temp` because we need to delete it later.
- **head = head->next**: We move the `head` pointer to the next node in the list.
- **delete temp**: After moving the `head`, we delete the old `head` node, freeing the memory.

This approach effectively deletes all the nodes in the list when the `LinkedList` object is destroyed, preventing memory leaks.

### Solution 2: Using `deleteNode()` (Extra Function)

Alternatively, you can create a separate helper method called `deleteNode()` to handle the deletion of the first node in the list. This method will be responsible for moving the `head` and deleting the node.

Here's how the helper function `deleteNode()` would look:

```cpp
void deleteNode() {
    if (head == nullptr) {
        return;  // No node to delete
    }
    Node* temp = head;
    head = head->next;  // Move the head pointer to the next node
    delete temp;  // Delete the old head node
}
```

Then, in the destructor, you can call `deleteNode()` to delete all nodes:

```cpp
~LinkedList() {
    while (head != nullptr) {
        deleteNode();  // Use the deleteNode method to delete nodes
    }
}
```

This approach works as well but adds an extra function call. The first solution is simpler and more efficient in this case, so I recommend using it.

### Full Corrected Code with Direct Deletion in Destructor

Here’s the final corrected version of your code using the direct deletion approach in the destructor:

```cpp
#include <iostream>
using namespace std;

// Node class definition
class Node {
public:
    int data;
    Node* next;

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
    LinkedList() {
        head = nullptr;  // Initialize head to nullptr, meaning the list is empty
    }

    ~LinkedList() {
        while (head != nullptr) {
            Node* temp = head;
            head = head->next;  // Move the head pointer to the next node
            delete temp;  // Delete the old head node
        }
    }

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

    void deleteFromBeginning() {
        if (head == nullptr) {
            cout << "List is empty. Cannot delete." << endl;
            return;
        }
        Node* temp = head;
        head = head->next;  // Move the head pointer to the next node
        cout << "Deleted " << temp->data << " from the beginning." << endl;
        delete temp;  // Delete the old head node
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
```

### Summary of Fix:
- **Destructor**: The `~LinkedList()` destructor was modified to directly delete nodes, freeing up memory as each node is removed.
- **Logic**: In both approaches, the goal is to prevent memory leaks by deleting all nodes when the linked list is destroyed.

Now, when the program ends, or the linked list is destroyed, the memory for all nodes is properly freed, avoiding memory leaks.

Sure! Let me explain how the program works in more detail.

### Overview

The program implements a **Producer-Consumer** problem using multithreading in Java. The problem is solved using a shared **`BlockingQueue`** (acting as the stack) to communicate between two producer threads and one consumer thread.

#### Components:
1. **Producer Threads**: These threads produce items and push them onto the shared stack (queue). Each producer produces 7 items in this example.
2. **Consumer Thread**: This thread consumes (pops) items from the stack. It consumes a total of 14 items—7 produced by each of the two producers.
3. **BlockingQueue**: A thread-safe queue that handles the synchronization between producer and consumer threads. The queue size is limited to 10 to prevent stack overflow.

The key goal is to ensure that:
- The stack does not overflow (no more than 10 items at any time).
- The consumer doesn’t try to pop from an empty stack (no underflow).
- Each item is consumed exactly once.

### Breakdown of the Code:

#### 1. **Producer Class**:
```java
class Producer implements Runnable {
    private final BlockingQueue<String> stack;
    private final int producerId;
    private static final int ITEMS_TO_PRODUCE = 7;

    public Producer(BlockingQueue<String> stack, int producerId) {
        this.stack = stack;
        this.producerId = producerId;
    }

    @Override
    public void run() {
        try {
            for (int i = 0; i < ITEMS_TO_PRODUCE; i++) {
                String item = "Item-" + producerId + "-" + (i + 1);
                System.out.println("Producer " + producerId + " pushing: " + item);

                // Put the item into the stack, will block if the stack is full
                stack.put(item);

                // Sleep for 500ms after pushing the item
                Thread.sleep(500);
            }
        } catch (InterruptedException e) {
            Thread.currentThread().interrupt();
        }
    }
}
```

- **`Producer` Class** implements the `Runnable` interface, so it can be run on a separate thread.
- Each producer pushes 7 items to the shared `BlockingQueue` (acting as the stack).
- The `stack.put(item)` method blocks the producer if the stack is full (with more than 10 items). This ensures that a producer doesn't add an item when the stack is full.
- After each item is pushed, the producer sleeps for 500ms (`Thread.sleep(500)`).

#### 2. **Consumer Class**:
```java
class Consumer implements Runnable {
    private final BlockingQueue<String> stack;
    private static final int TOTAL_ITEMS_TO_CONSUME = 14; // 2 producers * 7 items each

    public Consumer(BlockingQueue<String> stack) {
        this.stack = stack;
    }

    @Override
    public void run() {
        try {
            int itemsConsumed = 0;
            while (itemsConsumed < TOTAL_ITEMS_TO_CONSUME) {
                // Take an item from the stack, will block if the stack is empty
                String item = stack.take();
                System.out.println("Consumer popping: " + item);

                // Sleep for 600ms after consuming the item
                Thread.sleep(600);

                itemsConsumed++;
            }
        } catch (InterruptedException e) {
            Thread.currentThread().interrupt();
        }
    }
}
```

- The **`Consumer` Class** also implements `Runnable`.
- The consumer pops items from the `BlockingQueue` using `stack.take()`, which blocks the consumer if the stack is empty.
- After consuming each item, the consumer sleeps for 600ms (`Thread.sleep(600)`).
- The consumer continues to consume until it has consumed a total of 14 items (7 from each producer).

#### 3. **Main Method** (Starting Threads):
```java
public class ProducerConsumerExample {
    public static void main(String[] args) {
        // Create a BlockingQueue with a maximum size of 10 (acting as a stack)
        BlockingQueue<String> stack = new ArrayBlockingQueue<>(10);

        // Create producer threads
        Thread producer1 = new Thread(new Producer(stack, 1));
        Thread producer2 = new Thread(new Producer(stack, 2));

        // Create consumer thread
        Thread consumer = new Thread(new Consumer(stack));

        // Start the threads
        producer1.start();
        producer2.start();
        consumer.start();

        // Wait for all threads to finish
        try {
            producer1.join();
            producer2.join();
            consumer.join();
        } catch (InterruptedException e) {
            Thread.currentThread().interrupt();
        }
    }
}
```

- In the `main` method, we create the shared `BlockingQueue` with a capacity of 10. This queue will act as our stack.
- Two `Producer` threads (`producer1` and `producer2`) are created, each producing 7 items.
- One `Consumer` thread is created to consume the 14 items from the stack.
- `start()` is called on each thread to begin execution.
- `join()` is called on each thread to ensure the main thread waits for all threads to finish before it terminates.

### Key Concepts:
1. **Thread Safety with BlockingQueue**:
   - The `BlockingQueue` automatically synchronizes access between the producer and consumer threads.
   - The `put()` and `take()` methods block the calling thread when the queue is full or empty, respectively, which prevents stack overflow (producers can't add items if the queue is full) and underflow (consumers can't consume items if the queue is empty).

2. **Producer-Consumer Synchronization**:
   - **Producers**: They add items to the stack, but they must wait if the stack is full (when there are already 10 items). This is handled by `stack.put(item)`.
   - **Consumer**: The consumer waits for an item to be available if the stack is empty. This is managed by `stack.take()`.

3. **Thread Sleeping**:
   - Both the producers and the consumer thread sleep after performing their task (500ms for producers and 600ms for the consumer), which simulates the time it takes for each operation to complete and provides a realistic pacing.

### Execution Flow:
1. The producer threads start and begin pushing items onto the shared stack.
2. The consumer thread starts and begins consuming items from the stack.
3. Both the producers and the consumer respect the stack size limit and block appropriately when the stack is full or empty.
4. The program ensures that all items are consumed exactly once and that no overflow or underflow happens.

### File Naming and Execution:
Since the public class is named `ProducerConsumerExample`, the filename should also be **`ProducerConsumerExample.java`**. To run the program:

1. **Compile** the Java file:
   ```bash
   javac ProducerConsumerExample.java
   ```

2. **Run** the program:
   ```bash
   java ProducerConsumerExample
   ```

### Example Output:

```bash
Producer 1 pushing: Item-1-1
Producer 2 pushing: Item-2-1
Consumer popping: Item-1-1
Producer 1 pushing: Item-1-2
Producer 2 pushing: Item-2-2
Consumer popping: Item-2-1
...
```

In this output:
- Each item is pushed to the stack by one of the producers.
- The consumer pops items from the stack and processes them.
- The program ensures no stack overflow (because the queue is limited to 10 items) and no underflow (because the consumer waits if the queue is empty).

### Summary:
This program demonstrates a classic **Producer-Consumer** problem in multithreading. The `BlockingQueue` handles the synchronization of the shared resource (the stack) between the producer and consumer threads. By managing the sleep times and synchronization, we ensure that the stack operates without overflow or underflow, and each item is consumed exactly once.