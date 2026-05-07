/* * Aura-OS: AI-Driven Mode Selection & Energy Optimization
 * Lead Architect: Kagenyi Ibrahim
 */

#include <iostream>
#include <string>
#include <vector>

enum class DriveMode { ECO_REACTOR, COMFORT, HYPER_PLAID, EMERGENCY };

class AuraAIKernel {
private:
    float batteryTemp = 35.0;     // Celsius
    float energyEfficiency = 0.98; // 98% (Reactor Loop Efficiency)
    DriveMode currentMode = DriveMode::COMFORT;

public:
    // AI Inference: Predicts the best mode based on real-time sensor data
    DriveMode predictOptimalMode(float throttleRate, float incline, float batterySOC) {
        
        // 1. High-Performance Trigger
        if (throttleRate > 0.85 && batterySOC > 0.20 && batteryTemp < 55.0) {
            return DriveMode::HYPER_PLAID;
        }
        
        // 2. Efficiency Trigger (Eco-Reactor)
        // If driving is steady or battery is low, prioritize the Feedback Loop
        if (throttleRate < 0.30 || batterySOC < 0.15) {
            return DriveMode::ECO_REACTOR;
        }

        // 3. Safety Override
        if (batteryTemp > 65.0) {
            return DriveMode::EMERGENCY;
        }

        return DriveMode::COMFORT;
    }

    void executeMode(DriveMode mode) {
        currentMode = mode;
        std::cout << "--- Aura-OS AI Update ---" << std::endl;
        switch (mode) {
            case DriveMode::ECO_REACTOR:
                std::cout << "Mode: ECO-REACTOR | Feedback Loop: 100% Flow | Torque: Limited" << std::endl;
                break;
            case DriveMode::HYPER_PLAID:
                std::cout << "Mode: HYPER-PLAID | Dual Motors: MAX | Reactor: STANDBY" << std::endl;
                break;
            case DriveMode::EMERGENCY:
                std::cout << "Mode: THERMAL PROTECT | Limp Home Active | Cooling: MAX" << std::endl;
                break;
            default:
                std::cout << "Mode: COMFORT | Balanced Performance" << std::endl;
        }
    }
};

int main() {
    AuraAIKernel aura;
    
    // Scenario: You floor the pedal to overtake a truck in Kampala
    float throttle = 0.95; 
    float batteryLife = 0.80; // 80% SOC
    
    DriveMode selected = aura.predictOptimalMode(throttle, 0.0, batteryLife);
    aura.executeMode(selected);

    return 0;
}
