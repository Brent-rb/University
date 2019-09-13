human(jim).
human(fred).

aeroplane(boeing).
aeroplane(airbus).

on(jim, bike).
on(jim, airbus).
on(fred, boeing).

bird(percy).

animal(leo).
animal(tweety).
animal(peter).

has-feathers(tweety).
has-feathers(peter).

flies(X) :-
    bird(X).

flies(X) :-
    aeroplane(X).

flies(X) :-
    human(X),
    on(X,Y),
    aeroplane(Y).

bird(X) :-
    animal(X),
    has-feathers(X).

/*
flies(X)
    bird(X) %X = percy
    yes

flies(X)
    human(X)
    %X = jim
        on(jim, Y)
        %Y = bike
            aeroplane(bike)
            fyes
        %Y = airbus
            aeroplane(airbus)
            yes
                => jim
    %X = fred
        on(fred, Y)
        %Y = boeing
            aeroplane(boeing)
            yes
                => fred
*/
