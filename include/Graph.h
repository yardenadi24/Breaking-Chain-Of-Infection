#ifndef GRAPH_H_
#define GRAPH_H_
#include <vector>
#include <queue>
class Session;

class Graph{
public:
    //----constructor---//
    Graph();
    Graph(std::vector<std::vector<int>> matrix);

    //---destructor--//
    virtual ~Graph();

    //-----------functions-----------//

    //--bfs--//
    int BFS(Session &session, int node);
    void infectNode(int nodeInd);
    bool isInfected(int nodeInd);

    //--getter--//
    std::vector<std::vector<int>> getEdges()const;
    std::vector<int> getInfv()const;
    int getSize()const;
    std::vector<std::vector<int>> getNeighbours()const;

    //---setter---//
    void setEdg(std::vector<std::vector<int>> _edg);
    void setNeighbours(std::vector<std::vector<int>> _neighbours);
    void setInfv(std::vector<int> _infV);
    void setSize(int i);
private:
    std::vector<std::vector<int>> edges;
    int size;
    std::vector<std::vector<int>> neighbours;
    std::vector<int> infV;
public:

};

#endif
