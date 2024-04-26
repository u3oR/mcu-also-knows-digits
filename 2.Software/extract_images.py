from read_rawdata import *
import matplotlib.pyplot as plt

import numpy as np

def save_image_to_c_uchar_array(image, filename="image_data.h"):
    """ 将图像数据保存为C数组的形式 """
    with open(filename, "w") as file:
        file.write("unsigned char image_data[784] = {\n")
        for row in image:
            row_str = ", ".join(f"0x{val:02x}" for val in row)
            file.write(f"    {{{row_str}}},\n")
        file.write("};\n")

def save_image_to_c_float_array(image, filename="image_data.h"):
    """将图像数据保存为 C 数组的形式, float32_t"""
    with open(filename, "w") as file:
        file.write("float32_t image_data[784] = {\n")
        for row in image:
            # 归一化并转换为字符串
            row_str = ", ".join(f"{pixel / 255.0:.6f}f" for pixel in row)
            file.write("\t" + row_str + ", \n")
        file.write("};\n")


if __name__ == '__main__':

    images = read_idx_images('MNIST_ORG/t10k-images.idx3-ubyte')
    labels = read_idx_labels('MNIST_ORG/t10k-labels.idx1-ubyte')

    idx = 800

    print(labels[idx])
    # 调用函数保存图像为C数组
    save_image_to_c_float_array(images[idx], "image_data.h")

    plt.imshow(images[idx], cmap='gray')
    plt.title(labels[idx])
    plt.show()