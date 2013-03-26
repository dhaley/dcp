DROP TABLE IF EXISTS product;
CREATE TABLE product (
	id MEDIUMINT NOT NULL AUTO_INCREMENT,
	name TEXT,
	price FLOAT,
	PRIMARY KEY( id )
);

INSERT INTO product VALUES ( 0, "Code Generation in Action", 49.99 );
INSERT INTO product VALUES ( 0, "Podcasting Hacks", 29.99 );
INSERT INTO product VALUES ( 0, "PHP Hacks", 29.99 );
