# Práctica 3: Programación Dinámica - Algoritmos Recursivos - Monte Carlo
# Algoritmia y Estructuras de Datos Avanzadas - Curso 2026-2027

import math
import random

# =============================================================================
# I. Alineamiento de Proteínas
# =============================================================================

# I.A Alineamiento Global: Needleman-Wunsch

def needleman_wunsch_matrix(seq1: str, seq2: str, match: int = 2, mismatch: int = -1, gap: int = -1) -> list[list[int]]:
    """
    Construye y devuelve la matriz completa de programación dinámica para el 
    alineamiento global de dos secuencias mediante el algoritmo Needleman-Wunsch.

    La matriz resultante tiene dimensiones (len(seq2) + 1) x (len(seq1) + 1), 
    donde seq1 se desarrolla a lo largo de las columnas y seq2 a lo largo de las filas.

    :param seq1: Primera secuencia a alinear (desarrollada en columnas).
    :param seq2: Segunda secuencia a alinear (desarrollada en filas).
    :param match: Puntuación acordada para una coincidencia de caracteres.
    :param mismatch: Penalización por diferencia de caracteres.
    :param gap: Penalización por introducción de hueco (gap).
    :return: Matriz de programación dinámica (lista de listas de enteros).
    """
    pass

def needleman_wunsch_backtracking(matrix: list[list[int]], seq1: str, seq2: str, match: int = 2, mismatch: int = -1, gap: int = -1) -> tuple[str, str, int]:
    """
    Reconstruye las secuencias alineadas globalmente y calcula el score total a partir 
    de la matriz de programación dinámica de Needleman-Wunsch mediante backtracking.

    El backtracking comienza en la esquina inferior derecha (len(seq2), len(seq1)) y 
    recorre la matriz hasta la esquina superior izquierda (0, 0). 
    En la estructura de la matriz, seq1 se desarrolla en columnas y seq2 en filas.

    :param matrix: Matriz de programación dinámica previamente calculada.
    :param seq1: Primera secuencia original (desarrollada en columnas).
    :param seq2: Segunda secuencia original (desarrollada en filas).
    :param match: Puntuación acordada para una coincidencia.
    :param mismatch: Penalización por diferencia.
    :param gap: Penalización por hueco.
    :return: Tupla con (aligned_seq1, aligned_seq2, total_score).
    """
    pass

# I.B Alineamiento Local: Smith-Waterman

def smith_waterman_matrix(seq1: str, seq2: str, match: int = 2, mismatch: int = -1, gap: int = -1) -> list[list[int]]:
    """
    Construye y devuelve la matriz de programación dinámica para el alineamiento 
    local de dos secuencias mediante el algoritmo Smith-Waterman.

    Aplica inicialización a ceros en los bordes (primera fila y primera columna) 
    y truncamiento a cero en cada celda para evitar valores negativos. 
    La matriz tiene dimensiones (len(seq2) + 1) x (len(seq1) + 1), donde seq1 se 
    desarrolla a lo largo de las columnas y seq2 a lo largo de las filas.

    :param seq1: Primera secuencia a alinear (desarrollada en columnas).
    :param seq2: Segunda secuencia a alinear (desarrollada en filas).
    :param match: Puntuación por coincidencia.
    :param mismatch: Penalización por diferencia.
    :param gap: Penalización por hueco.
    :return: Matriz de programación dinámica local (lista de listas de enteros).
    """
    pass

def smith_waterman_backtracking(matrix: list[list[int]], seq1: str, seq2: str, match: int = 2, mismatch: int = -1, gap: int = -1) -> tuple[str, str, int]:
    """
    Reconstruye el alineamiento local óptimo y su puntuación a partir de la matriz 
    de Smith-Waterman mediante backtracking.

    Localiza el valor máximo global en la matriz y realiza el backtracking hasta 
    alcanzar una celda con valor 0. En la matriz, seq1 se desarrolla en columnas 
    y seq2 en filas.

    :param matrix: Matriz de programación dinámica local previamente calculada.
    :param seq1: Primera secuencia original (desarrollada en columnas).
    :param seq2: Segunda secuencia original (desarrollada en filas).
    :param match: Puntuación por coincidencia.
    :param mismatch: Penalización por diferencia.
    :param gap: Penalización por hueco.
    :return: Tupla con (sub_seq1, sub_seq2, max_score).
    """
    pass

