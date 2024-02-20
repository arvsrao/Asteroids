//
// Created by Arvind Rao on 18.02.24.
//

#include "GameObject.h"

// init static variable
int GameObject::_instance_count = 0;
std::mutex GameObject::_mutex;

GameObject::GameObject() { _instance_count++; }

GameObject::~GameObject() { _instance_count--; }

int GameObject::getNumberOfInstances() {
    return _instance_count;
}
