I = imread('moon.tif');
I = im2double(I);
laplacian_kernel_a = [0 1 0; 1 -4 1; 0 1 0];
laplacian_kernel_b = [1 1 1; 1 -8 1; 1 1 1];
% 图 3.46(a)
subplot(2,2,1);
imshow(I);
title('(a)');
% 图 3.46(b)
laplacian_a = imfilter(I, laplacian_kernel_a, 'replicate');
subplot(2,2,2);
imshow(laplacian_a);
title('(b)');
% 图 3.46(c)
c = -1;
I_sharpened_c = I + c * laplacian_a;
I_sharpened_c = mat2gray(I_sharpened_c);
subplot(2,2,3);
imshow(I_sharpened_c);
title('(c)');
% 图 3.46(d)
laplacian_b = imfilter(I, laplacian_kernel_b, 'replicate');
I_sharpened_d = I + c * laplacian_b;
I_sharpened_d = mat2gray(I_sharpened_d);
subplot(2,2,4);
imshow(I_sharpened_d);
title('(d)');
