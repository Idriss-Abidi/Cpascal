program test;
const toto1 = 10.5 ; toto2 = 555 ;
var  k:integer, tab:array[3] of integer, x:integer,i: integer, 
tab2:array[3] of float, y:float, z:float;
Begin
k:=0;
tab2[0]:=toto1;
tab2[1]:=toto2;
tab2[2]:=1;
write(tab2[0],tab2[1],tab2[2]);
z:=tab2[0]+tab2[1];
write(z);

write(111111111);

tab[0]:=10;
tab[1]:=20;
tab[2]:=30;
write(tab[0],tab[1],tab[2]);
k:=tab[0]+tab[1]+tab[2];
write(k)
end.