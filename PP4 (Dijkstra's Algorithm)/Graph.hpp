/**************************************************************************************************/
/* MIGUEL MATEO OSORIO VELA U96987884, EVAN PERSAD U28675784, PHONG Lien U31559628 
 Header file for Undirected Graph class

Notes: 
1. the class Graph is derived from base class GraphBase */
/**************************************************************************************************/

#ifndef GRAPH_H
#define GRAPH_H

#include "GraphBase.hpp"
#include <vector>
#include <string>

// Define INF as a large constant 
const unsigned long INF = 10000000000;  

class MinHeap {
private:
    std::vector<int> heap;
    std::vector<int> pos;
    const std::vector<unsigned long>& dist;
    void heapify_up(int i);
    void heapify_down(int i);
public:
    MinHeap(const std::vector<unsigned long>& dist, int n);
    bool empty() const { return heap.empty(); }
    int extract_min();
    void decrease_key(int vertex);
};

class Graph : public GraphBase {
private:
    std::vector<std::string> labels;
    std::vector<std::vector<std::pair<int, unsigned long>>> adj_list;
    int find_index(const std::string& label) const;
    void reverse_vector(std::vector<std::string>& vec);
public:
    void addVertex(std::string label) override;
    void removeVertex(std::string label) override;
    void addEdge(std::string label1, std::string label2, unsigned long weight) override;
    void removeEdge(std::string label1, std::string label2) override;
    unsigned long shortestPath(std::string startLabel, std::string endLabel, std::vector<std::string>& path) override;
};

#endif