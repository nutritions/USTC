clc, clear, close all
src=imread("..\实验材料\实验图像\lena.bmp");
min = input("下限:");
max = input("上限:");
histogram(src,'BinLimits',[min,max])%显示给定范围的灰度直方图