import numpy as np
import random

distance_matrix = np.array([
    [0, 3, 0, 8, 9],
    [3, 0, 3, 10, 5],
    [0, 3, 0, 4, 3],
    [8, 10, 4, 0, 20],
    [9, 5, 3, 20, 0]
], dtype=float) 
distance_matrix[distance_matrix == 0] = np.inf  # 不连通的路径设置为无穷大

# 生成初始种群
def create_population(size, num_cities):
    return [random.sample(range(num_cities), num_cities) for _ in range(size)]

# 计算路径长度，路径越短越好
def fitness(path):
    distance = 0
    for i in range(len(path)):
        if distance_matrix[path[i], path[(i + 1) % len(path)]] == np.inf:
            return np.inf  # 如果路径不连通，返回无穷大作为代价
        distance += distance_matrix[path[i], path[(i + 1) % len(path)]]
    return distance

# 选择函数：轮盘赌选择
def select(population, fitnesses):
    valid_fitnesses = fitnesses[np.isfinite(fitnesses)]
    if len(valid_fitnesses) == 0:
        return None 

    probabilities = 1 / valid_fitnesses
    probabilities /= probabilities.sum()  

    valid_indices = np.arange(len(population))[np.isfinite(fitnesses)]
    selected_index = np.random.choice(valid_indices, p=probabilities)

    return population[selected_index]


# 顺序交叉
def crossover(parent1, parent2):
    if parent1 is None or parent2 is None:
        return None
    size = len(parent1)
    idx1, idx2 = sorted(random.sample(range(size), 2))
    offspring = [None] * size
    offspring[idx1:idx2] = parent1[idx1:idx2]
    pointer = idx2
    for gene in parent2:
        if gene not in offspring:
            if pointer >= size:
                pointer = 0
            offspring[pointer] = gene
            pointer += 1
    return offspring

# 随机交换两个城市
def mutate(path, mutation_rate=0.01):
    if path is None:
        return None
    if random.random() < mutation_rate:
        idx1, idx2 = random.sample(range(len(path)), 2)
        path[idx1], path[idx2] = path[idx2], path[idx1]
    return path

# 主函数
def genetic_algorithm(distance_matrix, population_size=100, generations=500, mutation_rate=0.01):
    num_cities = len(distance_matrix)
    population = create_population(population_size, num_cities)
    for _ in range(generations):
        fitnesses = np.array([fitness(p) for p in population])
        new_population = []
        for _ in range(population_size):
            parent1 = select(population, fitnesses)
            parent2 = select(population, fitnesses)
            if parent1 is None or parent2 is None:
                print("No valid parents, terminating algorithm.")
                return None, np.inf

            offspring = crossover(parent1, parent2)
            offspring = mutate(offspring, mutation_rate)
            if offspring is not None:
                new_population.append(offspring)
        population = new_population
    best_path = min(population, key=fitness)
    return best_path, fitness(best_path)

best_path, best_distance = genetic_algorithm(distance_matrix)
print(f"Best Path: {best_path}\nDistance: {best_distance if best_distance != np.inf else 'Not connected'}")
