// BPlusTreeVisualizer.h
#ifndef BPLUSTREE_VISUALIZER_H
#define BPLUSTREE_VISUALIZER_H

#include <graphics.h>
#include "BplusTree.h"

template <typename T, int DEGREE>
class BPlusTreeVisualizer {
private:
    BPlusTree<T, DEGREE>& tree;
    static const int NODE_WIDTH = 90;
    static const int NODE_HEIGHT = 40;
    static const int LEVEL_HEIGHT = 100;
    static const int WINDOW_WIDTH = 1200;
    static const int WINDOW_HEIGHT = 800;
    static const int MIN_NODE_SPACING = NODE_WIDTH + 20;

    void drawNode(Node<T, DEGREE>* node, int x, int y, int level);
    void calculateNodePositions(Node<T, DEGREE>* node, int x, int y, int level);
    void drawLeafConnections();
    void setWindow();

public:
    BPlusTreeVisualizer(BPlusTree<T, DEGREE>& t);
    ~BPlusTreeVisualizer();
    void visualizeInsertion(const T& key);
    void visualizeRemoval(const T& key);
    void displayTree();
    void displayTraversal();
};

// implementazao
template <typename T, int DEGREE>
BPlusTreeVisualizer<T, DEGREE>::BPlusTreeVisualizer(BPlusTree<T, DEGREE>& t) : tree(t) {
    int gd = DETECT, gm;
    initgraph(&gd, &gm, (char*)"");
    setWindow();
}

template <typename T, int DEGREE>
void BPlusTreeVisualizer<T, DEGREE>::setWindow() {
    initwindow(WINDOW_WIDTH, WINDOW_HEIGHT, "B+ Tree Visualizer");
    setbkcolor(BLACK);
    setcolor(WHITE);
    cleardevice();
}

template <typename T, int DEGREE>
BPlusTreeVisualizer<T, DEGREE>::~BPlusTreeVisualizer() {
    closegraph();
}

template <typename T, int DEGREE>
void BPlusTreeVisualizer<T, DEGREE>::drawNode(Node<T, DEGREE>* node, int x, int y, int level) {
    if (!node) return;

    // Dibujar el nodo
    setcolor(WHITE);
    rectangle(x, y, x + NODE_WIDTH, y + NODE_HEIGHT);
    
    // Dibujar las claves
    char buffer[32];
    int textX = x + 10;
    for (int i = 0; i < node->numKeys; i++) {
        sprintf(buffer, "%d", node->keys[i]);
        outtextxy(textX, y + 10, buffer);
        textX += 25;
    }

    // Dibujar conexiones con los hijos
    if (!node->isLeaf) {

        int totalWidth = (node->numKeys + 1) * MIN_NODE_SPACING;
        int startX = x - (totalWidth / 2) + (NODE_WIDTH / 2);

        for (int i = 0; i <= node->numKeys; i++) {
            if (node->children[i]) {
                int childX = startX + (i * MIN_NODE_SPACING);
                line(x + NODE_WIDTH/2, y + NODE_HEIGHT,
                     childX + NODE_WIDTH/2, y + LEVEL_HEIGHT);
                drawNode(node->children[i], childX, y + LEVEL_HEIGHT, level + 1);
            }
        }
    }
}

template <typename T, int DEGREE>
void BPlusTreeVisualizer<T, DEGREE>::drawLeafConnections() {
    // Esta función se mantiene separada para dibujar las conexiones entre hojas
    if (!tree.getRoot()) return;
    
    Node<T, DEGREE>* leaf = tree.getRoot();
    while (!leaf->isLeaf) {
        leaf = leaf->children[0];
    }
    
    while (leaf && leaf->children[DEGREE]) {
        setcolor(RGB(147, 112, 219));
        
        int startX = getx() + NODE_WIDTH;
        int startY = gety() + NODE_HEIGHT/2;
        int endX = startX + 30;  
        
        line(startX, startY, endX, startY);
        
        // Punta de flecha
        int arrowLength = 10;
        int arrowWidth = 6;
        line(endX - arrowLength, startY - arrowWidth, endX, startY);
        line(endX - arrowLength, startY + arrowWidth, endX, startY);
        
        setcolor(WHITE);
        leaf = leaf->children[DEGREE];
    }
}

