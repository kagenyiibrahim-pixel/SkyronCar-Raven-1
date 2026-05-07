/* * Aura-OS: Safety Shield & Emergency Collision Avoidance
 * Lead Architect: Kagenyi Ibrahim
 */

#include <iostream>
#include <string>

class SafetyShield {
private:
    float safeDistanceThreshold = 5.0; // Meters
    bool emergencyBrakingActive = false;

public:
    struct SensorData {
        float distanceToObject; // From LiDAR/Camera
        float closingSpeed;     // How fast we are approaching
        std::string objectType; // "Pedestrian", "Vehicle", "Obstacle"
    };

    void evaluateRisk(SensorData data, float currentVehicleSpeed) {
        // Calculation: Time to Collision (TTC)
        float ttc = data.distanceToObject / (currentVehicleSpeed + 0.1f);

        std::cout << "--- Safety Shield Monitoring ---" << std::endl;

        // 1. Level 1: Warning (Visual/Audio alert)
        if (ttc < 3.0 && ttc > 1.5) {
            std::cout << "WARNING: Potential Collision with " << data.objectType << " in " << ttc << "s" << std::endl;
        } 
        
        // 2. Level 2: Emergency Intervention
        else if (ttc <= 1.5 || data.distanceToObject < safeDistanceThreshold) {
            applyEmergencyBrakes();
            std::cout << "CRITICAL: AEB ACTIVATED. Object: " << data.objectType << std::endl;
        } else {
            emergencyBrakingActive = false;
            std::cout << "Path Clear. Safety Shield Standby." << std::endl;
        }
    }

    void applyEmergencyBrakes() {
        emergencyBrakingActive = true;
        // Logic: Send 100% Signal to Regen + 100% to Hydraulic Brakes
        // Logic: Cut all power to Front and Rear Motors instantly
    }
};

int main() {
    SafetyShield shield;
    
    // Scenario: Approaching a stopped vehicle at 60km/h (16.6 m/s)
    SafetyShield::SensorData roadObject = {12.0, 16.6, "Vehicle"}; 
    
    shield.evaluateRisk(roadObject, 16.6); // This should trigger the shield

    return 0;
}
