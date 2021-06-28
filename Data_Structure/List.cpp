#include<bits/stdc++.h>

template<class T>
class List{
    public:
        virtual void insert(const T&,int) = 0;
        virtual void insert(const T&) = 0;
        virtual T* removeAt(int) = 0;
        virtual bool removeItem(const T& ) = 0;
        virtual bool empty() = 0;
        virtual int getSize() = 0;
        virtual void clear() = 0;
        virtual T* get(int) = 0;
        virtual void set(const T&,int) = 0;
        virtual int indexOf(const T&) = 0;
        virtual bool contains(const T&) = 0;
        virtual void traverseRL(void(*)(int)) = 0;
        virtual void traverseLR(void(*)(int)) = 0;
};
template<class T>
class ArrayList : List<T>{
    private:
        T* arr;
        int size;
        int cap;
    protected:
        void setCapacity(int);
        void ensureCapacity(int);
        void trim();
        void pack();
        bool rangeCheck(int);
    public:
        ArrayList(){cap = 100; arr = new T[cap];size = 0;}
        ArrayList(int cap){arr = new T[cap],this->cap = cap;size = 0;}
        ~ArrayList(){if(arr) delete[] arr;}
        void insert(const T&,int);
        void insert(const T&) ;
        T* removeAt(int) ;
        bool removeItem(const T& ) ;
        bool empty();
        int getSize();
        void clear();
        T* get(int);
        void set(const T&,int);
        int indexOf(const T&);
        bool contains(const T&);
        void traverseRL(void(*)(T));
        void traverseLR(void(*)(T));
        void Merge(ArrayList&);
};
template<class T>
bool ArrayList<T>::rangeCheck(int idx){
    if(idx < 0 || idx > this->size + 1)
        throw "Idx out of range";
    return true;
}
template<class T>
void ArrayList<T>::setCapacity(int newCap){
    T* newArr = new T[newCap];
    memcpy(newArr,this->arr,sizeof(T)*this->size);
    this->cap = newCap;
    delete[] this->arr;
    this->arr = newArr;
}
template<class T>
void ArrayList<T>::ensureCapacity(int minCap){
    if(minCap > this->cap){
        int newCap = (this->cap*3)/2 + 1;
        if(newCap < minCap) newCap = minCap;
        this->setCapacity(newCap);
    }
}
template<class T>
void ArrayList<T>::trim(){
    int newCap = this->size;
    this->setCapacity(newCap);
}
template<class T>
void ArrayList<T>::pack(){
    if(this->size < this->cap / 2){
        int newCap = (this->size * 3) / 2 + 1;
        this->setCapacity(newCap);
    }
}
template<class T>
void ArrayList<T>::insert(const T& data,int idx){
    if(rangeCheck(idx)){
        if(size == cap){
            setCapacity((3*cap)/2 + 1 );
        }
        for(int i = size-1; i >= idx; i--){
            arr[i+1] = arr[i];
        }
        arr[idx] = data;
        size++;
    }
}
template<class T>
void ArrayList<T>::insert(const T& data){
    if(size == cap){
            setCapacity((3*cap)/2 + 1 );
    }
    arr[size++] = data;
}
template<class T>
void ArrayList<T>::traverseLR(void(*func)(T)){
    for(int i = 0; i < size;i++){
        func(arr[i]);
    }
}
template<class T>
void ArrayList<T>::traverseRL(void(*func)(T)){
    for(int i = size-1; i >= 0 ;i--){
        func(arr[i]);
    }
}
template<class T>
T* ArrayList<T>::removeAt(int idx){
    rangeCheck(idx);
    if(size == 0) return NULL;
    T* temp = &arr[idx];
    for(int i = idx; i < this->size;i++ ){
        arr[i] = arr[i+1];
    }
    this->size--;
    return temp;
}
template<class T>
bool ArrayList<T>::removeItem(const T& data){
    int idx = -1;
    if(size == 0) return NULL;
    for(int i = 0; i < this->size;i++){
        if(arr[i] == data){
            idx = i;
            break;
        }
    }
    if(idx >= 0){
        this->removeAt(idx);
        return true;
    }
    else{return false;}
}
template<class T>
bool ArrayList<T>::empty(){
    if(this->size != 0) return false;
    return true;
}
template<class T>
void ArrayList<T>::clear(){
    delete[] arr;
    this->size = 0;
}
template<class T>
int ArrayList<T>::getSize(){
    return this->size;
}
template<class T>
T* ArrayList<T>::get(int idx){
    return &arr[idx];
}
template<class T>
void ArrayList<T>::set(const T& data,int idx){
    arr[idx] = data;
}
template<class T>
int ArrayList<T>::indexOf(const T& data){
    for(int i = 0; i < this->size; i++){
        if(arr[i] == data){
            return i;
        }
    }
    return -1;
}
template<class T>
bool ArrayList<T>::contains(const T& data){
    for(int i = 0; i < this->size; i++){
        if(arr[i] == data){return true;}
    }
    return false;
}
template<class T>
void ArrayList<T>::Merge(ArrayList<T>& b){
    if(this->cap < this->size + b.size){
        int newCap = (this->size + b.size)*3 / 2;
        this->setCapacity(newCap);
    }
    for(int i = 0; i < b.size; i++){
        this->arr[size+i] = b.arr[i];
    }
    this->size = this->size+b.size;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////LinkedList////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T>
class DLinkedList:List<T>
{
    public:
        class Node;
        class Iterator;
    private:
        Node* pHead;
        Node* pTail;
        int size;
    protected:
        bool rangeCheck(int );
    public:
        DLinkedList():pHead(NULL), pTail(NULL),size(0){}
        ~DLinkedList(){delete pHead; delete pTail;}
        void insert(const T&,int);
        void insert(const T&) ;
        T* removeAt(int) ;
        bool removeItem(const T& ) ;
        bool empty();
        int getSize();
        void clear();
        T* get(int);
        void set(const T&,int);
        int indexOf(const T&);
        bool contains(const T&);
        void traverseLR(void(*)(T));
        void traverseRL(void(*)(T));
        void Merge(DLinkedList&);
    public:
        class Node{
            private:
                T data;
                Node* next;
                Node* prev;
                friend class DLinkedList;
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
bool DLinkedList<T>::rangeCheck(int idx){
    if(idx < 0 || idx > this->size+1)
        throw "Idx out of range";
    return true;
}
template<class T>
void DLinkedList<T>::insert(const T& data,int idx){
    rangeCheck(idx);
    if(!pHead){
        pHead = new Node(data);
        size++;
        pTail = pHead;
        return;
    }
    if(idx == size){
        pTail->next = new Node(data,NULL,pTail);
        pTail = pTail->next;
        size++;
        return;
    }
    Node* temp = pHead;
    while(idx > 1){
        temp = temp->next;
        idx--;
    }
    temp->next = new Node(data,temp->next,temp);
    temp->next->prev = temp->next;
}
template<class T>
void DLinkedList<T>::traverseLR(void(*func)(T)){
    Node* temp = pHead;
    while(temp){
        func(temp->data);
        temp = temp->next;
    }
}
template<class T>
void DLinkedList<T>::traverseRL(void(*func)(T)){
    Node* temp = pTail;
    while(temp){
        func(temp->data);
        temp = temp->prev;
    }
}
template<class T>
void DLinkedList<T>::insert(const T& data){
    if(!pHead){
        pHead = new Node(data);
        size++;
        pTail = pHead;
        return;
    }
    pTail->next = new Node(data,NULL,pTail);
    pTail = pTail->next;
    size++;
    return;
}
template<class T>
T* DLinkedList<T>::removeAt(int idx){
    if(size == 0) return NULL;
    rangeCheck(idx);
    Node* temp = pHead;
    if(size == 1){
        pHead = pTail = NULL;
        size--;
        return &temp->data;
    }
    if(idx >= size-1){
        Node* res = pTail;
        pTail = pTail->prev;
        pTail->next = NULL;
        size--;
        return &res->data;
    }
    while(idx > 1){
        temp = temp->next;
        idx--;
    }
    Node* res = temp->next;
    temp->next = temp->next->next;
    temp->next->prev = temp;
    this->size--;
    return &res->data;
}
template<class T>
bool DLinkedList<T>::removeItem(const T& data){
    Node* temp = pHead;
    if(size == 0) return false;
    while(temp && temp->data != data){
        temp = temp->next;
    }
    if(temp->next == NULL){
        pTail = pTail->prev;
        pTail->next = NULL;
        return true;
    }
    if(temp){
        temp->prev->next = temp->next;
        temp->next->prev = temp->prev;
        size--;
        return true;
    }
    return false;
}
template<class T>
bool DLinkedList<T>::empty(){
    if(size == 0) return true;
    return false;
}
template<class T>
int DLinkedList<T>::getSize(){
    return size;
}
template<class T>
void DLinkedList<T>::clear(){
   while(pHead){
        Node* temp = pHead;
        pHead = pHead->next;
        delete temp;
    }
    pHead = pTail = NULL;
}
template<class T>
T* DLinkedList<T>::get(int idx){
    rangeCheck(idx);
    Node* temp = pHead;
    while(idx > 0){
        temp = temp->next;
        idx--;
    }
    return &temp->data;
}
template<class T>
void DLinkedList<T>::set(const T& data,int idx){
    rangeCheck(idx);
    Node* temp = pHead;
    while(idx > 0){
        temp = temp->next;
        idx--;
    }
    temp->data = data;
}
template<class T>
int DLinkedList<T>::indexOf(const T& data){
    Node* temp = pHead;
    int idx = 0;
    while(temp && temp->data != data){
        temp = temp->next;
        idx++;
    }
    if(rangeCheck(idx)) return idx;
}
template<class T>
bool DLinkedList<T>::contains(const T& data){
    Node* temp = pHead;
    while(temp && temp->data != data){
        temp = temp->next;
    }
    if(temp) return true;
    return false;
}
template<class T>
void DLinkedList<T>::Merge(DLinkedList& b){
    this->pTail->next = b.pHead;
    b.pHead->prev = this->pTail;
    this->pTail = b.pTail;
    this->size = this->size + b.size;
}

int main(){
    // DLinkedList<int> A;
    // for(int i = 0; i < 10; i++){
    //     A.insert(i+1,i);
        
    // }
    // DLinkedList<int> B;
    // for(int i =11; i < 20; i++){
    //     B.insert(i);
    // }
    // A.Merge(B);
    // A.traverseLR([](int i){std::cout << i << " " ;});
    // std::cout << std::endl;
    // A.traverseRL([](int i){std::cout << i << " " ;});
    return 0;
}

