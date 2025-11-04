clc, clear, close all
src=imread("..\实验材料\实验图像\lena.bmp");
[h,w] = size(src);
res=zeros(h,w);%初始化，避免计算时扩容

x1 = input("x1:");
y1 = input("y1:");
x2 = input("x2:");
y2 = input("y2:");

for i = 1 : h
    for j = 1 : w
        x=src(i,j);
        %灰度拉伸
        if(x < x1)
            fx = y1 / x1 * x;
        elseif(x <= x2)
            fx = (y2 - y1)/(x2 - x1)*(x - x1) + y1;
        else
            fx = (255 - y2)/(255 - x2)*(x - x2) + y2;
        end
        %保证范围
        if fx > 255
             fx = 255;
        elseif fx < 0
             fx = 0;
        end
        %赋值
        res(i,j)=fx;
    end  
end
subplot(1,2,1); imshow(src); title('原图'); 
subplot(1,2,2); imshow(uint8(res)); title('灰度拉伸后'); 