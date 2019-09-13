edge(a,b).
edge(b,f).
edge(b,d).
edge(d,e).
edge(a,c).
edge(c,d).
edge(f,g).

pad(X, Y) :-    %PR1
    edge(X, Y).

pad(X, Y) :-    %PR2
    pad(Z, Y),
    edge(X, Z).

/*
pad(b, e)
    Nee volgens PR 1
    PR2:
    edge(b, Z)      %Z = d
    pad(d, e)
    Ja volgens PR1
*/

/*
Vologorde is belangrijk als je zo snel mogelijk 1 resultaat wilt.
Hij gaat linear door de relaties dus als er een correct relatie vanboven staat gaat
deze eerder een goed resultaat vinden en stoppen.
*/

/*
De vologorde van regels ik ook belangrijk, het gaat bepalen of het programma eerst de
laatste edge gaat zoeken dus (X, e) en zo terugwerken naar de begin knoop.
Of het programma zoekt een edge met de eerste knoop en werkt zo naar het einde.
1 van de 2 mogelijkheden kan in een specifieke vologorde sneller resultaten geven.  
*/
