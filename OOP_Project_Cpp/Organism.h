#ifndef ORGANISM_H
#define ORGANISM_H

#include <string>

class World; 

class Organism {
protected:
    int strength;
    int initiative;
    int x, y;
    World* world;
    int age;

public:
    Organism(int strength, int initiative, int x, int y, World* world)
        : strength(strength), initiative(initiative), x(x), y(y), world(world), age(0) {}

    virtual ~Organism() {}

    virtual void action() = 0;
    virtual void collision(Organism* other) = 0;
    virtual char draw() const = 0;

    int getInitiative() const { return initiative; }
    int getStrength() const { return strength; }
    int getAge() const { return age; }
    void increaseAge() { age++; }
    int getX() const { return x; }
    int getY() const { return y; }
    void setPosition(int newX, int newY) { x = newX; y = newY; }
};

#endif // ORGANISM_H