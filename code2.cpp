#include <iostream>
#include <cmath>
#include <string>
#include <cstdlib>
#include <fstream>
#include <sstream>
using namespace std;

const double PI = 3.141592653589793238462643383279502884L;

const int ENVIRONMENT_SIZE = 80;
int environment[ENVIRONMENT_SIZE][ENVIRONMENT_SIZE];

struct PFStruct {
    float x, y, theta; // particle position
    float w;          // weight
    int mode;          // command mode
    float forwardDistance; // distance to move forward
    float rotateAngle;     // angle to rotate
};

void normalize(PFStruct S[]) {
    float sum = 0;

    for (int i = 0; i < 100; ++i) {
        sum += S[i].w;
    }

    for (int i = 0; i < 100; ++i) {
        S[i].w = S[i].w / sum;
    }

}

void initializeParticles(PFStruct S[]) {
    for (int i = 0; i < 100; ++i) {
        S[i].x = static_cast<float>(rand()) / static_cast<float>(RAND_MAX); // between 0 and 1
        S[i].y = static_cast<float>(rand()) / static_cast<float>(RAND_MAX); // between 0 and 1
        S[i].theta = static_cast<float>(rand()) / static_cast<double>(RAND_MAX) * 360.0; // between 0 and 360
        S[i].theta = static_cast<float>((static_cast<double>(S[i].theta) * 180.0) / PI);
        //convert redian to degree 

        S[i].w = 0.01; // sum of particles = 1
    }
}

int sampleParticle(PFStruct S[]) {
    int idx;

    do {
        idx = rand() % 100;
    } while (S[idx].w == 0);

    return idx;
}


float pdark = 0.8;  // Example probability of dark color
float pwhite = 0.2; // Example probability of white color

void updateWeight(PFStruct S[], float Z) {
    float updatedWeights[100];//مصفوفة جديدة لتخزين الأوزان بعد التحديث
    for (int i = 0; i < 100; ++i) {
        // Determine the color of the particle based on the environment
        int particleColor = environment[S[i].x][S[i].y];

        // Update weight based on the conditions
        if (particleColor == 0 && Z == 1) {
            // If the particle is on dark and the robot on dark
            S[i].w = pdark;
        }
        else if (particleColor == 1 && Z == 1) {
            // If the particle is on white and the robot on dark
            S[i].w = (1 - pdark);
        }
        else if (particleColor == 1 && Z == 0) {
            // If the particle is on white and the robot on white
            S[i].w = pwhite;
        }
        else if (particleColor == 0 && Z == 0) {
            // If the particle is on dark and the robot on white
            S[i].w = (1 - pwhite);
        }
        // نسخ الوزن بعد التحديث إلى المصفوفة()
        updatedWeights[i] = S[i].w;
    }


}

void PossitionForwerdOrRotate(PFStruct& particle, float commandValue) {
    if (particle.mode == 0) {
        // Forward command
        float dx = particle.forwardDistance *   cos(particle.theta  * (PI / 180.0));
        float dy = particle.forwardDistance * sin(particle.theta *  (PI / 180.0));
        particle.x += dx;
        particle.y += dy;
    }
    else if (particle.mode == 1) {
        // Rotate command
        particle.theta += particle.rotateAngle;
    }
}

void ParticleFilter(PFStruct S[], float Z, PFStruct U) {
    for (int j = 0; j < 100; ++j) {
        int i = sampleParticle(S); // اختيار جسيمة i عشوائياً بناءً على وزنها

        // تنفيذ الأمر U على الجسيمة المختارة
        PossitionForwerdOrRotate(S[i], U.mode == 0 ? U.forwardDistance : U.rotateAngle);

        // تحديث وزن الجسيمة المختارة بناءً على Z
        updateWeight(S, Z);
    }

    // توحيد الأوزان
    normalize(S);
}


void report(PFStruct S[], int numParticles, float robotX, float robotY, float& meanParticleX, float& meanParticleY, float& varParticleX, float& varParticleY) {
    float sumX = 0, sumY = 0, sumVarX = 0, sumVarY = 0;

    for (int i = 0; i < numParticles; i++) {
        sumX += S[i].x;
        sumY += S[i].y;
    }

    meanParticleX = sumX / numParticles;
    meanParticleY = sumY / numParticles;

    for (int i = 0; i < numParticles; i++) {
        sumVarX += (S[i].x - meanParticleX) * (S[i].x - meanParticleX);
        sumVarY += (S[i].y - meanParticleY) * (S[i].y - meanParticleY);
    }

    varParticleX = sumVarX / (numParticles - 1);  // استخدم (numParticles - 1) في المقام
    varParticleY = sumVarY / (numParticles - 1);  // لحساب الانحراف القياسي للعينة

}



// تعبئة البيئة بنمط شطرنجي
void fillEnvironment() {
    // يتم استخدام هذه الدالة لملء البيئة بمربعات سوداء وبيضاء كنمط شطرنج
    for (int i = 0; i < ENVIRONMENT_SIZE; ++i) {
        for (int j = 0; j < ENVIRONMENT_SIZE; ++j) {
            environment[i][j] = (i + j) % 2; // اللون يتناوب بين 0 و 1 لتكوين نمط شطرنجي
        }
    }
}







void readCSVLine(const string& filename, int lineNumber, float& x, float& y, float& displacement, float& angle) {
    ifstream file(filename);
    string line;

    if (!file.is_open()) {
        cout << "cannot find the file! " << filename << endl;
        return;
    }

    for (int i = 1; i <= lineNumber; ++i) {
        if (!getline(file, line)) {
            cout << "error in read this line " << lineNumber << "in file " << filename << endl;
            return;
        }

        if (i == lineNumber) {
            istringstream iss(line);
            string value;
            int count = 0;
            while (getline(iss, value, ',')) {
                count++;
                switch (count) {
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

int main() {
    // Initialize the particle filter   
    PFStruct particles[100];

    initializeParticles(particles);
    // Fill the environment with a checkerboard pattern
    fillEnvironment();

    // Process each line of the file

// Process each line of the file
    for (int i = 0; i <= 500; i++) {
        float robotX, robotY, displacement, angle;
        readCSVLine("robot.csv", i + 2, robotX, robotY, displacement, angle);

        // Perform particle filter based on the read data
        PFStruct command;
        command.mode = 0; // Assuming forward movement, you may change it based on your data
        command.forwardDistance = displacement; // Use displacement as the forward distance
        command.rotateAngle = angle; // Use angle as the rotation angle
        ParticleFilter(particles, 1, command); // Assuming Z = 1, change it based on your data
        ParticleFilter(particles, 0, command); // Assuming Z = 0, change it based on your data

        // Variables to store computed values
        float meanParticleX, meanParticleY, varParticleX, varParticleY;

        // Call the modified report function
        report(particles, 100, robotX, robotY, meanParticleX, meanParticleY, varParticleX, varParticleY);

        // Print the values
        std::cout << "Iteration " << i + 1 << ": " "robotx " << robotX << " " << "roboty:" << robotY << "  " << "meanParticleX" << ":" << meanParticleX << "  meanParticleY" << ":" << meanParticleY << "varParticleX:" << varParticleX << "   varParticleY:" << " " << varParticleY << "\n";
    }


}