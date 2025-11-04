clc, clear, close all
pout = imread("..\实验材料\实验图像\pout.bmp");
girl = imread("..\实验材料\实验图像\Girl.bmp");

% 理想低通滤波器
D0 = 25; 
pout_ideal = applyFilter(pout, 'ideal', D0);
girl_ideal = applyFilter(girl, 'ideal', D0);

% 巴特沃斯低通滤波器
D0 = 25; 
n = 1; 
pout_blpf = applyFilter(pout, 'blpf', D0, n);
girl_blpf = applyFilter(girl, 'blpf', D0, n);

% 高斯低通滤波器
D0 = 25; 
n = 2;
pout_gauss = applyFilter(pout, 'gaussian', D0, n);
girl_gauss = applyFilter(girl, 'gaussian', D0, n);

% 显示不同低通滤波器处理后的图像
figure;
subplot(2,4,1), imshow(pout, []), title('pout原图');
subplot(2,4,2), imshow(pout_ideal, []), title('理想低通滤波器');
subplot(2,4,3), imshow(pout_blpf, []), title('巴特沃斯低通滤波器');
subplot(2,4,4), imshow(pout_gauss, []), title('高斯低通滤波器');
subplot(2,4,5), imshow(girl, []), title('girl原图');
subplot(2,4,6), imshow(girl_ideal, []), title('理想低通滤波器');
subplot(2,4,7), imshow(girl_blpf, []), title('巴特沃斯低通滤波器');
subplot(2,4,8), imshow(girl_gauss, []), title('高斯低通滤波器');

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
