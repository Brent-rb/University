ouder(X, Y) :-
    vader(X, Y);
    moeder(X, Y).

zoon(X, Y) :-
    ouder(Y, X),
    man(X).

dochter(X, Y) :-
    ouder(Y, X),
    vrouw(X).

isvader(X) :-
    vader(X, Y).

ismoeder(X) :-
    moeder(X, Y).

broer(X, Y) :-
    ouder(Z, X),
    ouder(Z, Y),
    man(X),
    different(X, Y).

broer_no_stiefbroer(X, Y) :-
    zoon(X, V), zoon(X, N),
    ouder(V, Y), ouder(N, Y),
    different(X, Y), man(V), vrouw(N).

zus(X, Y) :-
    ouder(Z, X),
    ouder(Z, Y),
    vrouw(X),
    different(X, Y).

oom(X, Y) :-
    ouder(Z, Y),
    broer(X, Z).

tante(X, Y) :-
    ouder(Z, Y),
    zus(X, Z).

grootvader(X, Y) :-
    ouder(Z, Y),
    vader(X, Z).

grootmoeder(x, Y) :-
    ouder(Z, Y),
    moeder(X, Z).

heeftkind(X) :-
    ouder(X, Y).

heefttweekinderen(X) :-
    ouder(X, Y),
    ouder(X, Z),
    different(Z, Y).
