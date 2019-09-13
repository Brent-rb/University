-- Studentnummer: 1334252
-- Studierichting: Informatica
SELECT titel
FROM Evenement JOIN ((
	SELECT evenement
	FROM Label
	WHERE label = 'festival')

	INTERSECT

	(SELECT evenement
	FROM Label
	WHERE label = 'literatuur')
) AS x ON Evenement.id = x.evenement
ORDER BY titel;