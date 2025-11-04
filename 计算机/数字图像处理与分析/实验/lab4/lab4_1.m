clc, clear, close all
src1 = imread("..\实验材料\实验图像\Rect1.bmp");
src2 = imread("..\实验材料\实验图像\Rect2.bmp");
%傅里叶变换
f1 = fft2(src1);
%移动低频至中心并增强
f1_s=fftshift(f1);%平移
f1_f = log(abs(f1_s)+1);%尺度变化,abs获取幅度，log增强低频
%幅度逆变换
ifabs1 = uint8(ifft2(abs(f1)));
%相位逆变换
ifangle1 = uint8(abs(ifft2(4999*exp(1i*angle(f1)))));
%共轭逆变换
conj1 = conj(f1);% 获取 F1 和 F2 的共轭
ifconj1 = ifft2(conj1);% 对新的复数数组进行反变换得到图像



f2 = fft2(src2);
f2_s=fftshift(f2);
f2_f = log(abs(f2_s)+1);
ifabs2 = uint8(ifft2(abs(f2)));
ifangle2 = uint8(abs(ifft2(10000*exp(1i*angle(f2)))));
conj2 = conj(f2);
ifconj2 = ifft2(conj2);


subplot(2,5,1); imshow(src1); title('1'); 
subplot(2,5,2); imshow(f1_f,[]); title('1幅度谱'); 
subplot(2,5,3); imshow(ifabs1); title('1幅度逆变换'); 
subplot(2,5,4); imshow(ifangle1); title('1相位逆变换');
subplot(2,5,5); imshow(ifconj1,[]); title('1傅里叶共轭逆变换');
subplot(2,5,6); imshow(src2); title('2'); 
subplot(2,5,7); imshow(f2_f,[]); title('2幅度谱');
subplot(2,5,8); imshow(ifabs2); title('2幅度逆变换'); 
subplot(2,5,9); imshow(ifangle2); title('2相位逆变换'); 
subplot(2,5,10); imshow(ifconj2,[]); title('2傅里叶共轭逆变换');