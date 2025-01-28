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

void BPlusTree::easy_search(BPlusTreeNode* node, Libro& return_value, string key ){
        
    if (node == nullptr) return;    
    
    if (node->isLeaf) {
        for (const auto& pair : node->data) {
            if(key ==pair.second.getIsbn()){
                return_value = pair.second;
            }
        }
    } else {

        for (size_t i = 0; i < node->keys.size(); i++) {
            easy_search(node->children[i], return_value, key);
        }
        easy_search(node->children[node->keys.size()], return_value, key);
    }
}

Libro BPlusTree::search(const std::string& key) {
    BPlusTreeNode* current = root;
    while (!current->isLeaf) {
        int i = 0;
        while (i < current->keys.size() && key > current->keys[i]) {
            i++;
        }
        current = current->children[i];
    }
    
    for (size_t i = 0; i < current->keys.size(); i++) {
        if (current->keys[i] == key) {
            return current->data[i].second;
        }
    }
    return Libro();
}

Libro BPlusTree::searchByIsni(const std::string& isni) {
    BPlusTreeNode* currentNode = root;
    while (currentNode != nullptr) {
        for (const auto& pair : currentNode->data) {
            if (pair.second.getAutor().getIsni() == isni) {
                return pair.second;
            }
        }
        if (currentNode->isLeaf) {
            break;
        }
        currentNode = currentNode->children[0]; // Avanzar al siguiente nodo
    }
    return Libro(); // Retornar un libro vacío si no se encuentra
}

void BPlusTree::saveToFile(const std::string& filename) {
    std::ofstream archivo(filename);
    if (!archivo.is_open()) {
        std::cout << "Error al abrir el archivo para guardar el árbol B+.\n";
        return;
    }

    saveNodeToFile(root, archivo);
    archivo.close();
}

void BPlusTree::createBackup(const string& filename) {
    ofstream file("backup\\" + filename, ios::out | ios::trunc);
    if (!file) {
        cerr << "Error al abrir el archivo para guardar: " << filename << endl;
        return;
    }
    BPlusTreeNode* node = root;
    saveNodeToFile(node, file);
    file.close();
}

