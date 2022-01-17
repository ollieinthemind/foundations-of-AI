iright(L, R, [L | [R | _]]).
iright(L, R, [_ | Rest]) :- iright(L, R, Rest).
nextto(L, R, List) :- iright(L, R, List).
nextto(L, R, List) :- iright(R, L, List).

malemanager([A,B,C,D,E],List) :- member([A,taylor,C,D,E],List); member([A,ken,C,D,E],List); member([A,phillip,C,D,E],List).

no_dup([[_,A,_,_,_],[_,B,_,_,_],[_,C,_,_,_],[_,D,_,_,_],[_,E,_,_,_],[_,F,_,_,_]]) :- A\==B,A\==C,A\==D,A\==E,A\==F,B\==C,B\==D,B\==E,B\==F,C\==D,C\==E,C\==F,D\==E,D\==F,E\==F.

 
myprogram(Data)  :-    =(Data, [[_,_,_,_,_],[_,_,_,_,_],[_,_,_,_,_],[_,_,_,_,_],[_,_,_,_,_],[_,_,melrose,_,_]]),
member([isaac,kitty,santa_monica,_,_], Data),
iright([aaron,phillip,beverly,_,hot_dogs],[_,taylor,_,psychologist,_],Data),
member([durant,_,hollywood,writer,_],Data),
member([_,ken,sunset,_,_],Data),
malemanager([arthur,_,_,salesman,_], Data),
member([_,rose,_,Y,hamburger],Data), Y\==navy, Y\==historian,
member([bradley,_,_,soccer_player,kebabs],Data),
nextto([aaron,_,_,_,_],[manuel,_,_,_,_],Data),
nextto([manuel,_,_,_,_],[_,_,_,navy,tacos],Data),
member([arthur,_,_,_,bento],Data),
malemanager([_,_,wilshire,_,pasta],Data),
iright([_,_,sunset,_,_],[_,_,_,_,hamburger],Data),
no_dup(Data).