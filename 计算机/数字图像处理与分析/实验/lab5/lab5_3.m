source = imread('cameraman.bmp');
subplot(1,3,1); imshow(source); title('原图'); 
range_value = .5;%控制分割的粒度
S = qtdecomp(source,range_value,2);%四叉树分割
blocks = zeros(256);

%循环不同的分块大小，产生分块边界
for dim = [64 32 16 8 4 2]
	blk_cnt = length(find(S==dim)); %统计四叉树中尺寸为 dim 的块的数量   
	if (blk_cnt > 0)        
        values = repmat(uint8(1),[dim dim blk_cnt]);
        values(2:dim,2:dim,:) = 0;% 边界1  
	blocks = qtsetblk(blocks,S,dim,values);%分块保存在blocks中
  end
end

%产生分裂图，在图像上突出显示四叉树分割结果中的第一个块
output1 = source;
output1(blocks==1) = 255;
subplot(1,3,2); imshow(output1); title('分裂'); 

%将各块分别标记
i = 0;
for dim = [64 32 16 8 4 2]
    [vals,r,c] = qtgetblk(source,S,dim);%四叉树分解中的块值
    %块不空则标记
    if ~isempty(vals)
        for j = 1:length(r)
            i = i + 1;
            blocks(r(j):r(j)+ dim - 1,c(j):c(j)+ dim - 1) = i;%为每个块分配了一个唯一的标记
        end
    end
end

%将极差较小的块的标记合并
for j = 1 : i
    %  找到边界, 只有当两个像素值不相等时，才将其设置为 1
    bound = boundarymask(blocks==j,4) & (~(blocks==j));
    [r,l] = find(bound==1); % 找到边界像素的位置
    for k = 1 : size(r,1)
    %合并
	%识别并提取与当前处理的边界像素块相同的所有区域
	merge = source((blocks==j) | (blocks==blocks(r(k),l(k))));
	% 计算极差
        if(range(merge(:))<range_value*256)
	    %标记 如果满足条件，表示 merge 中像素值变化较小，可以视为一个相对均匀的区域，适合合并
            blocks(blocks==blocks(r(k),l(k))) = j;
        end
    end
end

%根据标记重新分割，合并相邻的分块
output2 = source;
for i = 2 : 255
    for j = 2 : 255
	%标记合并后，原图中还是不相同的块填充为白色区分边界
        if(blocks(i,j)~=blocks(i,j+1) || blocks(i,j)~=blocks(i+1,j))
            output2(i,j) = 255;
        end
    end
end

subplot(1,3,3); imshow(output2); title('合并');
