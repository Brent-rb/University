6.3.2)
	a)
	SELECT DISTINCT country
	FROM Classes NATURAL JOIN Ships
	WHERE bore >= ALL (	SELECT bore
						FROM Classes NATURAL JOIN Ships );

	SELECT DISTINCT country
	FROM Classes NATURAL JOIN Ships
	WHERE NOT (bore < ANY (	SELECT bore
						FROM Classes NATURAL JOIN Ships ));

	SELECT country
	FROM Classes c1
	WHERE NOT EXISTS (
		SELECT *
		FROM Classes c2
		WHERE c1.bore < c2.bore
	);

	b)
	SELECT name 
	FROM Ships
	WHERE class IN (SELECT class
					FROM Classes
					WHERE numGuns = 9);
	

	SELECT name 
	FROM Ships
	WHERE class = ANY (SELECT class
					FROM Classes
					WHERE numGuns = 9);


	c)
	SELECT battle
	FROM Outcomes
	WHERE ship IN (	SELECT name
					FROM Ships
					WHERE class = 'South Dakota');


	d)
	SELECT DISTINCT class
	FROM Ships
	WHERE name IN (	SELECT ship 
					FROM Outcomes
					WHERE result='sunk');

	e)
	SELECT DISTINCT name
	FROM Ships
	WHERE class IN (SELECT class
					FROM Classes AS x
					WHERE x.bore >= ALL (SELECT y.bore
										FROM Classes AS y
										WHERE y.numGuns = x.numGuns


	SELECT 
	FROM Ships s1, Class c1
	WHERE s1.class = c1.class AND bore >= ALL (
		SELECT 
		FROM Ships s2, Classes c2
		WHERE s2.class = c2.class AND c1.numGuns = c2.numGuns);
6.3.3)
	SELECT title FROM Movies AS Old WHERE year < ANY (SELECT year FROM Movies WHERE title = Old.title );

	SELECT DISTINCT x.title FROM Movies AS x, Movies AS y WHERE x.title = y.title AND x.year < y.year;

6.3.9)

	SELECT *
	FROM Ships JOIN Classes ON Ships.class = Classes.class;


6.4.2)
	g) 
	SELECT x.model, y.model, x.ram, y.ram, x.speed, y.speed
	FROM PC x JOIN PC y ON x.ram = y.ram AND x.speed = y.speed AND x.model < y.model;


	h)
	SELECT DISTINCT maker 
	FROM Product AS x
	WHERE (
		(SELECT count(*)
		FROM Product AS y JOIN PC ON type = 'pc' AND y.model = PC.model
		WHERE speed >= 2.20 AND x.maker = y.maker) +

		(SELECT count(*)
		FROM Product AS y JOIN Laptop ON type = 'laptop' AND y.model = Laptop.model
		WHERE speed >= 2.20 AND x.maker = y.maker)
	) >= 2);



	SCHETS)
	(SELECT p1.maker
	FROM PC pc1, PC pc2, Product p1, Product pc2
	WHERE  pc1.speed >= 2.20 AND pc2.speed >= 2.20 AND pc1.model <> pc2.model AND p1.maker = p2.maker)

	UNION

	(SELECT maker
	FROM Laptop c1, Laptop c2
	WHERE c1.model <> c2.model)

	UNION 

	(SELECT maker
	FROM Laptop, PC)


	SCHETS2)
	
	SELECT maker
	FROM (
		(SELECT maker, model, speed
		FROM PC NATURAL JOIN Product)

		UNION

		(SELECT maker, model, speed
		FROM Laptop NATURAL JOIN Product)
	)
	WHERE speed >= 2.20
	GROUP BY maker
	HAVING count(*) >= 2;


	i)
	SELECT DISTINCT x.maker
	FROM Product x
	WHERE (
		SELECT count(*)
		FROM Product
		WHERE type = 'pc' AND maker = x.maker
		) = 3;
	
	j)	
	SELECT DISTINCT maker
	FROM Product
	WHERE model IN (
		SELECT x.model
		FROM ((SELECT model, speed
				FROM PC)
				UNION
				(SELECT model, speed
				FROM Laptop)) AS x
		WHERE x.speed >= ALL ((SELECT speed 
							FROM PC)
							UNION
							(SELECT speed
							FROM Laptop)));

		
