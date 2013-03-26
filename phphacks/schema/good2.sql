DROP TABLE IF EXISTS author;
CREATE TABLE author (
	id INT NOT NULL AUTO_INCREMENT,
	name TEXT,
	PRIMARY KEY( id )
	);

DROP TABLE IF EXISTS book;
CREATE TABLE book (
	id INT NOT NULL AUTO_INCREMENT,
	name TEXT,
	PRIMARY KEY( id )
	);

DROP TABLE IF EXISTS book_author;
CREATE TABLE book_author (
	book_id INT,
	author_id INT
	);

INSERT INTO author VALUES ( 0, "Brad Phillips" );
INSERT INTO author VALUES ( 0, "Don Charles" );
INSERT INTO author VALUES ( 0, "Brad silver" );
INSERT INTO book VALUES ( 0, "MySQL in a bucket" );
INSERT INTO book VALUES ( 0, "Databases for Delinquents" );
INSERT INTO book_author VALUES ( 1, 1 );
INSERT INTO book_author VALUES ( 1, 2 );
INSERT INTO book_author VALUES ( 2, 3 );

SELECT 
	a.name AS author,
	b.name AS book,
	a.id AS author_id,
	b.name AS book_id
FROM
	author AS a,
	book AS b,
	book_author AS ba
WHERE
	a.id = ba.author_id AND
	b.id = ba.book_id;

SELECT 
	a.name AS author,
	b.name AS book,
	a.id AS author_id,
	b.name AS book_id
FROM
	author AS a,
	book AS b,
	book_author AS ba
WHERE
	a.id = ba.author_id AND
	b.id = ba.book_id AND
	ba.book_id = 1;
