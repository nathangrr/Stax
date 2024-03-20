//
//  main.cpp
//  Stax
//
//  Created by Nathan Anthony on 3/19/24.
//

#include <iostream>
#include <cassert>
#include <vector>

// Node class. Holds the data, and a pointer to next/previous
template<typename T>
struct Node {
    T data;
    Node* prev;
    Node* next;
};

// Doubly Linked List class. 
// Methods for adding to the front, back, and arbitarily. And a method for removing a node
template<typename T>
class DoublyLinkedList {
    
private:
    Node<T>* head = nullptr;
    Node<T>* tail = nullptr;

public:

    void insertFront(T data) {
        // Create a new node
        Node<T>* newNode = new Node<T>();
        newNode->data = data;
        
        // If list is empty, set head and tail
        if (!head) {
            head = tail = newNode;
        // Otherwise add the node to the front, O(1) complexity
        } 
        else {
            newNode->next = head;
            head->prev = newNode;
            head = newNode;
        }
    }

    void insertBack(T data) {
        // Create a new node
        Node<T>* newNode = new Node<T>();
        newNode->data = data;
        
        // If list is empty, set head and tail
        if (!tail) {
            head = tail = newNode;
        // Otherwise add the node to the back, O(1) complexity
        } 
        else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
    }
    
    bool removeFront() {
        if (head == nullptr)
            return false;
        
        Node<T>* temp = head;
        head = head->next;
        
        // Set previous to nullptr, first in the list
        if (head)
            head->prev = nullptr;
        // If no head (list is now empty after removal) then set tail to null
        else
            tail->prev = nullptr;
        
        delete temp;
        return true;
    }
    
    bool removeBack() {
        if (tail == nullptr) {
            return false;
        }

        Node<T>* temp = tail;
        tail = tail->prev; // Point to previous node in the list

        if (tail) {
            tail->next = nullptr;
        // If no tail (list is now empty after removal) then set head to null
        } 
        else {
            head = nullptr;
        }

        delete temp;
        return true;
    }

    bool remove(T data) {
        Node<T>* temp = head;
        
        // Step through the list until data is found
        while (temp != nullptr) {
            if (temp->data == data) {
                // If head, move to next node
                if (temp == head) {
                    head = head->next;
                    if (head) {
                        head->prev = nullptr;
                    }
                // If tail, set to previous node
                } 
                else if (temp == tail) {
                    tail = tail->prev;
                    if (tail) {
                        tail->next = nullptr;
                    }
                // Otherwise reset prev/next pointers
                } 
                else {
                    temp->prev->next = temp->next;
                    if (temp->next) {
                        temp->next->prev = temp->prev;
                    }
                }

                delete temp; // Remove the unused node
                return true;
            }
            temp = temp->next; // Move to next element, until data is found
        }
        return false; // data not found
    }
    
    // Add
    void insert(T data, int position) {
        Node<T>* newNode = new Node<T>();
        newNode->data = data;

        // If empty or first position, insert at front
        if (position == 0 || head == nullptr) {
            newNode->next = head;
            if (head != nullptr) {
                head->prev = newNode;
            }
            head = newNode;
            if (tail == nullptr) {
                tail = newNode;
            }
        } 
        // Otherwise we need to insert at position
        else {
            Node<T>* temp = head;
            for (int i = 0; i < position - 1; i++) {
                temp = temp->next;
            }
            
            // Do the insert
            newNode->next = temp->next;
            newNode->prev = temp;
            if (temp->next != nullptr) {
                temp->next->prev = newNode;
            }
            temp->next = newNode;

            // Set the tail if last element
            if (newNode->next == nullptr) {
                tail = newNode;
            }
        }
    }

    // For unit testing assertions
    std::vector<T> toVector() {
        std::vector<T> result;
        Node<T>* current = head;
        while (current != nullptr) {
            result.push_back(current->data);
            current = current->next;
        }
        return result;
    }
};

int main() {
    DoublyLinkedList<int> linkedList;

    // Test inserting
    linkedList.insert(5, 0);
    linkedList.insertBack(1);
    linkedList.insertFront(0);
    linkedList.insertBack(2);

    std::vector<int> expectedList = { 0, 5, 1, 2 };
    assert(linkedList.toVector() == expectedList);
    
    // Test removing
    assert(linkedList.removeFront() == true);
    assert(linkedList.remove(2) == true);
    assert(linkedList.remove(3) == false); // Test data that doesnt exist in the list
    assert(linkedList.removeBack() == true);
    
    std::vector<int> expectedList2 = { 5 };
    assert(linkedList.toVector() == expectedList2);
    
    return 0;
}
