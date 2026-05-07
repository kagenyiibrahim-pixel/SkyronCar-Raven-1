# SkyronCar Perception System - Digital Vision & Proximity
# Developed by: Kagenyi Ibrahim

class SkyronPerception:
    def __init__(self):
        self.camera_status = "Active"
        self.ultrasonic_range = 2.5  # Distance in meters

    def process_camera_feed(self):
        """Simulates real-time processing of the digital mirror system."""
        print(f"Mirrorless Vision System: {self.camera_status}")
        print("Optimizing low-light contrast for nighttime driving...")

    def obstacle_detection(self, distance):
        """Triggers emergency braking if an object is too close."""
        if distance < 1.0:
            return "ALARM: Object detected within 1m! Engaging Aura-OS Braking."
        else:
            return "Clearance: Path is safe."

# Test System
if __name__ == "__main__":
    vision = SkyronPerception()
    vision.process_camera_feed()
    print(vision.obstacle_detection(0.7))
