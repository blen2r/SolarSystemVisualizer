#include "shape.h"
#include <stdlib.h>
#include <iostream>

Shape::Shape(Node* parent) : Node(parent)
{
}

Shape::~Shape()
{

}

void Shape::doAction()
{
    draw();
}
