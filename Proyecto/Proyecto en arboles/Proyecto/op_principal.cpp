#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

// Clase Nodo para el B+ Tree
template <typename T>
class Node
{
public:
    bool isLeaf;
    vector<T> keys;
    vector<Node *> children;
    Node *next;

    Node(bool leaf = false)
        : isLeaf(leaf), next(nullptr)
    {
    }
};

// B plus tree class
template <typename T>
class BPlusTree
{
public:
    Node<T> *root;
    int t; // Minimum degree (defines the range for the number of keys)

    // Constructor
    BPlusTree(int degree) : root(nullptr), t(degree) {}

    // Funciones de uso público
    void insert(T key);
    bool search(T key);
    void remove(T key);
    vector<T> rangeQuery(T lower, T upper);
    void printTree();

private:
    // Funciones auxiliares
    void splitChild(Node<T> *parent, int index, Node<T> *child);
    void insertNonFull(Node<T> *node, T key);
    void remove(Node<T> *node, T key);
    void borrowFromPrev(Node<T> *node, int index);
    void borrowFromNext(Node<T> *node, int index);
    void merge(Node<T> *node, int index);
    void printTree(Node<T> *node, int level);
};

// Implementación de splitChild
template <typename T>
void BPlusTree<T>::splitChild(Node<T> *parent, int index, Node<T> *child)
{
    Node<T> *newChild = new Node<T>(child->isLeaf);
    parent->children.insert(parent->children.begin() + index + 1, newChild);
    parent->keys.insert(parent->keys.begin() + index, child->keys[t - 1]);

    newChild->keys.assign(child->keys.begin() + t, child->keys.end());
    child->keys.resize(t - 1);

    if (!child->isLeaf)
    {
        newChild->children.assign(child->children.begin() + t, child->children.end());
        child->children.resize(t);
    }

    if (child->isLeaf)
    {
        newChild->next = child->next;
        child->next = newChild;
    }
}

// Implementación de insertNonFull
template <typename T>
void BPlusTree<T>::insertNonFull(Node<T> *node, T key)
{
    if (node->isLeaf)
    {
        node->keys.insert(upper_bound(node->keys.begin(), node->keys.end(), key), key);
    }
    else
    {
        int i = node->keys.size() - 1;
        while (i >= 0 && key < node->keys[i])
        {
            i--;
        }
        i++;
        if (node->children[i]->keys.size() == 2 * t - 1)
        {
            splitChild(node, i, node->children[i]);
            if (key > node->keys[i])
            {
                i++;
            }
        }
        insertNonFull(node->children[i], key);
    }
}

// Implementación de remove
template <typename T>
void BPlusTree<T>::remove(Node<T> *node, T key)
{
    if (node->isLeaf)
    {
        auto it = find(node->keys.begin(), node->keys.end(), key);
        if (it != node->keys.end())
        {
            node->keys.erase(it);
        }
    }
    else
    {
        int idx = lower_bound(node->keys.begin(), node->keys.end(), key) - node->keys.begin();
        if (idx < node->keys.size() && node->keys[idx] == key)
        {
            if (node->children[idx]->keys.size() >= t)
            {
                Node<T> *predNode = node->children[idx];
                while (!predNode->isLeaf)
                {
                    predNode = predNode->children.back();
                }
                T pred = predNode->keys.back();
                node->keys[idx] = pred;
                remove(node->children[idx], pred);
            }
            else if (node->children[idx + 1]->keys.size() >= t)
            {
                Node<T> *succNode = node->children[idx + 1];
                while (!succNode->isLeaf)
                {
                    succNode = succNode->children.front();
                }
                T succ = succNode->keys.front();
                node->keys[idx] = succ;
                remove(node->children[idx + 1], succ);
            }
            else
            {
                merge(node, idx);
                remove(node->children[idx], key);
            }
        }
        else
        {
            if (node->children[idx]->keys.size() < t)
            {
                if (idx > 0 && node->children[idx - 1]->keys.size() >= t)
                {
                    borrowFromPrev(node, idx);
                }
                else if (idx < node->children.size() - 1 && node->children[idx + 1]->keys.size() >= t)
                {
                    borrowFromNext(node, idx);
                }
                else
                {
                    if (idx < node->children.size() - 1)
                    {
                        merge(node, idx);
                    }
                    else
                    {
                        merge(node, idx - 1);
                    }
                }
            }
            remove(node->children[idx], key);
        }
    }
}

// Implementación de las funciones auxiliares
template <typename T>
void BPlusTree<T>::borrowFromPrev(Node<T> *node, int index)
{
    Node<T> *child = node->children[index];
    Node<T> *sibling = node->children[index - 1];

    child->keys.insert(child->keys.begin(), node->keys[index - 1]);
    node->keys[index - 1] = sibling->keys.back();
    sibling->keys.pop_back();

    if (!child->isLeaf)
    {
        child->children.insert(child->children.begin(), sibling->children.back());
        sibling->children.pop_back();
    }
}

