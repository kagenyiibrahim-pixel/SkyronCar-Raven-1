/* * Aura-OS: Launch Control & Cheetah Stance Logic
 * Lead Architect: Kagenyi Ibrahim
 */

#include <iostream>
#include <algorithm>

class AuraLaunchController {
private:
    bool dragStripModeEnabled = false;
    float maxLaunchTorque = 1200.0; // Total Combined Nm
    float currentSlipRatio = 0.05;  // 5% slip is ideal for acceleration

public:
    struct LaunchStatus {
        bool ready;
        float frontTorque;
        float rearTorque;
        std::string message;
    };

    LaunchStatus prepareLaunch(bool brakePressed, float throttleInput) {
        LaunchStatus status = {false, 0.0, 0.0, "Standby"};

        // 1. Pre-condition: User must hold Brake and Throttle simultaneously
        if (brakePressed && throttleInput > 0.9) {
            dragStripModeEnabled = true;
            status.message = "CHEETAH STANCE ENABLED - READY TO LAUNCH";
            status.ready = true;
            
            // Pre-torque the motors slightly to take up slack in the driveline
            status.frontTorque = 50.0; 
            status.rearTorque = 50.0;
        } 
        
        // 2. Launch Execution: Release Brake while keeping Throttle pinned
        else if (!brakePressed && throttleInput > 0.9 && dragStripModeEnabled) {
            status.message = "LAUNCH ACTIVE: OPTIMAL SLIP ENGAGED";
            
            // Distribute torque based on weight transfer (Rear gets more grip)
            // We use 45/55 split for max traction on launch
            status.frontTorque = maxLaunchTorque * 0.45;
            status.rearTorque = maxLaunchTorque * 0.55;
            
            // Logic for Traction Control (Slip Prevention)
            if (currentSlipRatio > 0.15) { // If wheels spin > 15%
                status.frontTorque *= 0.8; // Reduce torque instantly
                status.rearTorque *= 0.8;
                status.message = "TRACTION CONTROL INTERVENING";
            }
        } else {
            dragStripModeEnabled = false;
        }

        return status;
    }

    void logTelemetry(bool brake, float throttle) {
        LaunchStatus s = prepareLaunch(brake, throttle);
        std::cout << "--- Raven-1 Launch Telemetry ---" << std::endl;
        std::cout << "Status: " << s.message << std::endl;
        if (s.ready || dragStripModeEnabled) {
            std::cout << "Torque Split: F[" << s.frontTorque << "Nm] R[" << s.rearTorque << "Nm]" << std::endl;
        }
    }
};

int main() {
    AuraLaunchController raven1_launch;

    // Phase 1: Prepping the "Cheetah Stance"
    std::cout << "Step 1: Holding Brake + Full Throttle" << std::endl;
    raven1_launch.logTelemetry(true, 1.0);

    // Phase 2: The Launch (Release Brake)
    std::cout << "\nStep 2: RELEASING BRAKE!" << std::endl;
    raven1_launch.logTelemetry(false, 1.0);

    return 0;
}
