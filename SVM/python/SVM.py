import pandas as pd
from sklearn.metrics import ConfusionMatrixDisplay, confusion_matrix
from sklearn.model_selection import train_test_split
import graphviz
import random
import numpy as np
from matplotlib import pyplot as plt
from sklearn.pipeline import Pipeline
from sklearn.preprocessing import StandardScaler
from sklearn.svm import LinearSVC
from sklearn.svm import SVC


# Extract dataset
dataset='../../DATASETS/features_train.csv'
crop_df = pd.read_csv(dataset, header=0)
Y_train = crop_df.Style.values
features = crop_df.columns.values[:-1]
crop_df = crop_df.drop('Style', axis=1)
X_train = crop_df.values

dataset='../../DATASETS/features_test.csv'
crop_df = pd.read_csv(dataset, header=0)
Y_test = crop_df.Style.values
features1 = crop_df.columns.values[:-1]
crop_df = crop_df.drop('Style', axis=1)
X_test = crop_df.values

classes = np.unique(Y_train)

print(features, classes)
print(classes.shape)

classes1 = np.unique(Y_test)

print(features1, classes1)
print(classes1.shape)

# TRAIN/TEST SPLIT
# X_train, X_test, Y_train, Y_test = train_test_split(X, Y, test_size=0.33, random_state=42)
print("Splitting test, train", X_train.shape, X_test.shape)

# Sklearn SVM
print("Training !")
clf = Pipeline ((
    ("scaler",StandardScaler()),("Linear_svc", LinearSVC()),
))
clf.fit(X_train, Y_train)

#SVC(kernel="linear" ,class_weight='balanced',C=1,gamma=0.001,decision_function_shape='ovr')
# PREDICTIONS

Y_pred = clf.predict(X_test)

print("print X_train.shape =",X_train.shape)

print(Y_pred[:20])
print('w = ',(clf["Linear_svc"].coef_).shape)
print('b = ',(clf["Linear_svc"].coef_).shape)

print("score :", clf.score(X_test, Y_test))

print('matrix x = ',(clf["scaler"].scale_).shape)

a=clf["Linear_svc"].coef_
b=clf["Linear_svc"].intercept_
mu=clf['scaler'].mean_
sigma=clf['scaler'].var_
print(sigma[:10])

print("mu_shape={},sigma_shape={}".format(mu.shape,sigma.shape))


def cppgenerator_coef():

    global a
    cpp1=open('coef_def.h','w')
    cpp1.write('double w[{}][{}];'.format(len(a),len(a[0])))
    cpp1.write("\n")
    cpp1.write('double b[{}];'.format(len(a)))
    cpp1.write("\n")
    cpp1.write('double mu[{}];'.format(len(a[0])))
    cpp1.write("\n")
    cpp1.write('double var[{}];'.format(len(a[0])))
    cpp1.write("\n")
    cpp1.write('void init(){')
    cpp1.write("\n")

    for i in range (len(a)):
        for j in range(len(a[0])):
            cpp1.write("w[{}][{}] ={};".format(i,j,a[i,j]))
            cpp1.write("\n")

    for i in range (len(a)):

        cpp1.write("b[{}] ={};".format(i,b[i]))
        cpp1.write("\n")

    for i in range (len(a[0])):

        cpp1.write("mu[{}] ={};".format(i,mu[i]))
        cpp1.write("\n")
    for i in range (len(a[0])):

        cpp1.write("var[{}] ={};".format(i,sigma[i]))
        cpp1.write("\n")
    cpp1.write("}")
    cpp1.close()
#vu chez le prof, C=1 gamma=0.0001 class_weight='baleanced', ovo

cppgenerator_coef()


ConfusionMatrixDisplay.from_predictions(Y_test, Y_pred, display_labels=classes)
plt.title("SVM pred")
plt.show()