template <typename T, int DEGREE>
void BPlusTreeVisualizer<T, DEGREE>::visualizeInsertion(const T& key) {
    cleardevice();
    
    // Mostrar información de inserción
    char buffer[50];
    sprintf(buffer, "Insertando: %d", key);
    outtextxy(10, 10, buffer);
    
    // Realizar la inserción
    tree.insert(key);
    
    // Mostrar el árbol
    drawNode(tree.getRoot(), WINDOW_WIDTH/2, 50, 0);
    drawLeafConnections();
    
    // Mostrar altura y profundidad usando los métodos existentes
    sprintf(buffer, "Altura: %d", tree.calculateHeight(tree.getRoot()));
    outtextxy(10, WINDOW_HEIGHT - 40, buffer);
    sprintf(buffer, "Profundidad: %d", tree.calculateDepth(tree.getRoot()));
    outtextxy(10, WINDOW_HEIGHT - 20, buffer);
    
    delay(1000);
    getch();
}

template <typename T, int DEGREE>
void BPlusTreeVisualizer<T, DEGREE>::displayTree() {
    cleardevice();
    drawNode(tree.getRoot(), WINDOW_WIDTH/2, 50, 0);
    drawLeafConnections();
    
    // Mostrar recorrido in-order
    setcolor(GREEN);
    outtextxy(10, WINDOW_HEIGHT - 60, (char*)"Recorrido in-order:");
    tree.display();
    getch();
}

template <typename T, int DEGREE>
void BPlusTreeVisualizer<T, DEGREE>::displayTraversal() {
    cleardevice();
    outtextxy(10, 10, (char*)"Recorrido del árbol:");
    tree.display();
    getch();
}

template <typename T, int DEGREE>
void BPlusTreeVisualizer<T, DEGREE>::visualizeRemoval(const T& key) {
    cleardevice();
    
    // Mostrar estado inicial
    char buffer[50];
    sprintf(buffer, "Eliminando: %d", key);
    outtextxy(10, 10, buffer);
    outtextxy(10, 30, (char*)"Estado inicial del arbol:");
    drawNode(tree.getRoot(), WINDOW_WIDTH/2, 50, 0);
    delay(1000);
    
    // Realizar la eliminación en el árbol
    tree.remove(key);
    
    // Mostrar estado final
    cleardevice();
    sprintf(buffer, "Se eliminó: %d", key);
    outtextxy(10, 10, buffer);
    outtextxy(10, 30, (char*)"Estado final del arbol:");
    
    if (tree.getRoot() == nullptr) {
        setcolor(WHITE);
        outtextxy(WINDOW_WIDTH/2 - 100, WINDOW_HEIGHT/2, (char*)"Arbol vacío");
    } else {
        // Dibujar árbol actualizado
        drawNode(tree.getRoot(), WINDOW_WIDTH/2, 50, 0);
        drawLeafConnections();
        
        // Mostrar estadísticas
        setcolor(WHITE);
        sprintf(buffer, "Altura: %d", tree.calculateHeight(tree.getRoot()));
        outtextxy(10, WINDOW_HEIGHT - 60, buffer);
        sprintf(buffer, "Profundidad: %d", tree.calculateDepth(tree.getRoot()));
        outtextxy(10, WINDOW_HEIGHT - 40, buffer);
        
        // Mostrar recorrido
        setcolor(GREEN);
        outtextxy(10, WINDOW_HEIGHT - 20, (char*)"Recorrido actual: ");
        tree.display();
    }
    
    getch();
}

#endif // BPLUSTREE_VISUALIZER_H