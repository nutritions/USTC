SET FOREIGN_KEY_CHECKS=0;

-- 管理员表
DROP TABLE IF EXISTS admin_login;
CREATE TABLE admin_login (
  admin_id char(20) NOT NULL,
  admin_pass char(20) DEFAULT NULL,
  PRIMARY KEY (admin_id)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
 
-- 插入管理员数据
INSERT INTO admin_login VALUES ('admin', 'admin');
 



-- 专业表
DROP TABLE IF EXISTS Major;

CREATE TABLE Major (
    MajorID INT PRIMARY KEY,
    MajorName VARCHAR(50) NOT NULL
);
INSERT INTO Major (MajorID, MajorName) VALUES (1, 'CS'), (2, 'Math'), (3, 'English');



-- 学生表
DROP TABLE IF EXISTS student;
CREATE TABLE student (
  id char(20) NOT NULL,
  name char(20) DEFAULT NULL,
  gender char(5) DEFAULT NULL,
  age char(5) DEFAULT NULL,
  MajorID INT,
  grade INT,
  PRIMARY KEY (id),
  FOREIGN KEY (MajorID) REFERENCES Major(MajorID)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
 
-- 插入学生数据
INSERT INTO student (id, name, gender, age, MajorID, grade) VALUES
('728', '小明', '男', '20', 1, 85),
('729', '小红', '女', '21',  2, 78),
('730', '小刚', '男', '19', 1, 90),
('731', '小美', '女', '22', 3, 75),
('732', '小强', '男', '20',  2, 88);

DROP TABLE IF EXISTS student_login;
CREATE TABLE student_login (
  stu_id char(20) NOT NULL,
  stu_pass char(20) DEFAULT NULL,
  PRIMARY KEY (stu_id)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
 
-- 专业变更表
DROP TABLE IF EXISTS MajorChange;
CREATE TABLE MajorChange (
    StudentID char(20) PRIMARY KEY,
    OldMajorID INT,
    NewMajorID INT
);
INSERT INTO student_login (stu_id, stu_pass) VALUES
('728','111111'),
('729', '111111'),
('730', '111111'),
('731', '111111'),
('732', '111111');




DROP TABLE IF EXISTS `t_course`;
CREATE TABLE `t_course` (
  `SNO` char(255) NOT NULL,
  `COURSE` char(255) DEFAULT NULL,
  `CREDIT` char(255) DEFAULT NULL,
  `GRADE` char(255) DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
 
-- ----------------------------
-- Records of t_course
-- ----------------------------
INSERT INTO `t_course` VALUES ('08300205', '程序设计', '4', '88');
INSERT INTO `t_course` VALUES ('08300205', '数据库', '2.5', '90');
INSERT INTO `t_course` VALUES ('08300205', 'python', '5', '92');
INSERT INTO `t_course` VALUES ('08080929', '数据库', '2.5', '85');
INSERT INTO `t_course` VALUES ('09350124', '数据库', '2.5', '92');
INSERT INTO `t_course` VALUES ('09620233', '数据库', '2.5', '80');
INSERT INTO `t_course` VALUES ('09300218', '数据库', '2.5', '78');
INSERT INTO `t_course` VALUES ('09010122', '数据库', '2.5', '87');
INSERT INTO `t_course` VALUES ('08080929', '程序设计', '4', '86');
INSERT INTO `t_course` VALUES ('09010122', '程序设计', '4', '80');
INSERT INTO `t_course` VALUES ('08300516', '程序设计', '4', '76');
 
-- ----------------------------
-- Table structure for `t_st`
-- ----------------------------
DROP TABLE IF EXISTS `t_st`;
CREATE TABLE `t_st` (
  `SNO` char(11) NOT NULL,
  `SNAME` char(255) DEFAULT NULL,
  `SSEX` char(255) DEFAULT NULL,
  `AGE` char(255) DEFAULT NULL,
  `DEPT` char(255) DEFAULT NULL,
  PRIMARY KEY (`SNO`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
 
-- ----------------------------
-- Records of t_st
-- ----------------------------
INSERT INTO `t_st` VALUES ('209044483', '王晨阳', '男', '20', '计204');
