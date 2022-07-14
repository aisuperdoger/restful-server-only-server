import os
import time

import torch
#from torch.autograd import Variable

from alexnet import AlexNet
#from mobile_net import MobileNetV3_Large,MobileNetV3_Small
import numpy as np
from letterbox import letterbox
import cv2
import math
#from image_process import resize_image_online

def softmax(x):
    e_x = np.exp(x - np.max(x))
    return e_x / e_x.sum()

class Classification():
    def __init__(self,model_path):
        super(Classification, self).__init__()
        self.model = AlexNet()

        if model_path != None:
            self.model.load_state_dict(torch.load(model_path))
            print("model_load_successful")
        if torch.cuda.is_available():
            device = torch.device('cuda')
            self.model = self.model.to(device)
        self.model.eval()

    def is_Life_jacket(self,image):
        start = time.time()
        # image = cv2.cvtColor(image, cv2.COLOR_BGR2RGB)
        # mean = np.array([0.406,0.456,0.485])
        # std = np.array([0.225,0.224,0.229])
        # image = (image/255 - mean)/std

        #
        #image_size = image.shape
        #if image_size[0]/image_size[1]>2 and image_size[0]/image_size[1]<=3:
        #   image = image[:math.floor(image_size[0]*3/4),:,:]
        #elif image_size[0]/image_size[1]>3 and image_size[0]/image_size[1]<=4:
        #    image = image[:math.floor(image_size[0]*2/3),:,:]
        #elif image_size[0] / image_size[1] > 4:
        #    image = image[:math.floor(image_size[0] * 1/2), :, :]
        #else:
        #    pass

        #image_size = image.shape
        #if image_size[0]/image_size[1]>2:
        #    image = image[math.floor(image_size[0]/6):,:,:]


        image = letterbox(image)
        image = np.expand_dims(image, axis=0)
        image = torch.from_numpy(image)
        image = image.permute(0, 3, 1, 2)
        image = image.float().cuda()
        pre_label = self.model(image).cpu().detach().numpy()
        pre_label = softmax(pre_label)
        # print("pre_label*******************")
        # print(pre_label)
        predict = pre_label.argmax(axis=1)#.cpu()
        end = time.time()
        #print(end-start)
        # if predict ==1 and pre_label[0][1]>=0.65:
        if predict ==1:
            return 1
        else:
            return 0

if __name__ =="__main__":
    model_classify = Classification('D:/FJF/model/alex_11_16_mor3.pth')
    imglist = os.listdir('D:/FJF/person_pos')
    for i in imglist:

        img = cv2.imread('D:/FJF/person_pos/'+ i)
        print(model_classify.is_Life_jacket(img))
    # for i in range(5):
    #     img = cv2.imread('D:/FJF/lenet/1_frame_000011.jpg')
    #     print(model_classify.is_Life_jacket(img))
