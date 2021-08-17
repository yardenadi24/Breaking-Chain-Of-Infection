#ifndef TREE_H_
#define TREE_H_
#include "Session.h"
#include <vector>



class Tree{
public:
    Tree();
    //--constructor--//
    Tree(int rootLabel);
    //--destructor--//
    virtual ~Tree();
    //----------------RULE OF 5------------------//
    //--copy constructor--//
    Tree(const Tree &otherTree);
    //--copy assignment operator--//
    const Tree& operator=(const Tree& other);
    //--move constructor--//
    Tree(Tree&& other);
    //--move assignment operator--//
    const Tree& operator=(Tree&& other);
    //------------functions----------------------------//
    //--getters--//
    std::vector<Tree*> getChildren();
    int getNode()const;
    //--setters--//
    void setNode(int node);
    //--move assignment operator--//
    void addChild(const Tree& child);
    void addChild(Tree* child);
    //--calls the right constructor tree--//
    static Tree* createTree(const Session& session, int rootLabel);
    //--comp max child--//
    void maxChild(Tree* tree,int *max,int *node);
    //-virtual-//
    virtual int traceTree()=0;
    virtual Tree* clone() const=0;


private:
    int node;
    std::vector<Tree*> children;
};

class CycleTree: public Tree{

public:
    CycleTree();
    CycleTree(int rootLabel, int currCycle);
    virtual int traceTree();
    virtual Tree* clone()const;

private:
    int currCycle;
};

class MaxRankTree: public Tree{

public:
    MaxRankTree();
    MaxRankTree(int rootLabel);

    virtual int traceTree();
    virtual Tree* clone()const;
};

class RootTree: public Tree{

private:

public:
    RootTree();
    RootTree(int rootLabel);
    virtual int traceTree();
    virtual Tree* clone()const;
};

#endif
