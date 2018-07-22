import pandas as pd 
from bs4 import BeautifulSoup
import re
import nltk
from nltk.tokenize import sent_tokenize
from nltk.tokenize import word_tokenize  
from nltk.corpus import stopwords  

def Retrieve_data(file_path):
    """ return (X, Y) where X is the review list of the data in the form
    [[sentence1_word1, ..., sentence1_wordn], ..., [sentencem_word1, ..., sentencem_wordn]]
    for one review. And Y is the sentiment list [1,0,0,1,...,1] 
    where 1 represents positive and 0 represents negative.
    """
    data = pd.read_csv(file_path, sep="\t", header=0, error_bad_lines=False)   # 导入数据，原数据用Tab分割，第一行为其列标题 
    data_X = data["review"]
    data_Y = data["sentiment"]
    
    subHtml = data_X.apply(Sub_html)
    lowerCase = subHtml.apply(Lower_case)
    sentenceList = lowerCase.apply(Sentence_token)
    senSub = sentenceList.apply(Sub_number_punc)
    wordList = senSub.apply(Word_token)
    wordStop = wordList.apply(Sen_stop)
    #wordStem = wordStop.apply(Sen_stem)
    #words = wordStem.apply(Sen_lemm)
    return (wordStop, data_Y)
    # return wordStop
    
    


def Sub_html(text):
    """ return text without <br/> and other html tags """
    return BeautifulSoup(text, "lxml").get_text()


def Lower_case(text):
    """ return lower case text """
    return text.lower()


def Sentence_token(paragraph):
    """ return [sentence1, ..., sentencen] """
    return sent_tokenize(paragraph)  


def Sub_number_punc(sentenceList):
    """ return sentenceList without numbers and punctuations"""
    return [re.sub("[^a-zA-Z]", " ", i) for i in sentenceList]    # the problem is it separates http and couldn't delete it


def Word_token(sentenceList):
    """ return sentenceList each is a list like [word1, ..., wordn] """
    return [word_tokenize(sentence) for sentence in sentenceList] 


def Sen_stop(sentenceList):
    """ return sentenceList like [[],[],[]] each small list is a word_list """
    return [Sub_stopwords(word_list) for word_list in sentenceList]


def Sub_stopwords(word_list):
    """ return word list without stopwords like he, we... and short words whose len<=2"""
    stop_words = set(stopwords.words('english'))
    len_re_short = [w for w in word_list if len(w)>= 2]
    return [w for w in len_re_short if not w in stop_words]


def Sen_stem(sentenceList):
    """ return sentenceList like [[],[],[]] each small list is a word_list """
    return [Stem(word_list) for word_list in sentenceList]


def Stem(word_list):
    """ return word list changed going to go, something like that """
    stemmer = nltk.stem.PorterStemmer()
    return [stemmer.stem(t) for t in word_list]


def Sen_lemm(sentenceList):
    """ return sentenceList like [[],[],[]] each small list is a word_list """
    return [Lemm(word_list) for word_list in sentenceList]


def Lemm(word_list):
    """ return word list changed women to woman, something like that """
    lemmatizer = nltk.stem.WordNetLemmatizer()
    return [lemmatizer.lemmatize(t) for t in word_list]



""" start from here """
train_data = "E:\\school\\2-2\\AI\\Project2\\data\\labeledTrainData.tsv"
train_data_X, train_data_Y = Retrieve_data(train_data)
save_path_y = "E:\\school\\2-2\\AI\\Project2\\data\\Modified_LTD_y.pkl"
save_path_x = "E:\\school\\2-2\\AI\\Project2\\data\\Modified_LTD_x.pkl"
train_data_Y.to_pickle(save_path_y)
train_data_X.to_pickle(save_path_x)

# train_data_un = "E:\\school\\2-2\\AI\\Project2\\data\\unlabeledTrainData.tsv"
# train_data_un_x = Retrieve_data(train_data_un)
# save_path = "E:\\school\\2-2\\AI\\Project2\\data\\Modified_ULTD_x.pkl"
# train_data_un_x.to_pickle(save_path)

# test_data = "E:\\school\\2-2\\AI\\Project2\\data\\testData.tsv"
# test_data_x = Retrieve_data(test_data)
# save_path = "E:\\school\\2-2\\AI\\Project2\\data\\Modified_TD_x.pkl"
# test_data_x.to_pickle(save_path)