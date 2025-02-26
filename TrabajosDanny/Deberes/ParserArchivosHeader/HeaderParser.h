#ifndef HEADER_PARSER_H
#define HEADER_PARSER_H

class Node
{
private:
    char *data;
    Node *next;

public:
    Node(const char *value);
    ~Node();
    char *getData() const;
    Node *getNext() const;
    void setNext(Node *node);

    friend class LinkedList;
};

class LinkedList
{
private:
    Node *head;
    int size;

public:
    LinkedList();
    ~LinkedList();
    void insert(const char *value);
    void clear();
    int getSize() const;
    Node *getHead() const;
};

class HeaderParser
{
private:
    LinkedList *prototypes;
    char *filePath;

    bool isPrototype(const char *line);
    char *trimWhitespace(const char *str);
    char *findImplementationFile() const;

public:
    
    HeaderParser(const char *path);
    ~HeaderParser();
    bool parseFile();
    void printPrototypes() const;
    LinkedList *getPrototypes() const;
    int getPrototypesCount() const;
    char *getPrototypeAt(int index) const;
};
#endif