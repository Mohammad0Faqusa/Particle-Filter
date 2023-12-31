#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
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
        initRobotLocation() ; 
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

    
    void calculate_X_Y(Particle & p , float stepMoved , float angleMoved ) {
            float angleDegree = (p.theta + angleMoved) ; 
            angleDegree > 360 ? angleDegree - 360 : angleDegree ; 

            float angleRadian = angleDegree * (PI / 180) ; 
            p.x = p.x + stepMoved * cos(angleRadian) ; 
            p.y = p.y + stepMoved * sin(angleRadian) ; 
            p.theta = angleDegree ; 

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

    void move(float stepMoved , float angleMoved ) { 

        sensor.color = getColorSeq(sensor.x , sensor.y ) ; 

        for (int i = 0 ; i < sizeArr ; i++ ) { 
            calculate_X_Y(particlesArr[i] ,stepMoved , angleMoved  ); 
            particlesArr[i].color = getColorSeq(particlesArr[i].x , particlesArr[i].y ) ; 
        }

    }

    void updateWeight () { 
        sumWeight = 0 ; 
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
        particlesArr[i].weight = particlesArr[i].weight / (float)sumWeight ; 
    }
   }


    void sample() { 
        float * spacePoints = new float [sizeArr] ; 
        float sum  = 0 ; 
        for (int i = 0 ; i < sizeArr ; i++ ) { 
            spacePoints[i] = sum ; 
            sum += particlesArr[i].weight * sizeArr  ; 
            
        }

        
        float r ; 
        Particle * newParticleArr = new Particle [sizeArr] ; 

        for (int i = 0 ; i < sizeArr ; i++ ) { 
            r = RandomFloat (0 , sum ) ;
            

            for (int j = 0 ; j < sizeArr ; j ++ ) { 
                if (r >= spacePoints[j]  && r <= spacePoints[j+1]){
        
                newParticleArr[i] = particlesArr[j] ; 
                break ; }
                
            
            }
           
        }
        if(sizeArr > 2)
        sizeArr-- ; 

        for (int i = 0 ;  i < sizeArr ; i ++ ) { 
            particlesArr[i] = newParticleArr[i] ; 
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

    void displayRobot () { 
        cout << "The real location of the robot :" << endl ; 
        cout << sensor.x << " " << sensor.y << " " << sensor.theta << " " <<  sensor.color << " " << endl ; 
    }

    void report() {
    float meanParticleX = 0, meanParticleY = 0, varParticleX = 0, varParticleY = 0;

    // Calculate mean
    for (int i = 0; i < sizeArr; i++) {
        meanParticleX += particlesArr[i].x;
        meanParticleY += particlesArr[i].y;
    }

    meanParticleX /= sizeArr;
    meanParticleY /= sizeArr;

    // Calculate variance
    for (int i = 0; i < sizeArr; i++) {
        varParticleX += (particlesArr[i].x - meanParticleX) * (particlesArr[i].x - meanParticleX);
        varParticleY += (particlesArr[i].y - meanParticleY) * (particlesArr[i].y - meanParticleY);
    }

    varParticleX = sqrt(varParticleX / sizeArr);
    varParticleY = sqrt(varParticleY / sizeArr);

    cout << "the mean Particle ( " << meanParticleX << " , " << meanParticleY << ") varParticle ( " << varParticleX
         << ", " << varParticleY << ")\n";
}


    void readCSVLine(const string& filename, int lineNumber, float &x, float &y, float &displacement, float &angle) {

        ifstream file(filename);
        string line;

        for (int i = 1; i <= lineNumber; ++i) {
            if (!getline(file, line)) {
                cout << "out of scope\n";
                return; 
            }
            if (i == lineNumber) {
                istringstream iss(line);
                string value;
                int count = 0;
                while (getline(iss, value, ',')) {
                    count++;
                    switch(count) {
                        case 1: x = stof(value); break;
                        case 2: y = stof(value); break;
                        case 3: displacement = stof(value); break;
                        case 4: angle = stof(value); break;
                    }
                }
                break;
            }
        }
        file.close();
}
    void play() { 
        char c ; 
        float stepMoved ; 
        float angleMoved ; 

        for (int i=0; i<=500; i++){
            float robotX, robotY, displacement, angle;
            readCSVLine("./robot.csv", i+2, sensor.x, sensor.y, stepMoved, angleMoved);
            move( stepMoved , angleMoved ); 
            displayRobot() ; 
            report() ;
            updateWeight() ;
            normalize() ;  
            sample() ;
    }
    } 
}; 


    int main() {
    P_filter app ; 
    app.play() ; 
    

    return 0 ;
    }
    

