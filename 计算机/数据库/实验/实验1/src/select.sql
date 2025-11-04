-- Active: 1715270697416@@127.0.0.1@3306@itcase
-- (1)
select b.bid, b.bname, w.borrow_Date
from Borrow w
         join Book b on w.book_ID = b.bid
         join Reader r on w.reader_ID = r.rid
where r.rname = 'Rose';

-- (2)
select r.rid, r.rname
from Reader r
where r.rid not in (select reader_ID
                   from Borrow)
  and r.rid not in (select reader_ID
                   from Reserve);
                   
-- (3)
-- 使用book
select au.author 
from 
(select b.author ,SUM(borrow_Times) as tot
from Book b
group by b.author) as au
order by tot desc 
limit 1;

-- 使用borrow
select author
from
(select w.book_ID ,b.author
from borrow w,book b where w.book_ID=b.bid ) as au
group by author 
order by count(author) desc
limit 1;

-- (4)
select b.bid, b.bname
from Book b
where b.bname like '%MySQL%' and b.bstatus=1;

-- (5)
select r.rname
from Reader r
         join Borrow w on w.reader_ID = r.rid
group by r.rid
having count(*) > 3;

-- (6)
select r.rid, r.rname
from Reader r
where r.rid not in 
(select r.rid
from Reader r
join Borrow w on w.reader_ID = r.rid
join Book b on w.book_ID = b.bid
where b.author = 'J.K. Rowling');
                    
-- (7)
select r.rid,r.rname,count(*) as num
from Reader r
         join Borrow w on w.reader_ID = r.rid
where w.borrow_Date like '2024%'
group by r.rid
order by num DESC
limit 3;

-- (8)
create view info as
select r.rid ,r.rname , b.bid , b.bname , w.borrow_Date
from Reader r
         join Borrow w on r.rid = w.reader_ID
         join Book b on b.bid = w.book_ID;
         
desc info;

select rid, count(distinct bid)
from info
where borrow_Date like '2024%'
group by rid;










