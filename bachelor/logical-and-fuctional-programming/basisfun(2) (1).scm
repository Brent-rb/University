
(define atom?
  (lambda (x)
    (and (not (pair? x)) (not (null? x))
    )
  )
)

(define lat?
  (lambda (l)
    (cond
	((null? l) #t)
	((atom? (car l)) (lat? (cdr l)))
	(else #f)
    )
  )
)

(define member?
  (lambda (a lat)
    (cond
      ((null? lat) #f)
      (else (or (eq? (car lat) a) 
                (member? a (cdr lat))
            )
      )
    )
  )
)

(define rember
  (lambda (a lat)
    (cond
      ((null? lat) (quote ()))
      ((eq? (car lat) a) (cdr lat))
      (else (cons (car lat) (rember a (cdr lat))))
    )
  )
)

(define firsts
  (lambda (l)
    (cond
      ((null? l) (quote ()))
      (else (cons (car (car l)) 
                  (firsts (cdr l))
            )
      )
    )
  )
)

(define insertR
  (lambda (adda pat lat)
    (cond
      ((null? lat) (quote ()))
      (else (cond
              ((eq? (car lat) pat) (cons pat (cons adda (cdr lat))))
              (else (cons (car lat) (insertR adda pat (cdr lat))))
            )
      )
    )
  )
)

(define insertL
  (lambda (adda pat lat)
    (cond
      ((null? lat) (quote ()))
      (else (cond
              ((eq? (car lat) pat) (cons adda (cons pat (cdr lat))))
              (else (cons (car lat) (insertL adda pat (cdr lat))))
            )
      )
    )
  )
)

(define add1
  (lambda (n)
    (+ n 1)))

(define sub1
  (lambda (n)
    (- n 1)))