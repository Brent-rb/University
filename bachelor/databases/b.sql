-- Studentnummer: 1334252
-- Studierichting: Informatica
SELECT DISTINCT naam
FROM (Gebruiker JOIN Review ON Review.gebruiker = Gebruiker.id JOIN inProvincie ON InProvincie.postcode = Gebruiker.postcode) as x
WHERE (
	SELECT count(*)
	FROM ((
		SELECT evenement
		FROM Review
		WHERE gebruiker = x.id
		)

		EXCEPT

		(
		SELECT id
		FROM Evenement JOIN InProvincie ON Evenement.postcode = InProvincie.postcode
		WHERE provincie = x.provincie
		) 
	) AS y
) = 0
ORDER BY naam;