var
    i, n: longint;

begin
    n := 200 div 3;
    writeln(n * 3, ' ', n * 4);
    randseed := 234589;
    for i := 1 to n do
    begin
        writeln(3 * i - 2, ' ', 3 * i - 1, ' ', 5432 + i - random(i), ' ', 5432 + i + random(n));
        writeln(3 * i - 1, ' ', 3 * i, ' ', 5432 + i - random(i), ' ', 5432 + i + random(n));
        writeln(3 * i, ' ', 3 * i - 2, ' ', 5432 + i - random(i), ' ', 5432 + i + random(n));
    end;
    for i := 1 to n do
    begin
        writeln(3 * i, ' ', 3 * (i mod n + 1), ' ', 9000 + random(4), ' ', 9004 + random(12));
    end;
end.