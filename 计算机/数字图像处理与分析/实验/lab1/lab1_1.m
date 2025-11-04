clc, clear, close all
i1=imread("..\实验材料\实验图像\alphabet1.jpg");
f = figure();

tx = input("水平平移量:");
ty = input("垂直平移量:");
se = translate(strel(1), [ty, tx]);
i2 = imdilate(i1, se);

subplot(1, 2, 1);
imshow(i1);
title('origin');

subplot(1, 2, 2);
imshow(i2);
title('translation');