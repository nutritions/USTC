clc, clear, close all
src=imread("..\实验材料\实验图像\lena.bmp");

[h,w] = size(src);
res=zeros(h,w);%初始化，避免计算时扩容
fa=input("斜率：");
fb=input("截距：");
for i = 1 : h
    for j = 1 : w
        res(i,j) = src(i,j)*fa+fb;%线性映射
        if res(i,j) > 255
             res(i,j) = 255;
        elseif res(i,j) < 0
             res(i,j) = 0;
        end
    end
end
subplot(1,2,1); imshow(src); title('原图'); 
subplot(1,2,2); imshow(uint8(res)); title('线性变换后'); 
%计算默认是 double
%不是uint8，会自动进行归一化操作，将图像的灰度值范围缩放到 [0,1]