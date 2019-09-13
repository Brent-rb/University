CREATE TABLE Customers (
	ssno INTEGER PRIMARY KEY,
	name VARCHAR(50) NOT NULL,
	addr VARCHAR(100),
	phone VARCHAR(50)
);

CREATE TABLE Flights (
	number INTEGER,
	day INTEGER,
	aircraft VARCHAR(50),
	CONSTRAINT pk_flights PRIMARY KEY(number, day)
);

CREATE TABLE Bookings (
	row INTEGER,
	seat INTEGER,
	c_id INTEGER REFERENCES Customers(ssno),
	f_id INTEGER,
	f_day INTEGER,
	CONSTRAINT fk_bookings FOREIGN KEY (f_id, f_day) REFERENCES Flights(number, day)
);