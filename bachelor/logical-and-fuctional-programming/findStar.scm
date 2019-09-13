(define atom?
  (lambda (x)
    (and (not (pair? x)) (not (null? x))
    )
  )
)


(define find*
  (lambda (list col)
    ((subfind* list col) '())))

(define subfind*
  (lambda (list col)
    (cond
      ((null? list) col)
      ((atom? (car list))
              (cond
                ((number? (car list)) (subfind* (cdr list) (lambda (lon) (col (cons (car list) lon)))))
                (else (subfind* (cdr list) col))))
      (else (subfind* (cdr list) (subfind* (car list) col))))))