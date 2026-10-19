import time # Para la funcion time_measure. Entender codigo dado.
import matplotlib.pyplot as plt # Para imprimir graficas. Entender codigo dado.
import random # Puede usarse random.randint(n, m) para generar listas aleatorias de enteros en las funciones dataprep.
import numpy as np
from p1 import (
     time_measure,
     has_sum_pair,
     dataprep_sum_pair_hit,
     dataprep_sum_pair_miss,
     plot_single_curve,
     rle_encode_naive,
     rle_encode_optimized,
     dataprep_rle
 )

Nlist = list(range(10, 10001, 100))

result_naive = time_measure(rle_encode_naive, dataprep_rle, Nlist, 10, 10)
result_optimized = time_measure(rle_encode_optimized, dataprep_rle, Nlist, 10, 10)

times_grouped_naive = [x[0] for x in result_naive]
times_grouped_optimized = [x[0] for x in result_optimized]

plot_single_curve(
     Nlist,
     times_grouped_naive,
     title="Tiempo de rle_encode - Caso naive (algoritmo ineficiente)",
     xlabel="Tamaño de la lista (n)",
    ylabel="Tiempo (s)",
    filename="grafica_naive.png"
 )

plot_single_curve(
     Nlist,
     times_grouped_optimized,
     title="Tiempo de rle_encode - Caso optimized (algoritmo eficiente)",
     xlabel="Tamaño de la lista (n)",
     ylabel="Tiempo (s)",
     filename="grafica_optimized.png"
 )