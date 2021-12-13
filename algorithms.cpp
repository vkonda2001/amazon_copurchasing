#include "algorithms.h"
#include <utility>
#include <iostream>
#include <stack>

std::unordered_map<Vertex, std::unordered_map<Vertex, int>> BFS(Graph graph) {
    
    std::unordered_map<Vertex, std::unordered_map<Vertex, int>> dists;
    
    for (Vertex v : graph.getVertices()) {
        std::vector<Vertex> vertices = graph.getVertices();
        std::vector<Edge> edges = graph.getEdges();
        
        std::unordered_map<Vertex, bool> vertexExplored;
        for (auto & v : graph.getVertices()) {
            vertexExplored[v] = false;
        }
        for (auto & e : graph.getEdges()) {
            graph.setEdgeLabel(e.source, e.dest, "Unexplored");
        }
        std::unordered_map<Vertex, int> distances;
        distances[v] = 0;
        BFS(graph, v, vertexExplored, distances);
        for (unsigned curr = 0; curr < vertices.size(); curr++) {
            if (!vertexExplored[vertices[curr]] && vertices[curr] == v) {
                
                BFS(graph, vertices[curr], vertexExplored, distances);
            }
        }
        dists[v] = distances;
    }
    
    return dists;
    
}

void BFS(Graph & graph, Vertex v, std::unordered_map<Vertex, bool> & explored, std::unordered_map<Vertex, int> & dist) {
    explored[v] = true;
    std::queue<Vertex> q;
    q.push(v);
    while (!q.empty()) {
        v = q.front();
        q.pop();
        for (Vertex w : graph.getAdjacent(v)) {
            if (!explored[w]) {
                graph.setEdgeLabel(v, w, "Discovery");
                explored[w] = true;
                q.push(w);
                dist[w] = dist[v] + 1;
            } else if (graph.getEdgeLabel(v, w) == "Unexplored") {
                graph.setEdgeLabel(v, w, "Cross");
            }
        }
    }
}

Graph makeGraph(std::string filename) {
    
    std::ifstream text(filename);
    std::vector<std::string> out;

    if (text.is_open()) {
        std::istream_iterator<std::string> iter(text);
        while (!text.eof()) {
            out.push_back(*iter);
            ++iter;
        }
        out.push_back(*iter);
    }
    Graph g(false, true);
    
    
    for (unsigned curr = 0; curr < out.size(); curr += 2) {
        Vertex source = out[curr];
        Vertex dest = out[curr+1];
        if (curr == out.size()-3) {
            dest = out[curr+2];
            curr += 2;
        }
        
        if (!g.vertexExists(source)) {
            g.insertVertex(source);
        } else if (!g.vertexExists(dest)) {
            g.insertVertex(dest);
        }
        g.insertEdge(source, dest);
    }

    return g;
    
}

std::unordered_map<Vertex, double> PageRank(const Graph & graph) {
    std::unordered_map<int, Vertex> vertices;
    int count = 0;
    for (auto & v : graph.getVertices()) {
        vertices[count] = v;
        count++;
    }

    std::vector<std::vector<double>> matrix;
    matrix.resize(vertices.size());
    for (auto & row : matrix) {
        row.resize(vertices.size());
    }

    for (unsigned row = 0; row < matrix.size(); row++) {
        for (unsigned col = 0; col < matrix[row].size(); col++) {
            if (graph.edgeExists(vertices[col], vertices[row])) {
                matrix[row][col] = (double) 1/graph.getAdjacent(vertices[col]).size();
            } else {
                matrix[row][col] = 0;
            }   
        }
    }

    std::vector<double> vect(vertices.size());
    for (auto & i : vect) {
        i = (double) 1/vect.size();
    }
    std::vector<double> temp;
    unsigned mSize = matrix.size();
    for (unsigned curr = 0; curr < 50; curr++) {
        temp.clear();
        temp.resize(vect.size());
        for (auto & i : temp) {
            i = 0;
        }
        for (unsigned row = 0; row < mSize; row++) {
            for (unsigned col = 0; col < mSize; col++) {
                temp[row] += matrix[row][col]*vect[col];
            }
            
        }
        vect = temp;
    }

    std::unordered_map<Vertex, double> steady_state;
    unsigned vectSize = vect.size();
    for (unsigned curr = 0; curr < vectSize; curr++) {
        steady_state[vertices[curr]] = vect[curr];
    }
    
    return steady_state;
}

void fillStack(const Graph & g, const Vertex & v, std::unordered_map<Vertex, bool> & visited, std::stack<Vertex> & st) {

    visited[v] = true;
    for (auto & adj : g.getAdjacent(v)) {
        if (!visited[adj]) {
            fillStack(g, adj, visited, st);
        }
    }
    st.push(v);
}

std::vector<std::vector<Vertex>> SCC(Graph graph) {
    std::vector<std::vector<Vertex>> components;
    std::stack<Vertex> st;

    std::unordered_map<Vertex, bool> visited;
    for (auto & v : graph.getVertices()) {
        visited[v] = false;
    }

    for (auto & v : graph.getVertices()) {
        if (!visited[v]) {
            fillStack(graph, v, visited, st);
        }
    }

    GraphTranspose(graph);

    for (auto & v : graph.getVertices()) {
        visited[v] = false;
    }

    while (!st.empty()) {
        Vertex curr = st.top();
        st.pop();
        if (!visited[curr]) {
            std::vector<Vertex> currComponent;
            SCC_Helper(graph, curr, visited, currComponent);
            components.push_back(currComponent);
        }  
    }

    return components;
}

void SCC_Helper(Graph & graph, const Vertex & v, std::unordered_map<Vertex, bool> & visited, std::vector<Vertex> & component) {
    visited[v] = true;
    component.push_back(v);
    for (auto & adj : graph.getAdjacent(v)) {
        if (!visited[adj]) {
            SCC_Helper(graph, adj, visited, component);
        }
    }

}

void GraphTranspose(Graph & graph) {
    std::vector<Edge> edges = graph.getEdges();
    for (auto & e : edges) {
        graph.insertEdge(e.dest, e.source);
        graph.removeEdge(e.source, e.dest);
    }
}
