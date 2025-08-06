#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <iostream>
using namespace std;

template <typename T>
class LNode {
public:
    T data;
    LNode* next;

    LNode(T val) {
        data = val;
        next = NULL;
    }
};

template <typename T>
class List {
private:
    LNode<T>* head;

public:
    List() {
        head = nullptr;
    }

    void insertAtEnd(T val) {
        LNode<T>* newNode = new LNode<T>(val);
        if (!head) {
            head = newNode;
        } else {
            LNode<T>* temp = head;
            while (temp->next != NULL) {
                temp = temp->next;
            }
            temp->next = newNode;
        }
    }

    int length() {
        int count = 0;
        LNode<T>* temp = head;
        while (temp != NULL) {
            count++;
            temp = temp->next;
        }
        return count;
    }

    void display() {
        LNode<T>* temp = head;
        while (temp != NULL) {
            cout << temp->data << " -> ";
            temp = temp->next;
        }
        cout << "NULL" << endl;
    }

    T getAt(int index) {
        int i = 0;
        LNode<T>* temp = head;
        while (temp != NULL) {
            if (i == index) {
                return temp->data;
            }
            i++;
            temp = temp->next;
        }
        return T(); // default value if out of range
    }

    LNode<T>* getHead() {
        return head;
    }
};

#endif
