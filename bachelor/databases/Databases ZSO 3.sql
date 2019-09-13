6.4.4)
	a)
	SELECT DISTINCT c1.country	
	FROM Classes c1, Classes c2
	WHERE c1.bore <= c2.bore
	GROUP BY c1.class, c1.country
	HAVING count(DISTINCT c2.bore) = 1;

	b)
	SELECT DISTINCT name
	FROM Ships JOIN Classes ON Ships.class = Classes.class
	WHERE numGuns = 9;


	c)
	SELECT DISTINCT battle
	FROM Outcomes JOIN Ships ON Ships.name = Outcomes.ship
	WHERE class = 'South Dakota';


	d)
	SELECT DISTINCT class
	FROM Ships JOIN Outcomes ON Ships.name = Outcomes.ship
	WHERE result = 'sunk';

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


6.4.6)
	a)
	SELECT AVG(hd)
	FROM PC;

	b)
	SELECT AVG(price)
	FROM Laptop
	WHERE speed >= 3.0;

	c)
	SELECT AVG(price)
	FROM Product JOIN PC ON Product.model = Pc.model
	WHERE maker = 'A';

	d)
	SELECT AVG(x.price)
	FROM ((SELECT price, maker FROM Product JOIN Pc on Product.model = PC.model) UNION ALL (SELECT price, maker FROM Product JOIN Laptop on Product.model = Laptop.model)) AS x
	WHERE x.maker = 'D';

	e)

	SELECT DISTINCT AVG(pc1.price), pc1.speed
	FROM PC pc1, PC pc2
	WHERE pc1.speed = pc2.speed
	GROUP BY pc1.speed
	ORDER BY pc1.speed;

	f)
	SELECT DISTINCT maker
	FROM Product c1
	WHERE 3 <= (
		SELECT count(model)
		FROM Product c2
		WHERE c1.maker = c2.maker);
	
	SELECT maker
	FROM Product JOIN PC on PC.model = Product.model
	GROUP BY maker
	HAVING count(pc.model) >= 3;

	g)
	SELECT maker, MAX(speed)
	FROM Product JOIN PC ON Product.model = PC.model
	GROUP BY maker;

	h)
	SELECT AVG(hd), speed
	FROM PC
	GROUP BY speed
	HAVING speed > 2.5

	i)

	SELECT maker, AVG(speed)
	FROM Product JOIN Laptop ON Product.model = Laptop.model
	GROUP BY maker;


	j)
	SELECT maker, AVG(hd)
	FROM Product JOIN PC ON Product.model = PC.model
	WHERE maker IN (
		SELECT maker
		FROM Product
		WHERE type = 'laptop') 	
	GROUP BY maker;


6.4.7)
	a)
	SELECT count(class)
	FROM Classes
	WHERE type = 'battle-cruiser'

	b)
	SELECT avg(bore)
	FROM Classes
	WHERE type = 'battle-cruiser';	
	GROUP BY class;

	c)
	SELECT avg(bore)
	FROM Classes
	WHERE type = 'battle-cruiser';

	d)


	