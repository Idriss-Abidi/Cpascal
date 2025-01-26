program test;
var x: integer, y: integer;
begin
   x:=0; y:=0;
   read(x);
case x of 
   1: read(x,y)
   2: begin x:=1 ; y:=2 end
   3: y:=x
   else write(4444)
end;
write(x,y)
end.