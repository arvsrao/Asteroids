#ifndef ASTEROIDS_GAMEOBJECT_H
#define ASTEROIDS_GAMEOBJECT_H

#include <mutex>

class GameObject {
public:
    GameObject();
    ~GameObject();

    static int getNumberOfInstances();

protected:
    static std::mutex _mutex;

private:
    static int _instance_count;

};

#endif //ASTEROIDS_GAMEOBJECT_H
