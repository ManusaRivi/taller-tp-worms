#ifndef WORM_H
#define WORM_H

#include <vector>

//Direcciones (despues quizas cambie a un angulo)
#define DIR_RIGHT 1
#define DIR_LEFT 0

//Estados (Despues va a haber mas)
#define STATUS_IDLE 0
#define STATUS_MOVING 1

class Worm {
    private:
    std::vector<int> position;  // (x,y)
    int dir;                    // Despues quizas cambie a un angulo
    int status;                 
    
    public:
    //Constructor
    Worm(std::vector<int> position, int dir, int status);
};

#endif