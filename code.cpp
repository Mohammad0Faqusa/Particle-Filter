#include <iostream>
#include <cmath> 
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

void initi(Particle* S) {
   
    for (int i = 0; i < 100; i++) {
        S[i].x =  rand() % 8; 
        S[i].y = rand() % 8  ; 
        S[i].theta =  rand() % 360  ; 
        S[i].w = 0.01 ; 
    }

}

void move(Particle* S , Particle U ) {

    for (int i = 0; i < 100; i++) {
        if ((S[i].x + U.x) < 100 )   
            S[i].x += U.x ; 
        else 
            S[i].x = 100 ; 
            
        if ((S[i].y + U.y) < 100 )   
            S[i].y += U.y ; 
        else 
            S[i].y = 100 ; 
        if (S[i].theta + U.theta > 360  ) {
            S[i].theta +=  U.theta ;
            S[i].theta -= 360 ; }
        else 
            S[i].theta += U.theta ; 
    }

    
} 


void sampleParticles(Particle* S) { 
    Particle M [100] ; 
    for (int i = 0 ; i < 100 ; i++ ) { 
        M[i] = S[rand() % 100 ] ; 

    }
    for (int i = 0 ; i < 100 ; i++ ) { 
        S[i] = M[i] ; 

    }
    
}

int main() {
    Particle S[100] ; 


    initi(S) ; 
    for (int i = 0 ; i < 5 ; i++ ) { 
        cout << S[i].x << " " << S[i].y << " " << S[i].theta << endl ; 
    }
    Particle U ; 
    U.x = 4 ; 
    U.y = 0 ; 
    U.theta = 10 ; 
    move(S , U ) ; 

     for (int i = 0 ; i < 5 ; i++ ) { 
        cout << S[i].x << " " << S[i].y << " " << S[i].theta << endl ; 
    }

    cout << "update done ! " ; 

    return 0 ; 

    
} 

