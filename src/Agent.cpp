#include "../include/Agent.h"
#include "../include/Session.h"
class ContactTracer;
class Virus;


Agent::Agent(){}

Agent::~Agent(){}
//--------contact tracer------//

//--constructor--//
ContactTracer::ContactTracer(){};
//--des--//
ContactTracer::~ContactTracer(){};
//----clone---//
Agent * ContactTracer::clone()const {
    return new ContactTracer(*this);
};

//--act--//
void ContactTracer::act(Session &session) {
    if(!session.getInfected().empty()){
        Graph g=session.getGraph();
        int infect = session.dequeueInfected();
        int index = g.BFS(session,infect);
        std::vector<std::vector<int>> _tempN = g.getNeighbours();
        for(int i=0;i<g.getSize();i++){
            if(_tempN[index][i]==1){
                _tempN[index][i]=0;
                _tempN[i][index]=0;
            }
        }
        g.setNeighbours(_tempN);
        g.setEdg(_tempN);
        session.setGraph(g);
    }
};


//--------Virus------//

//--constructor--//
Virus::Virus(int ind):nodeInd(ind){};
//--des--//
Virus::~Virus(){};
//----clone---//
Agent* Virus::clone()const {
    return new Virus(*this);
};

//--act--//
void Virus::act(Session &session) {
    Graph g=session.getGraph();
    int index=-1;
    int sickNode = this->nodeInd;
    if(!g.isInfected(nodeInd)){
        session.enqueueInfected(sickNode);
        session.setInf(sickNode);
    }
    std::vector<std::vector<int>> _tempN = g.getNeighbours();
    std::vector<int> _tempC = session.getCarry();
    for(int i=0;i<g.getSize()&&index==-1;i++){
        if(_tempN[sickNode][i]==1 && _tempC[i]!=1){
            index=i;
        }
    }

    if(index!=-1){
        //add new virus
        session.addAgent(Virus(index));
        _tempC[index]=1;
        session.setCarry(index);
        //mark this node as carry
    }
};




/// function to add on Graph :
/// minneighbour(index) - find the neighbour of index with the lowest index .
/// function to add on session :
/// Graph getGraph() - give us the private field g.






