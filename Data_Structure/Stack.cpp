#include <bits/stdc++.h>
template<class T>
class Stack{
    public: 
        virtual T* top() = 0;
        virtual void push(const T&) = 0;
        virtual void pop() = 0;
        virtual bool empty() = 0;
        virtual bool full() = 0;
        virtual int getSize() = 0;
        virtual void clear() = 0;
        virtual void traverse(void(*)(int)) = 0;
};
template<class T>
class ArrayStack:Stack<T>{
    private:
        T* arr;
        int size;
        int cap;
    public:
        ArrayStack():size(0),cap(10){arr = new T[cap];}
        ArrayStack(int cap):size(0),cap(cap){arr = new T[cap];}
        T* top();
        void push(const T&);
        void pop();
        bool empty();
        bool full();
        int getSize();
        void clear();
        void traverse(void(*)(int));
};
template<class T>
T* ArrayStack<T>::top(){
    return &arr[size-1];
}
template<class T>
bool ArrayStack<T>::empty(){
    if(size == 0) return true;
    return false;
}
template<class T>
bool ArrayStack<T>::full(){
    if(size == cap) return true;
    return false;
}
template<class T>
void ArrayStack<T>::push(const T& data){
    if(!full()){
        arr[size] = data;
        size++;
    }
}
template<class T>
void ArrayStack<T>::pop(){
    if(!empty()){
        size--;
    }
}
template<class T>
int ArrayStack<T>::getSize(){
    return size;
}
template<class T>
void ArrayStack<T>::clear(){
    size = 0;
    delete[] arr;
}
template<class T>
void ArrayStack<T>::traverse(void(*func)(int)){
    for(int i = 0; i < size; i++){
        func(i);
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////LinkedList//////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T>
class DLLStack:Stack<T>{
    public:
        class Node;
    private:
        Node* pHead;
        Node* pTail;
        int size;
        int cap;
    public:
        DLLStack():pHead(NULL),pTail(NULL),size(0),cap(10){}
        DLLStack(int cap):pHead(NULL),pTail(NULL),size(0){this->cap = cap;}
        T* top();
        void push(const T&);
        void pop();
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
                friend class DLLStack;
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
bool DLLStack<T>::empty(){
    if(size == 0) return true;
    return false;
}
template<class T>
bool DLLStack<T>::full(){
    if(size == cap) return true;
    return false;
}
template<class T>
void DLLStack<T>::push(const T& data){
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
T* DLLStack<T>::top(){
    return &pTail->data;
}
template<class T>
void DLLStack<T>::pop(){
    if(!empty()){
        Node* temp = pTail;
        pTail = pTail->prev;
        delete temp;
        size--;
    }
}
template<class T>
int DLLStack<T>::getSize(){return size;}
template<class T>
void DLLStack<T>::clear(){
    while(!pHead){
        Node* temp = pHead;
        pHead = pHead->next;
        delete temp;
    }
    pHead = pTail = NULL;
    size = 0;
}
template<class T>
void DLLStack<T>::traverse(void(*func)(int)){
    Node* temp = pHead;
    while(temp){
        func(temp->data);
        temp = temp->next;
    }
}
int main(){
    DLLStack<int> A;
    for(int i = 0; i < 10; i++){
        A.push(i);
    }
    A.clear();
    
    A.traverse([](int i ){std::cout << i << " ";});
    return 0;
}