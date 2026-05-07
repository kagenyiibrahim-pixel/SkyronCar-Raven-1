import numpy as np
import matplotlib.pyplot as plt

# Configuration for SkyronCar Raven-1
BATTERY_CAPACITY_KWH = 100.0
800V_LFP_EFFICIENCY = 0.96
REGEN_EFFICIENCY = 0.65  # Front-biased recovery
REACTOR_FEEDBACK_GAIN = 0.12 # System 1 Dynamo reclamation gain
DISTANCE_KM = 100

def simulate_journey(use_ai=True):
    # Simulated 100km trip with varying speed (km/h)
    time_steps = np.linspace(0, 1, 100) # 100 segments of the journey
    speeds = 60 + 40 * np.sin(time_steps * 2 * np.pi) # Varies between 20-100 km/h
    
    soc = 100.0 # Start at 100% State of Charge
    energy_history = []
    
    for speed in speeds:
        # Base consumption (Drag + Rolling resistance)
        base_drain = (speed**2 * 0.0005) + 0.1 
        
        if use_ai:
            # Aura-OS AI Logic:
            # 1. Optimizes Torque Split
            # 2. Activates Reactor Loop at steady speeds
            # 3. Predicts braking to maximize regen
            recovery = (base_drain * REACTOR_FEEDBACK_GAIN) if speed > 40 else 0
            net_drain = base_drain - recovery
        else:
            net_drain = base_drain # Standard EV (No feedback loop)
            
        soc -= (net_drain / BATTERY_CAPACITY_KWH) * 10
        energy_history.append(soc)
        
    return energy_history

# Run Sim
standard_ev = simulate_journey(use_ai=False)
skyron_raven1 = simulate_journey(use_ai=True)

# Visualize the "Skyron Advantage"
plt.figure(figsize=(10, 5))
plt.plot(standard_ev, label='Standard EV Strategy', color='red', linestyle='--')
plt.plot(skyron_raven1, label='Skyron Aura-OS (AI + Reactor)', color='green', linewidth=2)
plt.title('Raven-1 Energy Autonomy Simulation (100km Trip)')
plt.ylabel('Battery State of Charge (%)')
plt.xlabel('Journey Segment')
plt.legend()
plt.grid(True)
plt.show()

savings = skyron_raven1[-1] - standard_ev[-1]
print(f"Total Energy Saved by Aura-OS: {savings:.2f}%")
