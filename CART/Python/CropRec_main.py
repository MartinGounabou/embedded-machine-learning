import pandas as pd
from matplotlib import pyplot as plt
from sklearn import tree
from sklearn.metrics import ConfusionMatrixDisplay, confusion_matrix
from sklearn.model_selection import train_test_split
import graphviz
from CART import *


# Extract dataset
dataset='../../DATASETS/croprec.csv'
crop_df = pd.read_csv(dataset, header=0)
Y = crop_df.label.values
features = crop_df.columns.values[:-1]
crop_df = crop_df.drop('label', axis=1)
X = crop_df.values
classes = np.unique(Y)

print(features, classes)
print(classes.shape)


# TRAIN/TEST SPLIT
X_train, X_test, Y_train, Y_test = train_test_split(X, Y, test_size=0.33, random_state=42)
print("Splitting test, train", X_train.shape, X_test.shape)

# My CART_TREES TREE
print("Training !")
myclassifier = CartTree(max_depth=12);
myclassifier.fit(X_train, Y_train)
print(myclassifier)
myclassifier.ccpgenerator()

# SKLEARN CART_TREES TREE
clf = tree.DecisionTreeClassifier(random_state=None, max_depth=12)
clf = clf.fit(X_train, Y_train)

dot_data = tree.export_graphviz(clf,
                                out_file=None,
                                feature_names=features,
                                class_names=classes,
                                filled=True,
                                rounded=True,
                                special_characters=True)
graph = graphviz.Source(dot_data)
graph.render("Crop recommandations")

# PREDICTIONS
Y_pred = myclassifier.predict(X_test)
print(confusion_matrix(Y_test, Y_pred, labels=classes))
ConfusionMatrixDisplay.from_predictions(Y_test, Y_pred, display_labels=classes)
plt.title("My predictions")
plt.show()

Y_pred = clf.predict(X_test)
ConfusionMatrixDisplay.from_predictions(Y_test, Y_pred, display_labels=classes)
plt.title("SKLEARN")
plt.show()

