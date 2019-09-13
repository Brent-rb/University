
(define rle
  (lambda (list)
    (rle_inner (cdr list) (makeNewTupple (car list)))))

(define rle_inner
  (lambda (l last)
    (cond
      ((null? l) (cons last '()))
      ((eq? (car l) (getLetter last)) (rle_inner (cdr l) (add1ToTupple last)))
      (else (cons last (rle_inner (cdr l) (makeNewTupple (car l))))))))
        
(define getLetter
  (lambda (tupple)
    (car (cdr tupple))))

(define getNumber
  (lambda (tupple)
    (car tupple)))

(define makeNewTupple
  (lambda (letter)
    (cons '1 (cons letter '()))))

(define add1ToTupple
  (lambda (tupple)
    (cons (add1 (getNumber tupple)) (cons (getLetter tupple) '()))))

(define add1
  (lambda (number)
    (+ number 1)))

(define splitter
  (lambda (list)
    (splitter_inner list splitter_col)))

(define splitter_inner
  (lambda (list col)
    (cond
      ((null? list) (col '() '() 0 0))
      (else (splitter_inner (cdr list) (lambda (zList oList zCount oCount)
                                   (cond
                                     ((eq? (car list) 0) (col (cons '0 zList) oList (add1 zCount) oCount))
                                     (else (col zList (cons '1 oList) zCount (add1 oCount))))))))))

(define splitter_col
  (lambda (zList oList zCount oCount)
    (cons zList (cons oList (cons zCount (cons oCount '()))))))