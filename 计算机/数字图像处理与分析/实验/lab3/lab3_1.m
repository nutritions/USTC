clc, clear, close all
src = imread("..\实验材料\实验图像\lena.bmp");
%添加噪声
pepper = imnoise(src,'salt & pepper',0.03);
gaussian = imnoise(src,'gaussian');
random = imnoise(src,'speckle',0.05);
%均值滤波
pepper_output = imfilter(pepper,fspecial('average',3));
gaussian_output = imfilter(gaussian,fspecial('average',3));
poisson_output = imfilter(random,fspecial('average',3));
subplot(3,3,1); imshow(src); title('原图'); 
subplot(3,3,4); imshow(pepper); title('3%椒盐噪声'); 
subplot(3,3,5); imshow(gaussian); title('高斯噪声'); 
subplot(3,3,6); imshow(random); title('随机噪声'); 
subplot(3,3,7); imshow(pepper_output); title('椒盐均值滤波'); 
subplot(3,3,8); imshow(gaussian_output); title('高斯均值滤波'); 
subplot(3,3,9); imshow(poisson_output); title('随机均值滤波'); 

