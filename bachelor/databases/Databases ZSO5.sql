a)
INSERT INTO Classes VALUES ('Nelson', 'bb', 'Gt. Britain', 9, 16, 34000);
INSERT INTO Ships VALUES 
('Nelson', 'Nelson', 1927),
('Rodney', 'Nelson', 1927);

b)
INSERT INTO Classes VALUES ('Vittorio Veneto', 'bb', 'Italy', 9, 15, 41000);
INSERT INTO Ships VALUES
	('Vittorio Veneto', 'Vittorio Veneto', 1940),
	('Italia', 'Vittorio Veneto', 1940),
	('Roma', 'Vittorio Veneto', 1942);

c)
DELETE FROM Classes 
WHERE class IN (
	SELECT class
	FROM Ships
	GROUP BY class
	HAVING count(name) < 3

	OR class IN(
	SELECT class
	FROM Ships)); --> Niet in lijst ook verwijdere


d)
DELETE FROM Ships
WHERE name IN (
	SELECT ship
	FROM Outcomes
	WHERE result = 'sunk');

e)
UPDATE Classes
SET bore = bore * 2.5, displacement = displacement * 1.1;


7.1.1)
a) 
ALTER TABLE Movies
ADD PRIMARY KEY (producerC);
ALTER TABLE MovieExec
ADD PRIMARY KEY (cert);


ALTER TABLE Movies
ADD FOREIGN KEY (producerC) REFERENCES MovieExec(cert);

b)

ALTER TABLE Movies
ADD FOREIGN KEY (producerC) REFERENCES MovieExec(cert)
	ON DELETE cascade
	ON UPDATE cascade
;

c)
ALTER TABLE Movies
ADD FOREIGN KEY (producerC) REFERENCES MovieExec(cert)
	ON DELETE SET NULL
	ON UPDATE SET NULL
;

d)

ALTER TABLE StarsIn 
ADD PRIMARY KEY (movieTitle, movieYear, starName);

ALTER TABLE MovieStar
ADD PRIMARY KEY (name);

DELETE FROM StarsIn
WHERE starName NOT IN (
	SELECT name
	FROM MovieStar);

ALTER TABLE StarsIn
ADD FOREIGN KEY (starName) REFERENCES MovieStar(name)
	ON DELETE cascade
	ON UPDATE cascade;

e)
ALTER TABLE Movies 
ADD PRIMARY KEY (title);

DELETE FROM StarsIn
WHERE movieTitle NOT IN (
	SELECT title
	FROM Movies);

ALTER TABLE StarsIn
ADD FOREIGN KEY (movieTitle, movieYear) REFERENCES Movies(title, year);


7.1.3)
ALTER TABLE Classes 
ADD PRIMARY KEY (class);
ALTER TABLE Ships
ADD PRIMARY KEY (name, class, launched);
ALTER TABLE Battles
ADD PRIMARY KEY (name);
ALTER TABLE Outcomes
ADD PRIMARY KEY (ship, battle);


7.1.5)

a)
DELETE FROM Outcomes
WHERE battle NOT IN (
	SELECT name
	FROM Battles);

ALTER TABLE Outcomes
ADD FOREIGN KEY (battle) REFERENCES Battles(name)
	ON DELETE SET NULL
	ON UPDATE SET NULL;

b)
DELETE FROM Outcomes
WHERE ship NOT IN (
	SELECT name
	FROM Ships);

ALTER TABLE Outcomes
ADD FOREIGN KEY (ship) REFERENCES Ships(name)
	ON DELETE SET NULL
	ON UPDATE SET NULL;

c)
DELETE FROM Ships
WHERE class NOT IN (
	SELECT class
	FROM Classes);

ALTER TABLE Ships
ADD FOREIGN KEY (class) REFERENCES Classes(class)
 	ON DELETE SET NULL
 	ON UPDATE SET NULL;

7.2.1)
a)
ALTER TABLE Movies ADD CONSTRAINT lenghtLimit
	CHECK (length < 500 AND length > 30);

b)
ALTER TABLE Movies ADD CONSTRAINT yearLimit
	CHECK (year >= 1909);

c)
ALTER TABLE Movies ADD CONSTRAINT genreLimit
	CHECK (genre = 'drama' OR genre = 'comedy' OR genre = 'sciFi' OR genre = 'teen');

7.2.3)

ALTER TABLE StarsIn ADD CONSTRAINT yearLimit
	CHECK (EXTRACT( year FROM (SELECT birthdate 
		FROM MovieStar
		WHERE starName = name)) < movieYear);

ALTER TABLE MovieStar ADD CONSTRAINT yearLimit
	CHECK (EXTRACT(year FROM birthdate) < ALL (SELECT movieYear
		FROM StarsIn 
		WHERE name = starName)
	);

b)
ALTER TABLE Studio  ADD CONSTRAINT swegk
	CHECK (name IN (
		SELECT studioName
		FROM Movies));

ALTER TABLE Movies ADD CONSTRAINT swegk
	Check (studioName IN (
		SELECT name
		FROM Studio));

c)
ALTER TABLE MovieExec  ADD CONSTRAINT swegk
	CHECK (adress NOT IN (
		SELECT adress
		FROM MovieExec));

d)
ALTER TABLE MovieExec ADD CONSTRAINT richPplStuff
	CHECK (name NOT IN (
		SELECT name
		FROM MovieStar));

ALTER TABLE MovieStar ADD CONSTRAINT richPplStuff
	CHECK (name NOT IN (
		SELECT name
		FROM MovieExec));

e)

ALTER TABLE Movies ADD CONSTRAINT Stuff
	CHECK (producerC NOT IN (
		SELECT presC
		FROM Studio
		)

		OR 

		studioName IN (
			SELECT name
			FROM Studio
			WHERE presC = producerC)
		)
	);



7.3.1)
ALTER TABLE StarsIn
DROP PRIMARY KEY
ADD PRIMARY KEY (movieTitle, movieYear, starName);

ALTER TABLE Studio
ADD FOREIGN KEY (presC) REFERENCES MovieExec(cert);