
delimiter //
-- 当一本书被预约时, 自动将 Book 表中相应图书的status 修改为2，并增加 reserve_Times；
drop trigger if exists reserve_book;
create trigger reserve_book
    after insert  
    on Reserve
    for each row
begin
	update Book set bstatus = 2 where bid = new.book_id;
    update Book set reserve_Times = reserve_Times + 1 where bid = new.book_id;
end;


-- 当读者取消预约时或者预约的书借出时, 自动减少 reserve_Times
drop trigger if exists cancel_reserve;
create trigger cancel_reserve
    after delete  -- 在删除之后触发
    on Reserve
    for each row
begin
    update Book
    set reserve_Times = reserve_Times - 1
    where Book.bid=old.book_ID;
    
    -- 当某本书的最后一位预约者取消预约且该书未被借出
    select count(*) into @reserve
    from Reserve, Book
    Where Reserve.book_ID=old.book_ID and (Book.bid=old.book_ID and Book.bstatus!=1)and Reserve.book_ID=Book.bid;

    if @reserve=0 then
		update Book
		set bstatus = 0
		where Book.bid=old.book_ID;
	end if;
end;
//
delimiter ;


select * from reserve;
select * from book where bid='B012';
insert into Reserve (book_id, reader_id, take_Date)	 values ('B012', 'R001', '2024-06-09');

Delete from Reserve Where book_ID='B012' and take_Date='2024-06-09';
