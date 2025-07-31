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
