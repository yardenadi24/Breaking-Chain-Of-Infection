#include "../include/Tree.h"
#include <vector>

//--constructor--//
Tree::Tree():node(0),children(){};
Tree::Tree(int rootLabel):node(0),children({}){
node = rootLabel;
}
//--destructor--//
Tree::~Tree(){
    for(Tree* tree:children){
        delete(tree);
        tree= nullptr;
    }
};
//----------------RULE OF 5------------------//
//--copy constructor--//
Tree::Tree(const Tree &other):node(0),children(){
    node = other.getNode();
    for(Tree* child:other.children){
        Tree* clone = child->clone();
        children.push_back(clone);
    }
}
//--copy assignment operator--//
const Tree& Tree::operator=(const Tree& other){
    if(this==&other){return *this;}
    for(Tree* child:children){
        delete (child);
    }
    for(Tree* child:other.children){
        Tree* clone = child->clone();
        children.push_back(clone);
    }
    node = other.getNode();
    return *this;
}
//--move constructor--//
Tree::Tree(Tree&& other):node(0),children(){
    node = other.getNode();
    for(Tree* tree:other.children){
        addChild(tree);
        tree= nullptr;
    }
}
//--move assignment operator--//
const Tree& Tree::operator=(Tree&& other){
    if(this==&other){return *this;}
    node = other.getNode();
    for(Tree* child:children){
        delete (child);
    }
    for(Tree* tree:other.children){
        addChild(tree);
        tree= nullptr;
    }
    return *this;
}

//----------------------------------------//


//---FUNCTIONS---//

    //--getters--//
    std::vector<Tree*> Tree::getChildren(){
    return children;
    };
    int Tree::getNode()const{
    return this->node;
    }

    //--setters--//
    void Tree::setNode(int node){
    this->node = node;
    };

   //-add children--//
    void Tree::addChild(const Tree& child){
    Tree* clone = child.clone();
    children.push_back(clone);
    };

    void Tree::addChild(Tree* child){
       children.push_back(child);
    };

    //--create tree--//
     Tree* Tree::createTree(const Session& session, int rootLabel){
        if(session.getTreeType()==Cycle){
            return new CycleTree(rootLabel,session.getCycle());
        }
        if(session.getTreeType()==MaxRank){
            return new MaxRankTree(rootLabel);
        }
        else{
            return new RootTree(rootLabel);
        }
    };
    //--max function--//
    void Tree::maxChild(Tree* tree,int *max,int *node){
        int i=tree->getChildren().size();
        if(i>*max){
            *(max) = i;
            *(node)=tree->getNode();
        }
        if(i>0){
            for(Tree* child:tree->getChildren()){
                maxChild(child,max,node);
            }

        }
    }
 //------------inherent------------//
 //--cycle--//
   CycleTree::CycleTree():currCycle(){}
   CycleTree::CycleTree(int rootLabel, int currCycle):Tree(rootLabel),currCycle(currCycle){} ;
    int CycleTree::traceTree(){
        int curr_node = this->getNode();
        Tree* curr_tree =this;
        int cycleCount=currCycle;
        while(cycleCount>=0&&curr_tree->getChildren().size()>0){
            curr_tree = curr_tree->getChildren()[0];
            curr_node = curr_tree->getNode();
            cycleCount--;
        }
        return curr_node;
    };
   Tree* CycleTree::clone()const{return new CycleTree(*this);};

//--max--//
    MaxRankTree::MaxRankTree(){}
    MaxRankTree::MaxRankTree(int rootLabel):Tree(rootLabel){};
     int MaxRankTree::traceTree(){
         int index =this->getNode();
         int* node = &index;
         int _max = this->getChildren().size();
         int *max = &_max;

         for(Tree* child:this->getChildren()){
            maxChild(child,max,node);
         }
        return *node;
     };
     Tree* MaxRankTree::clone()const{return new MaxRankTree(*this);};

//--root--//
  RootTree::RootTree(){}
  RootTree::RootTree(int rootLabel):Tree(rootLabel){};

    int RootTree::traceTree(){return this->getNode();};
    Tree* RootTree::clone()const{return new RootTree(*this);};

