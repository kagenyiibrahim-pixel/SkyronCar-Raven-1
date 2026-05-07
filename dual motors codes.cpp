/* * Aura-OS: Dual-Motor Torque Vectoring & Reactor Sync 
 * Lead Architect: Kagenyi Ibrahim
 */

#include <iostream>
#include <algorithm>

struct MotorSystem {
    float torqueRequest; // 0.0 to 1.0
    float rpm;
    float temperature;
    bool isEngaged;
};

class AuraDriveController {
private:
    float batterySOC = 0.85;      // 85% Charge
    float maxCurrentAmps = 600.0; // 800V LFP Limit
    
public:
    MotorSystem frontMotor;
    MotorSystem rearMotor;

    void calculateTorque(float throttleInput, float steeringAngle) {
        // Basic Logic: Rear Motor is the "Primary" for the Kinetic Loop
        // Front Motor kicks in for performance and stability
        
        float baseTorque = throttleInput;
        
        // Torque Vectoring: Shift power to Front if steering is sharp
        if (std::abs(steeringAngle) > 0.2) {
            frontMotor.torqueRequest = baseTorque * 0.4;
            rearMotor.torqueRequest = baseTorque * 0.6;
        } else {
            // Straight line: Maximize efficiency on Rear Motor Reactor
            frontMotor.torqueRequest = baseTorque * 0.2;
            rearMotor.torqueRequest = baseTorque * 0.8;
        }

        // Safety: Overheat Protection
        if (rearMotor.temperature > 95.0) {
            rearMotor.torqueRequest *= 0.5; // Limp mode
            std::cout << "ALERT: Rear Motor Thermal Throttling" << std::endl;
        }
    }

    void displayDriveStatus() {
        std::cout << "--- Raven-1 Dual Motor Status ---" << std::endl;
        std::cout << "Front Motor Load: " << (frontMotor.torqueRequest * 100) << "%" << std::endl;
        std::cout << "Rear Motor Load:  " << (rearMotor.torqueRequest * 100) << "%" << std::endl;
        std::cout << "Reactor Sync:     ACTIVE" << std::endl;
    }
};

int main() {
    AuraDriveController raven1;
    
    // Simulate Driver input: 90% Throttle, 0% Steering (Straight line)
    raven1.calculateTorque(0.9, 0.0);
    raven1.displayDriveStatus();

    return 0;
}
