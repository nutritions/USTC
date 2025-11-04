clc,clear,close all
i1 = imread("..\实验材料\实验图像\alphabet1.jpg");%原图
i2=imread("..\实验材料\实验图像\alphabet2.jpg");%几何失真图
f=figure();

subplot(2,2,1); 
imshow(i1);
subplot(2,2,2); 
imshow(i2);

[x, y] = ginput(8);
moving = [x(1) y(1);x(3) y(3);x(5) y(5);x(7) y(7)];
fixed = [x(2) y(2);x(4) y(4);x(6) y(6);x(8) y(8)];
tform = fitgeotrans(moving,fixed,'projective');
res = imwarp(i2,tform,'OutputView',imref2d(size(i1)));

subplot(2,2,3);
imshow(res);
title('校正后');



