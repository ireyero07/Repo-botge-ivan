import time # Para la función time_measure. Entender código dado.
import matplotlib.pyplot as plt # Para imprimir gráficas. Entender código dado.
import random # Puede usarse random.randint(n, m) para generar listas aleatorias de enteros en las funciones dataprep.
import numpy as np

# I.A.1 Medición de tiempos de ejecución
def time_measure(f, dataprep, Nlist, Nrep=1000, Nstat=100):
    """Mide la media y varianza del tiempo de ejecución de la función f
    para cada tamaño n presente en Nlist.
    """
    res = []
    for n in Nlist:
        partial = []
        for _ in range(Nstat):
            data = dataprep(n)
            t1 = time.perf_counter()
            for _ in range(Nrep):
                f(data)
            t2 = time.perf_counter()
            t_elem = (t2 - t1) / float(Nrep)
            partial.append(t_elem)

        mean_val = sum(partial) / float(Nstat)
        var_val = sum((x - mean_val) ** 2 for x in partial) / float(Nstat)
        res.append((mean_val, var_val))
    return res

def dataprep_sum_pair_hit(n):
    if n < 2:
        return [1], 3

    lst = list(range(1, n + 1))
    target = n + (n - 1)

    return lst, target

def dataprep_sum_pair_miss(n):
    lst = list(range(1, n + 1))
    target = 2 * n + 1

    return lst, target

def dataprep_rle(n):
    if n <= 0:
        return []

    lst = []

    for i in range(n):
        lst.append(i // 3)

    return lst

# I.A.2 Búsqueda de duplicados manteniendo orden de aparición
def find_duplicates(lst):

    temp = []
    final_l = []

    for i in lst:
        if i in temp and i not in final_l:
            final_l.append(i)
        elif i not in temp:
            temp.append(i)

    return final_l


# I.A.3 Búsqueda de par que suma target con complejidad O(n)
def has_sum_pair(par):
    lst, target = par
    seen = set()

    for i in lst:
        compl = target - i
        if compl in seen:
            return True
        seen.add(i)

    return False

# I.B.1 RLE Naive / Ingenuo
def rle_encode_naive(lst):
    resultado = []
    elem_actual = lst[0]
    contador = 1

    if len(lst) == 0:
        return []

    for elem in lst[1:]:
        if elem == elem_actual:
            contador += 1
        else:
            resultado = resultado + [(elem_actual, contador)]
            elem_actual = elem
            contador = 1

    resultado = resultado + [(elem_actual, contador)]

    return resultado

# I.B.2 RLE Optimized / Óptimo
def rle_encode_optimized(lst):
    if len(lst) == 0:
        return []

    resultado = []
    elem_actual = lst[0]
    contador = 1

    for elem in lst[1:]:
        if elem == elem_actual:
            contador += 1
        else:
            resultado.append((elem_actual, contador))
            elem_actual = elem
            contador = 1

    resultado.append((elem_actual, contador))

    return resultado

# Función auxiliar para generar una gráfica de una serie de datos.
def plot_single_curve(
    x,
    y,
    title="Gráfica de Datos",
    xlabel="Eje X",
    ylabel="Eje Y",
    label=None,
    style="o-",
    color="b",
    grid=True,
    filename=None,
    figsize=(8, 5),
):
    """Genera y muestra/guarda una gráfica limpia para una única serie de datos."""
    plt.figure(figsize=figsize)  # Crea la figura con el tamaño indicado

    # Dibuja la curva
    plt.plot(x, y, style, color=color, label=label)

    # Personalización básica de ejes y título
    plt.title(title)  # Asigna el título
    plt.xlabel(xlabel)  # Etiqueta X
    plt.ylabel(ylabel)  # Etiqueta Y

    if grid:
        plt.grid(True, linestyle="--", alpha=0.6)

    if label:
        plt.legend(
            loc="best"
        )  # Muestra la leyenda si se definió una etiqueta

    plt.tight_layout()

    # Guarda la gráfica en un fichero si se especifica un nombre
    if filename:
        plt.savefig(
            filename, format=filename.split(".")[-1], dpi=300
        )  #

    plt.show()  # Muestra la figura


def init_cd(n: int)-> np.ndarray:
    return np.full(n, -1, dtype = int)


def union(rep_1: int, rep_2: int, p_cd: np.ndarray):
    if p_cd[rep_1] < 0 and p_cd[rep_2] < 0 and rep_1 != rep_2:

        if p_cd[rep_2] < p_cd[rep_1]:
            p_cd[rep_1] = rep_2
            return rep_2

        elif p_cd[rep_1] < p_cd[rep_2]:
            p_cd[rep_2] = rep_1
            return rep_1

        else:
            p_cd[rep_2] = rep_1
            p_cd[rep_1] -= 1
            return rep_1

    return None


def find(ind: int, p_cd: np.ndarray)-> int:
    root = ind
    
    while p_cd[root] >= 0:
        root = p_cd[root]

    z = ind
    while z != root:
        next = p_cd[z]
        p_cd[z] = root
        z = root #aqui no habria que poner next en vez de root???
    return root

def cd_2_dict(p_cd: np.ndarray) -> Dict:
    result = {}

    for i in range(len(p_cd)):
        rep = find(i, p_cd)

        if rep not in result:
            result[rep] = []

        result[rep].append(i)

    return result

def ccs(n: int, l: List)-> Dict:
    p_cd = init_cd(n)

    for x, y in l:
        rep_1 = find(x, p_cd)
        rep_2 = find(y, p_cd)

        if rep_1 != rep_2:
            union(rep_1, rep_2, p_cd)

    return cd_2_dict(p_cd)