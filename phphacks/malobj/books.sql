DROP TABLE IF EXISTS author;
CREATE TABLE author (
  id MEDIUMINT NOT NULL AUTO_INCREMENT,
  name TEXT,
  PRIMARY KEY( id )
);

INSERT INTO author VALUES ( 0, "jack" );
INSERT INTO author VALUES ( 0, "bob" );
