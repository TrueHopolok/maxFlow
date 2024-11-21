uses
    math;
var
    y, i, n, p, q, dq, z: longint;

begin
    n := 200 div 3;
    writeln(n * 3, ' ', n * 6);
    randseed := 234589;
    p := 0;
    q := 10;
    dq := 2;
    z := 10;
    for i := 1 to n do
    begin
        writeln(3 * i - 2, ' ', 3 * i - 1, ' ', i - random(i), ' ', i + p + random(n));
        writeln(3 * i - 1, ' ', 3 * i, ' ', i - random(i), ' ', i + p + random(n));
        writeln(3 * i, ' ', 3 * i - 2, ' ', i - random(i), ' ', i + p + random(n));
    end;
    for i := 1 to n do
    begin
        y := random(q + dq);
        writeln(3 * i - 2, ' ', 3 * (i mod n + 1) - 1, ' ', y, ' ', max(y, q) + random(z));
        y := random(q + dq);
        writeln(3 * i - 1, ' ', 3 * (i mod n + 1), ' ', y, ' ', max(y, q) + random(z));
        y := random(q + dq);
        writeln(3 * i, ' ', 3 * (i mod n + 1) - 2, ' ', y, ' ', max(y, q) + random(z));
    end;
end.