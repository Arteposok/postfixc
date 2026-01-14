#pragma once

class Node{
public:
    void* data;
    Node* next;
    Node(void* data, Node* next=nullptr);
};

class Stack{
public:
    Stack();
    void add(void* value);
    void* pop();
    int len() const;

private:
    Node* root;
};
