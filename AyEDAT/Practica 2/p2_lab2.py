
import time
import random
import matplotlib.pyplot as plt
from typing import List, Tuple
import p2

def run_experiment_and_plot():
    # Tamaños de entrada del apartado II.C
    sizes = [100, 500, 1000, 5000]
    num_repetitions = 10  # Medición repetida al menos 10 veces[cite: 4, 24]

    times_ms = []
    selected_counts = []
    selected_percentages = []

    print("Ejecutando mediciones experimentales...")
    for n in sizes:
        activities = p2.generate_activities(n, seed=42)
        
        # Repetir al menos 10 veces sobre la misma entrada[cite: 4, 24]
        exec_times = []
        for _ in range(num_repetitions):
            start_t = time.perf_counter()
            selected = p2.activity_selection(activities)
            end_t = time.perf_counter()
            exec_times.append(end_t - start_t)
            
        avg_time = (sum(exec_times) / num_repetitions) * 1000  # Convertir a milisegundos
        times_ms.append(avg_time)
        
        count = len(selected)
        selected_counts.append(count)
        selected_percentages.append((count / n) * 100)

    # Crear la figura con las 3 gráficas solicitadas[cite: 4, 24]
    plt.style.use('seaborn-v0_8-whitegrid' if 'seaborn-v0_8-whitegrid' in plt.style.available else 'default')
    fig, axes = plt.subplots(1, 3, figsize=(18, 5))

    # Gráfica 1: Tamaño de entrada vs Tiempo de ejecución[cite: 4, 24]
    axes[0].plot(sizes, times_ms, marker='o', color='#1f77b4', linewidth=2, markersize=7)
    axes[0].set_title("Tamaño de Entrada vs. Tiempo de Ejecución", fontsize=12, fontweight='bold')
    axes[0].set_xlabel("Número de Actividades (n)", fontsize=10)
    axes[0].set_ylabel("Tiempo Promedio (ms)", fontsize=10)
    axes[0].grid(True, linestyle='--', alpha=0.7)

    # Gráfica 2: Tamaño de entrada vs Número de actividades seleccionadas[cite: 4, 24]
    axes[1].plot(sizes, selected_counts, marker='s', color='#2ca02c', linewidth=2, markersize=7)
    axes[1].set_title("Tamaño de Entrada vs. Actividades Seleccionadas", fontsize=12, fontweight='bold')
    axes[1].set_xlabel("Número de Actividades (n)", fontsize=10)
    axes[1].set_ylabel("Cantidad Seleccionada", fontsize=10)
    axes[1].grid(True, linestyle='--', alpha=0.7)

    # Gráfica 3: Tamaño de entrada vs Porcentaje de actividades seleccionadas[cite: 4, 24]
    axes[2].plot(sizes, selected_percentages, marker='^', color='#d62728', linewidth=2, markersize=7)
    axes[2].set_title("Tamaño de Entrada vs. Porcentaje Seleccionado", fontsize=12, fontweight='bold')
    axes[2].set_xlabel("Número de Actividades (n)", fontsize=10)
    axes[2].set_ylabel("Porcentaje Seleccionado (%)", fontsize=10)
    axes[2].grid(True, linestyle='--', alpha=0.7)

    plt.tight_layout()
    plt.savefig("graficas_actividades_2c.png", dpi=300)
    print("Gráficas guardadas correctamente como 'graficas_actividades_2c.png'.")

if __name__ == "__main__":
    run_experiment_and_plot()