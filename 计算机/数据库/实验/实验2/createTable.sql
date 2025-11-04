DROP DATABASE if  EXISTS schooldb;
CREATE DATABASE SchoolDB;
use mysql; # 选择数据库mysql
update user set plugin='mysql_native_password'; # 修改加密方式


USE SchoolDB;



CREATE TABLE Department (
    DepartmentID INT PRIMARY KEY,
    DepartmentName VARCHAR(100) NOT NULL
);

CREATE TABLE Major (
    MajorID INT PRIMARY KEY,
    MajorName VARCHAR(100) NOT NULL,
    DepartmentID INT,
    FOREIGN KEY (DepartmentID) REFERENCES Department(DepartmentID)
);
DROP TABLE if  EXISTS student;
CREATE TABLE Student (
    StudentID INT PRIMARY KEY,
    Name VARCHAR(100) NOT NULL,
    Gender VARCHAR(10),
    BirthDate DATE,
    Hometown VARCHAR(100),
    Ethnicity VARCHAR(50),
    MajorID INT,
    Photo LONGBLOB,
    FOREIGN KEY (MajorID) REFERENCES Major(MajorID)
);

CREATE TABLE MajorChange (
    ChangeID INT PRIMARY KEY AUTO_INCREMENT,
    StudentID INT,
    OldMajorID INT,
    NewMajorID INT,
    ChangeDate DATE,
    ApplicationStatus VARCHAR(50),
    FOREIGN KEY (StudentID) REFERENCES Student(StudentID),
    FOREIGN KEY (OldMajorID) REFERENCES Major(MajorID),
    FOREIGN KEY (NewMajorID) REFERENCES Major(MajorID)
);

CREATE TABLE RewardPunishment (
    RecordID INT PRIMARY KEY AUTO_INCREMENT,
    StudentID INT,
    Type VARCHAR(50),
    Description TEXT,
    Date DATE,
    DepartmentID INT,
    FOREIGN KEY (StudentID) REFERENCES Student(StudentID),
    FOREIGN KEY (DepartmentID) REFERENCES Department(DepartmentID)
);

CREATE TABLE Course (
    CourseID INT PRIMARY KEY,
    CourseName VARCHAR(100) NOT NULL,
    Credits INT,
    Hours INT
);
CREATE TABLE Grades (
    student_id INT,
    course_id INT,
    grade DECIMAL(5, 2),
    PRIMARY KEY (student_id, course_id),
    FOREIGN KEY (student_id) REFERENCES Student(studentid),
    FOREIGN KEY (course_id) REFERENCES Course(courseid)
);

CREATE TABLE CourseEnrollment (
    EnrollmentID INT PRIMARY KEY AUTO_INCREMENT,
    StudentID INT,
    CourseID INT,
    Grade VARCHAR(10),
    FOREIGN KEY (StudentID) REFERENCES Student(StudentID),
    FOREIGN KEY (CourseID) REFERENCES Course(CourseID)
);


ALTER TABLE student MODIFY photo LONGBLOB;


SELECT DATABASE()



-- 插入Department数据
INSERT INTO department (DepartmentID,Departmentname) VALUES (1,'计算机系');
INSERT INTO department (DepartmentID,Departmentname) VALUES (2,'数学系');
INSERT INTO Department (DepartmentID, DepartmentName) VALUES (3, '物理系');


-- 插入Major数据
INSERT INTO Major (MajorID, MajorName, DepartmentID) VALUES (1, '计算机', 1);
INSERT INTO Major (MajorID, MajorName, DepartmentID) VALUES (2, '应用物理', 2);
INSERT INTO Major (MajorID, MajorName, DepartmentID) VALUES
(3, '应用数学', 2),
(4, '理论物理', 3);
INSERT INTO Major (MajorID, MajorName, DepartmentID) VALUES (5, '理论数学', 1);
INSERT INTO Major (MajorID, MajorName, DepartmentID) VALUES (6, '信息技术', 1);

-- 插入Student数据
INSERT INTO Student (StudentID, Name, Gender, BirthDate, Hometown, Ethnicity, MajorID, Photo) VALUES
(728, '刘芷辰', '男', '2003-11-22', '湖南', '土家', 2, NULL),
(705, '张朔', '男', '2003-07-30', '河北', '汉', 3, NULL);




-- 插入Course数据
INSERT INTO Course (CourseID, CourseName, Credits, Hours) VALUES
(1, 'Introduction to Programming', 4, 60),
(2, 'Data Structures', 3, 45),
(3, 'Calculus I', 4, 60);
INSERT INTO Course (CourseID, CourseName, Credits, Hours) VALUES
(4, '数据库', 4, 60),
(5, '计算机网络', 3, 45),
(6, '大数据算法', 4, 60);





