#ifndef NODE_H
#define NODE_H

#include <vector>
using namespace std;

class Node
{
public:
    Node(Node* parent);
    virtual ~Node(); //afin que les destructeurs des enfants soient appeles
    Node* getParent();
    virtual void doAction(); //effectue l'action du noeud courant

    virtual void actionSequences(); //effectue l'action du noeud courant puis appelle les actions des enfants

    void addChild(Node* n);
    Node* getChild(int index);
    int getNumberOfChildren();
    virtual void animate();

protected:
    Node* parent;
    vector<Node*> children;

};

#endif // NODE_H
