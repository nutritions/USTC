clc, clear, close all
src2 = imread("..\实验材料\实验图像\blood.bmp");

%Roberts算子
Roberts_blood = edge(src2,'Roberts');
%Sobel算子
Sobel_blood = edge(src2,'Sobel');
%Prewitt算子
Prewitt_blood = edge(src2,'Prewitt');
%拉普拉斯算子
Laplacian1_blood = imfilter(src2,[0 1 0; 1 -4 1; 0 1 0]);
Laplacian2_blood = imfilter(src2,[-1 -1 -1; -1 8 -1; -1 -1 -1]);
%Canny算子
Canny_blood = edge(src2,'Canny');

subplot(3,3,[1,3]); imshow(src2); title('原图'); 
subplot(3,3,4); imshow(Roberts_blood); title('Roberts_blood'); 
subplot(3,3,5); imshow(Sobel_blood); title('Sobel_blood'); 
subplot(3,3,6); imshow(Prewitt_blood); title('Prewitt_blood'); 
subplot(3,3,7); imshow(Laplacian1_blood); title('Laplacian1_blood'); 
subplot(3,3,8); imshow(Laplacian2_blood); title('Laplacian2_blood'); 
subplot(3,3,9); imshow(Canny_blood); title('Canny_blood'); 