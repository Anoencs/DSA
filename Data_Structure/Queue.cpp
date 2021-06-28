#include <bits/stdc++.h>
template<class T>
class Queue{
    public: 
        virtual T* Front() = 0;
        virtual T* Rear() = 0;
        virtual void Enqueue(const T&) = 0;
        virtual void Dequeue() = 0;
        virtual bool empty() = 0;
        virtual bool full() = 0;
        virtual int getSize() = 0;
        virtual void clear() = 0;
        virtual void traverse(void(*)(int)) = 0;
};
template<class T>
class ArrayQueue:Queue<T>{
    private:
        T* arr;
        int cap;
        int front;
        int rear;
        int size;
    public:
        ArrayQueue():size(0),cap(10){arr = new T[cap];}
        ArrayQueue(int cap):size(0),cap(cap){arr = new T[cap];}
        T* Front();
        T* Rear();
        void Enqueue(const T&);
        void Dequeue();
        bool empty();
        bool full();
        int getSize();
        void clear();
        void traverse(void(*)(int));
};
template<class T>
T* ArrayQueue<T>::Front(){
    return &arr[front%cap];
}
template<class T>
T* ArrayQueue<T>::Rear(){
    return &arr[rear%cap];
}
template<class T>
bool ArrayQueue<T>::empty(){
    return (front > rear || front == -1);
}
template<class T>
bool ArrayQueue<T>::full(){
    return rear - front + 1 == cap;
}
template<class T>
void ArrayQueue<T>::Enqueue(const T& data){
    if(!full()){
        if(front == -1){
            front = 0;
        }
        rear++;
        arr[rear % cap] = data;
    }
}
template<class T>
void ArrayQueue<T>::Dequeue(){
    if(!empty()){
        front++;
    }
}
template<class T>
int ArrayQueue<T>::getSize(){
    return rear - front + 1;
}
template<class T>
void ArrayQueue<T>::clear(){
    size = 0;
    delete[] arr;
}
template<class T>
void ArrayQueue<T>::traverse(void(*func)(int)){
    for(int i = 0; i < size; i++){
        func(i);
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////LinkedList//////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T>
class DLLQueue:Queue<T>{
    public:
        class Node;
    private:
        Node* pHead;
        Node* pTail;
        int size;
        int cap;
    public:
        DLLQueue():pHead(NULL),pTail(NULL),size(0),cap(10){}
        DLLQueue(int cap):pHead(NULL),pTail(NULL),size(0){this->cap = cap;}
        T* Front();
        T* Rear();
        void Enqueue(const T&);
        void Dequeue();
        bool empty();
        bool full();
        int getSize();
        void clear();
        void traverse(void(*)(int));
    public:
       class Node{
            private:
                T data;
                Node* next;
                Node* prev;
                friend class DLLQueue;
            public:
                Node(){next = prev = NULL ;}
                Node(Node* next,Node* prev){
                    this->next = next;
                    this->prev = prev;
                }
                Node(T data, Node* next = NULL,Node* prev=NULL){
                    this->data = data;
                    this->next = next;
                    this->prev = prev;
                }
        };
};
template<class T>
bool DLLQueue<T>::empty(){
    if(size == 0) return true;
    return false;
}
template<class T>
bool DLLQueue<T>::full(){
    if(size == cap) return true;
    return false;
}
template<class T>
void DLLQueue<T>::Enqueue(const T& data){
    if(!full()){
        if(empty()){
            pHead = new Node(data);
            pTail = pHead;
            size++;
            return;
        }
        pTail->next = new Node(data,NULL,pTail);
        pTail = pTail->next;
        size++;
    }
}
template<class T>
T* DLLQueue<T>::Front(){
    return &pHead->data;
}
template<class T>
T* DLLQueue<T>::Rear(){
    return &pTail->data;
}
template<class T>
void DLLQueue<T>::Dequeue(){
    if(!empty()){
        Node* temp = pHead;
        pHead = pHead->next;
        delete temp;
        size--;
    }
}
template<class T>
int DLLQueue<T>::getSize(){return size;}
template<class T>
void DLLQueue<T>::clear(){
    while(!pHead){
        Node* temp = pHead;
        pHead = pHead->next;
        delete temp;
    }
    pHead = pTail = NULL;
    size = 0;
}
template<class T>
void DLLQueue<T>::traverse(void(*func)(int)){
    Node* temp = pHead;
    while(temp){
        func(temp->data);
        temp = temp->next;
    }
}
int main(){
    DLLQueue<int> A;
    for(int i = 0; i < 10; i++){
        A.Enqueue(i);
    }
    A.traverse([](int i ){std::cout << i << " ";});
    return 0;
}