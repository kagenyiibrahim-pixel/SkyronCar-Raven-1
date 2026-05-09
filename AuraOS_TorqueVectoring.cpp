#include <iostream>
#include <algorithm>

/**
 * @file AuraOS_TorqueVectoring.cpp
 * @brief Dual-Motor Distribution for SkyronCar Raven-1
 * @author Kagenyi Ibrahim, Founder & CEO
 */

class TorqueVectoringUnit {
private:
    const float MAX_TORQUE_NM = 600.0f; // Per Axial Flux Motor
    const float VOLTAGE_THRESHOLD = 800.0f;

public:
    struct DriveInput {
        float throttlePos;    // 0.0 to 1.0
        float steeringAngle;  // -45 (Left) to 45 (Right)
        float currentVoltage; // 800V Loop Status
    };

    struct MotorCommands {
        float frontMotorTorque;
        float rearMotorTorque;
        bool reactorEngaged;
    };

    MotorCommands calculateDistribution(DriveInput input) {
        MotorCommands commands = {0, 0, false};

        // 1. Safety Voltage Check
        if (input.currentVoltage < 720.0f) {
            std::cout << "[Aura-OS] Warning: Voltage Drop. Limiting Torque Output." << std::endl;
            input.throttlePos *= 0.5f; // Limp Mode
        }

        // 2. Base Torque Calculation
        float totalRequestedTorque = input.throttlePos * (MAX_TORQUE_NM * 2);

        // 3. Torque Vectoring Logic (Cornering Optimization)
        if (input.steeringAngle > 5.0f || input.steeringAngle < -5.0f) {
            // Apply more torque to the outer motor for better cornering
            commands.frontMotorTorque = totalRequestedTorque * 0.6f;
            commands.rearMotorTorque = totalRequestedTorque * 0.4f;
        } else {
            // Straight-line cruising: Shift to Efficiency/Reclamation
            commands.frontMotorTorque = totalRequestedTorque * 0.5f;
            commands.rearMotorTorque = totalRequestedTorque * 0.5f;
            
            if (input.throttlePos < 0.2f) {
                commands.reactorEngaged = true; // Engage Kinetic Reactor (System 1)
            }
        }

        return commands;
    }
};

int main() {
    TorqueVectoringUnit tvu;
    
    // Scenario: High-speed cruising with the Steering straight
    TorqueVectoringUnit::DriveInput cruiseData = {0.15f, 0.0f, 800.0f};
    
    TorqueVectoringUnit::MotorCommands result = tvu.calculateDistribution(cruiseData);

    std::cout << "--- Raven-1 Dual-Motor Status ---" << std::endl;
    std::cout << "Front Motor: " << result.frontMotorTorque << " Nm" << std::endl;
    std::cout << "Rear Motor: " << result.rearMotorTorque << " Nm" << std::endl;
    std::cout << "Kinetic Reactor (System 1): " << (result.reactorEngaged ? "ACTIVE" : "IDLE") << std::endl;

    return 0;
}
