-- Studentnummer: 1334252
-- Studierichting: Informatica
SELECT titel, count(score) AS aantal, avg(score) AS score
FROM Evenement JOIN Review ON Evenement.id = Review.evenement
GROUP BY titel
ORDER BY titel;