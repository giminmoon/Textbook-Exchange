drop database if exists textbookexchange;
create database textbookexchange;

use textbookexchange;

create table User (
		userID int(50) primary key auto_increment,
        email varchar(50) not null,
        password varchar(200) not null,
        fname varchar(20) not null,
        lname varchar(30) not null,
        profilepic varchar(100),
        major varchar(30),
        phone varchar(15)
);

insert into User(email, password, fname, lname, profilepic, major, phone)
		values	('gmoon@usc.edu', '$31$16$vi_a5fdTUUBDVTQCCUCvcq00_g2pRTlwjFn3sqO9DOc', 'Gimin', 'Moon', 'images/profile1,jpg', 'Computer Science', '111-111-1111'),
					('chenghon@usc.edu', '$31$16$vi_a5fdTUUBDVTQCCUCvcq00_g2pRTlwjFn3sqO9DOc', 'Hongyu', 'Cheng', 'images/profile1,jpg', 'Computer Science', '111-111-1111'),
                    ('ascruggs@usc.edu', '$31$16$vi_a5fdTUUBDVTQCCUCvcq00_g2pRTlwjFn3sqO9DOc', 'Alicia', 'Scruggs', 'images/profile1,jpg', 'Computer Science', '111-111-1111');
                    
create table Book (
		bookID int(50) primary key auto_increment,
        name varchar(50) not null,
        class varchar(10) not null,
        author varchar(50) not null,
        isbn varchar(20) not null,
        bookimage varchar(100) not null
        
);

insert into Book(name, class, author, isbn, bookimage)
		values	('Intro to Java Programming', 'CSCI201', 'Y. Daniel Liang', 9780133813463, 'images/book.jpg'),
					('Nutrition and You', 'HBIO202', 'Joan Salge Blake', 9780134167541, 'images/book2.jpg'),
                    ('C++ for Everyone', 'CSCI104', 'Cay S. Horstmann', 9780470927137, 'images/book3.jpg'),
                    ('Essential Calculus Early Transcendentals', 'MATH125', 'James Stewart', 9781133112280, 'images/book7.jpg');
                    
                    
create table Listing(
		listingID int(100) primary key auto_increment,
        userID int(50) not null,
        bookID int(50) not null,
        bookcondition varchar(15) not null,
        price int(10) not null,
        foreign key fk1(userID) references User(userID),
        foreign key fk2(bookID) references Book(bookID)
);

insert into Listing(userID, bookID, bookcondition, price)
		values	(1, 1, 'Excellent', 50.0),
					(2, 2, 'Acceptable', 30.0),
                    (3, 3, 'Like New', 50.0);
                    

create table Chat (
		chatID int(50) primary key auto_increment,
        fromuserID int(50) not null,
        touserID int(50) not null,
        message varchar(200) not null,
        foreign key fk1(fromuserID) references User(userID),
        foreign key fk2(touserID) references User(userID)
);

insert into Chat(fromuserID, touserID, message)
		value	(1, 2, 'Hello, World!');