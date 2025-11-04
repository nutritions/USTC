-- 还书，参数：读者id、书id，还书日期
delimiter //
drop procedure if exists returnBook;
create procedure returnBook(in readerId char(8), in bookId char(8), in returnDate date)
end_lable:
begin
    -- 书是否可还
    select bstatus into @status from Book where bid = bookId;
    if @status != 1 then
        select "书没被借出";
		leave end_lable;
    end if;

    -- 是否是该读者借的
    select count(*) into @count from Borrow where bookId = book_ID and readerId = reader_ID;
    if @count = 0 then
        select "不是该读者借的";
		leave end_lable;
    end if;

    -- 更新借阅记录
    select count(*)
    into @count
    from Borrow
    where bookId = book_ID
      and readerId = reader_ID
      and return_Date is null
      and borrow_Date > returnDate;
    if @count != 0 then
        select "还书时间错误";
        leave end_lable;
    end if;
    update Borrow set return_Date = returnDate where bookId = book_ID and readerId = reader_ID and return_Date is null;

    -- 更新图书状态
    select count(*) into @count from Reserve where book_ID = bookId ;
    if @count != 0 then
        update Book set bstatus = 2 where bid = bookId;
    else
        update Book set bstatus = 0 where bid = bookId;
    end if;

    -- 输出成功信息
    select '还书成功' ;
end ;
//
delimiter ;

select * from borrow;
select *from book;

-- 没被借出
call returnBook('R001','B008','2024-05-10');

-- 还书成功，展示borrow表中的归还日期和book表中的状态
select * from borrow where reader_ID='R001' ;
select *from book where bid ='B001';
call returnBook('R001','B001','2024-05-10');

