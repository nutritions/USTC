import random
from sklearn.model_selection import train_test_split
from sklearn.preprocessing import LabelEncoder
import numpy as np
import pandas as pd


# 定义精确度评估指标
def calculate_accuracy(y_true, y_pred):
    return np.mean(y_true == y_pred)


# 定义决策树节点类
class TreeNode:
    def __init__(self, is_leaf=False, class_label=None, attribute=None, threshold=None, left=None, right=None):
        self.is_leaf = is_leaf
        self.class_label = class_label
        self.attribute = attribute
        self.threshold = threshold
        self.left = left
        self.right = right


# 定义决策树分类器类
class MyDecisionTreeClassifier:
    def __init__(self):
        self.root = None

    def train(self, X, y):
        self.root = self.trBuild(X, y)

    def trBuild(self, X, y):
        if len(set(y)) == 1:
            return TreeNode(is_leaf=True, class_label=y[0])

        B_attr, B_thr = self._find_best_split(X, y)
        if not B_attr:
            return TreeNode(is_leaf=True, class_label=np.bincount(y).argmax())

        ld = X[:, B_attr] < B_thr
        rd = X[:, B_attr] >= B_thr
        lt = self.trBuild(X[ld], y[ld])
        rt = self.trBuild(X[rd], y[rd])

        return TreeNode(attribute=B_attr, threshold=B_thr, left=lt, right=rt)

    def _find_best_split(self, X, y):
        B_gain = -1
        B_attr = None
        B_thr = None
        entropy_D = self.cal_epy(y)

        # 遍历所有可能的属性和阈值，进行扰动
        for attr, thr in self._generate_split_candidates(X, y):
            # 引入随机扰动到阈值
            perturbation = random.uniform(-0.1, 0.1)  # 调整范围以适应需求
            thr += perturbation

            ld = X[:, attr] < thr
            rd = X[:, attr] >= thr

            if not np.sum(ld) or not np.sum(rd):
                continue

            entropy_Dv = np.sum(ld) / len(y) * self.cal_epy(y[ld]) + \
                        np.sum(rd) / len(y) * self.cal_epy(y[rd])

            gain = entropy_D - entropy_Dv

            if gain > B_gain:
                B_gain = gain
                B_attr = attr
                B_thr = thr

        return B_attr, B_thr

    def _generate_split_candidates(self, X, y):
        candidates = []
        for attr in range(X.shape[1]):
            values = np.unique(X[:, attr])
            for thr in values:
                candidates.append((attr, thr))
        return candidates

    def cal_epy(self, y):
        _, counts = np.unique(y, return_counts=True)
        probabilities = counts / len(y)
        return -np.sum(probabilities * np.log2(probabilities + 1e-8))

    def predict(self, X):
        return np.array([self.spPre(x, self.root) for x in X])

    def spPre(self, x, node):
        if node.is_leaf:
            return node.class_label
        else:
            attr = node.attribute
            thr = node.threshold
            if x[attr] < thr:
                return self.spPre(x, node.left)
            else:
                return self.spPre(x, node.right)


def load_dataset(datapath='./data/ObesityDataSet_raw_and_data_sinthetic.csv'):
    df = pd.read_csv(datapath)
    discrete_features = ['Gender', 'CALC', 'FAVC', 'FCVC', 'NCP', 'SCC', 'SMOKE', 'CH2O',
                         'family_history_with_overweight', 'FAF', 'TUE', 'CAEC', 'MTRANS']

    X = df.drop(columns=['NObeyesdad'])  # 假设 'NObeyesdad' 是目标列
    y = df['NObeyesdad']

    # 编码离散特征
    label_encoder = LabelEncoder()
    for feature in discrete_features:
        X[feature] = label_encoder.fit_transform(X[feature])
    y = label_encoder.fit_transform(y)

    X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.2, random_state=42)

    return X_train.to_numpy(), X_test.to_numpy(), y_train, y_test


if __name__ == "__main__":
    X_train, X_test, y_train, y_test = load_dataset('./data/ObesityDataSet_raw_and_data_sinthetic.csv')

    # 训练决策树模型
    model = MyDecisionTreeClassifier()
    model.train(X_train, y_train)

    # 预测并评估精确度
    y_pred = model.predict(X_test)
    print(f'Accuracy: {calculate_accuracy(y_test, y_pred)}')
