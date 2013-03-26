DROP TABLE IF EXISTS roles;
CREATE TABLE roles (
 id MEDIUMINT NOT NULL AUTO_INCREMENT,
 name TEXT,
 PRIMARY KEY( id )
);

DROP TABLE IF EXISTS users;
CREATE TABLE users (
 id MEDIUMINT NOT NULL AUTO_INCREMENT,
 name TEXT,
 password TEXT,
 PRIMARY KEY( id )
);

DROP TABLE IF EXISTS user_role;
CREATE TABLE user_role (
 user_id MEDIUMINT,
 role_id MEDIUMINT
);

INSERT INTO roles VALUES ( 0, 'user' );
INSERT INTO roles VALUES ( 0, 'manager' );

INSERT INTO users VALUES ( 0, 'jack', MD5( 'toronto' ) );
INSERT INTO users VALUES ( 0, 'megan', MD5( 'seattle' ) );

INSERT INTO user_role VALUES ( 1, 1 );
INSERT INTO user_role VALUES ( 2, 1 );
INSERT INTO user_role VALUES ( 2, 2 );
