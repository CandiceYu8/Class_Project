# Standard library
import struct   # read from binary file and sperate into object, used for .idx3-ubyte data

# Third-party library
import numpy as np


def load_data():
    """ Used when data is in the form xx.idx3-ubyte. 
    Return training_data, validation_data and test_data in the form of tuple.
    
    The first entry is a numpy ndarray with 50,000/10,000/10,000
    entries respectively. And each entry is a numpy ndarray with
    784 values, representing the 28 * 28 = 784 pixels in a single
    MNIST image.

    The second entry is also a numpy ndarray with 50,000/10,000/10,000
    entries respectively. But each entry is the label of the corresponding
    image in the first entry. The label is a number between 0 and 9.
    """
    test_x = np.asarray(LoadImage("./MNIST_data/t10k-images.idx3-ubyte"), dtype="float32")
    test_y = np.asarray(LoadLabel("./MNIST_data/t10k-labels.idx1-ubyte"), dtype="int64")
    training_x = np.asarray(LoadImage("./MNIST_data/train-images.idx3-ubyte"), dtype="float32")
    training_y = np.asarray(LoadLabel("./MNIST_data/train-labels.idx1-ubyte"), dtype="int64")
    training_data = (training_x[:50000], training_y[:50000])
    validation_data = (training_x[50000:], training_y[50000:])
    test_data = (test_x, test_y)
    return (training_data, validation_data, test_data)




def load_data_wrapper():
    """ Modify the input data to use it for neural network more conveniently.
    Also return training data, validation data and test data 
    in the form of tuple.

    Each data is in the form of (x, y) where x is a 784*1 numpy.ndarray and 
    y is a 10*1 numpy.ndarray with 1 in the right position representing
    the label and 0 in the other 9 positions.
    """
    tr_d, va_d, te_d = load_data()
    training_x = np.asarray([np.reshape(x, (784, 1)) for x in tr_d[0]]).reshape(50000, 784)
    training_y = np.asarray([vactorize_y(y) for y in tr_d[1]]).reshape(50000, 10)
    training_data = (training_x, training_y)
    validation_x = np.asarray([np.reshape(x, (784, 1)) for x in va_d[0]]).reshape(10000, 784)
    validation_y = np.asarray([vactorize_y(y) for y in va_d[1]]).reshape(10000, 10)
    validation_data = (validation_x, validation_y)
    test_x = np.asarray([np.reshape(x, (784, 1)) for x in te_d[0]]).reshape(10000, 784)
    test_y = np.asarray([vactorize_y(y) for y in te_d[1]]).reshape(10000, 10)
    test_data = (test_x, test_y)
    return (training_data, validation_data, test_data)


def vactorize_y(j):
    """ Return a 10-dimentional vector with 1 in the jth position
    and 0 in the other position """
    vec = np.zeros((10, 1))
    vec[j] = 1
    return vec



def LoadImage(filename):
    """ Used for load_data, load image and return ndarray. """
    binaryfile = open(filename, 'rb')
    buffers = binaryfile.read()
    info = struct.unpack_from('>iiii', buffers)  # fmt: four 32 bit integer: magic number, number of images, rows, columns
    offset = struct.calcsize('>iiii')  # locate to 0016 where pixels start
                                       # fmt: '>': big-endian
    imgNum = info[1]        # 60000\10000
    rowNum = info[2]        # 28
    columnNum = info[3]     # 28
    
    pixels = imgNum * rowNum * columnNum
    imgFmt = '>' + str(pixels) + 'B'   # unsigned byte
    imgs = struct.unpack_from(imgFmt, buffers, offset)
    binaryfile.close()
    
    return np.reshape(imgs, [imgNum, rowNum*columnNum])   # 60000\10000 * 784



def LoadLabel(filename):
    """ Used for load_data, load label and return ndarray. """
    binaryfile = open(filename, 'rb')
    buffers = binaryfile.read()
    info = struct.unpack_from('>ii', buffers)  # fmt: two 32 bit integer: magic number, number of labels
    offset = struct.calcsize('>ii')  # locate to 0008 where label start
                                       # fmt: '>': big-endian
    labelNum = info[1]        # 60000\10000
    
    labelFmt = '>' + str(labelNum) + 'B'   # unsigned byte
    labels = struct.unpack_from(labelFmt, buffers, offset)
    binaryfile.close()
    
    return np.reshape(labels, [labelNum])   # 60000\10000 * 1


