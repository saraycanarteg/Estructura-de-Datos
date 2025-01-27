#include "BPlusTree.h"
#include <iostream>
#include <sstream>
#include <fstream>

BPlusTreeNode::BPlusTreeNode(bool leaf) : isLeaf(leaf) {}

BPlusTree::BPlusTree(int t) : root(new BPlusTreeNode(true)), minDegree(t) {}

BPlusTreeNode* BPlusTree::getRoot() const {
    return root;
}

void BPlusTree::setRoot(BPlusTreeNode* newRoot) {
    root = newRoot;
}

void BPlusTree::insert(const std::string& key, const Libro& value) {
    if (root->keys.size() == 2 * minDegree - 1) {
        BPlusTreeNode* s = new BPlusTreeNode(false);
        s->children.push_back(root);
        splitChild(s, 0, root);
        root = s;
    }
    insertNonFull(root, key, value);
}

Libro BPlusTree::search(const std::string& key) {
    BPlusTreeNode* node = search(root, key);
    if (node) {
        for (const auto& pair : node->data) {
            if (pair.first == key) {
                return pair.second;
            }
        }
    }
    return Libro("", "", Persona(), Fecha()); // Retornar un libro vacío si no se encuentra
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

    // Guardar los libros del nodo
    for (const auto& pair : node->data) {
        const Libro& libro = pair.second;
        archivo << libro.getTitulo() << ";"
                << libro.getAutor().getNombre() << ";"
                << libro.getAutor().getIsni() << ";"
                << libro.getAutor().getFechaNacimiento().mostrar() << ";"
                << libro.getIsbn() << ";"
                << libro.getFechaPublicacion().mostrar() << std::endl;
    }

    // Recorrer los hijos del nodo
    if (!node->isLeaf) {
        for (size_t i = 0; i <= node->keys.size(); ++i) {
            saveNodeToFile(node->children[i], archivo);
        }
    }
}

void BPlusTree::insertNonFull(BPlusTreeNode* node, const std::string& key, const Libro& value) {
    if (node->isLeaf) {
        node->keys.push_back(key);
        node->data.push_back({key, value});
        std::sort(node->keys.begin(), node->keys.end());
        std::sort(node->data.begin(), node->data.end(), [](const auto& a, const auto& b) {
            return a.first < b.first;
        });
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
        z->data.assign(y->data.begin() + minDegree, y->data.end());
        y->data.resize(minDegree - 1);
    }

    node->children.insert(node->children.begin() + i + 1, z);
    node->keys.insert(node->keys.begin() + i, y->keys[minDegree - 1]);
    y->keys.pop_back();
}

void BPlusTree::traverse(BPlusTreeNode* node, std::ostream& out) {
    node = root;
    if (node == nullptr) return;

    if (node->isLeaf) {
        for (const auto& pair : node->data) {
            cout << pair.first << " " << pair.second.getTitulo() << std::endl;
        }
    } else {
        for (size_t i = 0; i < node->keys.size(); i++) {
            traverse(node->children[i], out);
            out << node->keys[i] << std::endl;
        }
        traverse(node->children[node->keys.size()], out);
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

void BPlusTree::collectElements(BPlusTreeNode* node, std::vector<std::pair<std::string, Libro>>& elements) {
    if (node->isLeaf) {
        for (const auto& pair : node->data) {
            elements.push_back(pair);
        }
    } else {
        for (size_t i = 0; i < node->keys.size(); ++i) {
            collectElements(node->children[i], elements);
            elements.push_back({node->keys[i], node->data[i].second});
        }
        collectElements(node->children[node->keys.size()], elements);
    }
}

void BPlusTree::clearTree(BPlusTreeNode* node) {
    if (!node->isLeaf) {
        for (size_t i = 0; i <= node->keys.size(); ++i) {
            clearTree(node->children[i]);
        }
    }
    delete node;
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

    std::string line;
    while (std::getline(archivo, line)) {
        std::istringstream iss(line);
        std::string titulo, nombreAutor, isni, fechaNac, isbn, fechaPub;
        if (std::getline(iss, titulo, ';') && std::getline(iss, isbn, ';') &&
            std::getline(iss, nombreAutor, ';') && std::getline(iss, isni, ';') &&
            std::getline(iss, fechaNac, ';') && std::getline(iss, fechaPub)) {
            Persona autor(nombreAutor, isni, Fecha::crearDesdeCadena(fechaNac));
            Libro libro(titulo, isbn, autor, Fecha::crearDesdeCadena(fechaPub));
            insertObject(isbn, libro);
        }
    }

    archivo.close();
}

void BPlusTree::insertObject(const std::string& isbn, const Libro& libro) {
    insert(isbn, libro);
}

Libro BPlusTree::searchObject(const std::string& isbn) {
    return search(isbn);
}

void BPlusTree::insertNonFullObject(BPlusTreeNode* node, const std::string& isbn, const Libro& libro) {
    insertNonFull(node, isbn, libro);
}

void BPlusTree::saveNodeToFileObject(BPlusTreeNode* node, std::ofstream& archivo) {
    saveNodeToFile(node, archivo);
}

void BPlusTree::collectElementsObject(BPlusTreeNode* node, std::vector<std::pair<std::string, Libro>>& elements) {
    collectElements(node, elements);
}