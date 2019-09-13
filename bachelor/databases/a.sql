-- Studentnummer: 1334252
-- Studierichting: Informatica
SELECT titel 
FROM Evenement JOIN InProvincie ON Evenement.postcode = InProvincie.postcode
WHERE provincie = 'Limburg'
ORDER BY titel;