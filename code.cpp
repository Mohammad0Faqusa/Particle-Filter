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
        Particle sensor ; 

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

    void initRobotLocation() { 
            sensor.x = RandomFloat(0 , mapWidth ) ; 
            sensor.y = RandomFloat (0 , mapWidth); 
            sensor.theta = RandomFloat(0 , 360 ) ; 
            sensor.color = getColorSeq(sensor.x ,  sensor.y ) ; 
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

    
    void calculate_X_Y(Particle & p , float stepMoved , float angleMoved , float angleRadian ) {
            angleRadian = (sensor.theta + angleMoved) ; 
            angleRadian > 360 ? angleRadian - 360 : angleRadian ; 

            p.x = p.x + cos(angleRadian) ; 
            p.y = p.y + cos(angleRadian) ; 


            if (p.x > mapWidth )
                p.x = mapWidth ; 
            if (p.x < 0  ) 
                p.x = 0 ; 

            if (p.y > mapWidth )
                p.y = mapWidth ; 
            if (p.y < 0  ) 
                p.y = 0 ; 

            p.color = getColorSeq(p.x , p.y); 
    }
    void move() { 
        float stepMoved  ; 
        float angleMoved ; 

        float x2 , y2 ; 
        
        cout << "Enter the new step distance to move" << endl ; 
        cin >> stepMoved ; 
        cout << "Enter the new increasing angle value " << endl ; 
        cin >> angleMoved ; 
        float angleRadian ;
        
        calculate_X_Y(sensor ,stepMoved , angleMoved , angleRadian  ); 

        for (int i = 0 ; i < sizeArr ; i++ ) { 
            calculate_X_Y(particlesArr[i] ,stepMoved , angleMoved , angleRadian  ); 
        }

        
    }

    void updateWeight () { 

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
    app.move()  ; 
    app.displayPoints() ; 

    return 0 ; 
}