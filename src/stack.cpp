#include "stack.h"

Node::Node(void* data, Node* next)
    : data(data), next(next) {}

Stack::Stack(){
    root=nullptr;
}

void Stack::add(void* value){
    if (!root){
        root = new Node(value, nullptr);
    }else{
        Node* new_node = new Node(value, nullptr);
        new_node->next = root;
        root = new_node;
    }
}

void* Stack::pop(){
    if (!root) return nullptr;
    Node* temp = root;
    void* value = temp->data;
    root = root->next;
    delete temp;
    return value;
}

int Stack::len() const{
    if (!root) return 0;
    int i=0;
    Node* current = root;
    while (current!=nullptr){current=current->next;i++;}
    return i;
}
