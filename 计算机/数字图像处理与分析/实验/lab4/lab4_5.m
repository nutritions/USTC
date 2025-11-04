clc, clear, close all
pout = imread("..\实验材料\实验图像\pout.bmp");


% 理想高通滤波器
D0 = 15; 
pout_ideal_histeq_after = histeq(uint8(applyFilter(pout, 'ideal', D0)));
pout_ideal_histeq_first = applyFilter(histeq(uint8(pout)), 'ideal', D0);

% 巴特沃斯高通滤波器
D0 = 15; 
n = 1; 
pout_blpf_histeq_after = histeq(uint8(applyFilter(pout, 'blpf', D0,n)));
pout_blpf_histeq_first = applyFilter(histeq(uint8(pout)), 'blpf', D0,n);

% 高斯高通滤波器
D0 = 15; 
n = 2;
pout_gauss_histeq_after = histeq(uint8(applyFilter(pout, 'gaussian', D0,n)));
pout_gauss_histeq_first = applyFilter(histeq(uint8(pout)), 'gaussian', D0,n);


% 显示不同低通滤波器处理后的图像
figure;
subplot(2,4,1), imshow(pout, []), title('pout原图');
subplot(2,4,2), imshow(pout_ideal_histeq_after, []), title('ideal先高后直');
subplot(2,4,3), imshow(pout_blpf_histeq_after, []), title('blpf先高后直');
subplot(2,4,4), imshow(pout_gauss_histeq_after, []), title('gauss先高后直');
subplot(2,4,6), imshow(pout_ideal_histeq_first, []), title('ideal先直后高');
subplot(2,4,7), imshow(pout_blpf_histeq_first, []), title('blpf先直后高');
subplot(2,4,8), imshow(pout_gauss_histeq_first, []), title('gauss先直后高');

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
            H = D > D0;
        case 'blpf'
            H = 1.0 ./ (1.0 + (D0./ D) .^ (2 * n));
        case 'gaussian'
            H = exp(-(D0./ D) .^ n);
        otherwise
            error('error type.');
    end
    H=4*H+1;
    % 傅里叶变换并移位
    F = fft2(img);
    F = fftshift(F);
    % 应用频域滤波器
    G = F .* H;
    % 移回并反变换
    G = ifftshift(G);
    output = abs(ifft2(G));
end