void BPlusTree::saveNodeToFile(BPlusTreeNode* node, std::ofstream& archivo) {
    if (node == nullptr) return;

    // Guardar los libros del nodo
    for (const auto& pair : node->data) {
        const Libro& libro = pair.second;
        archivo << libro.getTitulo() << ";"
                << libro.getIsbn() << ";"
                << libro.getAutor().getNombre() << ";"
                << libro.getAutor().getIsni() << ";"
                << libro.getAutor().getFechaNacimiento().mostrar() << ";"
                << libro.getFechaPublicacion().mostrar() << std::endl;

        cout << endl<< libro.getTitulo() << ";"
                << libro.getIsbn() << ";"
                << libro.getAutor().getNombre() << ";"
                << libro.getAutor().getIsni() << ";"
                << libro.getAutor().getFechaNacimiento().mostrar() << ";"
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
    int i = node->keys.size() - 1;

    if (node->isLeaf) {
        // Encontrar la posición correcta para insertar
        while (i >= 0 && key < node->keys[i]) {
            i--;
        }
        i++;
        
        // Insertar en la posición correcta
        node->keys.insert(node->keys.begin() + i, key);
        node->data.insert(node->data.begin() + i, {key, value});
    } else {
        // Encontrar el hijo correcto
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

void BPlusTree::splitChild(BPlusTreeNode* parent, int index, BPlusTreeNode* child) {
    BPlusTreeNode* newChild = new BPlusTreeNode(child->isLeaf);
    
    // Dividir las claves y datos
    int mid = minDegree - 1;
    
    // Para nodos hoja
    if (child->isLeaf) {
        // Copiar la segunda mitad de las claves y datos al nuevo nodo
        for (int i = mid; i < child->keys.size(); i++) {
            newChild->keys.push_back(child->keys[i]);
            newChild->data.push_back(child->data[i]);
        }
        
        // Mantener la primera mitad en el nodo original
        child->keys.resize(mid);
        child->data.resize(mid);
        
        // Mantener la conexión entre nodos hoja
        newChild->nextLeaf = child->nextLeaf;
        child->nextLeaf = newChild;
    } 
    // Para nodos internos
    else {
        // Copiar la segunda mitad de las claves al nuevo nodo
        for (int i = mid + 1; i < child->keys.size(); i++) {
            newChild->keys.push_back(child->keys[i]);
            newChild->data.push_back(child->data[i]);
        }
        
        // Copiar los hijos correspondientes
        for (int i = mid + 1; i <= child->children.size(); i++) {
            newChild->children.push_back(child->children[i]);
        }
        
        // Ajustar el nodo original
        child->keys.resize(mid);
        child->data.resize(mid);
        child->children.resize(mid + 1);
    }
    
    // Insertar la clave media en el padre
    parent->keys.insert(parent->keys.begin() + index, child->keys[mid]);
    parent->data.insert(parent->data.begin() + index, child->data[mid]);
    parent->children.insert(parent->children.begin() + index + 1, newChild);
}

void BPlusTree::traverse(BPlusTreeNode* node, std::ostream& out) {
    if (root == nullptr) return;

    // Imprimir la cabecera de la tabla
    std::cout << left << setw(41) << "Título" 
              << setw(25) << "Autor" 
              << setw(25) << "ISNI" 
              << setw(20) << "ISBN"
              << setw(15) << "Publicación" 
              << setw(15) << "Nac. Autor" << endl;
    std::cout << string(140, '-') << endl;

    traverseHelper(root, std::cout);
}

void BPlusTree::traverseHelper(BPlusTreeNode* node, std::ostream& out) {
    
    if (node == nullptr) return;    

    if (node->isLeaf) {
        for (const auto& pair : node->data) {
            std::cout << left << setw(40) << pair.second.getTitulo()
                      << setw(25) << pair.second.getAutor().getNombre()
                      << setw(25) << pair.second.getAutor().getIsni() 
                      << setw(20) << pair.second.getIsbn()
                      << setw(15) << pair.second.getFechaPublicacion().mostrar()
                      << setw(15) << pair.second.getAutor().getFechaNacimiento().mostrar() << endl;
        }
    } else {
        for (size_t i = 0; i < node->keys.size(); i++) {
            traverseHelper(node->children[i], out);
        }
        traverseHelper(node->children[node->keys.size()], out);
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

//Metodos para eliminacion

void BPlusTree::remove(const std::string& key) {
    if (!root) {
        std::cout << "El árbol está vacío.\n";
        return;
    }

    removeNode(root, key);

    if (root->keys.size() == 0) {
        BPlusTreeNode* temp = root;
        if (root->isLeaf) {
            root = nullptr;
        } else {
            root = root->children[0];
        }
        delete temp;
    }

    // Update the book_tree.txt file
    std::ifstream infile("book_tree.txt");
    std::ofstream temp("temp.txt");
    std::string line;
    while (getline(infile, line)) {
        std::istringstream iss(line);
        std::string titulo, isbn, nombreAutor, isni, fechaNac, fechaPub;
        getline(iss, titulo, ';');
        getline(iss, isbn, ';');
        getline(iss, nombreAutor, ';');
        getline(iss, isni, ';');
        getline(iss, fechaNac, ';');
        getline(iss, fechaPub, ';');
        if (isbn != key) {
            temp << line << std::endl;
        }
    }
    infile.close();
    temp.close();
    remove("book_tree.txt");
    rename("temp.txt", "book_tree.txt");
}

void BPlusTree::removeNode(BPlusTreeNode* node, const std::string& key) {
    int idx = findKey(node, key);

    if (idx < node->keys.size() && node->keys[idx] == key) {
        if (node->isLeaf) {
            removeFromLeaf(node, idx);
        } else {
            removeFromNonLeaf(node, idx);
        }
    } else {
        if (node->isLeaf) {
            std::cout << "La clave " << key << " no existe en el árbol.\n";
            return;
        }

        bool flag = ((idx == node->keys.size()) ? true : false);

        if (node->children[idx]->keys.size() < minDegree) {
            fill(node, idx);
        }

        if (flag && idx > node->keys.size()) {
            removeNode(node->children[idx - 1], key);
        } else {
            removeNode(node->children[idx], key);
        }
    }
}

void BPlusTree::removeFromLeaf(BPlusTreeNode* node, int idx) {
    for (int i = idx + 1; i < node->keys.size(); ++i) {
        node->keys[i - 1] = node->keys[i];
    }
    node->keys.resize(node->keys.size() - 1);
}

void BPlusTree::removeFromNonLeaf(BPlusTreeNode* node, int idx) {
    std::string key = node->keys[idx];

    if (node->children[idx]->keys.size() >= minDegree) {
        std::string pred = getPred(node, idx);
        node->keys[idx] = pred;
        removeNode(node->children[idx], pred);
    } else if (node->children[idx + 1]->keys.size() >= minDegree) {
        std::string succ = getSucc(node, idx);
        node->keys[idx] = succ;
        removeNode(node->children[idx + 1], succ);
    } else {
        merge(node, idx);
        removeNode(node->children[idx], key);
    }
}

void BPlusTree::fill(BPlusTreeNode* node, int idx) {
    if (idx != 0 && node->children[idx - 1]->keys.size() >= minDegree) {
        borrowFromPrev(node, idx);
    } else if (idx != node->keys.size() && node->children[idx + 1]->keys.size() >= minDegree) {
        borrowFromNext(node, idx);
    } else {
        if (idx != node->keys.size()) {
            merge(node, idx);
        } else {
            merge(node, idx - 1);
        }
    }
}

void BPlusTree::borrowFromPrev(BPlusTreeNode* node, int idx) {
    BPlusTreeNode* child = node->children[idx];
    BPlusTreeNode* sibling = node->children[idx - 1];

    for (int i = child->keys.size() - 1; i >= 0; --i) {
        child->keys[i + 1] = child->keys[i];
    }

    if (!child->isLeaf) {
        for (int i = child->children.size() - 1; i >= 0; --i) {
            child->children[i + 1] = child->children[i];
        }
    }

    child->keys[0] = node->keys[idx - 1];

    if (!node->isLeaf) {
        child->children[0] = sibling->children[sibling->keys.size()];
    }

    node->keys[idx - 1] = sibling->keys[sibling->keys.size() - 1];

    sibling->keys.resize(sibling->keys.size() - 1);
}

void BPlusTree::borrowFromNext(BPlusTreeNode* node, int idx) {
    BPlusTreeNode* child = node->children[idx];
    BPlusTreeNode* sibling = node->children[idx + 1];

    child->keys[child->keys.size()] = node->keys[idx];

    if (!(child->isLeaf)) {
        child->children[(child->keys.size()) + 1] = sibling->children[0];
    }

    node->keys[idx] = sibling->keys[0];

    for (int i = 1; i < sibling->keys.size(); ++i) {
        sibling->keys[i - 1] = sibling->keys[i];
    }

    if (!sibling->isLeaf) {
        for (int i = 1; i <= sibling->children.size(); ++i) {
            sibling->children[i - 1] = sibling->children[i];
        }
    }

    sibling->keys.resize(sibling->keys.size() - 1);
}

void BPlusTree::merge(BPlusTreeNode* node, int idx) {
    BPlusTreeNode* child = node->children[idx];
    BPlusTreeNode* sibling = node->children[idx + 1];

    child->keys[minDegree - 1] = node->keys[idx];

    for (int i = 0; i < sibling->keys.size(); ++i) {
        child->keys[i + minDegree] = sibling->keys[i];
    }

    if (!child->isLeaf) {
        for (int i = 0; i <= sibling->children.size(); ++i) {
            child->children[i + minDegree] = sibling->children[i];
        }
    }

    for (int i = idx + 1; i < node->keys.size(); ++i) {
        node->keys[i - 1] = node->keys[i];
    }

    for (int i = idx + 2; i <= node->children.size(); ++i) {
        node->children[i - 1] = node->children[i];
    }

    child->keys.resize(minDegree - 1 + sibling->keys.size());
    node->keys.resize(node->keys.size() - 1);
    node->children.resize(node->children.size() - 1);

    delete sibling;
}

int BPlusTree::findKey(BPlusTreeNode* node, const std::string& key) {
    int idx = 0;
    while (idx < node->keys.size() && node->keys[idx] < key) {
        ++idx;
    }
    return idx;
}

std::string BPlusTree::getPred(BPlusTreeNode* node, int idx) {
    BPlusTreeNode* cur = node->children[idx];
    while (!cur->isLeaf) {
        cur = cur->children[cur->keys.size()];
    }
    return cur->keys[cur->keys.size() - 1];
}

std::string BPlusTree::getSucc(BPlusTreeNode* node, int idx) {
    BPlusTreeNode* cur = node->children[idx + 1];
    while (!cur->isLeaf) {
        cur = cur->children[0];
    }
    return cur->keys[0];
}

