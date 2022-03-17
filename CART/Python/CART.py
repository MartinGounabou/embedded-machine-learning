import random
import numpy as np


def impurity(target):
    acc = 0.0
    unique, frequency = np.unique(target, return_counts=True)
    size2 = float(target.shape[0])**2
    for i, c in enumerate(unique):
        acc += frequency[i]**2 / size2
    return 1.0 - acc


class CartTree:
    def __init__(self, max_depth=4):
        self.depth = 0  # start as root
        self.left = None
        self.right = None
        self.feature = None
        self.label = None
        self.purity_gain = None
        self.threshold = None
        self.n_features = None  # to prune
        self.max_depth = max_depth


    def fit(self, features, target):
        self.rec_tree_generation(features, target)
        self.prune(self.max_depth)

    def rec_tree_generation(self, features, target):
        self.n_features = features.shape[0]
        values, counts = np.unique(target, return_counts=True)
        # A unique class -> found !
        if len(counts) == 1:
            self.label = target[0]
            return
        # Find the largest class
        max_index = np.argmax(counts)
        max_class = values[max_index]
        self.label = max_class

        best_gain = 0.0
        best_feature = None
        best_threshold = None
        impurity_node = impurity(target)

        # Select best feature to split along max_class
        for feature_index in range(features.shape[1]):
            feature_scale = np.unique(features[:, feature_index])
            # print("Feature scale : ", feature_scale)
            thresholds = (feature_scale[:-1] + feature_scale[1:]) / 2.0
            # Thresholds are set to values between each features values
            # print("Thresholds : ", thresholds)

            for threshold in thresholds:
                left_target = target[features[:, feature_index] <= threshold]
                left_impurity = impurity(left_target)
                n_left = float(left_target.shape[0]) / self.n_features

                right_target = target[features[:, feature_index] > threshold]
                right_impurity = impurity(right_target)
                n_right = float(right_target.shape[0]) / self.n_features

                # the larger purity gain, the better classification.
                # (right and left) should be purer, so purity_gain > 0
                purity_gain = impurity_node - (n_left * left_impurity + n_right * right_impurity)
                if purity_gain > best_gain:
                    best_gain = purity_gain
                    best_feature = feature_index
                    best_threshold = threshold

        self.feature = best_feature
        self.purity_gain = best_gain
        self.threshold = best_threshold
        print("Best Feature to split : ", self.feature, " Gain : ", self.purity_gain, " Threshold : ", self.threshold)

        # Let the tree grow to the left and the right !
        left_features = features[features[:, self.feature] <= self.threshold]  # select features
        left_target = target[features[:, self.feature] <= self.threshold]  # select associated targets
        self.left = CartTree()
        self.left.depth = self.depth + 1
        self.left.rec_tree_generation(left_features, left_target)

        right_features = features[features[:, self.feature] > self.threshold]
        right_target = target[features[:, self.feature] > self.threshold]
        self.right = CartTree()
        self.right.depth = self.depth + 1
        self.right.rec_tree_generation(right_features, right_target)

    def prune(self, max_depth):
        if self.feature is None:
            return

        self.left.prune(max_depth)
        self.right.prune(max_depth)

        if self.depth >= max_depth:
            self.left = None
            self.right = None
            self.feature = None

    def predict(self, xfeatures):
        return np.array([self._predict(xf) for xf in xfeatures])

    def _predict(self, xfeature):
        if self.feature != None:
            if xfeature[self.feature] <= self.threshold:
                return self.left._predict(xfeature)
            else:
                return self.right._predict(xfeature)
        else:
            return self.label

    def ccpgenerator(self):
        cpp=open('mycart.cpp','w')
        cpp.write('string cart_predict(vector<double>feature)')
        cpp.write("\n{")
        cpp.write("\n")
        cpp.write('string classical="classical";')
        cpp.write("\n")
        cpp.write('string reggae= "reggae";')
        cpp.write("\n")
        cpp.write('string reggae= "rock";')
        cpp.write("\n")
        cpp.write('string blues="blues";')
        cpp.write("\n")
        cpp.write('string disco="disco";')
        cpp.write("\n")
        cpp.write('string jazz="jazz";')
        cpp.write("\n")
        cpp.write('string hiphop="hiphop";')
        cpp.write("\n")
        cpp.write('string metal="metal";')
        cpp.write("\n")
        cpp.write('string country="country";')
        cpp.write("\n")
        cpp.write('string pop="pop";')
        cpp.write("\n")    
        cpp.write(self.ccpgenerate_condition())
        cpp.write("\n"+"}")
        cpp.close()


    def ccpgenerate_condition(self):
        table='   '

        if self.feature == None:
            return table*(self.depth)+'   return {};'.format(self.label)
        else :
            return table*self.depth+ "   if (feature[{}]<={})".format(self.feature,self.threshold)+"\n"+table*self.depth+"   {\n"+self.left.ccpgenerate_condition()+"\n"+table*self.depth+"   }\n"+table*self.depth+"   else{\n"+self.right.ccpgenerate_condition()+"\n"+table*self.depth+"   }"




#TODO GENERATE C++ CODE TO TAKE THE DECISION !
#TODO TO GENERATE, OVERLOAD __str__ in this class and use a prefix walk of the tree.
