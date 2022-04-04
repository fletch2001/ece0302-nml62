#include "binary_search_tree.h"
#include <vector>

template <typename KeyType, typename ItemType>
BinarySearchTree<KeyType, ItemType>::BinarySearchTree()
{
    root = 0;
}

template <typename KeyType, typename ItemType>
BinarySearchTree<KeyType, ItemType>::BinarySearchTree(
    const BinarySearchTree<KeyType, ItemType>& rhs)
{
    root = 0;
    clone(rhs.root);
}

// this is an alternative implementation using a stack to simulate the recursion
template <typename KeyType, typename ItemType>
void BinarySearchTree<KeyType, ItemType>::clone(Node<KeyType, ItemType>* rhs)
{
    Node<KeyType, ItemType>** lhs = &root;

    std::stack<stackvar<KeyType, ItemType>> s;

    stackvar<KeyType, ItemType> rootvar;
    rootvar.rhs = rhs;
    rootvar.lhs = lhs;
    s.push(rootvar);

    while (!s.empty()) {
        stackvar<KeyType, ItemType> currentvar = s.top();
        s.pop();

        Node<KeyType, ItemType>* curr_rhs = currentvar.rhs;
        Node<KeyType, ItemType>** curr_lhs = currentvar.lhs;

        if (curr_rhs == 0)
            continue;

        // allocate new node and copy contents
        Node<KeyType, ItemType>* temp = new Node<KeyType, ItemType>;
        temp->key = curr_rhs->key;
        temp->data = curr_rhs->data;
        temp->left = 0;
        temp->right = 0;
        *curr_lhs = temp;

        // push left subtree
        currentvar.rhs = curr_rhs->left;
        currentvar.lhs = &((*curr_lhs)->left);
        s.push(currentvar);

        // push right subtree
        currentvar.rhs = curr_rhs->right;
        currentvar.lhs = &((*curr_lhs)->right);
        s.push(currentvar);
    }
}

template <typename KeyType, typename ItemType>
void BinarySearchTree<KeyType, ItemType>::destroy()
{
    std::stack<Node<KeyType, ItemType>*> s;
    s.push(root);

    while (!s.empty()) {
        Node<KeyType, ItemType>* curr = s.top();
        s.pop();

        if (curr != 0) {
            s.push(curr->left);
            s.push(curr->right);
            delete curr;
        }
    }
    root = 0;
}

template <typename KeyType, typename ItemType>
BinarySearchTree<KeyType, ItemType>& BinarySearchTree<KeyType, ItemType>::
operator=(const BinarySearchTree<KeyType, ItemType>& rhs)
{
    if (&rhs == this)
        return *this;

    destroy();

    root = 0;
    clone(rhs.root);

    return *this;
}

template <typename KeyType, typename ItemType>
BinarySearchTree<KeyType, ItemType>::~BinarySearchTree()
{
    destroy();
}

template <typename KeyType, typename ItemType>
bool BinarySearchTree<KeyType, ItemType>::insert(
    const KeyType& key, const ItemType& item)
{
    Node<KeyType, ItemType> *parent, *curr;
    parent = root;
    curr = nullptr;

    Node<KeyType, ItemType> *tmp = new Node<KeyType, ItemType>;
    tmp->data = item;
    tmp->key = key;

    if (isEmpty()) // empty tree
    {   
        root = tmp;
        tmp = nullptr;
        return true;
    }

    search(key, curr, parent);
    if(curr->key == key) return false; // case when key is already in tree

    if(key > curr->key) {
            curr->right = tmp; // set parent right key if 
    } else{
            curr->left = tmp;
    }

    tmp = nullptr;
    return true;
}

template <typename KeyType, typename ItemType>
bool BinarySearchTree<KeyType, ItemType>::isEmpty()
{
    return (root == 0);
}

template <typename KeyType, typename ItemType>
bool BinarySearchTree<KeyType, ItemType>::retrieve(
    const KeyType& key, ItemType& item)
{
    Node<KeyType, ItemType>* curr;
    Node<KeyType, ItemType>* curr_parent;
    search(key, curr, curr_parent);

    if (curr == 0)
        return false;

    if (curr->key == key) {
        item = curr->data;
        return true;
    }

    return false;
}

