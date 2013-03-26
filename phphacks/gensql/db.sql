DROP TABLE IF EXISTS book;
CREATE TABLE book (
	id int NOT NULL AUTO_INCREMENT
	,title text
	,publisher_id int
	,author_id int
	,primary key( id )
);
DROP TABLE IF EXISTS publisher;
CREATE TABLE publisher (
	id int NOT NULL AUTO_INCREMENT
	,name text
	,primary key( id )
);
DROP TABLE IF EXISTS author;
CREATE TABLE author (
	id int NOT NULL AUTO_INCREMENT
	,name text
	,primary key( id )
);
