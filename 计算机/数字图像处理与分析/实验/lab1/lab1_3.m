clc, clear, close all
i1=imread("..\实验材料\实验图像\lena.bmp");
f = figure();

[h, w, c] = size(i1);
x=input("水平缩放量：");
y=input("垂直缩放量：");

i2 = imresize(i1, [h*y,w*x], 'nearest'); % 最近邻插值
i3 = imresize(i1, [h*y,w*x], 'bilinear'); % 双线性插值

subplot(2, 2, [1, 2]);
imshow(i1);
title('origin');
subplot(2, 2, 3);
imshow(i2);
title('nearest');
subplot(2, 2, 4);
imshow(i3);
title('bilinear');