#include "../include/Session.h"
#include <iostream>
#include <vector>
#include "../include/Agent.h"


using json = nlohmann::json;
using namespace std;

//----destructor----/////
Session::~Session(){
    agents.clear();
};

//-----constructor---///
Session::Session() : g(), treeType(), agents(), cycle(),carry(), infected(){};
Session::Session(const std::string &path) : g(vector<vector<int>>()),treeType(), agents(), cycle(),carry(), infected(){
    cout<<path<<endl;
    ifstream i(path);
    json j;;
    cout<<j<<endl;
    i>>j;
    cycle=-1;
    string treeTyp = (string)j["tree"]; // Cycle,MaxRank,Root
    if(treeTyp == "M"){
        treeType=MaxRank;
    }
    else if(treeTyp == "C"){
        treeType=Cycle;
    }
    else{
        treeType=Root;
    }
    g=Graph(j["graph"]);
    int size = g.getSize();    //how many nodes do we have in the graph
    std::vector<int> tempInf;
    for (int i = 0; i < size; i++) {
        tempInf.push_back(0); //for every node push 0, because they arent infected in the beginning
    }
    g.setInfv(tempInf);
    for(int k=0;k<size;k++){
        carry.push_back(0);
    }
    for (auto& elem: j["agents"]) {
        if (elem[0] == "V") {
            agents.push_back(new Virus(elem[1])); //create V
            carry[elem[1]]=1;
        } else {
            agents.push_back(new ContactTracer()); //create CT
        }

    }
}

//--copy constructor-----//
Session::Session(const Session &other) : g(), treeType(), agents(), cycle(),carry(), infected(){
    cycle = other.cycle;
    g = Graph(other.g);
    for (int i = 0; i < (int)other.agents.size(); i++) {
        Agent *newAgent = other.agents[i]->clone();
        agents.push_back(newAgent);
    }
    treeType = other.treeType;

    infected = other.infected;

    for (int i = 0; i < (int)other.carry.size(); i++) {
        carry.push_back(other.carry[i]);
    }
}

//--copy assignment operator--//
const Session& Session::operator=(const Session& other){
    if(this==&other){return *this;}
    for(Agent* agent:agents){
        delete (agent);
    }
    for (int i = 0; i < (int)other.agents.size(); i++) {
        Agent *newAgent = other.agents[i]->clone();
        agents.push_back(newAgent);
    }
    for (int i = 0; i < (int)other.carry.size(); i++) {
        carry.push_back(other.carry[i]);
    }
    infected = other.infected;
    cycle = other.cycle;
    g = Graph(other.g);
    treeType = other.treeType;
    return *this;
};

//--move constructor--//
Session::Session(Session&& other) : g(), treeType(), agents(), cycle(),carry(), infected(){
    infected = other.infected;
    cycle = other.cycle;
    g = Graph(other.g);
    treeType = other.treeType;
    carry = other.carry;
    agents = other.agents;
    other.agents.clear();
};

//--move assignment operator--//
const Session& Session::operator=(Session&& other){
    if(this==&other){return *this;}
    for(Agent* agent:agents){
        delete (agent);
    }
    agents = other.agents;
    other.agents.clear();
    infected = other.infected;
    cycle = other.cycle;
    g = Graph(other.g);
    treeType = other.treeType;
    carry = other.carry;

    return *this;
};

//-------------------------------function--------------------///

void Session::simulate(){
        bool exit = false;
//    while (terminate(g)) {
        while (!exit) {// checks termination conditions
        int j = agents.size();
        for (int i=0;i<j;i++) {
            agents[i]->act(*this);
        }
        if(j==(int)agents.size()){exit= true;}
        cycle++;
    }
    json output;
    output["graph"]=g.getEdges();
    vector<int> infectedNodes ;
    for(int i=0;i<(int)carry.size();i++){
        if(carry[i]==1){
            infectedNodes.push_back(i);
        }
    }
    output["infected"]=infectedNodes;
    ofstream k("output.json");
    k<<output;

    for(int i=0;i<(int)agents.size();i++){
        delete(agents[i]);
    }
};


//----------------getters------------------//

int Session::getCycle() const {
    return cycle;
};
TreeType Session::getTreeType() const {
    return treeType;
};
Graph Session::getGraph()const {
    return g;
};



std::vector<int> Session::getCarry()const{
    return carry;
};
std::queue<int> Session::getInfected()const{
    return infected;
};


//------------------setters-----------------//

void Session::setGraph(const Graph &graph) {
    g.setEdg(graph.getEdges());
    g.setNeighbours(graph.getNeighbours());
    g.setSize(graph.getSize());
    g.setInfv(g.getInfv());
};

void Session::addAgent(const Agent &agent) {
    Agent *newAgent = agent.clone();
    agents.push_back(newAgent);
};

void Session::setInf(int index){
    g.infectNode(index);
};

void Session::setCarry(int index){
  carry[index]=1;
};


//---queue methods--//
void Session::enqueueInfected(int i) {
    infected.push(i);
    g.infectNode(i);
};

int Session::dequeueInfected() {
    int output = infected.front();
    infected.pop();

    return output;
};



