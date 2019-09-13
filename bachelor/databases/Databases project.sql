Databases project)

Relaties:

Gebruiker(-id-, naam, geboorteDatum, postcode)
	Deze relatie bevat alle geregistreerde bezoekers van de website. Deze
	mensen mogen evenementen plaatsen op de website en reviews schrijven.

Evenement(-id-, titel, beschrijving, startDatum, eindDatum, organisator, postcode)
	Deze relatie bevat alle evenementen.
	Attribuut organisator verwijst naar attribuut id van relatie Gebruiker.
	Voor elk evenement wordt aangegeven in welke stad of gemeente dit evenement doorgaat, via een postcode. 
	Dit is niet noodzakelijk de postcade van de organisator zelf.

Label(evenement, label)
	Deze relatie houdt voor elk evenement zijn beschrijvnde "labels" bij.
	Bijvoorbeeld, een rondleiding in een museum met schilderijen kan de
	volgende labels krijgen: 'tentoonstelling', 'schilderij', 'kunst'. Eenzelfde
	evenement kan dus meerdere labels hebben, en eenzelfde label kan toegekend
	worden aan meerdere evenementen.
	Attribuut evenement verwijst naar attribuut id van relatie Evenement.

InProvincie(-postcode-, provincie)
	Deze relatie bevat alle geregistreerde bezoekers van de website. Deze
	mensen mogen evenementen plaatsen op de website en reviews schrijven.

Review(-gebruiker, evenement-, tekst, score, datum)
	Deze relatie bevat alle review die gebruikers hebben geschreven over de 
	evenementen.
	Attribuut gebruiker verwijst naar attribuut id van relatie Gebruiker.
	Attribuut evenement verwijst naar attribuut id van relatie Evenement.


Oefeningen)

a)
SELECT titel 
FROM Evenement JOIN InProvincie ON Evenement.postcode = InProvincie.postcode
WHERE provincie = 'Limburg'
ORDER BY titel;

b)
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


c)
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

d)
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


e)
SELECT titel
FROM Evenement, Review
WHERE Evenement.id = Review.evenement AND Review.datum < Evenement.eindDatum
ORDER BY titel;

f)
SELECT naam
FROM Gebruiker AS x1
WHERE (
	SELECT count(DISTINCT label)
	FROM Review JOIN Gebruiker ON Review.gebruiker = Gebruiker.id JOIN Label ON Review.evenement = Label.evenement
	WHERE naam = x1.naam
) = 1
ORDER BY naam;

g)
SELECT titel, count(score) AS aantal, avg(score) AS score
FROM Evenement JOIN Review ON Evenement.id = Review.evenement
GROUP BY titel
ORDER BY titel;