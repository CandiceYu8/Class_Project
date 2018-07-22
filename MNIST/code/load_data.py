# -*- coding: utf-8 -*-
import numpy as np
import matplotlib.pyplot as plt
import struct

def LoadImage(filename):
    binaryfile = open(filename, 'rb')
    buffers = binaryfile.read()
    info = struct.unpack_from('>iiii', buffers)  # fmt: four 32 bit integer: magic number, number of images, rows, columns
    offset = struct.calcsize('>iiii')  # locate to 0016 where pixels start
                                       # fmt: '>': big-endian
    imgNum = info[1]        # 60000\10000
    rowNum = info[2]        # 28
    columnNum = info[3]     # 28
    print("imgNum: " + str(imgNum) + "   rowNum: " +  str(rowNum) + "   columnNum: " + str(columnNum))
    
    pixels = imgNum * rowNum * columnNum
    imgFmt = '>' + str(pixels) + 'B'   # unsigned byte
    imgs = struct.unpack_from(imgFmt, buffers, offset)
    binaryfile.close()
    
    return np.reshape(imgs, [imgNum, rowNum*columnNum])   # 60000\10000 * 784



def one_hot(i):
    a = np.zeros(10)
    a[i] = 1
    return a

 
    
def LoadLabel(filename):
    binaryfile = open(filename, 'rb')
    buffers = binaryfile.read()
    info = struct.unpack_from('>ii', buffers)  # fmt: two 32 bit integer: magic number, number of labels
    offset = struct.calcsize('>ii')  # locate to 0008 where label start
                                       # fmt: '>': big-endian
    labelNum = info[1]        # 60000\10000
    print("labelNum: " + str(labelNum))
    
    labelFmt = '>' + str(labelNum) + 'B'   # unsigned byte
    labels = struct.unpack_from(labelFmt, buffers, offset)
    binaryfile.close()
    
    labels =  np.reshape(labels, [labelNum])   # 60000\10000 * 1
    return [one_hot(i) for i in labels]     # one-hot for *10



trainImg = "E:\\school\\2-2\\AI\\Project1\\MNIST_data\\train-images.idx3-ubyte"
trainLabel = "E:\\school\\2-2\\AI\\Project1\\MNIST_data\\train-labels.idx1-ubyte"

train_data = np.asarray(LoadImage(trainImg), dtype="float32")
train_label = np.asarray(LoadLabel(trainLabel), dtype="float32")
print(train_data.shape)
print(train_label.shape)
print(train_data.dtype)
print(train_label.dtype)

plt.figure()
for i in range(10):
   image = train_data[i,:]
   plt.subplot(2, 5, i+1)
   plt.imshow(image.reshape([28, 28]), cmap="gray")
   plt.axis('off')
   print(train_label[i])

