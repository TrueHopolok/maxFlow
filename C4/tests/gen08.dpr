var
    i, n: longint;

begin
    n := 200 div 3;
    writeln(n * 3, ' ', n * 3);
    randseed := 234589;
    for i := 1 to n do
    begin
        writeln(3 * i - 2, ' ', 3 * i - 1, ' ', i - random(i), ' ', i + random(n));
        writeln(3 * i - 1, ' ', 3 * i, ' ', i - random(i), ' ', i + random(n));
        writeln(3 * i, ' ', 3 * i - 2, ' ', i - random(i), ' ', i + random(n));
    end;
end.