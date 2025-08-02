#include "generic.h"
int main() {
    LinkedList<int> l1;
    l1.insertAtEnd(1111);
    l1.insertAtEnd(15);
    l1.insertAtEnd(8);
    l1.display();


    LinkedList<string> l2;
    l2.insertAtEnd("name");
    l2.insertAtEnd("class");
    l2.display();

    return 0;
}
