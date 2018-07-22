# -*- coding: utf-8 -*-
import tensorflow as tf
from tensorflow.examples.tutorials.mnist import input_data


def weight_variable(shape):
  initial = tf.truncated_normal(shape, stddev=0.1)      # void all zeroes casuing gradient vanishing problem
  return tf.Variable(initial)

def bias_variable(shape):
  initial = tf.constant(0.1, shape=shape)           # set average percent for first time
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
sess.run(tf.initialize_all_variables())


# the first convolutional layer 
W_conv1 = weight_variable([5, 5, 1, 32])    # patch=5*5  input_channel=1   output_channel=32
b_conv1 = bias_variable([32])
x_image = tf.reshape(x, [-1,28,28,1])   # -1: caluculate according to other three parameters
h_conv1 = tf.nn.relu(conv2d(x_image, W_conv1) + b_conv1)
h_pool1 = pooling(h_conv1)         # picture size: 14*14


# the second convolutionsl layer 
W_conv2 = weight_variable([5, 5, 32, 64])   # first_layer channel=32
b_conv2 = bias_variable([64])
h_conv2 = tf.nn.relu(conv2d(h_pool1, W_conv2) + b_conv2)
h_pool2 = pooling(h_conv2)     # picture size: 7*7


# the full connection layer
W_fc1 = weight_variable([7 * 7 * 64, 1024])     
b_fc1 = bias_variable([1024])
h_pool2_flat = tf.reshape(h_pool2, [-1, 7*7*64])
h_fc1 = tf.nn.relu(tf.matmul(h_pool2_flat, W_fc1) + b_fc1)
# To avoid overfitting, drop out some features randomly
keep_prob = tf.placeholder("float")
h_fc1_drop = tf.nn.dropout(h_fc1, keep_prob)
    

# the output layer
W_out = weight_variable([1024, 10])
b_out = bias_variable([10])
y_out = tf.nn.softmax(tf.matmul(h_fc1_drop, W_out) + b_out)
    

# test accuracy
cross_entropy = -tf.reduce_sum(y*tf.log(y_out))
train_step = tf.train.AdamOptimizer(1e-4).minimize(cross_entropy)
correct_prediction = tf.equal(tf.argmax(y_out,1), tf.argmax(y,1))
accuracy = tf.reduce_mean(tf.cast(correct_prediction, "float"))
sess.run(tf.initialize_all_variables())           # initialize

for i in range(20000):
  batch = mnist.train.next_batch(50)
  if i%100 == 0:          # print accuracy + weight + bias every 100 steps 
    train_accuracy = accuracy.eval(feed_dict={
        x:batch[0], y: batch[1], keep_prob: 1.0})
    print ("step %d, training accuracy %g"%(i, train_accuracy))
    print ("bias:")
    print(sess.run(b_out))
    print ("weight:")
    print(sess.run(W_out))
    print()
  train_step.run(feed_dict={x: batch[0], y: batch[1], keep_prob: 0.5})

print ("test accuracy %g"%accuracy.eval(feed_dict={                 # print final test accuracy
    x: mnist.test.images, y: mnist.test.labels, keep_prob: 1.0}))
    
    
    
    