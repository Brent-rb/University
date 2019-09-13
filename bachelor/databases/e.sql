-- Studentnummer: 1334252
-- Studierichting: Informatica
SELECT titel
FROM Evenement, Review
WHERE Evenement.id = Review.evenement AND Review.datum < Evenement.eindDatum
ORDER BY titel;