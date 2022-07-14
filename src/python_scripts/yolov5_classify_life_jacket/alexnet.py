from  torch import nn
class AlexNet(nn.Module):
    def __init__(self):
        super(AlexNet,self).__init__()
        self.conv1 = nn.Sequential(
            nn.Conv2d(in_channels=3, out_channels=96, kernel_size=(11,11), stride=(4,4), padding=(0,0)),
            nn.ReLU(),
            nn.BatchNorm2d(96),
            nn.MaxPool2d(kernel_size=3,stride=2,padding=0)

        )
        self.conv2 = nn.Sequential(
            nn.Conv2d(in_channels=96, out_channels=256, kernel_size=(5,5), stride=(1,1), padding=(2,2)),
            nn.ReLU(),
            nn.BatchNorm2d(256),
            nn.MaxPool2d(kernel_size=3,stride=2,padding=0)

        )
        self.conv3 = nn.Sequential(
            nn.Conv2d(in_channels=256, out_channels=384, kernel_size=(3,3), stride=(1,1), padding=(1,1)),
            nn.ReLU(),
            nn.BatchNorm2d(384)

        )
        self.conv4 = nn.Sequential(
            nn.Conv2d(in_channels=384, out_channels=384, kernel_size=(3,3), stride=(1,1), padding=(1,1)),
            nn.ReLU(),
            nn.BatchNorm2d(384)

        )
        self.conv5 = nn.Sequential(
            nn.Conv2d(in_channels=384, out_channels=256, kernel_size=(3,3), stride=(1,1), padding=(1,1)),
            nn.ReLU(),
            nn.BatchNorm2d(256),
            nn.MaxPool2d(kernel_size=3,stride=2,padding=0)

        )
        self.linear1 = nn.Linear(in_features=3072,out_features=4096)#1536,3072,9216
        self.bn1 = nn.BatchNorm1d(4096)
        self.linear2 = nn.Linear(in_features=4096,out_features=4096)
        self.bn2 = nn.BatchNorm1d(4096)
        self.linear3 = nn.Linear(in_features=4096,out_features=2)

        #self.linear1 = nn.Linear(in_features=3072,out_features=2048)#1536,3072,9216
        #self.bn1 = nn.BatchNorm1d(2048)
        #self.linear2 = nn.Linear(in_features=2048,out_features=512)
        #self.bn2 = nn.BatchNorm1d(512)
        #self.linear3 = nn.Linear(in_features=512,out_features=2)

    def forward(self,x):
        x = self.conv1(x)
        x = self.conv2(x)
        x = self.conv3(x)
        x = self.conv4(x)
        x = self.conv5(x)
        x = x.reshape(x.shape[0],x.shape[1]*x.shape[2]*x.shape[3])
        x = self.bn1(self.linear1(x))
        x = self.bn2(self.linear2(x))
        # x = self.linear1(x)
        # x = self.linear2(x)
        x = self.linear3(x)
        return x


class AlexNet1(nn.Module):
    def __init__(self):
        super(AlexNet1,self).__init__()
        self.conv1 = nn.Sequential(
            nn.Conv2d(in_channels=3, out_channels=96, kernel_size=(11,11), stride=(4,4), padding=(0,0)),
            nn.ReLU(),
            nn.BatchNorm2d(96),
            nn.MaxPool2d(kernel_size=3,stride=2,padding=0)

        )
        self.conv2 = nn.Sequential(
            nn.Conv2d(in_channels=96, out_channels=256, kernel_size=(5,5), stride=(1,1), padding=(2,2)),
            nn.ReLU(),
            nn.BatchNorm2d(256),
            nn.MaxPool2d(kernel_size=3,stride=2,padding=0)

        )
        self.conv3 = nn.Sequential(
            nn.Conv2d(in_channels=256, out_channels=384, kernel_size=(3,3), stride=(1,1), padding=(1,1)),
            nn.ReLU(),
            nn.BatchNorm2d(384)

        )
        self.conv4 = nn.Sequential(
            nn.Conv2d(in_channels=384, out_channels=384, kernel_size=(3,3), stride=(1,1), padding=(1,1)),
            nn.ReLU(),
            nn.BatchNorm2d(384)

        )
        self.conv5 = nn.Sequential(
            nn.Conv2d(in_channels=384, out_channels=256, kernel_size=(3,3), stride=(1,1), padding=(1,1)),
            nn.ReLU(),
            nn.BatchNorm2d(256),
            nn.MaxPool2d(kernel_size=3,stride=2,padding=0)

        )
        self.linear1 = nn.Linear(in_features=256,out_features=2)
    def forward(self,x):
        x = self.conv1(x)
        x = self.conv2(x)
        x = self.conv3(x)
        x = self.conv4(x)
        x = self.conv5(x)
        x = nn.AvgPool2d(kernel_size=(x.shape[2],x.shape[3]),padding=0)(x)
        x = x.reshape(x.shape[0],x.shape[1]*x.shape[2]*x.shape[3])
        x = self.linear1(x)
        return x

