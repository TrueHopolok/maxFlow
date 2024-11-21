uses
    math, sysutils;
var
    l, hl, dhl, i, j, n, p, q, sp, sq: longint;

begin
    n := strtoint(paramstr(1));
    sp := strtoint(paramstr(2));
    sq := strtoint(paramstr(3));
    writeln(n * n, ' ', 2 * n * n);
    randseed := 234589 + n;
    for i := 1 to n do
    begin
        dhl := q + random(sp);
        hl := dhl + random(10000 - sp - dhl);
        for j := 1 to n do
        begin
            p := (i - 1) * n + j;
            q := (i - 1) * n + (j mod n) + 1;
            l := hl + sq - random(dhl + sq);
            writeln(p, ' ', q, ' ', l, ' ', max(l, hl) + random(dhl));
        end;
    end;
    for j := 1 to n do
    begin
        dhl := q + random(sp);
        hl := dhl + random(10000 - sp - dhl);
        for i := 1 to n do
        begin
            p := (i - 1) * n + j;
            q := (i mod n) * n + j;
            l := hl + sq - random(dhl + sq);
            writeln(p, ' ', q, ' ', l, ' ', max(l, hl) + random(dhl));
        end;
    end;
end.