#include <iostream> 




using namespace std ; 

struct Particle
{
    float x , y , theta ; 
    string color ; 

};


class P_filter  { 
    private : 
        float mapWidth ; 
        float numberOfSequares ; 
        float sequareWidth; 

    public : 

    P_filter () { 
        initMap() ; 
    }

    void initMap () {
        cout << "Enter the width of the map " << endl ; 
        cin >> mapWidth ; 
        cout << "Enter the number of sequares in long width" << endl ; 
        cin >> sequareWidth ; 

        this -> sequareWidth = mapWidth / numberOfSequares ; 
    }

    
    string colorSeq (Particle p) { 
        
        int XsequareLocation = p.x / sequareWidth ; 
        int YsequareLocation = p.y / sequareWidth ; 

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
        
};


int main () 

{ 
    P_filter app ; 
    Particle p = { 8 , 4 , 100 , "" };

    cout << app.colorSeq(p) ;
    return 0 ; 
}