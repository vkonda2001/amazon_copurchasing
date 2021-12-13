#include "algorithms.h"
#include "graph.h"
#include <iostream>
#include <unordered_map>
#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>

int main() {
    Graph amazonProductsComplete = makeGraph("amazon0302.txt");
    std::cout << amazonProductsComplete.getVertices().size() << " " << amazonProductsComplete.getEdges().size() << std::endl;

    Graph amazonProducts = makeGraph("amazon0302small.txt");
    std::vector<std::vector<Vertex>> stronglyConnectedComponents = SCC(amazonProducts);
    std::unordered_map<Vertex, double> pagerank = PageRank(amazonProducts);
    std::unordered_map<Vertex, std::unordered_map<Vertex, int>> productDistances = BFS(amazonProducts);
    
    std::vector<std::pair<Vertex, double>> productImportance(pagerank.begin(), pagerank.end());
    std::sort(productImportance.begin(), productImportance.end(), [](auto &left, auto &right) {
        return left.second > right.second;
        });
    std::ofstream importanceOutput;
    importanceOutput.open("Product_Importance.txt");
    std::string line;
    for (unsigned curr = 0; curr < productImportance.size(); curr++) {
        line = std::to_string(curr + 1) + ". " + productImportance[curr].first;
        importanceOutput << line << endl; 
    }
    importanceOutput.close();

    
    std::ofstream distanceOutput;
    distanceOutput.open("Product_Distances.txt");
    for (auto & first : productDistances) {
        for (auto & second : first.second) {
            line = first.first + " -> " + second.first + " = " + std::to_string(second.second);
            distanceOutput << line << endl;
        }
    }
    distanceOutput.close();
    
    std::cout << "Number of strongly connected components in graph: " << stronglyConnectedComponents.size() << std::endl;
    /*
    std::ofstream componentOutput;
    componentOutput.open("Product_components.txt");
    for (unsigned component = 0; component < stronglyConnectedComponents.size(); component++) {
        
    }
    */

    return 0;
}