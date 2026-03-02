
#include "Graph.hpp"
/**************************************************************************************************/
/* MIN_HEAP CLASS*/
/* Data structures inside
    1. heap: a vector that stores the indices of the vertices in the heap.
    2. dist: a vector that contains the distances from the source vertex to each vertex.(determines Priority)
    3. pos: a vector that maps each vertex to its position in the heap.
 */
 /**************************************************************************************************/

 /**************************************************************************************************/
/* MIN_HEAP CONSTRUCTOR*/
/**************************************************************************************************/
MinHeap::MinHeap(const std::vector<unsigned long>& dist, int n) : pos(n, -1), dist(dist){
    /* reserve space for the heap vector, method from <vector>*/
    heap.reserve(n);
    for (int i = 0; i < n; i++) {
        /* Add new element to the end of vector, method from <vector>*/
        heap.push_back(i) ;
        /* Save each postion of the heap*/
        pos[i] = i;
    }
    /* Heapify down to ensure min heap property*/
    for (int i = n / 2 - 1; i >= 0; i--) {
        heapify_down(i);
    }
}
/**************************************************************************************************/
/*HEAPIFY UP Restores Min heap property by moving an element UP if its smaller than its parent.

 Parameters:
    i: index of the element to heapify up.

Returns:
    none
 */
/**************************************************************************************************/
void MinHeap::heapify_up(int i) {
    while (i > 0) {
        // calculate index of parent
        int parent = (i - 1) / 2;
        // evaluate priority by looking at the distances
        if (dist[heap[i]] < dist[heap[parent]]) {
            // swap the current element with its parent
            std::swap(heap[i], heap[parent]);
            // update positions in the pos vector
            pos[heap[i]] = i ;
            pos[heap[parent]] = parent;
            i = parent;
        } else {
            // the code above will be repeated until min heap property is restored or we reach the root
            break;
        }
    }
}
/**************************************************************************************************/
/*HEAPIFY DOWN Restores Min heap property by moving an element down if its larger than one of its children.

 Parameters:
    i: index of the element to heapify down.

Returns:
    none
 */
/**************************************************************************************************/
void MinHeap::heapify_down(int i) {
    // calculate size of heap vector
    int n = heap.size();
    while (true) {
        // calculate indices of children
        int left = 2 * i + 1;
        int right = 2 * i + 2;
        // find the smallest among the current node and its children
        int smallest = i;
        if (left < n && dist[heap[left]] < dist[heap[smallest]]) {
            smallest = left;
        }
        if (right < n && dist[heap[right]] < dist[heap[smallest]]) {
            smallest = right ;
        }
        /* if the current node its not the smallest*/
        if (smallest != i) {
            /* swap with the smallest child*/
            std::swap(heap[i], heap[smallest]);
            // update positions in the pos vector
            pos[heap[i]] = i;
            pos[heap[smallest]] = smallest;
            i = smallest;
        } else {
            // The code above will be repeated until the current node is the smallest
            break;
        }
    }
}
/**************************************************************************************************/
/*Extract_Min Removes and returns the vertex with the minimum distance from the heap.(root)

 Parameters:
    none

Returns:
    element with the minimum distance
 */
/**************************************************************************************************/
int MinHeap::extract_min() {
    //copy root
    int min_vertex = heap[0];
    // copy last element of the vector, method from <vector>
    int last = heap.back();
    // replace root with last element and update position
    heap[0] = last;
    pos[last] = 0;
    // remove last element from the heap
    heap.pop_back();
    // heapify down to restore min heap property
    if (!heap.empty()) {
        heapify_down(0);
    }
    // mark the extracted vertex as not in the heap
    pos[min_vertex] = -1;
    return min_vertex;
}
/**************************************************************************************************/
/* DECREASE_KEY Decreases the key of a vertex in the heap, when the distance to the source decreases.

 Parameters:
    vertex: index of the vertex whose key is to be decreased.

Returns:
    none
 */
