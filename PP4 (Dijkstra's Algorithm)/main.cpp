#include "Graph.hpp"
#include <iostream>
#include <vector>
#include <tuple>

// Function to print the shortest path and its distance
void print_path(const std::vector<std::string> &path, unsigned long dist)
{
    // Print the distance of the path
    std::cout << "Distance: " << dist << std::endl;
    // Loop through the path and print each vertex
    for (size_t i = 0; i < path.size(); i++)
    {
        std::cout << path[i];
        // Print an arrow between vertices if it's not the last vertex
        if (i < path.size() - 1)
            std::cout << " -> ";
    }
    // Print a newline at the end
    std::cout << std::endl;
}

// Main function
int main()
{
    // Test Graph 1
    Graph g1; // Create a new graph g1
    // Define a list of vertices for graph g1
    std::vector<std::string> vertices1 = {"1", "2", "3", "4", "5", "6"};
    // Add each vertex in vertices1 to graph g1
    for (const auto &v : vertices1)
    {
        g1.addVertex(v);
    }
    std::vector<std::tuple<std::string, std::string, unsigned long>> edges1 = {
        {"1", "2", 7}, {"1", "3", 9}, {"1", "6", 14}, {"2", "3", 10}, {"2", "4", 15}, {"3", "4", 11}, {"3", "6", 2}, {"4", "5", 6}, {"5", "6", 9}};
    // Loop through all edges in edges1 and add them to graph g1
    for (const auto &e : edges1)
    {
        g1.addEdge(std::get<0>(e), std::get<1>(e), std::get<2>(e));
    }
    // Declare a vector to store the shortest path for graph g1
    std::vector<std::string> path1;
    // Calculate the shortest path from vertex "1" to vertex "5" in graph g1
    unsigned long dist1 = g1.shortestPath("1", "5", path1);
    // Print the shortest path and its distance for graph g1
    std::cout << "Graph 1 Shortest Path from 1 to 5:\n";
    print_path(path1, dist1);

    // Test Graph 2
    Graph g2; // Create a new graph g2
    // Define a list of vertices for graph g2
    std::vector<std::string> vertices2 = {"BSN", "LIB", "ENB", "MSC", "CAS", "SUB", "SUN"};
    // Add each vertex in vertices2 to graph g2
    for (const auto &v : vertices2)
    {
        g2.addVertex(v);
    }
    // Define a list of edges for graph g2, with weights
    std::vector<std::tuple<std::string, std::string, unsigned long>> edges2 = {
        {"BSN", "LIB", 871}, {"BSN", "CAS", 1672}, {"BSN", "MSC", 2355}, {"SUN", "SUB", 1265}, {"LIB", "MSC", 1615}, {"LIB", "SUN", 1847}, {"ENB", "SUN", 2885}, {"ENB", "CAS", 454}, {"ENB", "LIB", 1078}};
    // Loop through all edges in edges2 and add them to graph g2
    for (const auto &e : edges2)
    {
        g2.addEdge(std::get<0>(e), std::get<1>(e), std::get<2>(e));
    }
    // Declare a vector to store the shortest path for graph g2
    std::vector<std::string> path2;
    // Calculate the shortest path from vertex "ENB" to vertex "SUN" in graph g2
    unsigned long dist2 = g2.shortestPath("ENB", "SUN", path2);
    // Print the shortest path and its distance for graph g2
    std::cout << "\nGraph 2 Shortest Path from ENB to SUN:\n";
    print_path(path2, dist2);

    std::vector<std::string> path3;
    unsigned long dist3 = g2.shortestPath("LIB", "CAS", path3);
    std::cout << "\nGraph 2 Shortest Path from LIB to CAS:\n";
    print_path(path3, dist3);

    return 0;
}
