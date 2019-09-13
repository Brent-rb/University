
;--------------------------------------------------
; Algemene hulpfuncties

(define first
    (lambda (l)
        (car l)
    )
)

(define second
    (lambda (l)
        (car (cdr l))
    )
)

(define makepair
    (lambda (x y)
        (cons x (cons y '()))
    )
)

;--------------------------------------------------
; frequency

(define frequency
    (lambda (l col)
        (makepairs l col)
    )
)

; Hulpfunctie 'makepairs': zet een lijst 'l' van letters om naar
; een lijst van paren (x a), met x de frequentie van letter a
; in de lijst 'l'.
; Deze functie krijgt een collector 'col' mee die op het einde wordt
; opgeroepen met de lijst van paren (x a). De output van 'makepairs'
; is dan de output die de collector geeft.
(define makepairs
    (lambda (l col)
        (cond
            ( (null? l) (col '()) )
            ( else
                (makepairs (cdr l)
                            (lambda (pairs)
                                ; (car l) is een letter. Daar gaan we de frequentie
                                ; van verhogen in 'pairs' -> geeft nieuwe
                                ; pairs die we doorgeven aan de collector.
                                (col (increment (car l) pairs))
                            )
                )
            )
        )
    )
)

; De hulpfunctie 'increment' verhoogt de frequentie
; van een letter in een lijst van paren (x a).
(define increment
    (lambda (letter pairs)
        (cond
            ( (null? pairs) 
                ; Letter komt nog niet voor in pairs: nieuw pair
                ; aanmaken.
                (cons (makepair 1 letter) '() )
            )
            ( (eq? letter (second (car pairs)))
                ; Dan komt letter wel voor -> verhoog frequentie
                (cons (makepair (+ 1 (first (car pairs)))
                                letter)
                      (cdr pairs)
                )
            )
            (else 
                ; verder zoeken
                (cons (car pairs)
                      (increment letter (cdr pairs))
                )
            )
        )
    )
)


;- - - - - - - - - - - - - - - - - - - - - - - - - - -  - -
; Hier volgen de collector-definities. De collectors
; max-finder en min-finder krijgen een lijst van paren (x a) mee,
; waarbij x de frequentie is van a.

; Max-finder

(define max-finder
    (lambda (pairs)
        (cons pairs              
              (cons (vind-max pairs (lambda (maximum) maximum))
                    '()
              )
        )
    )
)

; Hulpfunctie vind-max roept de collector-parameter 'col' op het
; einde aan met het pair (x a) in 'pairs' waarbij x de grootste frequentie
; is. De output van vind-max is dan de output die de collector geeft.
(define vind-max
    (lambda (pairs col)
        (cond 
            ( (null? pairs) (col '()) ) ; in het basisgeval geven we een ongeldig pair
            ( else
                (vind-max (cdr pairs)
                          (lambda (pair)
                            (cond            
                                ; Als we nog geen geldig pair hebben -> dan 
                                ; gebruiken we (car pairs)
                                ( (null? pair) (col (car pairs)) )
                                
                                ; Als (car pairs) een hogere frequentie heeft ->
                                ; dan gebruiken we (car pairs)
                                ( (> (first (car pairs))
                                     (first pair))
                                    (col (car pairs))
                                )
                                
                                ; Anders behouden we het tot zover gevonden
                                ; pair.
                                (else 
                                    (col pair))
                            )
                          )
                )
            )
        )
    )
)

; Min-finder

(define min-finder
    (lambda (pairs)
        (cons pairs              
              (cons (vind-min pairs (lambda (minimum) minimum))
                    '()
              )
        )
    )
)

; Hulpfunctie vind-min roept de collector-parameter 'col' op het
; einde aan met het pair (x a) in 'pairs' waarbij x de kleinste frequentie
; is.
(define vind-min
    (lambda (pairs col)
        (cond 
            ( (null? pairs) (col '()) ) ; in het basisgeval geven we een ongeldig pair
            ( else
                (vind-min (cdr pairs)
                          (lambda (pair)
                            (cond            
                                ; Als we nog geen geldig pair hebben -> dan 
                                ; gebruiken we (car pairs)
                                ( (null? pair) (col (car pairs)) )
                                
                                ; Als (car pairs) een lagere frequentie heeft ->
                                ; dan gebruiken we (car pairs)
                                ( (< (first (car pairs))
                                     (first pair))
                                    (col (first pairs))
                                )
                                
                                ; Anders behouden we het tot zover gevonden
                                ; pair.
                                (else 
                                    (col pair))
                            )
                          )
                )
            )
        )
    )
)

;-----------------------------------------------------------
; special-counter

(define special-counter
    (lambda (l g)
        (hulp l g (lambda (som prod) 
                    (makepair som prod)))
    )
)

; De hulpfunctie krijgt de extra collector parameter mee. De collector
; wordt op het einde opgeroepen met twee parameters: (1) de som van de
; getallen in l en (2) het product van alle getallen in l kleiner dan g.
(define hulp
    (lambda (l g col)
      (cond
        ( (null? l) (col 0 1) )
        ( else
            (hulp (cdr l) g
                  (lambda (som prod)
                    (cond 
                        ; Afhankelijk van hoe (car l) zich verhoudt
                        ; tot g, zullen we een ander product doorgeven aan
                        ; de collector.
                        ( (< (car l) g)
                            (col (+ som (car l))
                                 (* prod (car l))
                            )
                        )
                        ( else
                            (col (+ som (car l))
                                 prod ; product ongewijzigd
                            )
                        )
                    )
                 )                 
            )
        )
      )
   )
)
            