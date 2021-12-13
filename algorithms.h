#pragma once

#include "graph.h"
#include <queue>
#include <vector>
#include <unordered_map>
#include <iostream>
#include <fstream>
#include <string>

/**
 * Conducts a Breadth first traversal of the directed graph
 * Counts the shortest paths between two vertices
 * Returns a map of maps that stores the distances between two vertices
 */
std::unordered_map<Vertex, std::unordered_map<Vertex, int>> BFS(Graph graph);

/**
 * Helper function for BFS main function
 */
void BFS(Graph & graph, Vertex v, std::unordered_map<Vertex, bool> & explored, std::unordered_map<Vertex, int> & dist);

/**
 * Reads in a file storing graph data
 * Each line is an edge between two vertices
 * Creates and returns a directed and unweighted graph from it
 */
Graph makeGraph(std::string filename);

/**
 * Conducts the PageRank algorithm on a graph
 * Calculates the relative significance of every vertex to every other vertex
 * Returned number is arbitray and not significant but its relative value is significant
 */
std::unordered_map<Vertex, double> PageRank(const Graph & graph);

/**
 * Calculates the strongly connected components of a graph
 * Each component contains vertices where every vertex is accessible by an other vertex
 */
std::vector<std::vector<Vertex>> SCC(Graph graph);

/**
 * Inverts the graph by reversing the edges in a directed graph
 */
void GraphTranspose(Graph & graph);

/**
 * Helper function for strongly connected component main function
 */
void SCC_Helper(Graph & graph, const Vertex & v, std::unordered_map<Vertex, bool> & visited, std::vector<Vertex> & component);

