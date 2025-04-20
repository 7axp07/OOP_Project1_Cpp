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
    const int movement[8][2] = { 
        {-1, 0},    // up
        {-1, 1},    // up right
        {0, 1},     // right
        {1, 1},     // down right
        {1, 0},     // down
        {1, -1},    // down left
        {0, -1},    // left
        {-1, -1}    // up left
    };

public:
    Organism(char symbol, int strength, int initiative, int x, int y);
    Organism(const Organism& a);
    virtual void action() = 0;
    virtual void collision(Organism* other) = 0;
    virtual string toString();
    virtual bool isRunningAway();
    virtual Organism* child() = 0;

    char getSymbol();
    int getInitiative();
    int getStrength();
    int getAge();
    virtual int getColor();

    void increaseAge(int value = 1);
    void increaseStrength(int value);
    void kill();

    static int priority(Organism* a, Organism* b);

    //positon stuff
    int getX();
    int getY();
    virtual bool setPosition(pair<int, int> pos, bool isEmpty);
    void goBack();

};

#endif // ORGANISM_H