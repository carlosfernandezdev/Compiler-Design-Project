program helloworld;
var x, y: integer;
begin
    x := 10;
    y := x + 5;
    for y:=1 to 50 do
    begin  
      x = 2*y;
    end;
    writeln('Hola, mundo'); // Esto es un comentario
end.