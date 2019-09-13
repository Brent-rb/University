member(H, [H | T]) :- !.
member(X, [H | T]) :-
	member(X, T).

doorsnede([], _, []) :- !.

doorsnede([H | T], V2, V3) :-
	member(H, V2),
	doorsnede(T, V2, V4),
	V3 = [H | V4], !.

doorsnede([H | T], V2, V3) :-
	doorsnede(T, V2, V3).

unie([], V2, V2):- !.

unie([H | T], V2, V3) :-
	member(H, V2),
	unie(T, V2, V3), !.

unie([H | T], V2, V3) :-
	unie(T, V2, V4),
	V3 = [H | V4].
	




to_words(0) :-
	write('nul').

to_words(1) :-
	write('een').

to_words(2) :-
	write('twee').

to_words(3) :-
	write('drie').

to_words(4) :-
	write('vier').

to_words(5) :-
	write('vijf').

to_words(6) :-
	write('zes').

to_words(7) :-
	write('zeven').

to_words(8) :-
	write('acht').

to_words(9) :-
	write('negen').

to_words(X) :-
	Y is X mod 10,
	Z is X // 10,
	to_words(Z),
	write('-'),
	to_words(Y).

name(sartre).
name(calvino).
name(joyce).
female(murdoc).
female(bembridge).

female_author :- 
	author(X), 
	write(X), 
	write('is an author'),
	nl, 
	female(X), 
	write('' and female'), 
	nl.

female_author :- write('no such luck'), nl.

author(X) :- name(X), !.

author(_) :- write('no more found'), nl, fail.