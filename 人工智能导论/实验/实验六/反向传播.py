# 定义训练集和测试集的行号范围
train_lines = list(range(1, 26)) + list(range(51, 76)) + list(range(101, 126))

# 打开原始数据集文件，训练集文件和测试集文件
with open('Iris.txt', 'r') as original_file:
    with open('Iris_train.txt', 'w') as train_file:
        with open('Iris_test.txt', 'w') as test_file:
            # 遍历原始数据集的每一行
            for i, line in enumerate(original_file, start=1):
                # 判断当前行号是否属于训练集的范围
                if i in train_lines:
                    # 如果是，写入训练集文件
                    train_file.write(line)
                else:
                    # 如果不是，写入测试集文件
                    test_file.write(line)

# import numpy as np
#
#
# # 定义Sigmoid激活函数及其导数
# def sigmoid(x):
#     return 1 / (1 + np.exp(-x))
#
#
# def sigmoid_derivative(x):
#     return x * (1 - x)
#
#
# # 初始化网络参数
# def initialize_parameters(input_size, hidden_size, output_size):
#     np.random.seed(0)  # 确保每次初始化都能得到相同的结果
#     parameters = {
#         "W1": np.random.randn(input_size, hidden_size),
#         "b1": np.zeros((1, hidden_size)),
#         "W2": np.random.randn(hidden_size, output_size),
#         "b2": np.zeros((1, output_size))
#     }
#     return parameters
#
#
# # 前向传播
# def forward_propagation(X, parameters):
#     W1 = parameters["W1"]
#     b1 = parameters["b1"]
#     W2 = parameters["W2"]
#     b2 = parameters["b2"]
#
#     Z1 = np.dot(X, W1) + b1
#     A1 = sigmoid(Z1)
#     Z2 = np.dot(A1, W2) + b2
#     A2 = sigmoid(Z2)
#
#     cache = {"Z1": Z1, "A1": A1, "Z2": Z2, "A2": A2}
#     return A2, cache
#
#
# # 计算损失
# def compute_loss(Y, A2):
#     m = Y.shape[0]
#     loss = -(1 / m) * np.sum(Y * np.log(A2) + (1 - Y) * np.log(1 - A2))
#     return loss
#
#
# # 反向传播
# def backward_propagation(parameters, cache, X, Y):
#     m = X.shape[0]
#
#     W2 = parameters["W2"]
#     A1 = cache["A1"]
#     A2 = cache["A2"]
#
#     dZ2 = A2 - Y
#     dW2 = (1 / m) * np.dot(A1.T, dZ2)
#     db2 = (1 / m) * np.sum(dZ2, axis=0, keepdims=True)
#     dZ1 = np.dot(dZ2, W2.T) * sigmoid_derivative(A1)
#     dW1 = (1 / m) * np.dot(X.T, dZ1)
#     db1 = (1 / m) * np.sum(dZ1, axis=0, keepdims=True)
#
#     grads = {"dW1": dW1, "db1": db1, "dW2": dW2, "db2": db2}
#     return grads
#
#
# # 更新参数
# def update_parameters(parameters, grads, learning_rate=1.2):
#     parameters["W1"] -= learning_rate * grads["dW1"]
#     parameters["b1"] -= learning_rate * grads["db1"]
#     parameters["W2"] -= learning_rate * grads["dW2"]
#     parameters["b2"] -= learning_rate * grads["db2"]
#
#     return parameters
#
#
# # 预测
# def predict(parameters, X):
#     A2, cache = forward_propagation(X, parameters)
#     predictions = np.argmax(A2, axis=1)
#     return predictions
#
#
# # 构建并训练模型
# def model(X_train, Y_train, X_test, Y_test, n_hidden=10, n_epochs=1000, print_cost=False):
#     np.random.seed(1)  # 确保随机数生成是可复现的
#     n_x = X_train.shape[1]
#     n_y = Y_train.shape[1]
#
#     parameters = initialize_parameters(n_x, n_hidden, n_y)
#
#     for i in range(n_epochs):
#         A2, cache = forward_propagation(X_train, parameters)
#         cost = compute_loss(Y_train, A2)
#         grads = backward_propagation(parameters, cache, X_train, Y_train)
#         parameters = update_parameters(parameters, grads)
#
#         if print_cost and i % 1000 == 0:
#             print(f"Cost after epoch {i}: {cost}")
#
#     predictions_train = predict(parameters, X_train)
#     predictions_test = predict(parameters, X_test)
#
#     accuracy_train = np.mean(predictions_train == np.argmax(Y_train, axis=1)) * 100
#     accuracy_test = np.mean(predictions_test == np.argmax(Y_test, axis=1)) * 100
#
#     if print_cost:
#         print(f"Training accuracy: {accuracy_train}%")
#         print(f"Test accuracy: {accuracy_test}%")
#
#     return accuracy_test

import numpy as np
import pandas as pd
from sklearn.preprocessing import LabelEncoder
from sklearn.model_selection import train_test_split
from sklearn.metrics import accuracy_score

def sigmoid(x):
    return 1 / (1 + np.exp(-x))

def sigmoid_derivative(x):
    return x * (1 - x)

