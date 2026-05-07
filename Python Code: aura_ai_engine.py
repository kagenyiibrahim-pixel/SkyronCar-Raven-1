# Aura-OS AI Inference Engine - SkyronCar Raven-1
# Lead Architect: Kagenyi Ibrahim

class AuraAI:
    def __init__(self):
        self.model_state = "Inference_Mode"
        self.confidence_threshold = 0.85 # 85% certainty required

    def scan_environment(self, sensor_data):
        """Simulates AI identifying objects from camera/sensor fusion."""
        objects = sensor_data.get('detected_objects', [])
        actions = []

        for obj in objects:
            label = obj['label']
            confidence = obj['confidence']

            if confidence >= self.confidence_threshold:
                if label == "Obstacle":
                    actions.append("PATH_RECALCULATION: Veer Left")
                elif label == "Pedestrian":
                    actions.append("SAFETY_PROTOCOL: Apply Braking")
            
        return actions if actions else ["Maintaining Current Path"]

# Testing the AI Logic
if __name__ == "__main__":
    ai_core = AuraAI()
    # Simulated data from camera sensors
    test_input = {
        'detected_objects': [
            {'label': 'Obstacle', 'confidence': 0.92},
            {'label': 'Tree', 'confidence': 0.45}
        ]
    }
    
    results = ai_core.scan_environment(test_input)
    print(f"AI Decision Output: {results}")
