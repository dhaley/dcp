DROP TABLE IF EXISTS author;
CREATE TABLE author (
	id INT NOT NULL AUTO_INCREMENT,
	name TEXT,
	PRIMARY KEY( id )
	);

SELECT LAST_INSERT_ID();
