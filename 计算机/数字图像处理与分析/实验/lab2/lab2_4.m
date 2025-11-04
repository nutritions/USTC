clc, clear, close all
src=imread("..\实验材料\实验图像\pout.bmp");

subplot(3,2,1); imshow(src); title('原图'); 
subplot(3,2,2); histogram(src);title('原图直方图');

res1 = histeq(src);%直方图均衡
subplot(3,2,3); imshow(res1);title('直方图均衡');
subplot(3,2,4); histogram(res1);title('增强后直方图');

res2 = histeq(src,normpdf((0:1:255),100,50));
subplot(3,2,5); imshow(res2);title('直方图规定化');
subplot(3,2,6); histogram(res2);title('规定化后直方图');

