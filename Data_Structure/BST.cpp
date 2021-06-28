#include<bits/stdc++.h>

template<class K, class V>
class BST{
    public:
        class Node;
    private:
        Node* root;
    protected:
        void printHelper(Node* root,std::string indent,bool last){
             if(root){
            std::cout << indent;
            if(last){
                std::cout << "R----";
                indent += "     "; 
            } 
            else{
                std::cout << "L----";
                indent += "|    ";
            }
            std::cout << root->key << std::endl;
            printHelper(root->pLeft,indent,false);
            printHelper(root->pRight,indent,true);
            }
        }
        Node*removeNode(Node* root,K key){
            if(!root) return root;
            if(key < root->key){
                root->pLeft = removeNode(root->pLeft,key);
            }
            else if(key > root->key){
                root->pRight = removeNode(root->pRight,key);
            }
            else{
                if(!root->pLeft){
                    Node* temp = root->pRight;
                    delete root;
                    return temp;
                }
                else if(!root->pRight){
                    Node* temp = root->pLeft;
                    delete root;
                    return temp;
                }
                else{
                    Node* temp = root->pLeft;
                    while(temp && temp->pRight){
                        temp = temp->pRight;
                    }
                    root->key = temp->key;
                    root->value = temp->value;
                    root->pLeft = removeNode(root->pLeft,temp->key);
                }
            }
            return root;
        }
        V searchNode(Node* root, K key){
            if(root->key == key) return root->value;
            if(key < root->key){
                return searchNode(root->pLeft,key);
            }
            else{
                return searchNode(root->pRight,key);
            }
        }
        void inorder(Node* root,void(*func)(K*)){
            if(root){
                inorder(root->pLeft,func);
                func(&root->key);
                inorder(root->pRight,func);
            }
        }
        void clear(Node* root){
            if(root){
                clear(root->pLeft);
                delete root;
                clear(root->pRight);
            }
        }
        Node* addNode(Node* root,K key, V value){
            if(!root){
                return root = new Node(key,value);
            }
            if(root->key > key ){
                root->pLeft = addNode(root->pLeft,key,value); 
            }
            else{
                root->pRight = addNode(root->pRight,key,value);
            }
        }
    public:
        BST() : root(NULL) {}
        ~BST() {}
        void clear();
        void removeNode(K);
        void addNode(K,V);
        void prettyPrint();
        void inorder(void(*)(K*));
        V searchNode(K);
    public:
        class Node{
            private:
                Node* pLeft;
                Node* pRight;
                K key;
                V value;
                friend class BST;
            public:
                Node(K key, V value):key(key),value(value),pLeft(NULL),pRight(NULL){}
                ~Node(){}
        };
};
template<class K,class V>
void BST<K,V>::removeNode(K key){
    removeNode(this->root,key);
}
template<class K,class V>
void BST<K,V>::prettyPrint(){
    printHelper(root,"",true);
}
template<class K,class V>
void BST<K,V>::addNode(K key,V value){
    this->root = addNode(this->root,key,value);
}
template<class K,class V>
V BST<K,V>::searchNode(K key){
    return searchNode(this->root,key);
}
template<class K,class V>
void BST<K,V>::inorder(void(*func)(K*)){
    inorder(this->root,func);
}
template<class K,class V>
void BST<K,V>::clear(){
    clear(root);
}
int main(){
    BST<int,int>A;
    A.addNode(50,2);
    A.addNode(30,2);
    A.addNode(20,2);
    A.addNode(40,2);
    A.addNode(70,2);
    A.addNode(60,3);
    A.addNode(80,2);
    A.prettyPrint();
    A.inorder([](int* i){std::cout << *i << " ";});
    return 0;
}