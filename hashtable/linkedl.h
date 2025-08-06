#ifndef NODE_H
#define NODE_H

#include <iostream>
using namespace std;

template<typename T, typename T1>
class Node {
public:
    T key;
    T1 value;
    Node<T, T1>* next;

    Node(T key, T1 value) {
        this->key = key;
        this->value = value;
        next = NULL;
    }
};

template <typename T, typename T1>
class LinkedList {
private:
    Node<T, T1>* head;

public:
    LinkedList() {
        head = NULL;
    }

    Node<T, T1>* getHead() {
        return head;
    }


    void insertAtEnd(T key, T1 value) {
        Node<T, T1>* newNode = new Node<T, T1>(key, value);
        if (!head) {
            head = newNode;
        } else {
            Node<T, T1>* temp = head;
            while (temp->next != NULL) {
                temp = temp->next;
            }
            temp->next = newNode;
        }
    }

    void insertAtFirst(T key,T1 value){
        Node<T, T1>* newNode = new Node<T,T1>(key, value);
        newNode->next = head;
        head = newNode;
    }

    void deleteAtFirst(){
        if(head==NULL){
            cout << "List is empty, nothing to delete." << endl;
            return;
        }
        Node<T,T1>* temp = head;
        head = head->next;
        delete temp;
    }

    void deleteAtLast(){
        if(head==NULL){
            cout << "List is empty, nothing to delete." << endl;
            return;
        }
        if(head->next==NULL){
            delete head;
            head = NULL;
            return;
        }
        Node<T,T1>* temp = head;
        while(temp->next->next != NULL){
            temp = temp->next;
        }
        delete temp->next;
        temp->next = NULL;
    }

    void display(){
        Node<T,T1>* temp = head;
        while(temp != NULL){
            cout << "(" << temp->key << ", " << temp->value << ") -> ";
            temp = temp->next;
        }
        cout << "NULL" << endl;
    }
};

#endif
