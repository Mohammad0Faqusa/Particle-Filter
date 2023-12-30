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
        Particle* resampledParticles = new Particle[sizeArr];

        // Roulette wheel resampling
        float cumulativeWeight = 0.0;
        float step = sumWeight / sizeArr;
        float pointer = RandomFloat(0, step);

        for (int i = 0; i < sizeArr; ++i) {
            cumulativeWeight += particlesArr[i].weight;
            while (pointer < cumulativeWeight) {
                resampledParticles[i] = particlesArr[i];
                pointer += step;
            }
        }

        // Deallocate old array
        delete[] particlesArr;

        // Update particlesArr with resampled particles
        particlesArr = resampledParticles;
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

    void report(){   
        float meanParticleX, meanParticleY, varParticleX, varParticleY;

        float sum=0;
	    for (int i=0;i<sizeArr ;i++)
	    	sum+=particlesArr[i].x;
            meanParticleX=sum/(float)sizeArr ;

	    sum=0;
	    for (int i=0;i<sizeArr ;i++)
	    	sum+=particlesArr[i].y;
            meanParticleY=sum/(float)sizeArr ;

	    sum=0;
	    for (int i=0;i<sizeArr ;i++)
	    	sum+= ((particlesArr[i].x - meanParticleX)*(particlesArr[i].x - meanParticleX));

            varParticleX=sqrt(sum/(float)sizeArr) ;
	
	    sum=0;
	    for (int i=0;i<sizeArr ;i++)
	        sum+=((particlesArr[i].y - meanParticleY)*(particlesArr[i].y - meanParticleY));

            varParticleY=sqrt(sum/((float)sizeArr )) ;	
  
	    cout<< "the mean Particle ( " << meanParticleX<<" , "<<meanParticleY<<") varParticle ( "<<varParticleX<<", "<<varParticleY<<")\n";
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

        for (int i=0; i<=100; i++){
            float robotX, robotY, displacement, angle;
            readCSVLine("./uploads/robot.csv", i+2, sensor.x, sensor.y, stepMoved, angleMoved);
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
    

