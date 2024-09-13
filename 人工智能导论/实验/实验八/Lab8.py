import numpy as np
import pandas as pd
from collections import Counter
from sklearn.preprocessing import LabelEncoder, StandardScaler
from sklearn.model_selection import train_test_split, cross_val_score
from sklearn.base import BaseEstimator, ClassifierMixin

def euclidean_distance(x1, x2):
    """计算两个向量之间的欧几里得距离"""
    return np.linalg.norm(x1 - x2)

class KNN(BaseEstimator, ClassifierMixin):
    def __init__(self, k=3):
        self.k = k

    def fit(self, X, y):
        """存储训练数据"""
        self.X_train = X
        self.y_train = y
        return self

    def predict(self, X):
        """对给定数据集X进行预测，返回预测标签数组"""
        y_pred = [self._predict(x) for x in X]
        return np.array(y_pred)

    def _predict(self, x):
        """对单个数据点x进行预测，返回预测的标签"""
        # 计算与所有训练数据点的距离
        distances = [euclidean_distance(x, x_train) for x_train in self.X_train]
        # 获取最近的k个邻居的索引
        k_indices = np.argsort(distances)[:self.k]
        # 根据最近的k个邻居的标签进行投票
        k_nearest_labels = [self.y_train[i] for i in k_indices]
        # 返回最多的标签
        most_common = Counter(k_nearest_labels).most_common(1)
        return most_common[0][0]

def load_dataset(train_path, test_path):
    """加载训练集和测试集文件，返回处理后的训练和测试数据及标签"""
    train_df = pd.read_csv(train_path, header=None)
    test_df = pd.read_csv(test_path, header=None)
    full_df = pd.concat([train_df, test_df], axis=0)
    le = LabelEncoder()
    full_df[4] = le.fit_transform(full_df[4])
    scaler = StandardScaler()
    X = scaler.fit_transform(full_df.iloc[:, :-1])
    Y = full_df.iloc[:, -1].values
    X_train, X_test, Y_train, Y_test = train_test_split(X, Y, test_size=0.2, random_state=1)
    return X_train, X_test, Y_train, Y_test

def find_best_k(X, y):
    """通过交叉验证找到最佳的K值"""
    k_values = range(1, 31)
    cross_val_scores = []
    for k in k_values:
        clf = KNN(k=k)
        scores = cross_val_score(clf, X, y, cv=5)
        cross_val_scores.append(scores.mean())
    best_k = k_values[np.argmax(cross_val_scores)]
    return best_k, cross_val_scores

if __name__ == "__main__":
    X_train, X_test, Y_train, Y_test = load_dataset('Iris_train.txt', 'Iris_test.txt')
    best_k, scores = find_best_k(X_train, Y_train)
    print(f"Best K: {best_k}")
    # 使用最佳K值训练全数据集并测试
    clf = KNN(k=best_k)
    clf.fit(X_train, Y_train)
    predictions = clf.predict(X_test)
    accuracy = np.mean(predictions == Y_test)
    print(f"Accuracy with best K: {accuracy}")
