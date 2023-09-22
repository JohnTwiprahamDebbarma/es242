import numpy as np

# Given parameters
L = 30.0  # Cord length (m)
m = 68.1  # Mass (kg)
cd = 0.25  # Drag coefficient (kg/m)
k = 40.0  # Spring constant (N/m)
gamma = 8.0  # Dampening coefficient (Ns/m)
g = 9.81  # Gravitational constant (m/s^2)

# Time parameters
t0, tf, dt = 0.0, 50.0, 0.1

# Initial conditions
x, v = 0.0, 0.0

# Function to compute the derivatives
def f(t, x, v):
    drag_force = -cd/m * v**2
    if x > L:
        drag_force -= k/m * (x - L) + gamma/m * v
    return g - np.sign(v) * drag_force

# Initialize arrays to store results
time_points = np.arange(t0, tf + dt, dt)
x_values, v_values = [], []

# Fourth Order Runge-Kutta method
for t in time_points:
    x_values.append(x)
    v_values.append(v)
    
    k1x = dt * v
    k1v = dt * f(t, x, v)
    
    k2x = dt * (v + 0.5 * k1v)
    k2v = dt * f(t + 0.5 * dt, x + 0.5 * k1x, v + 0.5 * k1v)
    
    k3x = dt * (v + 0.5 * k2v)
    k3v = dt * f(t + 0.5 * dt, x + 0.5 * k2x, v + 0.5 * k2v)
    
    k4x = dt * (v + k3v)
    k4v = dt * f(t + dt, x + k3x, v + k3v)
    
    x += (k1x + 2 * k2x + 2 * k3x + k4x) / 6
    v += (k1v + 2 * k2v + 2 * k3v + k4v) / 6

# Print the results
print("Time (s)\tPosition (m)\tVelocity (m/s)")
for t, x, v in zip(time_points, x_values, v_values):
    print(f"{t:.2f}\t\t{x:.2f}\t\t{v:.2f}")
