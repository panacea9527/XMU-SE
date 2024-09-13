import numpy as np
import random


# 适应度函数：评估给定路径的总距离
def evaluate(path, distance_matrix):
    return sum(distance_matrix[path[i], path[(i + 1) % len(path)]] for i in range(len(path)))


# 初始化粒子群：生成初始解
def init_population(num_particles, num_cities):
    return [np.random.permutation(num_cities) for _ in range(num_particles)]


# 找到最佳解
def find_best_solution(population, distance_matrix):
    best_path = min(population, key=lambda path: evaluate(path, distance_matrix))
    return best_path, evaluate(best_path, distance_matrix)


# 更新路径：通过随机交换两个城市来模拟“速度”更新
def update_path(path, distance_matrix, best_global_path):
    new_path = path.copy()
    # 随机交换两个位置
    i, j = random.sample(range(len(path)), 2)
    new_path[i], new_path[j] = new_path[j], new_path[i]
    # 如果新路径更好，则接受它
    if evaluate(new_path, distance_matrix) < evaluate(path, distance_matrix):
        return new_path
    return path

# PSO算法主体
def pso_tsp(distance_matrix, num_particles=50, max_iterations=1000):
    num_cities = len(distance_matrix)
    population = init_population(num_particles, num_cities)
    best_global_path, best_global_distance = find_best_solution(population, distance_matrix)

    for _ in range(max_iterations):
        for i in range(num_particles):
            population[i] = update_path(population[i], distance_matrix, best_global_path)
            current_distance = evaluate(population[i], distance_matrix)
            if current_distance < best_global_distance:
                best_global_path, best_global_distance = population[i], current_distance

    return best_global_path, best_global_distance


distance_matrix = np.array([
    [0, 3, 0, 8, 9],
    [3, 0, 3, 10, 5],
    [0, 3, 0, 4, 3],
    [8, 10, 4, 0, 20],
    [9, 5, 3, 20, 0]
], dtype=float)
distance_matrix[distance_matrix == 0] = np.inf  # 不连通的路径设置为无穷大

# 执行PSO
num_particles = 50
max_iterations = 1000
best_path, best_distance = pso_tsp(distance_matrix, num_particles, max_iterations)
print(f"Best Path: {best_path}\nBest Distance: {best_distance}")
