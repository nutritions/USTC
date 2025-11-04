clc, clear, close all
src = imread("..\实验材料\实验图像\lena.bmp");
%添加噪声
pepper = imnoise(src,'salt & pepper',0.03);
gaussian = imnoise(src,'gaussian');
random = imnoise(src,'speckle',0.05);
%超限中值滤波
pepper_output = filter(pepper,30);
gaussian_output = filter(gaussian,30);
speckle_output = filter(random,30);
subplot(3,3,1); imshow(src); title('原图'); 
subplot(3,3,4); imshow(pepper); title('3%椒盐噪声'); 
subplot(3,3,5); imshow(gaussian); title('高斯噪声'); 
subplot(3,3,6); imshow(random); title('随机噪声'); 
subplot(3,3,7); imshow(pepper_output); title('椒盐超限中值滤波'); 
subplot(3,3,8); imshow(gaussian_output); title('高斯超限中值滤波'); 
subplot(3,3,9); imshow(speckle_output); title('随机超限中值滤波'); 


function [output] = filter(input,T)
    output = input;
    [r,l] = size(output);
    for i = 2 : (r - 1)
        for j = 2 : (l - 1)
            temp = input(i - 1 : i + 1, j - 1 : j + 1);
            middle_value = median(temp(:));
            if(abs(double(input(i,j)) - double(middle_value)) > T)
                output(i,j) = middle_value;
            end
        end
    end
end


