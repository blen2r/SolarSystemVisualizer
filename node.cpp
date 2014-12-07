#include "node.h"

#include <iostream>
using namespace std;

Node::Node(Node* parent)
{
    this->parent = parent;
}

Node* Node::getParent()
{
    return parent;
}

Node::~Node()
{
    for(int i = 0; i < getNumberOfChildren(); i++)
    {
        delete getChild(i);
    }
}

void Node::doAction()
{

}

void Node::addChild(Node* n)
{
    children.push_back(n);
}

Node* Node::getChild(int index)
{
    if(index < children.size())
        return children.at(index);
    else
        return NULL;
}

int Node::getNumberOfChildren()
{
    return children.size();
}

void Node::actionSequences()
{
    doAction();

    for(int i = 0; i < getNumberOfChildren(); i++)
    {
        getChild(i)->actionSequences();
    }
}

void Node::animate()
{
    for(int i = 0; i < getNumberOfChildren(); i++)
    {
        getChild(i)->animate();
    }
}
