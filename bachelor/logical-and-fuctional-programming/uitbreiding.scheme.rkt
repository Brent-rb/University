(define knightsTour
  (lambda (n startPos)
    (knightsTour_inner (setCell (getX startPos) (getY startPos) 1 (generateMatrix n n)) n 1 startPos)))

(define getX
  (lambda (tupple)
    (car tupple)))

(define getY
  (lambda (tupple)
    (car (cdr tupple))))

(define generateMatrix
  (lambda (rows columns)
    (generateMatrix_inner rows columns '())))

(define generateMatrix_inner
  (lambda (rows columns matrix)
    (cond
      ((zero? rows) matrix)
      (else (generateMatrix_inner (- rows 1) columns (cons (generateRow columns '()) matrix))))))
     
(define generateRow
  (lambda (columns curRow)
    (cond
      ((zero? columns) curRow)
      (else (generateRow (- columns 1) (cons '0 curRow))))))
    
(define getCell
  (lambda (row column matrix)
    (cond
      ((zero? row) (getColumn column (car matrix)))
      (else (getCell (- row 1) column (cdr matrix))))))

(define getColumn
  (lambda (column row)
    (cond
      ((zero? column) (car row))
      (else (getColumn (- column 1) (cdr row))))))

(define visited
  (lambda (row column matrix)
    (not (eq? (getCell row column matrix) 0))))

(define canVisit
  (lambda (row column n matrix)
    (and (inRange row column n) (zero? (getCell row column matrix)))))

(define inRange
  (lambda (row column n)
    (and (and (and (< row n) (>= row 0)) (< column n)) (>= column 0))))

(define setCell
  (lambda (row column element matrix)
    (cond
      ((zero? row) (cons (setColumn column element (car matrix)) (cdr matrix)))
      (else (cons (car matrix) (setCell (- row 1) column element (cdr matrix)))))))

(define setColumn
  (lambda (column  element row)
    (cond
      ((zero? column) (cons element (cdr row)))
      (else (cons (car row) (setColumn (- column 1) element (cdr row)))))))

(define addMove
  (lambda (x y move)
    (cons (+ (getX move) x) (cons (+ (getY move) y) '()))))

(define testResult
  (lambda (result)
    (not (eq? result #f))))

(define knightsTour_inner
  (lambda (matrix n index lastMove)
    (cond
      ((= (* n n) index) matrix)
      (else
       (local
         ((define tryMove1
            (cond
              ((canVisit (+ (getX lastMove) 1) (+ (getY lastMove) 2) n matrix) (knightsTour_inner (setCell (+ (getX lastMove) 1) (+ (getY lastMove) 2) (+ index 1) matrix) n (+ index 1) (addMove 1 2 lastMove)))
              (else #f)))
         (define tryMove2
            (cond
              ((canVisit (+ (getX lastMove) 1) (- (getY lastMove) 2) n matrix) (knightsTour_inner (setCell (+ (getX lastMove) 1) (- (getY lastMove) 2) (+ index 1) matrix) n (+ index 1) (addMove 1 -2 lastMove)))
              (else #f)))
         (define tryMove3
           (cond
             ((canVisit (+ (getX lastMove) 2) (+ (getY lastMove) 1) n matrix) (knightsTour_inner (setCell (+ (getX lastMove) 2) (+ (getY lastMove) 1) (+ index 1) matrix) n (+ index 1) (addMove 2 1 lastMove)))
             (else #f)))
         (define tryMove4
           (cond
             ((canVisit (+ (getX lastMove) 2) (- (getY lastMove) 1) n matrix) (knightsTour_inner (setCell (+ (getX lastMove) 2) (- (getY lastMove) 1) (+ index 1) matrix) n (+ index 1) (addMove 2 -1 lastMove)))
             (else #f)))
         (define tryMove5
           (cond
             ((canVisit (- (getX lastMove) 1) (+ (getY lastMove) 2) n matrix) (knightsTour_inner (setCell (- (getX lastMove) 1) (+ (getY lastMove) 2) (+ index 1) matrix) n (+ index 1) (addMove -1 2 lastMove)))
             (else #f)))
         (define tryMove6
           (cond
             ((canVisit (- (getX lastMove) 1) (- (getY lastMove) 2) n matrix) (knightsTour_inner (setCell (- (getX lastMove) 1) (- (getY lastMove) 2) (+ index 1) matrix) n (+ index 1) (addMove -1 -2 lastMove)))
             (else #f)))
         (define tryMove7
           (cond
             ((canVisit (- (getX lastMove) 2) (- (getY lastMove) 1) n matrix) (knightsTour_inner (setCell (- (getX lastMove) 2) (- (getY lastMove) 1) (+ index 1) matrix) n (+ index 1) (addMove -2 -1 lastMove)))
             (else #f)))
         (define tryMove8
           (cond
             ((canVisit (- (getX lastMove) 2) (+ (getY lastMove) 1) n matrix) (knightsTour_inner (setCell (- (getX lastMove) 2) (+ (getY lastMove) 1) (+ index 1) matrix) n (+ index 1) (addMove -2 1 lastMove)))
             (else #f))))
         
         (cond
           ((testResult tryMove1) tryMove1)
           ((testResult tryMove2) tryMove2)
           ((testResult tryMove3) tryMove3)
           ((testResult tryMove4) tryMove4)
           ((testResult tryMove5) tryMove5)
           ((testResult tryMove6) tryMove6)
           ((testResult tryMove7) tryMove7)
           ((testResult tryMove8) tryMove8)
           (else #f)))))))
            

(define cond-lines-of cdr)

            
              
            
              