/**************************************************************************************************/
void MinHeap::decrease_key(int vertex) {
    // find the position of the vertex
    int i = pos[vertex];
    // if the vertex in the heap(pos != -1), heapify up to restore min heap property
    if (i != -1) {
        heapify_up(i);
    }
}
/**************************************************************************************************/
/* Graph CLASS*/
/* Implemented using an adjacency list following instructions advice
2 vectors:
    1. labels: main vector that stores the labels of the vertices.
    2. adj_list: vector of vectors, inner ones store adjacency lists as pairs(neighbour vertex, weight of the edge)

Notes: because the graph in undirected, each edge is stored twice, once for each vertex.
 */
 /**************************************************************************************************/

/**************************************************************************************************/
/* FIND_INDEX Searches for the index of a vertex by its label.

 Parameters:
    label: the label of the vertex to search for.
Returns:
    index of the vertex if found, -1 otherwise.
 */
/**************************************************************************************************/
 int Graph::find_index(const std::string& label) const {
    // Iterate through labels vector
    for (size_t i = 0; i < labels.size(); i++) {
        // If label matches, return index
        if (labels[i] == label) return static_cast<int>(i);
    }
    // If label not found, return -1
    return -1;
}
/**************************************************************************************************/
/* ADD_VERTEX Adds a new vertex to the graph with the given label

 Parameters:
    label: the label of the vertex to ADD.
Returns:
    NONE
 */
/**************************************************************************************************/
void Graph::addVertex(std::string label) {
    // Check if the label already exists
    if (find_index(label) != -1) return;
    // Add the new label and an empty adjacency list for it
    labels.push_back(label);
    adj_list.push_back(std::vector<std::pair<int, unsigned long>>());
}
/**************************************************************************************************/
/* REMOVE_VERTEX Removes a vertex from the graph by its label.

 Parameters:
    label: the label of the vertex to remove.
Returns:
    none.
    Notes: Deletion is done by replacing the vertex to be removed with the last vertex in the labels vector.
    and then deleting the last vertex.
 */
/**************************************************************************************************/
void Graph::removeVertex(std::string label) {
    int idx = find_index(label);
    // If the vertex is not found, return
    if (idx == -1) return;
    // Remove the vertex from the adjacency list of its neighbors
    /* Outer loop iterates over all the neighbors of the vertex being removed*/
    for (const auto& neighbor : adj_list[idx]) {
        /* Extract index of the current neighbor*/
        int k = neighbor.first;
        /* Inner loop iterates through the adjacency list of neighbor using an iterator*/
        for (auto it = adj_list[k].begin(); it != adj_list[k].end(); ++it) {
            if (it->first == idx) {
                /* replace edge with the last element of list*/
                *it = adj_list[k].back();
                /* remove the last edge wich was already copied*/
                adj_list[k].pop_back();
                break;
            }
        }
    }
    // find the last index of the labels 
    int last_idx = static_cast<int>(labels.size()) - 1;
    /* if the vertex is not the last one in the labels vector*/
    if (idx != last_idx) {
        // replace the vertex to be removed with the last vertex in the labels vector
        labels[idx] = labels[last_idx];
        adj_list[idx] = adj_list[last_idx];
        // update the new index in the neighbors adjacency list
        for (const auto& neighbor : adj_list[idx]) {
            int m = neighbor.first;
            for (auto& p : adj_list[m]) {
                if (p.first == last_idx) {
                    p.first = idx;
                    break;
                }
            }
        }
    }
    // remove the last vertex from the labels and adjacency list
    labels.pop_back();
    adj_list.pop_back();
}
/**************************************************************************************************/
/* ADD_EDGE adds an edge between two vertices with a specified width

 Parameters:
     2 labels: the label of the vertices to connect.
        weight: the weight of the edge to add
Returns:
    none.
 */
/**************************************************************************************************/
void Graph::addEdge(std::string label1, std::string label2, unsigned long weight) {
    // find the indices of the vertices
    int idx1 = find_index(label1);
    int idx2 = find_index(label2);
    // If either one of the vertices is not found, or they are the same, do nothing
    if (idx1 == -1 || idx2 == -1 || idx1 == idx2) return;
    /* Ensure the edge does not already exist*/
    for (const auto& p : adj_list[idx1]) {
        if (p.first == idx2) return;
    }
    // Add the edge to both vertices adjacency lists
    adj_list[idx1].push_back(std::make_pair(idx2, weight));
    adj_list[idx2].push_back(std::make_pair(idx1, weight));
}
/**************************************************************************************************/
/* remove_EDGE removes an edge between two vertices.

 Parameters:
     2 labels: the label of the vertices to connect.

Returns:
    none.
 */
