/* * SkyronCar Raven-1: Real-time Sensor Fusion
 * Monitoring Reactor Temperature and Vehicle Stability
 */

#include <iostream>
#include <string>

class SensorSuite {
public:
    float getReactorTemp() {
        return 45.5; // Simulated degrees Celsius
    }

    void checkStability(float pitch, float roll) {
        if (pitch > 15.0 || roll > 15.0) {
            std::cout << "Aura-OS Warning: Vehicle Tilt Detected. Adjusting suspension." << std::endl;
        } else {
            std::cout << "Stability Status: Optimal." << std::endl;
        }
    }
};

int main() {
    SensorSuite raven1Sensors;
    std::cout << "Reactor Temperature: " << raven1Sensors.getReactorTemp() << "C" << std::endl;
    raven1Sensors.checkStability(2.0, 1.5);
    return 0;
}
