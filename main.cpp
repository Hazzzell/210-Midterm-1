#include <iostream>
#include <ctime>
#include <cstdlib>
using namespace std;

// define constant for the random list 
const int MIN_NR = 10, MAX_NR = 99, MIN_LS = 5, MAX_LS = 20;

// Doubly Linked List Class
class DoublyLinkedList {
// only access by class's methods
private:
    // define a Node structure which represents each element
    struct Node {
        int data;
        // pointer to previous node            
        Node* prev;
        // pointer to next node
        Node* next;
        // node constructor, initialize the value and pointer
        Node(int val, Node* p = nullptr, Node* n = nullptr) {
            data = val; 
            prev = p;
            next = n;
        }
    };

    Node* head;     // pointer to first node in the list
    Node* tail;     // pointer to last node in the list

// can be called from outside the class
public:
    // constructor, initialize both head and tail
    DoublyLinkedList() { head = nullptr; tail = nullptr; } 

    // insert after a given position 
    void insert_after(int value, int position) {
        if (position < 0) {
            cout << "Position must be >= 0." << endl;
            return;
        }

        // create a new node
        Node* newNode = new Node(value);

        // if the list is empty, new node becomes head and tail
        if (!head) {
            head = tail = newNode;
            return;
        }

        // traversing from head
        Node* temp = head;
        // move temp to node at position
        for (int i = 0; i < position && temp; ++i)
            temp = temp->next;

        // position exceeds list size
        if (!temp) {
            cout << "Position exceeds list size. Node not inserted.\n";
            delete newNode;
            return;
        }

        // new node points to next node then temp
        newNode->next = temp->next;
        newNode->prev = temp;

        // temp is not tail
        if (temp->next)
            // next node's prev point to new node
            temp->next->prev = newNode;
        else
            // new node is tail
            tail = newNode;
        // temp points forward to new node
        temp->next = newNode;
    }

    // delete node by value
    void delete_val(int value) {
        if (!head) return;      // empty list

        // start at begining head
        Node* temp = head;
        
        // traverse till there is node with match value
        while (temp && temp->data != value)
            temp = temp->next;

        // value not found
        if (!temp) return; 

        // not head, prev node skips over temp
        if (temp->prev)
            temp->prev->next = temp->next;
        else
            head = temp->next;      // delete head, move the head pointer

        // not tail, next node skips over temp
        if (temp->next)
            temp->next->prev = temp->prev;
        else
            tail = temp->prev;      // delete tail, move the tail pointer
        
        // delete temp memory
        delete temp;
    }

    // delete node by position
    void delete_pos(int pos) {
        // empty list
        if (!head) {
            cout << "List is empty." << endl;
            return;
        }
        
        // first position with pop_front()
        if (pos == 1) {
            pop_front();
            return;
        }

        // start at begining head
        Node* temp = head;
    
        // move temp to node at position
        for (int i = 1; i < pos; i++){
            // position exceed
            if (!temp) {
                cout << "Position doesn't exist." << endl;
                return;
            }
            else
                temp = temp->next;          // move forward
        }
        // check again outside for loop
        if (!temp) {
            cout << "Position doesn't exist." << endl;
            return;
        }
        
        // last node with pop_back()
        if (!temp->next) {
            pop_back();
            return;
        }
        
        // link the previous and next node to skip temp
        Node* tempPrev = temp->prev;
        tempPrev->next = temp->next;
        temp->next->prev = tempPrev;
        delete temp;
    }

    // push value to back
    void push_back(int v) {
        // allocate new node
        Node* newNode = new Node(v);
        // empty list, head and tail point to new node
        if (!tail)
            head = tail = newNode;
        else {
            tail->next = newNode;       // tail point forward new node
            newNode->prev = tail;       // new node point to tail
            tail = newNode;             // update tail
        }
    }
    
    // push value to front
    void push_front(int v) {
        // allocate new node
        Node* newNode = new Node(v);
        // empty list, head and tail point to new node
        if (!head)
            head = tail = newNode;
        else {
            newNode->next = head;       // new node point forward head
            head->prev = newNode;       // head point to new node
            head = newNode;             // update head
        }
    }
    
    // delete head, pop front
    void pop_front() {
        // empty list
        if (!head) {
            cout << "List is empty." << endl;
            return;
        }

        // save temp head
        Node * temp = head;
        // more than one node
        if (head->next) {
            head = head->next;          // head move forward
            head->prev = nullptr;       // new head has no previous
        }   
        // one node
        else
            head = tail = nullptr;      // empty list
        delete temp;                    // delete temp memory
    }

    // delete tail, pop back
    void pop_back() {
        // empty list
        if (!tail) {
            cout << "List is empty." << endl;
            return;
        }
        // save temp tail
        Node * temp = tail;
        // more than one node
        if (tail->prev) {
            tail = tail->prev;          // tail move backward
            tail->next = nullptr;       // new tail point to nothing 
        }
        // one node 
        else
            head = tail = nullptr;      // empty list 
        delete temp;                    // delete temp memory
    }

    // destructor 
    ~DoublyLinkedList() {
        // while not empty list
        while (head) {
            Node* temp = head;          // save current head
            head = head->next;          // move head forward
            delete temp;                // delete temp memory
        }
    }

    // print list
    void print() {
        Node* current = head;           // start at head
        // empty list
        if (!current) {
            cout << "List is empty." << endl;
            return;
        }
        while (current) {
            cout << current->data << " ";
            current = current->next;    // move to next node
        }
        cout << endl;
    }

    // print list reverse
    void print_reverse() {
        Node* current = tail;           // start at tail
        // empty list
        if (!current) { 
            cout << "List is empty." << endl;
            return;
        }
        while (current) {
            cout << current->data << " ";
            current = current->prev;    // move to previous node 
        }
        cout << endl;
    }

    // print every data starting with the first element
    void every_other_element(){
        Node* current = head;
        // empty list
        if (!current) { 
            cout << "List is empty." << endl;
            return;
        }
        // current point to a valid node
        while (current) {
            // print node pointing to 
            cout << current->data << " ";
            // move current two steps forward
            if (current->next){
                current = current->next->next;
            }
            // initialize to exit 
            else {
                current = nullptr;
            }
        }
        cout << endl; 
    }
};

int main() {
    // empty doubly linked list
    DoublyLinkedList list;
    int size = rand() % (MAX_LS-MIN_LS+1) + MIN_LS;
    
    // randomly generate number
    cout << "List with " << size << " random numbers:\n";

    for (int i = 0; i < size; ++i)
        list.push_back(rand() % (MAX_NR-MIN_NR+1) + MIN_NR);
    list.print();
    cout << endl;

    cout << "Every other element \n";
    list.every_other_element();
    cout << endl;

    cout << "Deleting the first node \n";
    list.pop_front();
    list.print();
    cout << endl;

    cout << "Deleting the last node \n";
    list.pop_back();
    list.print();
    cout << endl;

    cout << "Deleting node at position 2 \n";
    list.delete_pos(2);
    list.print();
    cout << endl;

    cout << "Deleting node with value 50\n";
    list.delete_val(50);
    list.print();
    cout << endl;

    cout << "Reverse order \n";
    list.print_reverse();
    cout << endl;

    return 0;
}

