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
        float sumWeight ; 

        
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

        this -> numberOfSequares = mapWidth / sequareWidth ; 
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
        sensor.color = getColorSeq(sensor.x , sensor.y ) ; 

        for (int i = 0 ; i < sizeArr ; i++ ) { 
            calculate_X_Y(particlesArr[i] ,stepMoved , angleMoved , angleRadian  ); 
            particlesArr[i].color = getColorSeq(particlesArr[i].x , particlesArr[i].y ) ; 
        }

    }

    void updateWeight () { 
        for (int i = 0 ; i < sizeArr ; i++ ) { 
            if (particlesArr[i].color == sensor.color) 
                particlesArr[i].weight = 0.7 ;
            else 
                particlesArr[i].weight = 0.3 ;

        sumWeight += particlesArr[i].weight ; 
        }
    }

   void normalize() { 
    for (int i = 0 ; i < sizeArr ; i++ ) { 
        particlesArr[i].weight = particlesArr[i].weight / sumWeight ; 
    }
   }

   void sample() { 
        float * spacePoints = new float [sizeArr] ; 
        float sum  = 0 ; 
        for (int i = 0 ; i < sizeArr ; i++ ) { 
            spacePoints[i] = sum ; 
            sum += particlesArr[i].weight * sizeArr  ; 
            
        }
        // int size2 ; 

        // if (sizeArr > 0 && sizeArr <= 10)
        // size2 = sizeArr ; 
        // else 
        // int size2 = sizeArr - 10  ; 

        float r ; 
        Particle * newParticleArr = new Particle [sizeArr] ; 

        for (int i = 0 ; i < sizeArr ; i++ ) { 
            r = RandomFloat (0 , sum ) ;
            

            for (int j = 0 ; j < sizeArr ; j ++ ) { 
                if (r >= spacePoints[j] ){
        
                newParticleArr[i] = particlesArr[j] ; 
                break ; }
            
            }
            
        }

        
        
   }


    
    string getColorSeq (float x , float y) { 
        
        int sequareLocationX = x / this->sequareWidth ; 
        int sequareLocationY = y / this->sequareWidth ; 
    
        if (sequareLocationY % 2 == 0 ) { 
            if (sequareLocationX % 2 == 0 ) { 
                return "white" ; 
            }
            else { 
                return "black" ; 
            }
        
        } else { 
            if (sequareLocationX % 2 == 0 ) { 
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

    void play() { 
        char c ; 
        while (true) {  
            displayPoints() ;  
            move()  ; 
            updateWeight() ;
            normalize() ;  
            // sample() ; 

            if (sizeArr <= 10) 
            break ; 
            cout << "press anyThing to continue , press n to exit" << endl ; 
            cin >> c  ; 
            if (c == 'n') {
            cout << "the operation closed !" << endl ;
            break; 
            }
        }
    }


        
};


int main () 

{ 
    P_filter app ; 
    app.play() ; 
    

    return 0 ; 
}