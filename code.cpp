#include <iostream> 
#include <cmath> 

// Name : Mohammad Faqusa 
// ID : 201014 
// Github link : https://github.com/Mohammad0Faqusa/Particle-Filter.git

using namespace std ; 

const float PI = 3.14159274101257324219 ;

struct Particle
{
    float x , y , theta , weight ; 
    string color ; 

};


class P_filter  { 
    private : 
        float mapWidth ; 
        int numberOfSequares ; 
        float sequareWidth; 
        int sizeArr ; 

        
        Particle* particlesArr ; 

    public : 

    P_filter () { 
        initMap() ; 
        initParticlesArr() ; 
    }

    void initMap () {
        cout << "Enter the width of the map " << endl ; 
        cin >> mapWidth ; 
        cout << "Enter the number of sequares in long width" << endl ; 
        cin >> sequareWidth ; 

        this -> sequareWidth = mapWidth / numberOfSequares ; 
    }

    void initParticlesArr() { 
        this -> sizeArr  = mapWidth * mapWidth ; 
        this -> particlesArr = new Particle[sizeArr] ; 

        for (int i = 0 ; i < sizeArr ; i++ ) { 
            particlesArr[i].x = RandomFloat(0 , mapWidth ) ; 
            particlesArr[i].y = RandomFloat (0 , mapWidth); 
            particlesArr[i].theta = RandomFloat(0 , 360 ) ; 
            particlesArr[i].color = getColorSeq(particlesArr[i].x ,  particlesArr[i].y ) ; 
            particlesArr[i].weight = 1.0 / (float)sizeArr ; 

        }
    }

    void Move() { 
        float stepMoved  ; 
        float angleMoved ; 

        float x2 , y2 ; 
        
        cout << "Enter the new step distance to move" << endl ; 
        cin >> stepMoved ; 
        cout << "Enter the new increasing angle value " << endl ; 
        cin >> angleMoved ; 
        float angleRadian ;

        for (int i = 0 ; i < sizeArr ; i++ ) { 
        
            angleRadian = (particlesArr[i].theta + angleMoved) ; 
            angleRadian > 360 ? angleRadian - 360 : angleRadian ; 

            particlesArr[i].x = particlesArr[i].x + cos(angleRadian) ; 
            particlesArr[i].y = particlesArr[i].y + cos(angleRadian) ; 

            particlesArr[i].color = getColorSeq(particlesArr[i].x , particlesArr[i].y); 

            if (particlesArr[i].x > mapWidth )
                particlesArr[i].x = mapWidth ; 
            if (particlesArr[i].x < 0  ) 
                particlesArr[i].x = 0 ; 

            if (particlesArr[i].y > mapWidth )
                particlesArr[i].y = mapWidth ; 
            if (particlesArr[i].y < 0  ) 
                particlesArr[i].y = 0 ; 

        }

        
    }

    

    
    string getColorSeq (int x , int y) { 
        
        int XsequareLocation = (int)(x / sequareWidth) ; 
        int YsequareLocation = (int)(y / sequareWidth) ; 

        if (YsequareLocation % 2 == 0 ) { 
            if (XsequareLocation % 2 == 0 ) { 
                return "white" ; 
            }
            else { 
                return "black" ; 
            }
        
        } else { 
            if (XsequareLocation % 2 == 0 ) { 
                return "black"; 
            }
            else { 
                return "white" ; 
            }
        }
        
    } 

    float RandomFloat(float a, float b) {
        float random = ((float) rand()) / (float) RAND_MAX;
        float diff = b - a;
        float r = random * diff;
    return a + r;
}
    void displayPoints () { 
        for (int i = 0 ; i < sizeArr ; i ++ ) { 
            cout << particlesArr[i].x << " " 
            << particlesArr[i].y << " " 
            << particlesArr[i].theta << " " 
            << particlesArr[i].color << " "
            << particlesArr[i].weight <<  endl; 
        }
    }


        
};


int main () 

{ 
    P_filter app ; 
    cout << app.getColorSeq(2.5 , 0) ; 
    app.displayPoints() ; 
    app.Move()  ; 
    app.displayPoints() ; 
    return 0 ; 
}