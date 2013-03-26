DROP TABLE IF EXISTS author;
CREATE TABLE author (
	id INT,
	name TEXT
	);

DROP TABLE IF EXISTS book;
CREATE TABLE book (
	id INT,
	name TEXT,
	authors TEXT
	);

INSERT INTO author VALUES ( 1, "Brad Phillips" );
INSERT INTO author VALUES ( 2, "Don Charles" );
INSERT INTO author VALUES ( 3, "Brad silver" );
INSERT INTO book VALUES ( 1, "MySQL in a bucket", "1,2" );
INSERT INTO book VALUES ( 2, "Databases for Delinquents", "3" );
