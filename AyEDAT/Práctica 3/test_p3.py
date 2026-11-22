import random
from p3 import calculate_escape_probability

# Fijamos una semilla para reproducir los resultados
random.seed(42)

num_particulas = 1000
radio_maximo = 15

for pasos in [50, 200, 500]:
    prob = calculate_escape_probability(num_particulas, pasos, radio_maximo)
    porcentaje = prob * 100
    print(f"Pasos: {pasos:3d} | Probabilidad: {prob:.4f} ({porcentaje:.2f}%)")