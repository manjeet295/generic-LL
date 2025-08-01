#ifndef LINKEDLIST_H
#define LINKEDLIST_H
#include <iostream>
using namespace std;

template <typename T>
class Node{
public:
    T data;
    Node* next;
    Node(T val){
        data = val;
        next = nullptr;
    }
};

template <typename T>
class LinkedList{
private:
    Node<T>* head;
public:
    
    LinkedList(){
    head = nullptr;
    
}
void insertAtFirst(T val){
        Node<T>* newNode = new Node<T>(val);
        newNode->next = head;
        head = newNode;
    }

    void deleteNode(T val){
        if (!head) return;
        if(head->data == val){
            Node<T>* temp = head;
            head = head->next;
            delete temp;
            return;
        }

        Node<T>* current = head;
        while(current->next && current->next->data != val){
            current = current->next;
        }
        if(current->next){
            Node<T>* temp = current->next;
            current->next = current->next->next;
            delete temp;
        }
    }
void insertAtEnd(T val){
    Node<T>* newNode = new Node<T>(val);
    if(!head){
        head = newNode;
    }
    else{
        Node<T>* temp = head;
        while(temp->next!=nullptr){
            temp = temp->next;
    }
        temp->next = newNode;
}
}
void display(){
    Node<T>* temp=head;

    while(temp != nullptr){
        cout<< temp->data <<" -> ";
        temp=temp->next;

    }
    cout << "NULL"<< endl;
    
}
};



#endif
