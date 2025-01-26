program test;
var x: integer, y:integer;
begin
   for x:=0 into 5 do  
	  write(x);


   for x:=3 downto 1 do  
	  write(x);

   y:=0;
   for x:=0 into 3 do
   begin
   y:=y+2;
   write(y);
   end
end.


