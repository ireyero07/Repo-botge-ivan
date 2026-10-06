import time # Para la función time_measure. Entender código dado.
import matplotlib.pyplot as plt # Para imprimir gráficas. Entender código dado.
import random # Puede usarse random.randint(n, m) para generar listas aleatorias de enteros en las funciones dataprep.
import numpy as np
from p1 import (
    time_measure,
    has_sum_pair,
    dataprep_sum_pair_hit,
    dataprep_sum_pair_miss,
    plot_single_curve
)

Nlist = list(range(10, 10001, 100))

result_hit = time_measure(has_sum_pair, dataprep_sum_pair_hit, Nlist)
result_miss = time_measure(has_sum_pair, dataprep_sum_pair_miss, Nlist)

times_hit = [x[0] for x in result_hit]
times_miss = [x[0] for x in result_miss]

plot_single_curve(
    Nlist,
    times_hit,
    title="Tiempo de has_sum_pair - Caso hit",
    xlabel="Tamaño de la lista (n)",
    ylabel="Tiempo (s)"
)

plot_single_curve(
    Nlist,
    times_miss,
    title="Tiempo de has_sum_pair - Caso miss",
    xlabel="Tamaño de la lista (n)",
    ylabel="Tiempo (s)"
)