template <typename T>
void BPlusTree<T>::borrowFromNext(Node<T> *node, int index)
{
    Node<T> *child = node->children[index];
    Node<T> *sibling = node->children[index + 1];

    child->keys.push_back(node->keys[index]);
    node->keys[index] = sibling->keys.front();
    sibling->keys.erase(sibling->keys.begin());

    if (!child->isLeaf)
    {
        child->children.push_back(sibling->children.front());
        sibling->children.erase(sibling->children.begin());
    }
}

template <typename T>
void BPlusTree<T>::merge(Node<T> *node, int index)
{
    Node<T> *child = node->children[index];
    Node<T> *sibling = node->children[index + 1];

    child->keys.push_back(node->keys[index]);
    child->keys.insert(child->keys.end(), sibling->keys.begin(), sibling->keys.end());
    if (!child->isLeaf)
    {
        child->children.insert(child->children.end(), sibling->children.begin(), sibling->children.end());
    }

    node->keys.erase(node->keys.begin() + index);
    node->children.erase(node->children.begin() + index + 1);

    delete sibling;
}

template <typename T>
void BPlusTree<T>::printTree(Node<T> *node, int level)
{
    if (node != nullptr)
    {
        for (int i = 0; i < level; ++i)
        {
            cout << "  ";
        }
        for (const T &key : node->keys)
        {
            cout << key << " ";
        }
        cout << endl;
        for (Node<T> *child : node->children)
        {
            printTree(child, level + 1);
        }
    }
}

template <typename T>
void BPlusTree<T>::printTree()
{
    printTree(root, 0);
}

template <typename T>
bool BPlusTree<T>::search(T key)
{
    Node<T> *current = root;
    while (current != nullptr)
    {
        int i = 0;
        while (i < current->keys.size() && key > current->keys[i])
        {
            i++;
        }
        if (i < current->keys.size() && key == current->keys[i])
        {
            return true;
        }
        if (current->isLeaf)
        {
            return false;
        }
        current = current->children[i];
    }
    return false;
}

template <typename T>
vector<T> BPlusTree<T>::rangeQuery(T lower, T upper)
{
    vector<T> result;
    Node<T> *current = root;
    while (!current->isLeaf)
    {
        int i = 0;
        while (i < current->keys.size() && lower > current->keys[i])
        {
            i++;
        }
        current = current->children[i];
    }
    while (current != nullptr)
    {
        for (const T &key : current->keys)
        {
            if (key >= lower && key <= upper)
            {
                result.push_back(key);
            }
            if (key > upper)
            {
                return result;
            }
        }
        current = current->next;
    }
    return result;
}

template <typename T>
void BPlusTree<T>::insert(T key)
{
    if (root == nullptr)
    {
        root = new Node<T>(true);
        root->keys.push_back(key);
    }
    else
    {
        if (root->keys.size() == 2 * t - 1)
        {
            Node<T> *newRoot = new Node<T>();
            newRoot->children.push_back(root);
            splitChild(newRoot, 0, root);
            root = newRoot;
        }
        insertNonFull(root, key);
    }
}

template <typename T>
void BPlusTree<T>::remove(T key)
{
    if (root == nullptr)
    {
        return;
    }
    remove(root, key);
    if (root->keys.empty() && !root->isLeaf)
    {
        Node<T> *tmp = root;
        root = root->children[0];
        delete tmp;
    }
}

// Función main
int main()
{
    BPlusTree<int> tree(4);

    tree.insert(10);
    tree.insert(20);
    tree.insert(23);
    tree.insert(22);
    tree.insert(21);
    tree.insert(5);
    tree.insert(15);
    tree.insert(24);
    tree.insert(30);
    tree.insert(25);
    tree.insert(1);
    tree.insert(12);

    cout << "B+ Tree after insertions:" << endl;
    tree.printTree();

    int searchKey = 15;
    cout << "\nSearching for key " << searchKey << ": " << (tree.search(searchKey) ? "Found" : "Not Found") << endl;

    int lower = 10, upper = 30;
    vector<int> rangeResult = tree.rangeQuery(lower, upper);
    cout << "\nRange query [" << lower << ", " << upper << "]: ";
    for (int key : rangeResult)
    {
        cout << key << " ";
    }
    cout << endl;

    int removeKey = 25;
    tree.remove(removeKey);
    cout << "\nB+ Tree after removing " << removeKey << ":"
         << endl;
    tree.printTree();

    return 0;
}