def initialize_parameters(input_size, hidden_size, output_size):
    parameters = {
        "W1": np.random.randn(input_size, hidden_size) * 0.01,
        "b1": np.zeros((1, hidden_size)),
        "W2": np.random.randn(hidden_size, output_size) * 0.01,
        "b2": np.zeros((1, output_size))
    }
    return parameters

def forward_propagation(X, parameters):
    W1 = parameters["W1"]
    b1 = parameters["b1"]
    W2 = parameters["W2"]
    b2 = parameters["b2"]
    Z1 = np.dot(X, W1) + b1
    A1 = sigmoid(Z1)
    Z2 = np.dot(A1, W2) + b2
    A2 = sigmoid(Z2)
    cache = {"A1": A1, "A2": A2}
    return A2, cache

def compute_loss(Y, A2):
    m = Y.shape[0]
    logprobs = np.multiply(np.log(A2), Y) + np.multiply((1 - Y), np.log(1 - A2))
    loss = - np.sum(logprobs) / m
    return loss

def backward_propagation(parameters, cache, X, Y):
    m = X.shape[0]
    W2 = parameters["W2"]
    A1 = cache["A1"]
    A2 = cache["A2"]
    dZ2 = A2 - Y
    dW2 = (1 / m) * np.dot(A1.T, dZ2)
    db2 = (1 / m) * np.sum(dZ2, axis=0, keepdims=True)
    dZ1 = np.dot(dZ2, W2.T) * sigmoid_derivative(A1)
    dW1 = (1 / m) * np.dot(X.T, dZ1)
    db1 = (1 / m) * np.sum(dZ1, axis=0, keepdims=True)
    grads = {"dW1": dW1, "db1": db1, "dW2": dW2, "db2": db2}
    return grads

def update_parameters(parameters, grads, learning_rate=0.01):
    parameters["W1"] = parameters["W1"] - learning_rate * grads["dW1"]
    parameters["b1"] = parameters["b1"] - learning_rate * grads["db1"]
    parameters["W2"] = parameters["W2"] - learning_rate * grads["dW2"]
    parameters["b2"] = parameters["b2"] - learning_rate * grads["db2"]
    return parameters

def convert_to_one_hot(Y, C):
    Y = np.eye(C)[Y.reshape(-1)].T
    return Y

def load_dataset(train_path, test_path):
    train_df = pd.read_csv(train_path, header=None)
    test_df = pd.read_csv(test_path, header=None)
    full_df = pd.concat([train_df, test_df], axis=0)
    le = LabelEncoder()
    full_df[4] = le.fit_transform(full_df[4])
    X = full_df.iloc[:, :-1].values
    Y = full_df.iloc[:, -1].values
    Y = convert_to_one_hot(Y, 3).T
    X_train, X_test, Y_train, Y_test = train_test_split(X, Y, test_size=test_df.shape[0] / full_df.shape[0], random_state=1)
    return X_train, X_test, Y_train,Y_test



# 训练模型
def train_model(X_train, Y_train, X_test, Y_test, hidden_size=10, learning_rate=1.2, n_epochs=10000):
    # 初始化网络参数，注意这里不再设置随机种子以获取不同的结果
    input_size = X_train.shape[1]
    output_size = Y_train.shape[1]
    parameters = initialize_parameters(input_size, hidden_size, output_size)

    for epoch in range(n_epochs):
        # 前向传播
        A2, cache = forward_propagation(X_train, parameters)

        # 计算损失
        cost = compute_loss(Y_train, A2)

        # 如果想每个epoch都打印损失，可以去掉下面这行的条件判断
        if epoch % 1000 == 0:
            print(f"Epoch {epoch}/{n_epochs} - Loss: {cost} - Learning Rate: {learning_rate}")

        # 反向传播
        grads = backward_propagation(parameters, cache, X_train, Y_train)

        # 更新参数
        parameters = update_parameters(parameters, grads, learning_rate)

    # 在训练结束后计算测试集上的准确率
    predictions = np.argmax(forward_propagation(X_test, parameters)[0], axis=1)
    true_labels = np.argmax(Y_test, axis=1)
    accuracy = accuracy_score(true_labels, predictions)

    return accuracy, cost  # 返回准确率和最后的损失值


# 主函数
import numpy as np

def main(train_path, test_path):
    X_train, X_test, Y_train, Y_test = load_dataset(train_path, test_path)
    accuracies = []
    losses = []

    for i in range(10):  # 独立训练模型十次
        accuracy, loss = train_model(X_train, Y_train, X_test, Y_test, hidden_size=10, learning_rate=0.03, n_epochs=10000)
        print(f"Training {i+1}: Accuracy = {accuracy}, Loss = {loss}")
        accuracies.append(accuracy)
        losses.append(loss)

    mean_accuracy = np.mean(accuracies)
    std_accuracy = np.std(accuracies)
    print("\nFinal Results across all trainings:")
    print(f"Mean Accuracy: {mean_accuracy}")
    print(f"Standard Deviation of Accuracy: {std_accuracy}")
    print(f"Mean Loss: {np.mean(losses)}")
    print(f"Standard Deviation of Loss: {np.std(losses)}")

# Replace 'Iris_train.txt' and 'Iris_test.txt' with your actual file paths
main('Iris_train.txt', 'Iris_test.txt')


