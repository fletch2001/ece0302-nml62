#include "binary_search_tree.h"

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
    
    if(isEmpty()) return false;

    Node<KeyType, ItemType> *curr, *tmp;
    curr = nullptr;
    tmp = nullptr;
    search(key, curr, tmp);
    //tmp = nullptr;
    tmp = nullptr;

    // if(tmp == 0) {
    //     tmp = nullptr;
    //     curr = nullptr;
    //     return false; // if item does not exist in list
    // }
    if(curr == root) {
        delete root;
        root = nullptr;
        curr = nullptr;
        return true;
    }

    // case one thing in the tree or has no children
    if((curr->right == 0) && (curr->left == 0)) {
        delete curr;
        tmp = nullptr;
        curr = nullptr;
        return true;
    } else if(curr->right == 0 && curr->left != 0) { // case when only left child
        curr->data = curr->left->data;
        curr->key = curr->left->key;
        curr->left = curr->left->left;
        curr->right = curr->left->right;
        delete curr->left;
        curr->left = nullptr;
        return true;
    } else if(curr->left == 0 && curr->right != 0) { // case when only right child
        curr->data = curr->right->data;
        curr->key = curr->right->key;
        curr->left = curr->right->left;
        curr->right = curr->right->right;
        delete curr->right;
        curr->right = nullptr;
        return true;
    } else { // case when has two children
        curr->data = curr->right->data;
        curr->key = curr->right->key;
        delete curr->right;
        curr->right = nullptr;
        return true;
    }
   return false;
}

template <typename KeyType, typename ItemType>
void BinarySearchTree<KeyType, ItemType>::inorder(Node<KeyType, ItemType>* curr,
    Node<KeyType, ItemType>*& in, Node<KeyType, ItemType>*& parent)
{
    if(curr->left == 0) {
            in = curr;
            return;
    } else {
        inorder(curr->left, in, curr);
    }
    // TODO 
    // move right once
    // move left as far as possible
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
    // TODO: check for duplicate items in the input array

    // TODO: use the tree to sort the array items

    // TODO: overwrite input array values with sorted values
}
