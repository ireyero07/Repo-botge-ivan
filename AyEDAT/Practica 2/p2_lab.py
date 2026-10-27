import p2
import time

systems = [
    [200, 100, 50, 20, 10, 5, 2, 1],
    [10, 5, 2, 1],
    [25, 10, 4, 1],
    [4, 3, 1]
]

amounts = range(1, 501)
total_amounts = len(amounts)
summary_results = []

print("Ejecutando análisis experimental para cantidades de 1 a 500...\n")

for coins in systems:
    optimal_count = 0
    suboptimal_count = 0
    greedy_failed_count = 0
    impossible_count = 0
    
    # Medición de tiempos de ejecución globales para el rango [1, 500]
    start_t_greedy = time.perf_counter()
    for amt in amounts:
        _ = p2.greedy_change(coins, amt)
    time_greedy = time.perf_counter() - start_t_greedy
    
    start_t_optimal = time.perf_counter()
    for amt in amounts:
        _ = p2.optimal_change(coins, amt)
    time_optimal = time.perf_counter() - start_t_optimal
    
    # Clasificación detallada
    for amt in amounts:
        g_res = p2.greedy_change(coins, amt)
        o_res = p2.optimal_change(coins, amt)
        
        o_success = (o_res is not None)
        g_success = (g_res is not None)
        
        if not o_success:
            impossible_count += 1
        elif not g_success:
            greedy_failed_count += 1
        else:
            if len(g_res) == len(o_res):
                optimal_count += 1
            else:
                suboptimal_count += 1
                
    # Cálculo de porcentajes
    summary_results.append({
        "Sistema": str(coins),
        "Optimal": optimal_count,
        "Opt_%": (optimal_count / total_amounts) * 100,
        "Suboptimal": suboptimal_count,
        "Sub__%": (suboptimal_count / total_amounts) * 100,
        "Failed": greedy_failed_count,
        "Fail_%": (greedy_failed_count / total_amounts) * 100,
        "Impossible": impossible_count,
        "Imp_%": (impossible_count / total_amounts) * 100,
        "T_Greedy(s)": round(time_greedy, 5),
        "T_Optimal(s)": round(time_optimal, 5)
    })

# --- 3. MOSTRAR RESULTADOS EN TABLA ---

print(f"{'Sistema de Monedas':<35} | {'Opt':<8} | {'Subopt':<8} | {'Fail':<8} | {'Impos':<8} | {'T.Greedy':<10} | {'T.Optimo':<10}")
print("-" * 100)

for res in summary_results:
    sistema = res["Sistema"]
    opt_str = f"{res['Optimal']} ({res['Opt_%']:.1f}%)"
    sub_str = f"{res['Suboptimal']} ({res['Sub__%']:.1f}%)"
    fail_str = f"{res['Failed']} ({res['Fail_%']:.1f}%)"
    imp_str = f"{res['Impossible']} ({res['Imp_%']:.1f}%)"
    t_g = f"{res['T_Greedy(s)']}"
    t_o = f"{res['T_Optimal(s)']}"
    
    print(f"{sistema:<35} | {opt_str:<10} | {sub_str:<10} | {fail_str:<10} | {imp_str:<10} | {t_g:<10} | {t_o:<10}")