DROP TABLE IF EXISTS media;
CREATE TABLE media (
	id MEDIUMINT NOT NULL AUTO_INCREMENT,
	filename TEXT,
	mime_type TEXT,
	PRIMARY KEY( id )
);