template <typename KeyType, typename ItemType>
bool BinarySearchTree<KeyType, ItemType>::remove(KeyType key)
{
    // << root->data << "\n";
    
    if(isEmpty()) return false;

    Node<KeyType, ItemType> *curr, *tmp;
    curr = nullptr;
    tmp = nullptr;
    search(key, curr, tmp);

    
    if(!tmp) { // no parent to curr; therefore curr is root

    }
    
    
    // case one thing in the tree or has no children


    if((curr->right == 0) && (curr->left == 0)) {
        if(curr == root) {
            delete root;
            root = nullptr;
            curr = nullptr;
            return true;
        } else {
            if(tmp->left == curr) {
                delete curr;
                tmp->left = nullptr;
                curr = nullptr;
                return true;
            } else if(tmp->right == curr) {
                delete curr;
                curr = nullptr;
                tmp->right = nullptr;
                return true;
            } else {
                delete curr;
                curr = nullptr;
                return true;
            }
        }

    } else if(curr->right == 0 && curr->left != 0) { // case when only left child
        // Node<KeyType, ItemType> *tmp = curr; // get curr node (node to remove);
        if(curr == root) {
            root->data = curr->left->data;
            root->key = curr->left->key;
        }
        // go to left, get right child from left, left right child with parent until at end
        curr->data = curr->left->data;
        curr->key = curr->left->key;
        
        if(curr->left->right != 0) {
            curr = curr->left->right; // get right child of left child of node to remove
            while(curr->right != 0) {
                tmp = curr;
                curr->key = curr->right->key;
                curr->data = curr->right->data;
                curr = curr->right;
            }

            delete curr;
            curr = nullptr;
            tmp->right = nullptr;
            tmp = nullptr;
            return true;
        }

        delete curr->left;
        curr->left = nullptr;
        tmp = nullptr;
        return true;
        
    } else {
        if(curr == root) {
            root->data = curr->right->data;
            root->key = curr->right->key;
        } else {
            curr->data = curr->right->data;
            curr->key = curr->right->key;
        }

        delete curr->right;
        curr->right = nullptr;
        // check for mem leaks

        return true;
    } 
    
   return false;
}

template <typename KeyType, typename ItemType>
void BinarySearchTree<KeyType, ItemType>::inorder(Node<KeyType, ItemType>* curr,
    Node<KeyType, ItemType>*& in, Node<KeyType, ItemType>*& parent)
{
    if(curr != 0){
        parent = curr;
        inorder(curr->left, in, parent);
        in = curr;
        inorder(curr->right, in, parent);
    }
    // parent = 0;
    // curr = curr->right;
    // if(curr->left == 0) {
    //         in = curr;
    //         return;
    // } else {
    //     parent = curr;
    //     inorder(curr->left, in, curr);
    // }
}

template <typename KeyType, typename ItemType>
void BinarySearchTree<KeyType, ItemType>::search(KeyType key,
    Node<KeyType, ItemType>*& curr, Node<KeyType, ItemType>*& parent)
{
    curr = root;
    parent = 0;

    if (isEmpty())
        return;

    while (true) {
        if (key == curr->key) {
            break;
        } else if (key < curr->key) {
            if (curr->left != 0) {
                parent = curr;
                curr = curr->left;
            } else
                break;
        } else {
            if (curr->right != 0) {
                parent = curr;
                curr = curr->right;
            } else
                break;
        }
    }
}

template<typename KeyType, typename ItemType>
void BinarySearchTree<KeyType, ItemType>::treeSort(ItemType arr[], int size) {

    for(unsigned i = 1; i < size; i++ ) {
        for(unsigned j = 0; j < size; j++) {
            if(i == j) {}
            else {
                if(arr[i] == arr[j]) {
                    return;
                    //std::cout << "d\n"; return; // case when duplicate item found 
                }
            }
        }
    }

    ItemType min = arr[0];
    for(unsigned i = 1; i < size; i++) {
        if(arr[i] < min) {
            min = arr[i];
        }
    }
   
    for(unsigned i = 0;  i< size; i++) {
        insert(arr[i], arr[i]);
    }

    Node<KeyType, ItemType> *tmp, *curr, *parent;
    unsigned i = 0;
    inordertraversal(root, arr, i);
    tmp = nullptr;
    curr = nullptr;
}


template<typename KeyType, typename ItemType>
void BinarySearchTree<KeyType, ItemType>::inordertraversal(Node<KeyType, ItemType>* start, ItemType arr[], unsigned &i) {
   if(start != nullptr) {
        inordertraversal(start->left, arr, i);
        //td::cout << start->data << "\n";
        arr[i++] = start->data;
        inordertraversal(start->right, arr, i);
   } else return;
}