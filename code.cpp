#include <iostream> 
#include <cmath> 



using namespace std ; 

struct Particle
{
    float x , y , theta ; 
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
            getColorSeq(particlesArr[i].x ,  particlesArr[i].y ) ; 

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
            cout << particlesArr[i].x << " " << particlesArr[i].y << " " << particlesArr[i].theta << " " << particlesArr[i].color << endl; 
        }
    }
        
};


int main () 

{ 
    P_filter app ; 
    Particle p = { 8 , 4 , 100 , "" };
    cout << app.getColorSeq(2.5 , 0) ; 
    app.displayPoints() ; 
    return 0 ; 
}