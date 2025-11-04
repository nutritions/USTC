clc, clear, close all
girl = imread("..\实验材料\实验图像\Girl.bmp");

% 加椒盐噪声和高斯噪声
sp = imnoise(girl, 'salt & pepper', 0.03);
gauss = imnoise(girl, 'gaussian');
% 理想低通滤波器
D0 = 50; 
sp_ideal = applyFilter(sp, 'ideal', D0);
gauss_ideal = applyFilter(gauss, 'ideal', D0);

% 巴特沃斯低通滤波器
D0 = 50; 
n = 1; % 阶数
sp_blpf = applyFilter(sp, 'blpf', D0, n);
gauss_blpf = applyFilter(gauss, 'blpf', D0, n);

% 高斯低通滤波器
D0 = 50; 
n = 2;
sp_gauss = applyFilter(sp, 'gaussian', D0, n);
gauss_gauss = applyFilter(gauss, 'gaussian', D0, n);

% 显示不同低通滤波器处理后的图像
figure;
subplot(3,3,1), imshow(girl, []), title('原图');
subplot(3,3,2), imshow(sp, []), title('椒盐噪声');
subplot(3,3,3), imshow(gauss, []), title('高斯噪声');
subplot(3,3,4); imshow(sp_ideal, []); title('椒盐噪声ideal');
subplot(3,3,5); imshow(sp_blpf, []); title('椒盐噪声blpf');
subplot(3,3,6); imshow(sp_gauss, []); title('椒盐噪声gauss');
subplot(3,3,7); imshow(gauss_ideal, []); title('高斯噪声ideal');
subplot(3,3,8); imshow(gauss_blpf, []); title('高斯噪声blpf');
subplot(3,3,9); imshow(gauss_gauss, []); title('高斯噪声gauss');

function output = applyFilter(img, type, D0, n)
    if nargin < 4
        n = 1; % 默认阶数为1
    end
    [M, N] = size(img);    
    % 构建坐标
    [U, V] = meshgrid(-N/2:N/2-1, -M/2:M/2-1);
    D = hypot(U, V); % 计算中心偏移距离, 生成矩阵
    
    % 生成滤波器掩膜
    switch type
        case 'ideal'
            H = D <= D0;
        case 'blpf'
            H = 1.0 ./ (1.0 + (D ./ D0) .^ (2 * n));
        case 'gaussian'
            H = exp(-(D ./ D0) .^ n);
        otherwise
            error('error type.');
    end
    
    % 傅里叶变换并移位
    F = fft2(img);
    F = fftshift(F);
    % 应用频域滤波器
    G = F .* H;
    % 移回并反变换
    G = ifftshift(G);
    output = abs(ifft2(G));
end
