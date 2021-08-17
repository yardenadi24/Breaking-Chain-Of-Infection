#include "../include/Graph.h"
#include "../include/Tree.h"
class tree;

//--constructor--//
Graph::Graph():edges(),size(),neighbours(),infV(){}
Graph::Graph(std::vector<std::vector<int>> matrix) : edges({{}}), size(0), neighbours({}), infV({}) {
    edges = matrix;
    size = edges.size();
    neighbours = matrix;

    for (int i = 0; i < (int)edges.size(); i++) {
        infV.push_back(0);
    }
};
//--destructor--///
Graph::~Graph() {}

//--getter--//
std::vector<std::vector<int>> Graph::getEdges()const{
    return edges;
};
std::vector<int> Graph::getInfv()const{
    return infV;
};
int Graph::getSize()const{
    return size;
}
std::vector<std::vector<int>> Graph::getNeighbours()const{
    return neighbours;
};



//------setters-----//
void Graph::setEdg(std::vector<std::vector<int>> _edg){
    edges = _edg;
};
void Graph::setNeighbours(std::vector<std::vector<int>> _neighbours){
    neighbours=_neighbours;
}
void Graph::setInfv(std::vector<int> _infV){
    infV=_infV;
}
void Graph::setSize(int i){
    size = i;
}


// ----------function---------------//

//---bfs---//
int Graph::BFS(Session &session, int node) {
    Tree *BfsTree = Tree::createTree(session, node);
    //--build bfs--//
    std::queue<Tree *> que;
    std::vector<bool> visited;
    for (int i = 0; i < size; i++) {
        visited.push_back(false);
    }
    que.push(BfsTree);
    visited[node] = true;
    int i =0;
    while (!que.empty()) {
        Tree *curr_root = que.front();
        int nodeId = curr_root->getNode();
        que.pop();
        for (int j = 0; j < (int)edges[nodeId].size(); j++) {
            if (edges[nodeId][j] == 1 && !visited[j]) {   //if they are neighbours
                Tree *child = Tree::createTree(session, j); //create new child
                curr_root->addChild(child); //add the child to the tree
                que.push(child); //add the child to que
                visited[j] = true;  //mark him as visited
            }
        }
        i++;
    }
    //--end of bfs--//
    //--now we have shortest path tree for our sick node--//
    int output = BfsTree->traceTree();
    delete (BfsTree);
    return output;
}

void Graph::infectNode(int nodeInd) {
    infV[nodeInd] = 1;
};

bool Graph::isInfected(int nodeInd) {
    return infV[nodeInd] == 1;
};
