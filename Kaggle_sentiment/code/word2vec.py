#### Library used
import pandas as pd
import numpy as np
import warnings
warnings.filterwarnings(action='ignore', category=UserWarning, module='gensim')
import gensim
from gensim.models import Word2Vec

def Train_model(train_times=1, size_=100, window_=5, min_count_=5):
    """ Input: train_times is the time you want to retrain your model, default=1.
        size_ is the vector size of your model, default=100.
        window_ is the context range of each word.
        min_count_ is the least appearence time that a word will be added to the model.    
        Output: A trained model by gensim.models.Word2Vec.
    """
    # load data
    train_x = pd.read_pickle('E:\\school\\2-2\\AI\\Project2\\data\\Modified_LTD_x.pkl')
    train_un_x = pd.read_pickle('E:\\school\\2-2\\AI\\Project2\\data\\Modified_ULTD_x.pkl')
    test_x = pd.read_pickle('E:\\school\\2-2\\AI\\Project2\\data\\Modified_TD_x.pkl')
    sentences = []
    for review in train_x:
        for sentence in review:
            sentences.append(sentence)
    for review in train_un_x:
        for sentence in review:
            sentences.append(sentence)
    for review in test_x:
        for sentence in review:
            sentences.append(sentence)
    # train model
    model = Word2Vec(sentences, size=size_, window=window_, min_count=min_count_, workers=4)
    while (train_times>1):
        model.train(sentences, total_examples=model.corpus_count, epochs=model.epochs)
        train_times = train_times-1
    # return
    return model


def Avg_vector(model, data, model_size, save_path):
    """ Input: model is the model trained before using Word2Vec.
               data is the review contents.
               model_size is the size of each word vector in model.
               save_path is the path to store the average vector of each review. 
    """
    result = []
    index2word_set = set(model.wv.index2word)
    for review in data:
        cnt = 0
        vec = np.zeros((1, model_size))
        for sentence in review:
            for word in sentence:
                if word in index2word_set:
                    vec = vec + model.wv.__getitem__(word)
                    cnt = cnt+1
        vec = vec/cnt
        result.extend(vec)
    result = np.array(result)
    np.save(save_path, result)


def Save_y_npy(data_y, path_y):
    result = np.array(data_y)
    np.save(path_y, result)



## start form here
# model = Train_model(train_times=2, size_=400, window_=5, min_count_=30)
# model.save('E:\\school\\2-2\\AI\\Project2\\data\\model_400_30')

# model = Word2Vec.load('E:\\school\\2-2\\AI\\Project2\\data\\model_400_30')
# data = pd.read_pickle('E:\\school\\2-2\\AI\\Project2\\data\\Modified_TD_x.pkl')
# save_path = 'E:\\school\\2-2\\AI\\Project2\\data\\test_x_400_30.npy'
# Avg_vector(model, data, 400, save_path)

# data = pd.read_pickle('E:\\school\\2-2\\AI\\Project2\\data\\Modified_LTD_y.pkl')
# save_path = 'E:\\school\\2-2\\AI\\Project2\\data\\train_y.npy'
# Save_y_npy(data, save_path)
