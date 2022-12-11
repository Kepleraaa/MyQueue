/*
 * File: main.cpp
 * --------------
 * Blank C++ project configured to use Stanford cslib and Qt
 */

#include "console.h"
#include "simpio.h"
#include "error.h"
using namespace std;

template <typename ValueType>
class LinkedQueue{
public:
    LinkedQueue();
    ~LinkedQueue();

    LinkedQueue(const LinkedQueue& queue2);
    LinkedQueue& operator=(const LinkedQueue& queue2);

    void enqueue(const ValueType& value);
    ValueType dequeue();
    const ValueType& peek() const;
    int size() const;
    bool isEmpty() const;   
    void clear();
    void show() const;

private:
    struct node{
        ValueType data;
        node* next;
    };
    node* head;
    node* tail;
};

template <typename ValueType>
LinkedQueue<ValueType>::LinkedQueue(){
    head=tail=nullptr;
}

template <typename ValueType>
LinkedQueue<ValueType>::~LinkedQueue(){
    while (head!=nullptr){
        node* temp=head;
        head=head->next;
        delete temp;
    }
}

template <typename ValueType>
LinkedQueue<ValueType>::LinkedQueue(const LinkedQueue& queue2){
    node* cur=nullptr;
    node* cur2=queue2.head;
    while (cur2!=nullptr){
        node* newNode=new node{cur2->data,nullptr};
        if (cur!=nullptr){
            cur->next=newNode;
            cur=newNode;
        }
        else{
            head=cur=newNode;
        }
        cur2=cur2->next;
    }
    tail=cur;
}

template <typename ValueType>
LinkedQueue<ValueType>& LinkedQueue<ValueType>::operator=(const LinkedQueue& queue2){
    clear();
    node* cur=nullptr;
    node* cur2=queue2.head;
    while (cur2!=nullptr){
        node* newNode=new node{cur2->data,nullptr};
        if (cur==nullptr){
            head=cur=newNode;
        }
        else{
            cur->next=newNode;
            cur=newNode;
        }
        cur2=cur2->next;
    }
    tail=cur;
    return *this;
}

template <typename ValueType>
void LinkedQueue<ValueType>::enqueue(const ValueType& value){
    node* newNode=new node{value,nullptr};
    if (isEmpty()){
        head=tail=newNode;
    }
    else{
        tail->next=newNode;
        tail=newNode;
    }
}

template <typename ValueType>
ValueType LinkedQueue<ValueType>::dequeue(){
    if (isEmpty()){
        error("Attempting to dequeue an empty queue");
    }
    node* temp=head;
    ValueType value=head->data;
    head=head->next;
    delete temp;
    if (head==nullptr){
        tail=nullptr;
    }
    return value;
}

template <typename ValueType>
const ValueType& LinkedQueue<ValueType>::peek() const{
    if (isEmpty()){
        error("Attempting to dequeue an empty queue");
    }
    return head->data;
}

template <typename ValueType>
int LinkedQueue<ValueType>::size() const{
    node* temp=head;
    int count=0;
    while (temp!=nullptr){
        temp=temp->next;
        count++;
    }
    return count;
}

template <typename ValueType>
bool LinkedQueue<ValueType>::isEmpty() const{
    return head==nullptr;
}

template <typename ValueType>
void LinkedQueue<ValueType>::clear(){
     while (head!=nullptr){
         node* temp=head;
         head=head->next;
         delete temp;
    }
    tail=nullptr;
}

template <typename ValueType>
void LinkedQueue<ValueType>::show() const{
    node* temp=head;
    cout<<"---------------------------------"<<endl;
    cout<<"the queue is:  ";
    if (head==nullptr){
        cout<<"an empty queue";
    }
    while (temp!=nullptr){
        cout<<temp->data<<" ";
        temp=temp->next;
    }
    cout<<endl;
    cout<<"---------------------------------"<<endl;
}

int main()
{
    LinkedQueue<int> q;
    q.show();
    q.enqueue(11);
    q.show();
    cout<<"q.isEmpty() "<<q.isEmpty()<<endl;
    cout<<"q.size() "<<q.size()<<endl;
    cout<<"q.peek() "<<q.peek()<<endl;
    cout<<"q.dequeue() "<<q.dequeue()<<endl;
    q.show();
    cout<<"q.isEmpty() "<<q.isEmpty()<<endl;
    q.enqueue(22);
    q.enqueue(33);
    q.show();
    q.clear();
    q.show();
    return 0;
}
