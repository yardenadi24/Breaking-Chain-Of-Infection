#ifndef AGENT_H_
#define AGENT_H_
#include <vector>
#include <string>
#include "Session.h"


using namespace std;
class Agent{
public:
    Agent();
    virtual ~Agent()=0;
    virtual Agent* clone()const=0;
    virtual void act(Session& session)=0;

};

class ContactTracer: public Agent{
public:
    ContactTracer();
    virtual ~ContactTracer();
    virtual Agent* clone()const;
    virtual void act(Session& session);

};


class Virus:public Agent{
public:
    Virus(int nodeInd);
    virtual ~Virus();
    virtual Agent* clone()const;
    virtual void act(Session& session);

private:
    const int nodeInd;
};

#endif
