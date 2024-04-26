import numpy as np
import matplotlib.pyplot as plt

def read_idx_labels(filename):
    with open(filename, 'rb') as f:
        magic, num_items = int.from_bytes(f.read(4), 'big'), int.from_bytes(f.read(4), 'big')
        if magic != 2049:  # Magic number for the MNIST label file
            raise ValueError("File is not a valid MNIST label file.")

        # Read the labels
        labels = np.frombuffer(f.read(), dtype=np.uint8)
        return labels


def read_idx_images(filename):
    with open(filename, 'rb') as f:
        # Read the magic number
        magic = int.from_bytes(f.read(4), 'big')
        if magic != 2051:  # Magic number for the MNIST image file
            raise ValueError("File is not a valid MNIST image file.")

        # Read dimensions: number of images, rows, and columns
        num_images = int.from_bytes(f.read(4), 'big')
        rows = int.from_bytes(f.read(4), 'big')
        cols = int.from_bytes(f.read(4), 'big')

        # Read the data
        data = np.frombuffer(f.read(), dtype=np.uint8)
        data = data.reshape(num_images, rows, cols)
        return data


if __name__ == "__main__":

    images_train = read_idx_images('MNIST_ORG/train-images.idx3-ubyte')
    labels_train = read_idx_labels('MNIST_ORG/train-labels.idx1-ubyte')

    images_test = read_idx_images('MNIST_ORG/t10k-images.idx3-ubyte')
    labels_test = read_idx_labels('MNIST_ORG/t10k-labels.idx1-ubyte')

    print(images_train.shape)
    
    plt.imshow(images_train[100], cmap='gray')
    plt.title(labels_train[100])
    plt.show()

