-- Studentnummer: 1334252
-- Studierichting: Informatica
SELECT naam
FROM Gebruiker AS x1
WHERE (
	SELECT count(DISTINCT label)
	FROM Review JOIN Gebruiker ON Review.gebruiker = Gebruiker.id JOIN Label ON Review.evenement = Label.evenement
	WHERE naam = x1.naam
) = 1
ORDER BY naam;
