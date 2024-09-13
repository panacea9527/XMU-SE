import pandas as pd
import numpy as np
from collections import Counter

# 加载数据函数
def load_data(filepath):
    return pd.read_csv(filepath, header=None, delim_whitespace=True)

# 计算熵函数
def entropy(y):
    """计算给定数据集的熵"""
    counter = Counter(y)
    probs = [count / len(y) for count in counter.values()]
    return -sum(p * np.log2(p) for p in probs)

# 寻找最佳分割点函数
def find_best_split(X, y):
    """寻找最佳分割点，返回最佳分割索引和分割值"""
    best_entropy = float('inf')
    best_split = None
    best_index = None
    for index in range(X.shape[1]):
        values = sorted(set(X[:, index]))
        split_points = [(values[i] + values[i + 1]) / 2 for i in range(len(values) - 1)]
        for split in split_points:
            left_mask = X[:, index] < split
            right_mask = ~left_mask
            left_entropy = entropy(y[left_mask])
            right_entropy = entropy(y[right_mask])
            split_entropy = (left_entropy * sum(left_mask) + right_entropy * sum(right_mask)) / len(y)
            if split_entropy < best_entropy:
                best_entropy = split_entropy
                best_split = split
                best_index = index
    return best_index, best_split

# 构建决策树函数
def build_tree(X, y, depth=1, max_depth=5, min_samples_split=2):
    """构建决策树，使用递归方式。可以设置最大深度和最小样本分割数进行预剪枝"""
    # 预剪枝条件：达到最大深度、样本太少、纯度已足够
    if depth == max_depth or len(set(y)) == 1 or len(y) < min_samples_split:
        return Counter(y).most_common(1)[0][0]

    best_index, best_split = find_best_split(X, y)
    if best_index is None:
        return Counter(y).most_common(1)[0][0]

    left_mask = X[:, best_index] < best_split
    right_mask = ~left_mask
    if sum(left_mask) < min_samples_split or sum(right_mask) < min_samples_split:
        return Counter(y).most_common(1)[0][0]  # 如果子集小于min_samples_split，则停止分裂

    left_child = build_tree(X[left_mask], y[left_mask], depth + 1, max_depth, min_samples_split)
    right_child = build_tree(X[right_mask], y[right_mask], depth + 1, max_depth, min_samples_split)

    return {"index": best_index, "split": best_split, "left": left_child, "right": right_child}

def classify(instance, tree):
    """对单个实例进行分类，根据决策树递归查找分类结果"""
    if not isinstance(tree, dict):
        return tree
    if instance[tree['index']] < tree['split']:
        return classify(instance, tree['left'])
    else:
        return classify(instance, tree['right'])


def print_tree(node, depth=0, feature_names=None):
    """递归打印决策树"""
    indent = "    " * depth  # 缩进显示
    if not isinstance(node, dict):
        print(indent + f"预测结果: {node}")
    else:
        if feature_names:
            feature_name = feature_names[node['index']]
        else:
            feature_name = f"特征 {node['index']}"

        # 打印当前节点的分割条件
        print(indent + f"{feature_name} < {node['split']:.3f}?")
        # 递归打印左子树
        print(indent + f"是 -> (左子树)")
        print_tree(node['left'], depth + 1, feature_names)
        # 递归打印右子树
        print(indent + f"否 -> (右子树)")
        print_tree(node['right'], depth + 1, feature_names)

# 主程序
if __name__ == "__main__":
    # 加载训练数据和测试数据
    train_data_path = './traindata.txt'
    test_data_path = './testdata.txt'
    train_data = pd.read_csv(train_data_path, header=None, delim_whitespace=True)
    test_data = pd.read_csv(test_data_path, header=None, delim_whitespace=True)

    X_train = train_data.iloc[:, :-1].values
    y_train = train_data.iloc[:, -1].values
    X_test = test_data.iloc[:, :-1].values
    y_test = test_data.iloc[:, -1].values

    # 构建决策树，设置最小分裂样本数为2，最大深度为3
    tree = build_tree(X_train, y_train, max_depth=3, min_samples_split=2)

    predictions = [classify(instance, tree) for instance in X_test]

    accuracy = sum(pred == real for pred, real in zip(predictions, y_test)) / len(y_test)
    print(f"分类准确率: {accuracy * 100:.2f}%")

    # 打印决策树
    print("决策树结构：")
    print_tree(tree)