import random
import numpy as np
import matplotlib.pyplot as plt

# Step size (time step) for Euler integration method
timestep = 0.001
# Amplitude of the noise term
amp = 0.01
# Time duration for the simulation
end_time = 100
# Create a time vector from 0 to end_time, separated by timestep
t = np.arange(0, end_time, timestep)

# Initializing rabbits (x) and foxes (y) population vectors
x = []
y = []

# Noise term to perturb the differential equations
def StochasticTerm(amp):
    return amp * random.uniform(-1, 1)

# Lotka-Volterra parameters definition
a = 1.0  # Birth rate of rabbits
b = 0.1  # Death rate of rabbits due to predation
c = 0.5  # Factor describing how many eaten rabbits lead to a new fox
d = 0.02  # Natural death rate of foxes

# Euler integration
# Initial conditions for rabbits (x) and foxes (y) populations at time=0
x.append(100)  # Initial rabbit population
y.append(20)   # Initial fox population

# Forward Euler method of integration with stochasticity
for index in range(1, len(t)):
    # Add stochastic noise to the parameters
    a_stochastic = a + StochasticTerm(amp)
    b_stochastic = b + StochasticTerm(amp)
    c_stochastic = c + StochasticTerm(amp)
    d_stochastic = d + StochasticTerm(amp)

    # Evaluate the current differentials
    xd = x[index - 1] * (a_stochastic - b_stochastic * y[index - 1])
    yd = -y[index - 1] * (c_stochastic - d_stochastic * x[index - 1])

    # Calculate the next values of x and y using the Euler method
    next_x = x[index - 1] + xd * timestep
    next_y = y[index - 1] + yd * timestep

    # Append the next values of x and y
    x.append(next_x)
    y.append(next_y)

# Visualization of the populations over time
if amp == 0:
    # Visualization of deterministic populations against time
    plt.plot(t, x)
    plt.plot(t, y)
    plt.xlabel('Time')
    plt.ylabel('Population Size')
    plt.legend(('Rabbits', 'Foxes'))
    plt.title('Deterministic Lotka-Volterra')
    plt.show()

    # Deterministic phase portrait
    plt.plot(x, y)
    plt.xlabel('Fox Population')
    plt.ylabel('Rabbit Population')
    plt.title('Phase Portrait of Deterministic Lotka-Volterra')
    plt.show()
else:
    # Visualization of stochastic populations against time
    plt.plot(t, x)
    plt.plot(t, y)
    plt.xlabel('Time')
    plt.ylabel('Population Size')
    plt.legend(('Rabbits', 'Foxes'))
    plt.title('Stochastic Lotka-Volterra')
    plt.show()

    # Stochastic phase portrait
    plt.plot(x, y)
    plt.xlabel('Fox Population')
    plt.ylabel('Rabbit Population')
    plt.title('Phase Portrait of Stochastic Lotka-Volterra')
    plt.show()

    # Visualization of the noise term
    noise = []
    n = []
    for sample in range(100):
        noise.append(StochasticTerm(amp))
        n.append(sample)

    plt.plot(n, noise)
    plt.xlabel('Arbitrary Noise Samples')
    plt.ylabel('Noise')
    plt.title('Perturbation to Differentials')
    plt.show()