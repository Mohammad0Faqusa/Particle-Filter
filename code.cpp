#include <iostream>
#include <cstdlib>
#include <ctime> 
using namespace std;

struct Particle { 
    float x, y, theta; 
    float w; 
};

float normalize(Particle* S) {
    float sum = 0; 
    for (int i = 0; i < 100; i++) {
        sum += S[i].w;
    }
    for (int i = 0; i < 100; i++) {
        S[i].w = S[i].w / sum;
    }

    return sum;
}

Particle* initi(Particle* S) {
   

    for (int i = 0; i < 100; i++) {
        S[i].x = rand() * 50 ; 
        S[i].y = rand() * 100 ; 
        S[i].theta = rand() * 360 ; 
        S[i].w = 0.01 ; 
    }
    return S;
}


int main() {
    Particle* S = new Particle[100] ; 


    S = initi(S) ; 

    return 0 ; 

    
} 

