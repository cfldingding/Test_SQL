#include "Composite.h"



void Leaf::operation()
{
    fprintf(stderr, "----operation leaf\n");
}


void Composite::add(Component* c)
{
    m_leafs.push_back(c);
}



void Composite::operation()
{
    fprintf(stderr, "operation Composite\n");
    vector<Component*>::iterator comIter = m_leafs.begin();

    for (; comIter != m_leafs.end(); comIter++)
    {
        fprintf(stderr, "----");
        (*comIter)->operation();
    }
}
