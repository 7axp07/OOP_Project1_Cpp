#ifndef ORGANISM_H
#define ORGANISM_H
#include <string>
using namespace std;

class World; 

class Organism {
    char symbol;
    int strength;
    int initiative;
    pair<int, int> position;
    pair<int, int> prevPosition;
    int age;
protected:
    World* world;
    const int movement[4][2] = { {0,1},{1,0},{0,-1},{-1,0} };

public:
    Organism(char symbol, int strength, int initiative, int x, int y);
    Organism(const Organism& a);
    virtual void action() = 0;
    virtual void collision(Organism* other) = 0;
    virtual char draw() const = 0;
    virtual string toString();
    virtual bool isRunningAway();

    char getSymbol();
    int getInitiative();
    int getStrength();
    int getAge();

    void increaseAge(int value = 1);
    void increaseStrength(int value);
    void kill();

    static int priority(Organism* a, Organism* b);

    //positon stuff
    int getX();
    int getY();
    bool setPosition(pair<int, int> pos, bool isEmpty);
    void goBack();

};

#endif // ORGANISM_H