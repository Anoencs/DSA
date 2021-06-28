#include<bits/stdc++.h>

template<class K, class V>
class AVLT{
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
            std::string balance;
            switch(root->bf){
                case -1:
                    balance += "LH";
                    break;
                case 0:
                    balance += "EH";
                    break;
                case 1:
                    balance += "RH";
                    break; 
            }
            std::cout << root->key << " (" << balance << ")" << std::endl;
            printHelper(root->pLeft,indent,false);
            printHelper(root->pRight,indent,true);
            }
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
        Node* addNode(Node* root,K key, V value,bool& taller){
            if(!root){
                taller = true;
                return root = new Node(key,value);
            }
            if(root->key > key ){
                root->pLeft = addNode(root->pLeft,key,value,taller); 
                if(taller){
                    if(root->bf == -1){
                        root = leftBalance(root,taller);
                        taller = false; 
                    }
                    else if(root->bf == 0){
                        root->bf = -1;
                    }
                    else{
                        root->bf = 0;
                        taller = false;
                    }
                }
            }
            else{
                root->pRight = addNode(root->pRight,key,value,taller);
                if(taller){
                    if(root->bf == -1){
                        root->bf = 0;
                        taller = false;
                    }
                    else if(root->bf == 0){
                        root->bf = 1;
                    }
                    else{
                       root = rightBalance(root,taller);
                       taller = false;
                    }
                }
            }
            return root;
        }
        Node* rotateRight(Node* root){
            Node* temp = root->pLeft;
            root->pLeft = temp->pRight;
            temp->pRight = root;
            return temp;
        }
        Node* rotateLeft(Node* root){
            Node* temp = root->pRight;
            root->pRight = temp->pLeft;
            temp->pLeft = root;
            return temp;
        }
        Node* leftBalance(Node* root,bool& taller){
            Node* leftTree = root->pLeft;
            if(leftTree->bf == -1){
                root = rotateRight(root);
                root->bf = 0;
                leftTree->bf = 0;
                root->pRight->bf = 0;
                taller = false;
            }
            else{
                Node* rightTree = leftTree->pRight;
                root->pLeft = rotateLeft(leftTree);
                root = rotateRight(root);
                if(rightTree->bf == -1){
                    root->bf = 0;
                    leftTree->bf = 0;
                    root->pRight->bf = 1;
                }
                else if(rightTree == 0){
                    leftTree->bf = 0;
                    root->bf = 0;
                    root->pRight->bf = 0;
                }
                else{
                    leftTree->bf = -1;
                    root->bf = 0;
                    root->pRight->bf = 0;
                }
                rightTree->bf = 0;
                taller = false;
            }
            return root;
        }
        Node* rightBalance(Node* root,bool& taller){
            Node* rightTree = root->pRight;
            if(rightTree->bf == 1){
                root = rotateLeft(root);
                root->bf = 0;
                rightTree->bf = 0;
                root->pLeft->bf = 0;
                taller = false;
            }
            else{
                Node* leftTree = rightTree->pLeft;
                root->pRight = rotateLeft(rightTree);
                root = rotateRight(root);
                if(leftTree->bf == 1){
                    root->bf = 0;
                    rightTree->bf = 0;
                    root->pLeft->bf = 1;
                }
                else if(leftTree->bf == 0){
                    rightTree->bf = 0;
                    root->bf = 0;
                    root->pLeft->bf = 0;
                }
                else{
                    rightTree->bf = 1;
                    root->bf = 0;
                    root->pLeft->bf = 0;
                }
                leftTree->bf = 0;
                taller = false;
            }
            return root;
        }
        Node* remove(Node* root,K key, bool& shorter, bool& success){
            if(!root){
                shorter = false;
                success = false;
                return NULL;
            }
            if(root->key > key){
                root->pLeft = remove(root->pLeft,key,shorter,success);
                if(shorter){
                    root = removeRightBalanced(root,shorter);
                }
            }
            else if(root->key < key){
                root->pRight = remove(root->pRight,key,shorter,success);
                if(shorter){
                    root = removeLeftBalanced(root,shorter);
                } 
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
                    Node* dltNode = root->pRight;
                    while(dltNode->pLeft && dltNode){
                        dltNode = dltNode->pLeft;
                    }
                    root->value = dltNode->value;
                    root->key = dltNode->key;
                    root->pRight = remove(root->pRight,dltNode->key,shorter,success);
                    if(shorter){
                        root = removeLeftBalanced(root,shorter);
                    }
                }
            }
            return root;
        }
        Node* removeRightBalanced(Node* root,bool& shorter){
            /* The (sub)tree is shorter after a deletion on the left branch. 
            Adjust the balance factors and if necessary balance the tree by rotating left.*/
            if(root->bf == -1){
                root->bf = 0;
            }
            else if(root->bf == 0){
                root->bf = 1;
                shorter = false;
            }
            else{
                Node* rightTree = root->pRight;
                if(rightTree->bf == -1){
                    Node* leftTree = rightTree->pLeft;
                    if(leftTree->bf == -1){
                        rightTree->bf = 1;
                        root->bf = 0;
                    }
                    else if(leftTree->bf == 0){
                        //
                        root->bf = 0;
                        rightTree->bf = 0;
                    }
                    else{
                        root->bf = -1;
                        rightTree->bf = 0;
                    }
                    leftTree->bf = 0;
                    root->pRight = rotateRight(rightTree);
                    root = rotateLeft(root);
                }
                else{
                    if(rightTree->bf == 0){
                        root->bf = 1;
                        rightTree->bf = -1;
                        shorter = false;
                    }
                    else{
                        root->bf = 0;
                        rightTree->bf = 0;             
                    }
                    root = rotateLeft(root);
                }
            }
            return root;
        }
        Node* removeLeftBalanced(Node* root,bool& shorter){
            /* The (sub)tree is shorter after a deletion on the right branch. 
            Adjust the balance factors and if necessary balance the tree by rotating right. */
            if(root->bf == 1){
                root->bf = 0;
            }
            else if(root->bf == 0){
                root->bf = -1;
                shorter = false;
            }
            else{
                Node* leftTree = root->pLeft;
                if(leftTree->bf == 1){
                    Node* rightTree = leftTree->pRight;
                    if(rightTree->bf == 1){
                        root->bf = 0;
                        leftTree->bf = -1;
                    }
                    else if(rightTree->bf == 0){
                        //
                        root->bf = 0;
                        leftTree->bf = 0;
                    }
                    else{
                        root->bf = 1;
                        leftTree->bf = 0;
                    }
                    rightTree->bf = 0;
                    root->pLeft = rotateLeft(leftTree);
                    root = rotateRight(root);
                }
                else{
                    if(leftTree->bf == 0){
                        root->bf = -1;
                        leftTree->bf = 1;
                        shorter = false;
                    }
                    else{
                        root->bf = 0;
                        leftTree->bf = 0;
                    }
                    root = rotateRight(root);
                }
            }
            return root;
        }

    public:
        AVLT() : root(NULL) {}
        ~AVLT() {}
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
                int bf; //balance factor LH: -1 , EH: 0, RH: 1
                K key;
                V value;
                friend class AVLT;
            public:
                Node(K key, V value):key(key),value(value),pLeft(NULL),pRight(NULL),bf(0){}
                ~Node(){}
        };
};
template<class K,class V>
void AVLT<K,V>::removeNode(K key){
    bool success = false;
    bool shorter = true;
    this-> root = remove(this->root,key,shorter,success);
}
template<class K,class V>
void AVLT<K,V>::prettyPrint(){
    printHelper(root,"",true);
}
template<class K,class V>
void AVLT<K,V>::addNode(K key,V value){
    bool taller = true;
    this->root = addNode(this->root,key,value,taller);
}
template<class K,class V>
V AVLT<K,V>::searchNode(K key){
    return searchNode(this->root,key);
}
template<class K,class V>
void AVLT<K,V>::inorder(void(*func)(K*)){
    inorder(this->root,func);
}
template<class K,class V>
void AVLT<K,V>::clear(){
    clear(root);
}
int main(){
    AVLT<int,int>A;
    A.addNode(5,2);
    A.addNode(2,2);
    A.addNode(8,2);
    A.addNode(1,2);
    A.addNode(3,2);
    A.addNode(7,2);
    A.addNode(10,2);
    A.addNode(4,2);
    A.addNode(6,2);
    A.addNode(9,2);
    A.addNode(11,2);
    A.addNode(12,2);
    A.removeNode(1);
    

    A.prettyPrint();
    return 0;
}   