# =============================================================================
# II. Optimización de Rutas en una Cuadrícula
# =============================================================================

# II.A Recursividad Ingenua (Enfoque de Fuerza Bruta)

def min_path_recursive(grid: list[list[int]], i: int, j: int) -> int:
    """
    Calcula el coste mínimo para alcanzar la celda (i, j) desde el origen (0, 0) 
    utilizando una estrategia recursiva pura (fuerza bruta sin memoización).

    :param grid: Matriz rectangular de costes numéricos enteros.
    :param i: Índice de la fila de la celda destino.
    :param j: Índice de la columna de la celda destino.
    :return: Coste acumulado mínimo para llegar a la celda (i, j).
    """
    # Caso base 1: celda de inicio (0, 0)
    if i == 0 and j == 0:
        return grid[0][0]
    
    # Caso base 2: borde superior (solo se puede venir desde la izquierda)
    if i == 0:
        return grid[i][j] + min_path_recursive(grid, i, j - 1)
    
    # Caso base 3: borde izquierdo (solo se puede venir desde arriba)
    if j == 0:
        return grid[i][j] + min_path_recursive(grid, i - 1, j)
    
    # Caso general: elegimos el camino más barato entre venir de arriba o de la izquierda
    coste_arriba = min_path_recursive(grid, i - 1, j)
    coste_izquierda = min_path_recursive(grid, i, j - 1)
    
    return grid[i][j] + min(coste_arriba, coste_izquierda)

# II.B Programación Dinámica (Enfoque Bottom-Up)

def min_path_dp(grid: list[list[int]]) -> tuple[int, list[list[int]]]:
    """
    Calcula el coste mínimo para ir desde la celda (0, 0) hasta (N-1, M-1) 
    mediante programación dinámica ascendente (bottom-up).

    :param grid: Matriz de costes de dimensiones N x M.
    :return: Tupla con el coste mínimo global (int) y la matriz dp de costes acumulados.
    """
    N = len(grid)
    M = len(grid[0])
    
    # 1. Creamos una matriz N x M rellena de ceros
    dp = [[0 for _ in range(M)] for _ in range(N)]
    
    # 2. Caso base: esquina superior izquierda
    dp[0][0] = grid[0][0]
    
    # 3a. Rellenamos la primera fila (solo se puede venir desde la izquierda)
    for j in range(1, M):
        dp[0][j] = dp[0][j - 1] + grid[0][j]
        
    # 3b. Rellenamos la primera columna (solo se puede venir desde arriba)
    for i in range(1, N):
        dp[i][0] = dp[i - 1][0] + grid[i][0]
        
    # 4. Rellenamos el resto de la matriz fila por fila
    for i in range(1, N):
        for j in range(1, M):
            dp[i][j] = grid[i][j] + min(dp[i - 1][j], dp[i][j - 1])
            
    # Devolvemos el coste mínimo final (esquina inferior derecha) y la tabla dp completa
    return dp[N - 1][M - 1], dp

# II.C Reconstrucción de la Ruta Óptima

def get_optimal_path(grid: list[list[int]]) -> tuple[int, list[tuple[int, int]]]:
    """
    Reconstruye la secuencia exacta de coordenadas (0, 0) ... (N-1, M-1) que forman 
    el camino de coste mínimo en la cuadrícula.

    Invoca internamente a min_path_dp(grid) para generar la matriz de costes acumulados.

    :param grid: Matriz original de costes.
    :return: Tupla con el coste total mínimo y la lista de coordenadas (i, j) de la ruta.
    """
    # 1. Llamamos a la función del apartado II.B para obtener el coste mínimo y la matriz dp
    min_cost, dp = min_path_dp(grid)
    
    N = len(grid)
    M = len(grid[0])
    
    # 2. Empezamos desde la esquina inferior derecha (destino)
    i = N - 1
    j = M - 1
    path = [(i, j)]
    
    # 3. Retrocedemos hasta llegar al origen (0, 0)
    while i > 0 or j > 0:
        if i == 0:
            # En el borde superior, solo pudimos venir de la izquierda
            j -= 1
        elif j == 0:
            # En el borde izquierdo, solo pudimos venir de arriba
            i -= 1
        else:
            # En el interior, retrocedemos hacia el vecino con menor coste acumulado en dp
            if dp[i - 1][j] < dp[i][j - 1]:
                i -= 1
            else:
                j -= 1
        
        path.append((i, j))
        
    # 4. Invertimos la lista para que vaya desde (0, 0) hasta (N - 1, M - 1)
    path.reverse()
    
    return min_cost, path

