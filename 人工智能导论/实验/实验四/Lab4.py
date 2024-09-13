import numpy as np

# 定义目标函数
def target_function(x):
    return 11 * np.sin(6 * x) + 7 * np.cos(5 * x)

# 模拟退火算法的实现
def simulated_annealing(func, x0, bounds, initial_temp, final_temp, cooling_rate, markov_chain_length_func):
    current_x = x0  # 初始解
    current_value = func(current_x)  # 初始解的函数值
    best_x = current_x  # 记录找到的最佳解
    best_value = current_value  # 最佳解的函数值
    temp = initial_temp  # 初始温度

    # 当当前温度高于终止温度时继续迭代
    while temp > final_temp:
        markov_chain_length = markov_chain_length_func(temp)  # 根据当前温度计算Markov链长度
        for _ in range(markov_chain_length):
            perturbation = np.random.uniform(-1, 1) * (bounds[1] - bounds[0]) * (temp / initial_temp)
            candidate_x = current_x + perturbation  # 生成新的候选解
            candidate_x = np.clip(candidate_x, bounds[0], bounds[1])  # 确保候选解在边界内
            candidate_value = func(candidate_x)  # 计算候选解的函数值

            # 如果候选解更优或按照一定概率接受更差的解
            if candidate_value < current_value or np.random.rand() < np.exp((current_value - candidate_value) / temp):
                current_x = candidate_x
                current_value = candidate_value
                if candidate_value < best_value:
                    best_x = candidate_x
                    best_value = candidate_value

        temp *= cooling_rate  # 更新温度

    return best_x, best_value

# 温度衰减函数定义：指数衰减
def exponential_decay(temp):
    return int(100 + 5000 * (temp / initial_temp))

# 参数设置
x0 = np.random.uniform(0, 2 * np.pi)  # 初始解
bounds = [0, 2 * np.pi]  # x的边界
initial_temp = 100.0  # 初始温度
final_temp = 0.01  # 终止温度
cooling_rate = 0.95  # 温度衰减率
markov_chain_length_func = exponential_decay  # Markov链长度函数

# 执行模拟退火算法
best_x, best_value = simulated_annealing(target_function, x0, bounds, initial_temp, final_temp, cooling_rate, markov_chain_length_func)
print(f"在 x = {best_x} 处找到最小值, f(x) = {best_value}")
