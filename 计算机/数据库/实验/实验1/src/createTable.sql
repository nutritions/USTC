-- Active: 1715270697416@@127.0.0.1@3306@lab1

drop TABLE if EXISTS borrow ;


drop TABLE if EXISTS reserve ;

drop table if EXISTS book ;
drop TABLE if EXISTS reader ;



create table Book
(
    bid            char(8) ,
    bname          varchar(100) not null,
    author        varchar(50),
    price         float,
    bstatus        int default 0 check ( bstatus in (0, 1, 2) ),
    borrow_Times  int default 0,
    reserve_Times int default 0,
    primary key (bid)
);

create table Reader
(
    rid    char(8) primary key,
    rname    varchar(20),
    age     int check ( age >= 0 ),
    address varchar(100)
);

create table Borrow
(
    book_ID     char(8) ,
    reader_ID   char(8) ,
    borrow_Date date,
    return_Date date,
    primary key (book_ID, reader_ID, borrow_Date),
    constraint FK_book foreign key(book_ID) references Book (bid),
    constraint FK_reader foreign key(reader_ID) references reader (rid)
);

create table Reserve
(
    book_ID      char(8) ,
    reader_ID    char(8) ,
    reserve_Date date default (curdate()),
    take_Date    date,
    primary key (book_ID, reader_ID, reserve_Date),
    check ( take_Date >= reserve_Date )
);