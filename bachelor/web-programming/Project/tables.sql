userInfo table:

CREATE TABLE userInfo (
	UserID SERIAL references users(UserID) ON DELETE CASCADE,
	Voornaam varchar NOT NULL,
	Achternaam varchar NOT NULL,
	Leeftijd smallint,
	Straat varchar NOT NULL,
	Stad varchar NOT NULL,
	Postcode varchar(4),
	Email varchar NOT NULL,
	RegDate TIMESTAMP DEFAULT NOW(),
	Avatar VARCHAR
);

Users table:

CREATE TABLE users (
	UserID SERIAL,
	Username varchar NOT NULL PRIMARY KEY,
	Password varchar NOT NULL,
	Salt varchar NOT NULL,
	Rights varchar NOT NULL
);


Event table:

CREATE TABLE event (
	EventID SERIAL PRIMARY KEY NOT NULL,
	StartDate TIMESTAMP NOT NULL,
	EndDate TIMESTAMP NOT NULL,
	Street VARCHAR NOT NULL,
	City VARCHAR NOT NULL,
	Postcode VARCHAR NOT NULL,
	Description VARCHAR NOT NULL,
	Tags VARCHAR,
	RegDate TIMESTAMP DEFAULT NOW(),
	Name VARCHAR NOT NULL,
	Price VARCHAR,
	Views INTEGER DEFAULT 0,
	Website VARCHAR,
	SubID SERIAL REFERENCES subcat(subid),
	Organisator VARCHAR NOT NULL
);

CREATE TABLE eventImages (
	EventID SERIAL REFERENCEs event(EventID),
	ImagePath VARCHAR
);

CREATE TABLE comments (
	CommentID SERIAL PRIMARY KEY,
	EventID SERIAL REFERENCES event(eventid) NOT NULL ON DELETE CASCADE,
	UserID SERIAL REFERENCES users(userid) NOT NULL ON DELETE CASCADE,
	content VARCHAR NOT NULL,
	postdate TIMESTAMP DEFAULT NOW()
);

CREATE TABLE hoofdcat (
	HoofdID SERIAL PRIMARY KEY,
	Name VARCHAR NOT NULL,
	Description VARCHAR
);

CREATE TABLE subcat (
	SubID SERIAL PRIMARY KEY,
	HoofdID SERIAL REFERENCES hoofdcat(HoofdID) ON DELETE CASCADE
);