import pandas as pd
import numpy as np
from keras import regularizers, Sequential
from keras.layers import Dense, Dropout
from sklearn.linear_model import LogisticRegression as LR
import sklearn.svm as svm
from sklearn.model_selection import GridSearchCV
from sklearn.linear_model.stochastic_gradient import SGDClassifier as sgd



def Only_Dense(parameters, train_data_x, train_data_y, test_data_x, test_y_path=None):
    """ Input train data and test_x， store result in test_y_path.
        Only Dense, so input including a list parameters
        [[out_put dim, input_dim, act, dropout], [out_put dim, act, dropout]].
    """
    model = Sequential()
    model.add(Dense(parameters[0][0],input_dim=parameters[0][1], activation=parameters[0][2]))
    model.add(Dropout(parameters[0][3]))

    for i in range(1, len(parameters)-1):
        model.add(Dense(parameters[i][0], activation=parameters[i][1]))
        model.add(Dropout(parameters[i][2]))

    model.add(Dense(parameters[-1][0], activation=parameters[-1][1]))

    model.compile(loss='binary_crossentropy',
              optimizer='adam',
              metrics=['accuracy'])

    model.fit(train_data_x, train_data_y,
          epochs=10, shuffle= True,
          batch_size=128, validation_split=0.2)

    print (model.evaluate(train_data_x, train_data_y, batch_size=128))

    
    if test_y_path:
        test_data_y = model.predict(test_data_x)
        Store_result(test_y_path, test_data_y)


def Logist(train_data_x, train_data_y, test_data_x, test_y_path=None):
    # choose parameters
    grid_values = {'C':[1, 15, 30]}
    model_LR = GridSearchCV(LR(), grid_values, scoring='roc_auc', cv=20)
    model_LR.fit(train_data_x,train_data_y)
    print (model_LR.best_params_)
    print (model_LR.grid_scores_)

    # store result
    if test_y_path:
        test_data_y = model_LR.predict(test_data_x)
        Store_result(test_y_path, test_data_y)


def SVM(train_data_x, train_data_y, test_data_x, test_y_path=None):
    # choose parameters
    grid_values = {'C':[0.3, 1, 3]}
    model_SVM = GridSearchCV(svm.SVC(), grid_values, scoring='roc_auc', cv=10)
    model_SVM.fit(train_data_x,train_data_y)
    print (model_SVM.best_params_)
    print (model_SVM.grid_scores_)

    # store result
    if test_y_path:
        test_data_y = model_SVM.predict(test_data_x)
        Store_result(test_y_path, test_data_y)


def SGD(train_data_x, train_data_y, test_data_x, test_y_path=None):
    # choose parameters
    grid_values = {'alpha': [0.0005, 0.001, 0.005, 0.01]}
    model_SGD = GridSearchCV(sgd(loss = 'modified_huber', max_iter=1000, tol=1e-4, shuffle = True), 
                                grid_values, scoring='roc_auc', cv=10)
    model_SGD.fit(train_data_x,train_data_y)
    print (model_SGD.best_params_)
    print (model_SGD.grid_scores_)

    # store result
    if test_y_path:
        test_data_y = model_SGD.predict(test_data_x)
        Store_result(test_y_path, test_data_y)


def Store_result(test_y_path, test_data_y):
    test_id = pd.read_csv('E:\\school\\2-2\\AI\\Project2\\data\\testData.tsv', sep="\t", header=0)
    test_id['sentiment'] = test_data_y
    test_id.to_csv(test_y_path, columns=['id', 'sentiment'], index=0)







### start from here
train_data_x = np.load("E:\\school\\2-2\\AI\\Project2\\data\\train_x_400_30.npy")
train_data_y = np.load("E:\\school\\2-2\\AI\\Project2\\data\\train_y.npy")
test_data_x = np.load("E:\\school\\2-2\\AI\\Project2\\data\\test_x_400_30.npy")
# test_y_path = 'E:\\school\\2-2\\AI\\Project2\\data\\w2vKeras_400_30.csv'
# parameters = [[800, 400, 'relu', 0.5], [400,'relu', 0.5], [1, 'sigmoid']]
# Only_Dense(parameters, train_data_x, train_data_y, test_data_x, test_y_path)

# test_y_path = 'E:\\school\\2-2\\AI\\Project2\\data\\w2vLR.csv'
# Logist(train_data_x, train_data_y, test_data_x, test_y_path)

# test_y_path = 'E:\\school\\2-2\\AI\\Project2\\data\\w2vSGD.csv'
# SGD(train_data_x, train_data_y, test_data_x, test_y_path)

# test_y_path = 'E:\\school\\2-2\\AI\\Project2\\data\\w2vSVM.csv'
# SVM(train_data_x, train_data_y, test_data_x, test_y_path)