% 读取图像
I = imread('moon.tif');
% 转换为双精度类型，方便后续计算
I = im2double(I);
laplacian_kernel_a = [0 1 0; 1 -4 1; 0 1 0];
laplacian_a = imfilter(I, laplacian_kernel_a, 'replicate');
imshow(laplacian_a);