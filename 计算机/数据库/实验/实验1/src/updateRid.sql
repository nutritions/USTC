delimiter //
drop procedure if exists updateReaderID;

create procedure updateReaderID(in oldID char(8), in newID char(8))
end_lable:
begin
    SET SQL_SAFE_UPDATES = 0;
    Alter Table Borrow Drop Foreign key FK_reader;
    -- 新id是否存在
    select count(*) into @count from Reader where rid = newID;
    if @count > 0 then
       select "error";
       LEAVE end_lable;
    end if;

    -- 旧id是否存在
    select count(*) into @count from Reader where rid = oldID;
    if @count = 0 then
        select "error";
        LEAVE end_lable;
    end if;

    start transaction;
    update Borrow set Reader_ID = newID where Reader_ID = oldID;
    update Reserve set Reader_ID = newID where Reader_ID = oldID;
    update Reader set rid = newID where rid = oldID;
    commit;
    Alter Table Borrow Add constraint FK_reader Foreign key (reader_id) references Reader(rid);
    SET SQL_SAFE_UPDATES = 1;
end;
//
delimiter ;

select *from reader;
select *from borrow;
select *from reserve;
call updateReaderID('R006','R999');
call updateReaderID('R999','R006');