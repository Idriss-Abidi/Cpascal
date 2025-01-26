program test;
var x: integer, b: integer;
begin
   x:=5;

   repeat 
   begin
   if x = 3 then write(200);
   x:=x-1;
   write(x);
   end
   until x=0;
   write(999);
end.
