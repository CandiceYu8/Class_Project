# -*- coding: utf-8 -*-
import tensorflow as tf
from tensorflow.examples.tutorials.mnist import input_data


def weight_var(shape):
  initial = tf.truncated_normal(shape, stddev=0.1)      # void all zeroes casuing gradient vanishing problem
  return tf.Variable(initial)

def bias_var(shape):
  initial = tf.truncated_normal(shape, stddev=0.1)           # set average percent for first time
  return tf.Variable(initial)

def conv2d(x, W):
      return tf.nn.conv2d(x, W, strides=[1, 1, 1, 1], padding='SAME')       # stride=1, with zero padding

def pooling(x):
  return tf.nn.max_pool(x, ksize=[1, 2, 2, 1],
                        strides=[1, 2, 2, 1], padding='SAME')       # 2*2 pooling


# load data
mnist = input_data.read_data_sets('MNIST_data', one_hot=True)
sess = tf.InteractiveSession()
x = tf.placeholder("float", shape=[None, 784])
y = tf.placeholder("float", shape=[None, 10])
sess.run(tf.global_variables_initializer())


# the convolution and pooling layer 
W_conv = weight_var([5, 5, 1, 32])    # patch=5*5  input_channel=1   output_channel=32
b_conv = bias_var([32])
x_image = tf.reshape(x, [-1,28,28,1])   # -1: caluculate according to other three parameters
R_conv = tf.nn.relu(conv2d(x_image, W_conv) + b_conv)
P_conv = pooling(R_conv)         # picture size: 14*14


# the full connection layer
W_fc = weight_var([14 * 14 * 32, 512])     
b_fc = bias_var([512])
F_fc = tf.reshape(P_conv, [-1, 14*14*32])           # reshape 
R_fc = tf.nn.relu(tf.matmul(F_fc, W_fc) + b_fc)     # relu
    

# the output layer
W_out = weight_var([512, 10])
b_out = bias_var([10])
y_out = tf.nn.softmax(tf.matmul(R_fc, W_out) + b_out)
    

# test accuracy
cross_entropy = -tf.reduce_sum(y * tf.log(y_out))
train_step = tf.train.AdamOptimizer(1e-4).minimize(cross_entropy)
prediction = tf.equal(tf.argmax(y_out, 1), tf.argmax(y, 1))
accuracy = tf.reduce_mean(tf.cast(prediction, "float"))
sess.run(tf.initialize_all_variables())             # initialize

for i in range(2000):
  batch = mnist.train.next_batch(50)
  if i%100 == 0:              # print accuracy + weight + bias every 100 steps 
    train_accuracy = accuracy.eval(feed_dict={
        x:batch[0], y: batch[1]})
    print ("step %d, training accuracy %g"%(i, train_accuracy))
    print ("bias:")
    print(sess.run(b_out))
    print ("weight:")
    print(sess.run(W_out))
    print()
  train_step.run(feed_dict={x: batch[0], y: batch[1]})
     
print ("test accuracy %g"%accuracy.eval(feed_dict={       # print final test accuracy
    x: mnist.test.images, y: mnist.test.labels}))
    
    
    
    