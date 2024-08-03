//Create a simple data structure, called Grab Bag, using linked lists.
//The two major functions are to add items into the bag, and remove things from the bag, RANDOMLY.
//The program also keeps track of the count of items in the bag so as to know the size of the bag and give a message to the programmer if the bag is empty.
//The add method is used to add new items into the bag.    
//The get frequency method keeps track of how many times an item is repeated in the bag. 
//The "include random" is used here to generate random numbers to be removed from the bag. 
//The grab() method is used to pick a node at random and remove it from the bag. 
//Finally, the empty() method is used to empty out the entire bag. 

#ifndef GRABBAG_RAMKUMAR_HPP
#define GRABBAG_RAMKUMAR_HPP

#include <iostream>
#include <stdio.h>
#include <random>
#include <stdexcept>
#include <memory> 
#include <time.h>

// Forward declaration of BagNode class
template <typename T>
class BagNode;

// GrabBag class declaration
template <typename T>
class GrabBag {
private:
    int count; // Count of number of items in the bag
    unsigned int seed; // Seed to generate a random number
    BagNode<T>* front; // Pointer to the front node of the linked list
    std::minstd_rand randgen; // Random number generator

public:
    GrabBag(); // Default constructor
    GrabBag(unsigned int seed); // Constructor with seed    
    ~GrabBag(); // Destructor

    int getCurrentSize(); // Get current size of the bag
    bool isEmpty(); // Check if bag is empty
    void add(T item); // Add an item to the bag
    T grab(); // Grab random item from the bag
    int getFrequencyOf(T item); // Get frequency of specific item in the bag
    void empty(); // Empty bag
};

// BagNode class declaration
template <typename T>
class BagNode {
private:
    T item; // Data of node
    BagNode* next; // Pointer to the next node in linked list

public:
    BagNode(T item); // Constructor for BagNode

    T getItem(); // Get item stored in the node
    BagNode* getNext(); // Get the next node in the linked list
    void setNext(BagNode* nextNode); // Set the next node in the linked list

    friend class GrabBag<T>; // Allow GrabBag to access private members of BagNode
};

// Implementation of BagNode class methods
template <typename T>
BagNode<T>::BagNode(T item) : item(item), next(nullptr) {}

template <typename T>
T BagNode<T>::getItem() {
    return item;
}

template <typename T>
BagNode<T>* BagNode<T>::getNext() {
    return next;
}

template <typename T>
void BagNode<T>::setNext(BagNode* nextNode) {
    next = nextNode;
}

// Implementation of GrabBag class methods
template <typename T>
GrabBag<T>::GrabBag() : seed(static_cast<unsigned int>(time(nullptr))), count(0), front(nullptr), randgen(seed) {}

template <typename T>
GrabBag<T>::GrabBag(unsigned int seed) : seed(seed), count(0), front(nullptr), randgen(seed) {}

template <typename T>
int GrabBag<T>::getCurrentSize() {
    return count;
}

template <typename T>
bool GrabBag<T>::isEmpty() {
    return count == 0;
}

template <typename T>
void GrabBag<T>::add(T item) {
    // Create a new node and add it to the front of the linked list
    BagNode<T>* newNode = new BagNode<T>(item);
    newNode->setNext(front);
    front = newNode;
    count++;
}

template <typename T>
T GrabBag<T>::grab() {
    if (isEmpty()) {
        throw std::logic_error("Cannot grab from an empty bag.");
    }

    // Generate a random index to choose a node from the linked list
    std::uniform_int_distribution<int> distribution(0, count - 1);
    int randomIndex = distribution(randgen);

    BagNode<T>* current = front;
    BagNode<T>* previous = nullptr;

    // Traverse the linked list to the randomly chosen index
    for (int i = 0; i < randomIndex; ++i) {
        previous = current;
        current = current->getNext();
    }

    // Remove the chosen node from the linked list
    if (previous) {
        previous->setNext(current->getNext());
    } else {
        front = current->getNext();
    }

    T grabbedItem = current->getItem();
    delete current;
    count--;

    return grabbedItem;
}

template <typename T>
int GrabBag<T>::getFrequencyOf(T item) {
    int frequency = 0;
    BagNode<T>* current = front;

    // Traverse the linked list to increment the count of the frequency of the specified item
    while (current) {
        if (current->getItem() == item) {
            frequency++;
        }
        current = current -> getNext();
    }

    return frequency;
}

template <typename T>
void GrabBag<T>::empty() {
    // Remove all nodes from the linked list and free memory
    while (front) {
        BagNode<T>* temp = front;
        front = front->getNext();
        delete temp;
    }

    count = 0;
}

template <typename T>
GrabBag<T>::~GrabBag() {
    empty();
}

#endif // GRABBAG_RAMKUMAR_HPP