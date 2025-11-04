clc, clear, close all
src = imread("..\实验材料\实验图像\lena.bmp");

%添加噪声
pepper = imnoise(src,'salt & pepper',0.03);
gaussian = imnoise(src,'gaussian');
random = imnoise(src,'speckle',0.05);
%中值滤波
pepper_output = medfilt2(pepper);
gaussian_output = medfilt2(gaussian);
speckle_output = medfilt2(random);
subplot(3,3,1); imshow(src); title('原图'); 
subplot(3,3,4); imshow(pepper); title('3%椒盐噪声'); 
subplot(3,3,5); imshow(gaussian); title('高斯噪声'); 
subplot(3,3,6); imshow(random); title('随机噪声'); 
subplot(3,3,7); imshow(pepper_output); title('椒盐中值滤波'); 
subplot(3,3,8); imshow(gaussian_output); title('高斯中值滤波'); 
subplot(3,3,9); imshow(speckle_output); title('随机中值滤波'); 

