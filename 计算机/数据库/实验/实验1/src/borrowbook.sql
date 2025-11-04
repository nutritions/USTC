-- 借书，参数：读者id、书id，借书日期
-- 借书，参数：读者id、书id，借书日期
delimiter //
drop procedure if exists borrowBook;
create procedure borrowBook(in readerId char(8), in bookId char(8), in borrowDate date)
end_lable:
begin
    -- 书是否被别人借了 
    select count(*) into @borrow from Borrow where book_ID = bookId and return_Date is null and reader_id != readerid;
    if @borrow>0 then
       select "书已经被别人借了";
       leave end_lable;
    end if;
    
    -- 同一天不允许同一个读者重复借阅同一本读书；
    select count(*) into @count from Borrow
    where book_ID = bookId
      and reader_ID = readerId
      and borrow_date = borrowDate;
    if @count > 0 then
        select "同一天不能再借一样的书";
        leave end_lable;
    end if;

    -- 一个读者最多只能借阅 3 本图书
    select count(*) into @count from Borrow where reader_ID = readerId and return_date is null;
    if @count >= 3 then
        select "一个人最多借三本书";
        leave end_lable;
    end if;

    -- 如果该图书存在预约记录，而当前借阅者没有预约，则不允许借阅；
    select count(*) into @count_me from Reserve where book_ID = bookId and reader_ID = readerId;
    select count(*) into @count_others from Reserve where book_ID = bookId and reader_id !=readerId;
    if @count_me = 0 and @count_others > 0 then  
		select "没预约，别人已经预约了";
        leave end_lable;
    end if;

    -- 检查通过，可以借阅
    -- 插入borrow
    insert into Borrow(reader_ID, book_ID, borrow_Date) values (readerId, bookId, borrowDate);
    -- 修改book中的time和bstatus
    update Book set borrow_Times = Book.borrow_Times + 1, bstatus = 1 where bid = bookId;
    -- 借阅成功删除预约记录
    delete from Reserve where book_ID = bookId and reader_ID = readerId;

    -- 输出成功信息
    select "借阅成功";

end;
//
delimiter ;


select * from borrow ;
select *from reserve;
-- 未预约，别人预约，借阅失败
call borrowBook('R001','B008','2024-05-9');

-- 预约成功的，展示预约记录被删除还有book表的变化
select *from reserve;
select *from book where bid ='B001';
call borrowBook('R001','B001','2024-05-9');

-- 同一天，同一个人再次借阅同一本书
call borrowBook('R001','B001','2024-05-9');

-- 同一个人借三本书未还
call borrowBook('R005','B008','2024-05-9');




