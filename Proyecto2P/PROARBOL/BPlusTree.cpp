#include "BPlusTree.h"
#include <iostream>
#include <sstream>
#include <fstream>


BPlusTreeNode::BPlusTreeNode(bool leaf) : isLeaf(leaf) {}

BPlusTree::BPlusTree(int t) : root(new BPlusTreeNode(true)), minDegree(t) {}

void BPlusTree::insert(const std::string& key, const std::string& value) {
    if (root->keys.size() == 2 * minDegree - 1) {
        BPlusTreeNode* s = new BPlusTreeNode(false);
        s->children.push_back(root);
        splitChild(s, 0, root);
        root = s;
    }
    insertNonFull(root, key, value);
}

std::string BPlusTree::search(const std::string& key) {
    BPlusTreeNode* node = search(root, key);
    if (node && node->data.find(key) != node->data.end()) {
        return node->data[key];
    }
    return "";
}

void BPlusTree::saveToFile(const std::string& filename) {
    std::ofstream archivo(filename);
    if (!archivo.is_open()) {
        std::cout << "Error al abrir el archivo para guardar el árbol B+.\n";
        return;
    }

    // Recorrer y guardar las hojas del árbol B+
    saveNodeToFile(root, archivo);
    archivo.close();
}

void BPlusTree::saveNodeToFile(BPlusTreeNode* node, std::ofstream& archivo) {
    if (node == nullptr) return;

    // Guardar las claves y valores del nodo
    for (size_t i = 0; i < node->keys.size(); ++i) {
        archivo << node->keys[i] << ";" << node->data[node->keys[i]] << std::endl;
    }

    // Recorrer los hijos del nodo
    if (!node->isLeaf) {
        for (size_t i = 0; i <= node->keys.size(); ++i) {
            saveNodeToFile(node->children[i], archivo);
        }
    }
}

void BPlusTree::loadFromFile(const std::string& filename) {
    std::ifstream archivo(filename);
    if (!archivo.is_open()) {
        std::cout << "Error al abrir el archivo para cargar el árbol B+.\n";
        return;
    }

    // Limpiar el árbol actual
    clearTree(root);
    root = new BPlusTreeNode(true);

    // Leer y cargar las hojas del árbol B+
    std::string line;
    while (std::getline(archivo, line)) {
        std::istringstream iss(line);
        std::string key, value;
        if (std::getline(iss, key, ';') && std::getline(iss, value, ';')) {
            insert(key, value);
        }
    }
    archivo.close();
}

void BPlusTree::insertNonFull(BPlusTreeNode* node, const std::string& key, const std::string& value) {
    if (node->isLeaf) {
        node->keys.push_back(key);
        node->data[key] = value;
        std::sort(node->keys.begin(), node->keys.end());
    } else {
        int i = node->keys.size() - 1;
        while (i >= 0 && key < node->keys[i]) {
            i--;
        }
        i++;
        if (node->children[i]->keys.size() == 2 * minDegree - 1) {
            splitChild(node, i, node->children[i]);
            if (key > node->keys[i]) {
                i++;
            }
        }
        insertNonFull(node->children[i], key, value);
    }
}

void BPlusTree::splitChild(BPlusTreeNode* node, int i, BPlusTreeNode* y) {
    BPlusTreeNode* z = new BPlusTreeNode(y->isLeaf);
    z->keys.assign(y->keys.begin() + minDegree, y->keys.end());
    y->keys.resize(minDegree - 1);

    if (!y->isLeaf) {
        z->children.assign(y->children.begin() + minDegree, y->children.end());
        y->children.resize(minDegree);
    } else {
        z->data.insert(y->data.begin(), y->data.end());
        y->data.clear();
    }

    node->children.insert(node->children.begin() + i + 1, z);
    node->keys.insert(node->keys.begin() + i, y->keys[minDegree - 1]);
    y->keys.pop_back();
}

void BPlusTree::traverse(BPlusTreeNode* node, std::ofstream& archivo) {
    if (node->isLeaf) {
        for (const auto& key : node->keys) {
            archivo << key << " " << node->data[key] << std::endl;
        }
    } else {
        for (size_t i = 0; i < node->keys.size(); i++) {
            traverse(node->children[i], archivo);
            archivo << node->keys[i] << std::endl;
        }
        traverse(node->children[node->keys.size()], archivo);
    }
}

BPlusTreeNode* BPlusTree::search(BPlusTreeNode* node, const std::string& key) {
    int i = 0;
    while (i < node->keys.size() && key > node->keys[i]) {
        i++;
    }
    if (i < node->keys.size() && key == node->keys[i]) {
        return node;
    }
    if (node->isLeaf) {
        return nullptr;
    }
    return search(node->children[i], key);
}

void BPlusTree::sort() {
    std::vector<std::pair<std::string, std::string>> elements;
    collectElements(root, elements);
    std::sort(elements.begin(), elements.end());
    clearTree(root);
    for (const auto& element : elements) {
        insert(element.first, element.second);
    }
}

void BPlusTree::collectElements(BPlusTreeNode* node, std::vector<std::pair<std::string, std::string>>& elements) {
    if (node->isLeaf) {
        for (const auto& key : node->keys) {
            elements.emplace_back(key, node->data[key]);
        }
    } else {
        for (size_t i = 0; i < node->keys.size(); i++) {
            collectElements(node->children[i], elements);
            elements.emplace_back(node->keys[i], node->data[node->keys[i]]);
        }
        collectElements(node->children[node->keys.size()], elements);
    }
}

void BPlusTree::clearTree(BPlusTreeNode* node) {
    if (!node->isLeaf) {
        for (auto child : node->children) {
            clearTree(child);
        }
    }
    delete node;
}