/**************************************************************************************************/
void Graph::removeEdge(std::string label1, std::string label2) {
    /* find indices of the two vertices*/
    int idx1 = find_index(label1);
    int idx2 = find_index(label2);
    if (idx1 == -1 || idx2 == -1) return;
    /* remove edge from both lists by replacing by the last element and removing last*/
    for (auto it = adj_list[idx1].begin(); it != adj_list[idx1].end(); ++it) {
        if (it->first == idx2) {
            *it = adj_list[idx1].back();
            adj_list[idx1].pop_back();
            break;
        }
    }
    for (auto it = adj_list[idx2].begin(); it != adj_list[idx2].end(); ++it) {
        if (it->first == idx1) {
            *it = adj_list[idx2].back();
            adj_list[idx2].pop_back();
            break;
        }
    }
}
/**************************************************************************************************/
/* Reverse_VECTOR Reverses the order of elements in a vector.

 Parameters:
    vec: a reference to the vector to reverse.
Returns:
    none.
 */
/**************************************************************************************************/
void Graph::reverse_vector(std::vector<std::string>& vec) {
    size_t n = vec.size();
    /* swap elements until middle is reached*/
    for (size_t i = 0; i < n / 2; i++) {
        std::swap(vec[i], vec[n - 1 - i]);
    }
}
/**************************************************************************************************/
/* SHORTEST_PATH Finds the shortest path between two vertices using Dijkstra's algorithm.

 Parameters:
     -start and end labels of th vertices to find the path between.
     -path: a reference to a vector that will store the labels of the vertices in the shortest path.
Returns:
    The length of the shortest path, or 0 if no path exists.
Notes:
    1. Uses Dijkstra's algorithm with a min-heap to efficiently find the shortest path.
    2. The path is stored in reverse order, so it is reversed before returning.
 */
/**************************************************************************************************/
unsigned long Graph::shortestPath(std::string startLabel, std::string endLabel, std::vector<std::string>& path) {
    /* find the indices of the vertices*/
    int start_idx = find_index(startLabel);
    int end_idx = find_index(endLabel);
    // If either vertex is not found, clear the path and return 0
    if (start_idx == -1 || end_idx == -1) {
        path.clear();
        return 0;
    }
    //initialize total number of vertices
    int n = static_cast<int>(labels.size());
    // Initialize shortes known distance to all vertices as infinity(INF) declared in Graph.hpp
    std::vector<unsigned long> dist(n, INF); 
    // Initialize A vector that stores the previous vertex on the shortest path for each vertex
    std::vector<int> prev(n, -1);
    // Set the distance to the start vertex to 0
    dist[start_idx] = 0;
    // Create a min-heap to store vertices based on their distances
    MinHeap heap(dist, n);
    // Main loop of Dijkstra's algorithm
    while (!heap.empty()) {
        // extract the vertex with the minimum distance 
        int u = heap.extract_min();
        if (dist[u] == INF) break;
        //check if the path through the current vertex is shorter for each neighbor
        for (const auto& neighbor : adj_list[u]) {
            int v = neighbor.first;
            unsigned long weight = neighbor.second;
            if (dist[u] + weight < dist[v]) {
                // Update the distance and previous vertex if a shorter path is found
                dist[v] = dist[u] + weight;
                prev[v] = u;
                // Update the priority of the vertex v in the heap
                heap.decrease_key(v);
            }
        }
    }
    // If the end vertex is unreachable, clear the path and return 0
    if (dist[end_idx] == INF) {
        path.clear();
        return 0;
    }
    // Reconstruct the shortest path by backtracking from the end vertex
    path.clear();
    for (int r = end_idx; r != -1; r = prev[r]) {
        path.push_back(labels[r]);
    }
    // Reverse the path to get it from start to end
    reverse_vector(path);  
    return dist[end_idx];
}