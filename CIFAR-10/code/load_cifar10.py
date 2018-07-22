import pickle
import numpy as np
import matplotlib.pyplot as plt
    
def load_cifar10():
    """ load data from directory
        return train_images, train_labels, test_images, test_labels
    """
    # load train data
    directory = 'E:\\school\\2-2\\ac_eng\\cifar\\cifar-10-batches-py'
    images, labels = [], []
    for filename in ['%s\\data_batch_%d' % (directory, j) for j in range(1, 6)]:
        with open(filename, 'rb') as fo:
            cifar10 = pickle.load(fo, encoding='bytes')
        for i in range(len(cifar10[b"labels"])):         #按标签依次读取数据
            image = np.reshape(cifar10[b"data"][i], (3, 32, 32))
            image = np.transpose(image, (1, 2, 0))
            image = image.astype(float)
            images.append(image)
        labels += cifar10[b"labels"]
    images = np.array(images, dtype='float')
    labels = np.array(labels, dtype='int')   
    train_images, train_labels = images, labels

    # load test data
    images, labels = [], []
    for filename in ['%s\\test_batch' % (directory)]:
        with open(filename, 'rb') as fo:
            cifar10 = pickle.load(fo, encoding='bytes')
        for i in range(len(cifar10[b"labels"])):
            image = np.reshape(cifar10[b"data"][i], (3, 32, 32))
            image = np.transpose(image, (1, 2, 0))
            image = image.astype(float)
            images.append(image)
        labels += cifar10[b"labels"]
    images = np.array(images, dtype='float')
    labels = np.array(labels, dtype='int')
    test_images, test_labels = images, labels
    return train_images, train_labels, test_images, test_labels


def wrapper_data():
    """ return train_data: (train_images, train_labels) 45000*3072, 45000*10, 
    validation_data: (validation_images, validation_labels) 5000*3072, 5000*1, 
    test_data: (test_images, test_labels) 10000*3072, 10000*1.
    for images 3072 = 3*32*32 standing for R G B respectively.
    """
    train_images, train_labels, test_images, test_labels = load_cifar10()
    train_x = train_images[:45000]
    train_y = train_labels[:45000]
    validation_x = train_images[45000:]
    validation_y = train_labels[45000:]
    training_x = [np.reshape(x, (3072, 1)) for x in train_x]
    training_y = [vactorize_y(y) for y in train_y]
    training_data = zip(training_x, training_y)
    validation_x = [np.reshape(x, (3072, 1)) for x in validation_x]
    validation_data = zip(validation_x, validation_y)
    test_x = [np.reshape(x, (3072, 1)) for x in test_images]
    test_data = zip(test_x, test_labels)
    return (list(training_data), list(validation_data), list(test_data))



def vactorize_y(j):
    """ Return a 10-dimentional vector with 1 in the jth position
    and 0 in the other position """
    vec = np.zeros((10, 1))
    vec[j] = 1
    return vec


def ShowPic(pic_num, pic_img, pic_label, subplot_size, save_path=None):
    """ pic_num is the number of pictures to show
        pic_img is a numpy array with shape(numbers, 32, 32, 3)
        pic_label is the index in names
        subplot_size is the way to show these pictures: [row, col]
    """
    meta_file = 'E:\\school\\2-2\\ac_eng\\cifar\\cifar-10-batches-py\\batches.meta'
    with open(meta_file, 'rb') as fo:
        dict = pickle.load(fo, encoding='bytes')
    names = [x.decode('utf-8') for x in dict[b'label_names']]

    for i in range(1, pic_num+1, 1):
        img = pic_img[i]
        plt.subplot(subplot_size[0], subplot_size[1], i)
        plt.imshow(img)
        plt.axis('off')
        plt.title(names[pic_label[i]])
    plt.show()
    if save_path:
        plt.savefig(save_path)


def plot_model_details(model_details):
    """ plot Keras model details """
    plt.figure(figsize=(15, 5))
     # plot model accuracy
    plt.subplot(1, 2, 1)
    plt.title('Model Accuracy')
    plt.ylabel('Accuracy')
    plt.xlabel('Epoch')
    plt.plot(range(1, len(model_details.history['acc'])+1), model_details.history['acc'])
    plt.plot(range(1, len(model_details.history['val_acc'])+1), model_details.history['val_acc'])
    plt.xticks(np.arange(1, len(model_details.history['acc'])+len(model_details.history['acc'])/10, len(model_details.history['acc'])/10))
    plt.legend(['train', 'validation'], loc='best')
    
    # plot model loss
    plt.subplot(1, 2, 2)
    plt.title('Model Loss')
    plt.ylabel('Loss')
    plt.xlabel('Epoch')
    plt.plot(range(1, len(model_details.history['loss'])+1), model_details.history['loss'])
    plt.plot(range(1, len(model_details.history['val_loss'])+1), model_details.history['val_loss'])
    plt.xticks(np.arange(1, len(model_details.history['loss'])+len(model_details.history['loss'])/10, len(model_details.history['loss'])/10))
    plt.legend(['train', 'validation'], loc='best')




# path = 'F:\\school\\data_science\\2-2\\ac_eng\\final\\cifar-10-batches-py'
# train_images, train_labels, test_images, test_labels = load_cifar10(path)
# numpy.save(path+'\\train_images', train_images)
# numpy.save(path+'\\train_labels', train_labels)
# numpy.save(path+'\\test_images', test_images)
# numpy.save(path+'\\test_labels', test_labels)
