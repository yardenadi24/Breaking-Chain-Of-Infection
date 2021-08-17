#ifndef SESSION_H_
#define SESSION_H_

#include "Graph.h"
#include "Agent.h"
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <queue>
#include "json.hpp"
class Agent;



enum TreeType{
  Cycle,
  MaxRank,
  Root
};

class Session{
public:
    //---destructor----//
    virtual ~Session();
    //---constructors---//
    //--default--//
    Session();
    //normal//
    Session(const std::string& path);
//----------------RULE OF 5------------------//

    //--copy constructor--//
    Session(const Session &other);
    //--copy assignment operator--//
    const Session& operator=(const Session& other);
    //--move constructor--//
    Session(Session&& other);
    //--move assignment operator--//
    const Session& operator=(Session&& other);


    //--------functions------///
    void simulate();


    //------getters-----//
    int getCycle()const;
    TreeType getTreeType() const;
    Graph getGraph()const;
    std::vector<int> getCarry()const;
    std::queue<int> getInfected()const;


    //------setters-----//
    void setGraph(const Graph& graph);
    void addAgent(const Agent& agent);
    void setInf(int index);
    void setCarry(int index);


    //---queue methods--//
    void enqueueInfected(int);
    int dequeueInfected();


private:
    Graph g;
    TreeType treeType;
    std::vector<Agent*> agents;
    int cycle;
    std::vector<int> carry;
    std::queue<int> infected ;
public:

};

#endif
