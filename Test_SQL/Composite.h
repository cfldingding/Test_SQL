#pragma once
#ifndef _COMPONENT_H_
#define _COMPONENT_H_

#include <vector>
#include <stdio.h>

using namespace std;

class Component
{
public:
    Component() {};
    virtual ~Component() {};

    virtual void operation() = 0;
};



class Leaf : public Component
{
public:
    Leaf() {};
    ~Leaf() {};

    void operation();
};


class Composite : public Component
{
public:
    Composite() {};
    ~Composite() {};

    void add(Component*);
    void operation();

private:
    vector<Component*> m_leafs;
};

#endif

