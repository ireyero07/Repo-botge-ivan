"""
Práctica 2: Algoritmos codiciosos.
Algoritmia y Estructuras de Datos Avanzadas.
Curso 2026-27.
"""

from typing import List, Tuple, Dict, Optional
import random

# =============================================================================
# I. Problema del cambio de monedas
# =============================================================================

# def greedy_change(coins: List[int], amount: int) -> Tuple[List[int], int]:
#     """
#     Estrategia codiciosa para el problema del cambio de monedas.
#     Selecciona en cada paso la moneda de mayor valor que no supere la cantidad restante.
#     """
#     coins = sorted (coins, reverse=True)

#     used = []

#     for coin in coins:
#         while amount >= coin:
#             amount -=  coin
#             used.append (coin)
#     return used, amount

# def optimal_change(coins: List[int], amount: int) -> Optional[List[int]]:
#     """
#     Solución óptima mediante programación dinámica para el problema del cambio de monedas.
#     Determina el menor número de monedas necesario para obtener la cantidad objetivo.
#     """
#     if amount == 0:
#         return []

#     coins = sorted (coins, reverse=True)
#     l = len(List+1)
#     a = amount +1
    
#     m = [[0 for _ in range(a)]for _ in range(l)]

#     for i in range(1, l):
#         m[0][i] = float('inf')

#     for i in range(1,l):
        
#         for j in range(1, a):
#             if (a < i):
#                 m[i][j] = m[i-1] [j]
#             elif (a <= i):
#                 m[i][j] = min(m[i-1][j], 1 + m[i][j-])
            


        




    
#     pass

# def compare_change(coins: List[int], max_amount: int) -> Dict[str, List[int]]:
#     """
#     Evalúa todas las cantidades entre 1 y max_amount, clasifica cada cantidad en
#     'optimal', 'suboptimal', 'greedy_failed' o 'impossible'.
#     """

#     k = {
#     'optimal': [],
#     'suboptimal': [],
#     'greedy_failed': [],
#     'impossible': []
#     }

#     if max_amount == 0:
#         return []

#     for i in range (1, max_amount + 1):
#         g, amount = greedy_change(List,i)
#         o = optimal_change(List, i)
#         if amount == 0:
#             if len(g) == len(o):
#                 k['optimal'].append[i]
#             else: 
#                 k['suboptimal'].append[i]       
#         elif o != None:
#             k['greedy_failed'].append[i]
#         else: 
#             k['impossible'].append[i]

#     return k


# =============================================================================
# II. Selección de actividades
# =============================================================================

def activity_selection(activities: List[Tuple[str, int, int]]) -> List[Tuple[str, int, int]]:
    """
    Selecciona el máximo número posible de actividades compatibles.
    Ordena por tiempo de finalización ascendente, y en caso de empate por inicio e identificador.
    """

    l = []

    


    pass

# def generate_activities(n: int, seed: int = 42) -> List[Tuple[str, int, int]]:
#     """
#     Genera n actividades aleatorias reproducibles.
#     start en [0, 10000], duration en [1, 100], end = start + duration.
#     """

#     for i in range(seed):
#         a
#     pass

# =============================================================================
# III. Planificación de tareas con fechas límite
# =============================================================================

def job_scheduling(jobs: List[Tuple[str, int, int]]) -> Tuple[List[Optional[Tuple[str, int, int]]], int]:
    """
    Planificación de tareas de duración unitaria con fecha límite (deadline).
    Devuelve la secuencia de tareas asignadas (con None para intervalos vacíos) y el beneficio total.
    """
    if len(jobs) == 0:
        return [], 0
    
    jobs_sorted = sorted(jobs, key=lambda job: (-job[1], job[2], job[0]))

    max_deadline = max(job[2] for job in jobs)
    schedule = [None] * max_deadline

    total_profit = 0

    for job in jobs_sorted:
        identifier, profit, deadline = job

        for i in range(deadline -1, -1, -1):
            if schedule[i] is None:
                schedule[i] = job
                total_profit += profit
                break

    return schedule, total_profit


def generate_jobs(n: int, seed: int = 42) -> List[Tuple[str, int, int]]:
    """
    Genera n tareas aleatorias con fecha límite reproducibles.
    profit en [1, 1000], deadline en [1, max(1, n // 10)].
    """

    random.seed(seed)
    jobs = []
    max_deadline = max(1, n // 10)
    
    for i in range(n):
        identifier = f"J{i}"
        profit = random.randint(1, 1000)
        deadline = random.randint(1, max_deadline)
        jobs.append((identifier, profit, deadline))
        
    return jobs