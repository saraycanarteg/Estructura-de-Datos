#include "HeaderParser.h"
#include <iostream>
#include <fstream>
#include <cstring>

// Node implementation
Node::Node(const char *value)
{
    int len = strlen(value) + 1;
    data = new char[len];
    strcpy(data, value);
    next = nullptr;
}

Node::~Node()
{
    delete[] data;
}

char *Node::getData() const
{
    return data;
}

Node *Node::getNext() const
{
    return next;
}

void Node::setNext(Node *node)
{
    next = node;
}

// LinkedList implementation
LinkedList::LinkedList()
{
    head = nullptr;
    size = 0;
}

LinkedList::~LinkedList()
{
    clear();
}

void LinkedList::insert(const char *value)
{
    Node *newNode = new Node(value);
    if (!head)
    {
        head = newNode;
    }
    else
    {
        Node *current = head;
        while (current->getNext())
        {
            current = current->getNext();
        }
        current->setNext(newNode);
    }
    size++;
}

void LinkedList::clear()
{
    while (head)
    {
        Node *temp = head;
        head = head->getNext();
        delete temp;
    }
    size = 0;
}

int LinkedList::getSize() const
{
    return size;
}

Node *LinkedList::getHead() const
{
    return head;
}

// HeaderParser implementation
HeaderParser::HeaderParser(const char *path)
{
    int len = strlen(path) + 1;
    filePath = new char[len];
    strcpy(filePath, path);
    prototypes = new LinkedList();
}

HeaderParser::~HeaderParser()
{
    delete[] filePath;
    delete prototypes;
}

bool HeaderParser::isPrototype(const char *line)
{
    // Busca características típicas de un prototipo
    return (strchr(line, '(') != nullptr &&
            strchr(line, ')') != nullptr &&
            strstr(line, "class") == nullptr &&
            strstr(line, "#") == nullptr &&
            line[strlen(line) - 1] == ';');
}

char *HeaderParser::trimWhitespace(const char *str)
{
    while (*str == ' ' || *str == '\t')
        str++;

    char *result = new char[strlen(str) + 1];
    strcpy(result, str);

    int end = strlen(result) - 1;
    while (end >= 0 && (result[end] == ' ' || result[end] == '\t' || result[end] == '\n' || result[end] == '\r'))
    {
        result[end] = '\0';
        end--;
    }

    return result;
}

bool HeaderParser::parseFile()
{
    std::ifstream file(filePath);
    if (!file.is_open())
    {
        std::cerr << "Error: No se pudo abrir el archivo " << filePath << std::endl;
        return false;
    }

    char line[256];
    while (file.getline(line, sizeof(line)))
    {
        if (isPrototype(line))
        {
            char *trimmed = trimWhitespace(line);
            prototypes->insert(trimmed);
            delete[] trimmed;
        }
    }

    file.close();
    return true;
}

void HeaderParser::printPrototypes() const
{
    Node *current = prototypes->getHead();
    while (current)
    {
        std::cout << current->getData() << std::endl;
        current = current->getNext();
    }
}

LinkedList *HeaderParser::getPrototypes() const
{
    return prototypes;
}

char *HeaderParser::findImplementationFile() const
{
    // Encontrar la posición del último punto en el nombre del archivo
    const char *dot = strrchr(filePath, '.');
    if (!dot)
    {
        std::cerr << "Error: No se encontró extensión en el archivo" << std::endl;
        return nullptr;
    }

    // Calcular la longitud del nombre base (sin la extensión)
    size_t baseLen = dot - filePath;
    // +5 para ".cpp\0"
    char *cppFile = new char[baseLen + 5];

    // Copiar el nombre base
    strncpy(cppFile, filePath, baseLen);
    // Añadir la extensión .cpp
    strcpy(cppFile + baseLen, ".cpp");

    // Verificar que el archivo existe
    std::ifstream file(cppFile);
    if (!file.good())
    {
        std::cerr << "No se pudo encontrar el archivo: " << cppFile << std::endl;
        delete[] cppFile;
        return nullptr;
    }

    file.close();
    std::cout << "Archivo CPP encontrado: " << cppFile << std::endl;
    return cppFile;
}

int HeaderParser::getPrototypesCount() const
{
    return prototypes->getSize();
}

char *HeaderParser::getPrototypeAt(int index) const
{
    if (index < 0 || index >= prototypes->getSize())
        return nullptr;

    Node *current = prototypes->getHead();
    for (int i = 0; i < index && current; i++)
    {
        current = current->getNext();
    }
    return current ? current->getData() : nullptr;
}