# =============================================================================
# III. Simulación de Movimiento y Difusión mediante Caminata Aleatoria (Random Walk)
# =============================================================================

# III.A El comportamiento de una partícula individual

def simulate_single_walk(steps: int) -> tuple[float, float, float]:
    """
    Simula la trayectoria bidimensional de una sola partícula que parte desde el origen (0.0, 0.0) 
    y da un número determinado de pasos en direcciones aleatorias uniformes [0, 2*pi).

    :param steps: Número de pasos a simular.
    :return: Tupla con la posición final (x, y) y la distancia euclidiana final al origen.
    """
    pass

# III.B El enfoque de Monte Carlo y la Ley de Difusión

def monte_carlo_diffusion_simulation(num_particles: int, num_steps: int) -> float:
    """
    Aplica el método de Monte Carlo simulando un conjunto masivo de partículas independientes 
    para calcular la Distancia Cuadrática Media (R^2).

    :param num_particles: Número total de partículas independientes a simular.
    :param num_steps: Número de pasos por caminata.
    :return: Valor de la Distancia Cuadrática Media (R^2).
    """
    pass

# III.C Confinamiento y barreras absorbentes

def simulate_particle_with_barrier(steps: int, max_radius: float) -> bool:
    """
    Simula la caminata paso a paso de una partícula evaluando en cada paso si supera 
    un radio límite (barrera absorbente).

    :param steps: Número máximo de pasos.
    :param max_radius: Radio límite de la barrera desde el origen.
    :return: True si la partícula cruza la barrera en algún paso, False en caso contrario.
    """
    # 1. Posición inicial en el origen (0.0, 0.0)
    x = 0.0
    y = 0.0
    
    # 2. Simulamos paso a paso hasta el límite de pasos permitido
    for _ in range(steps):
        # Elegimos un ángulo aleatorio en [0, 2*pi) como pide el enunciado
        theta = random.uniform(0, 2 * math.pi)
        
        # Actualizamos las coordenadas (paso de longitud 1)
        x += math.cos(theta)
        y += math.sin(theta)
        
        # Calculamos la distancia euclidiana actual al origen (0, 0)
        distance = math.sqrt(x**2 + y**2)
        
        # Comprobamos si en este paso ha cruzado la barrera
        if distance > max_radius:
            return True
            
    # 3. Si completa todos los pasos sin superar max_radius, no ha escapado
    return False

def calculate_escape_probability(num_particles: int, num_steps: int, max_radius: float) -> float:
    """
    Estima la probabilidad de escape de un conjunto de partículas en presencia 
    de una barrera absorbente mediante el método de Monte Carlo.

    :param num_particles: Número de partículas a simular.
    :param num_steps: Número máximo de pasos por partícula.
    :param max_radius: Radio de la barrera absorbente.
    :return: Probabilidad de escape expresada en el intervalo [0.0, 1.0].
    """
    # Protección por si se llamara con 0 partículas (evita división por cero)
    if num_particles <= 0:
        return 0.0
        
    # 1. Inicializamos un contador a 0 para ir sumando las partículas que logren salir
    escaped_count = 0
    
    # 2. Repetimos el experimento independiente para cada partícula
    for _ in range(num_particles):
        # Llamamos a la función del apartado III.C.1
        if simulate_particle_with_barrier(num_steps, max_radius):
            escaped_count += 1
            
    # 3. Calculamos la proporción (probabilidad entre 0.0 y 1.0)
    return escaped_count / num_particles