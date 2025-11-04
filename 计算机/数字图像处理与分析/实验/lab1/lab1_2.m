clc, clear, close all
i1=imread("..\实验材料\实验图像\alphabet1.jpg");
f = figure();
angle=input("旋转角度：");
i2 = imrotate(i1, angle, 'nearest'); % 最近邻插值
i3 = imrotate(i1, angle, 'bilinear'); % 双线性插值

subplot(2, 2, [1, 2]);
imshow(i1);
title('origin');
subplot(2, 2, 3);
imshow(i2);
title('nearest');
subplot(2, 2, 4);
imshow(i3);
title('bilinear');