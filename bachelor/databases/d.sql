-- Studentnummer: 1334252
-- Studierichting: Informatica
SELECT titel
FROM Evenement
WHERE titel IN (
	SELECT titel 
	FROM Evenement JOIN Review ON Evenement.id = Review.evenement
	GROUP BY titel
	HAVING count(score) >= ALL (
		SELECT count(score)
		FROM Evenement JOIN Review ON Evenement.id = Review.evenement
		GROUP BY titel
	)
)
ORDER BY titel;