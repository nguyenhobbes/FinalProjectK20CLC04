# FinalProjectK20CLC04
Courses Management System

Group 09
University of Science HCMC

Nguyen Vu Nham Nguyen (Leader), ID: 20127262
          
Nguyen Thi Hao Trinh, ID: 20127367 

Thai Cam Phong, ID: 20127406

Nguyen Thien Phu, ID: 20127594

................................................

Setting.csv file: To setting the start date and end date of school year and semester
Note: The default year is the current year
Example:
Time,Start,End
School year,01/08,14/08
Semester 1,15/08,20/08
Semester 2,01/02,05/02
Semester 3,20/05,25/05

................................................

After add new student to class, the student account will be created and have the format "StudentID/1" (username/password)
!! File format of

Classes.csv:
schoolYear1,numOfClass
className,no,studentID,lastname,firstname,gender,dob,socialID,.....
Example:
2020-2021,1
20CLC1,1,20127406,Phong,Thai Cam,Male,1/1/2002,079123456789,2,20123456,A,B C,Male,1/2/2002,079123987654
2021-2022,0

Accounts.csv:
username,password,type

Semester.csv:
semester,schoolyear // data of the selected semester
semester,schoolyear,startData,endDate,startRegDate,endRegDate,numOfCourse
id,name,teacher,credit,maxStudents,days,session1,session2,...,enrolled
Example:
1,2020-2021
1,2020-2021,01/09/2020,01/12/2020,25/08/2020,30/08/2020,1
CSC10002,KTLT,Dinh Ba Tien,4,50,3,WED S1,THU S1,SAT S3,0

StudentData.csv: to save the course that student enrolled
studentID,numOfCourse,id1,name,teacher,credit,maxStudents,days,session1,session2,...,id2,....
20127406,1,CSC10002,KTLT,Dinh Ba Tien,4,50,3,WED S1,THU S1,SAT S3
................................................

Teacher:

Do Nguyen Kha

Truong Phuoc Loc

Dinh Ba Tien

