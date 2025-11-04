source = imread('lena.bmp');
subplot(1,2,1); imshow(source); title('lena'); 
subplot(1,2,2); imshow(imbinarize(source, OSTU(source)/255)); title('分割二值化结果'); 

function k = OSTU(I)
    I = im2double(I);
    [M,N]=size(I);
    pix=M*N;                   
    gray=0;                         
    ICV_t=0;                            
    temp = 0;
    %得到图像总灰度值
    for i=1:M
        for j=1:N
            gray=gray+I(i,j);
        end
    end
    gray_aver=gray*255/pix;   %图像灰度值的总平均值
 
 
    %按照t分割，并分别计算前景和背景的像素比例和平均灰度
    for t=0:255                  
        gray_A=0;       %总灰度值
        gray_B=0;                      
        pix_A=0;        %总像素
        pix_B=0;                   

        for i=1:M  
            for j=1:N
                if (I(i,j)*255>=t)    
                    pix_A=pix_A+1;  %A总像素和总灰度
                    gray_A=gray_A+I(i,j);
		   
                elseif (I(i,j)*255<t) 
                    pix_B=pix_B+1;  %B总像素和总灰度
                    gray_B=gray_B+I(i,j); 
		      
                end
            end
        end

	    PA=pix_A/pix; %A像素比例和平均灰度
		A_ave=gray_A*255/pix_A;   
        PB=pix_B/pix; %B像素比例和平均灰度           
        B_ave=gray_B*255/pix_B;    
                  
        %Otsu算法
        ICV=PA*((A_ave-gray_aver)^2)+PB*((B_ave-gray_aver)^2);  
        if (ICV>ICV_t) %得到最大方差
            ICV_t=ICV;
            temp=t;                       
        end
    end

    k =temp;
end
