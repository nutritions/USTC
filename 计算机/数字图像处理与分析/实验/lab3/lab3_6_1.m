clc, clear, close all
src1 = imread("..\实验材料\实验图像\lena.bmp");
%Roberts算子
Roberts_lena = edge(src1,'Roberts');
%Sobel算子
Sobel_lena = edge(src1,'Sobel');
%Prewitt算子
Prewitt_lena = edge(src1,'Prewitt');
%拉普拉斯算子
Laplacian1_lena = imfilter(src1,[0 1 0; 1 -4 1; 0 1 0]);
Laplacian2_lena = imfilter(src1,[-1 -1 -1; -1 8 -1; -1 -1 -1]);
%Canny算子
Canny_lena = edge(src1,'Canny');

subplot(3,3,1); imshow(src1); title('原图'); 
subplot(3,3,4); imshow(Roberts_lena); title('Roberts_lena'); 
subplot(3,3,5); imshow(Sobel_lena); title('Sobel_lena'); 
subplot(3,3,6); imshow(Prewitt_lena); title('Prewitt_lena'); 
subplot(3,3,7); imshow(Laplacian1_lena); title('Laplacian1_lena'); 
subplot(3,3,8); imshow(Laplacian2_lena); title('Laplacian2_lena'); 
subplot(3,3,9); imshow(Canny_lena); title('Canny_lena'); 