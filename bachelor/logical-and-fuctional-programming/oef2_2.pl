
letter(a).
letter(b).
letter(c).
letter(d).
letter(e).
letter(f).

digit(0).
digit(1).
digit(2).
digit(3).
digit(4).
digit(5).
digit(6).
digit(7).
digit(8).
digit(9).

str(a,b,2,c).
str(b).
str(t,a).
str(a,b,c).
str(1,2,3,4,5).



letter_or_digit(X) :-
    letter(X);
    digit(X).


identifier(L1) :-
    letter(L1).

identifier(L1, L2) :-
    indentifier(L1),
    letter_or_digit(L2).

identifier(L1, L2, L3) :-
    indentifier(L1, L2),
    letter_or_digit(L3).

indentifier(L1, L2, L3, L4) :-
    indentifier(L1, L2, L3),
    letter_or_digit(L4).

indentifier(L1, L2, L3, L4, L5) :-
    indentifier(L1, L2, L3, L4),
    letter_or_digit(L5).

begin_letter(X) :-