class AlexNet2(nn.Module):
    def __init__(self):
        super(AlexNet2,self).__init__()
        self.conv0 = nn.Sequential(
            nn.Conv2d(in_channels=3, out_channels=96, kernel_size=(3,3), stride=(1,1), padding=(1,1)),
            nn.ReLU(),
            nn.BatchNorm2d(96),


        )
        self.conv1 = nn.Sequential(
            nn.Conv2d(in_channels=96, out_channels=96, kernel_size=(11,11), stride=(4,4), padding=(0,0)),
            nn.ReLU(),
            nn.BatchNorm2d(96),
            nn.MaxPool2d(kernel_size=3,stride=2,padding=0)

        )
        self.conv2 = nn.Sequential(
            nn.Conv2d(in_channels=96, out_channels=256, kernel_size=(5,5), stride=(1,1), padding=(2,2)),
            nn.ReLU(),
            nn.BatchNorm2d(256),
            nn.MaxPool2d(kernel_size=3,stride=2,padding=0)

        )
        self.conv3 = nn.Sequential(
            nn.Conv2d(in_channels=256, out_channels=384, kernel_size=(3,3), stride=(1,1), padding=(1,1)),
            nn.ReLU(),
            nn.BatchNorm2d(384)

        )
        self.conv4 = nn.Sequential(
            nn.Conv2d(in_channels=384, out_channels=384, kernel_size=(3,3), stride=(1,1), padding=(1,1)),
            nn.ReLU(),
            nn.BatchNorm2d(384)

        )
        self.conv5 = nn.Sequential(
            nn.Conv2d(in_channels=384, out_channels=256, kernel_size=(3,3), stride=(1,1), padding=(1,1)),
            nn.ReLU(),
            nn.BatchNorm2d(256),
            nn.MaxPool2d(kernel_size=3,stride=2,padding=0)

        )
        self.linear1 = nn.Linear(in_features=3072,out_features=4096)#1536,3072,9216
        self.bn1 = nn.BatchNorm1d(4096)
        self.linear2 = nn.Linear(in_features=4096,out_features=4096)
        self.bn2 = nn.BatchNorm1d(4096)
        self.linear3 = nn.Linear(in_features=4096,out_features=2)

        #self.linear1 = nn.Linear(in_features=3072,out_features=2048)#1536,3072,9216
        #self.bn1 = nn.BatchNorm1d(2048)
        #self.linear2 = nn.Linear(in_features=2048,out_features=512)
        #self.bn2 = nn.BatchNorm1d(512)
        #self.linear3 = nn.Linear(in_features=512,out_features=2)

    def forward(self,x):
        x = self.conv0(x)
        x = self.conv1(x)
        x = self.conv2(x)
        x = self.conv3(x)
        x = self.conv4(x)
        x = self.conv5(x)
        x = x.reshape(x.shape[0],x.shape[1]*x.shape[2]*x.shape[3])
        x = self.bn1(self.linear1(x))
        x = self.bn2(self.linear2(x))
        # x = self.linear1(x)
        # x = self.linear2(x)
        x = self.linear3(x)
        return x
