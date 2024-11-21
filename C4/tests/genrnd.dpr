uses                                
    math, sysutils;
var
    l, r: array [1..200, 1..200] of longint;
    u: array [1..200, 1..200] of boolean;
    i, j, k, n, m, p, w, q, t: longint;
    d: array [1..200] of longint;
begin
    n := strtoint(paramstr(1));
    m := strtoint(paramstr(2));
    w := strtoint(paramstr(3));
    p := strtoint(paramstr(4));
    q := strtoint(paramstr(5));
    randseed := 234589 + n + m * 23 + p * q;

    for i := 1 to m do
    begin
        repeat
            j := random(n) + 1;
            k := random(n) + 1;
        until (j <> k) and (not u[j][k]) and (not u[k][j]);
        if d[j] > d[k] then
        begin
            t := j; j := k; k := t;
        end;
        u[j][k] := true;
        l[j][k] := w + random(p);
        r[j][k] := w + p + random(q);
        inc(d[j]);
        dec(d[k]);
    end;

    writeln(n, ' ', m);
    for i := 1 to n do
        for j := 1 to n do
            if r[i][j] > 0 then
                writeln(i, ' ', j, ' ', l[i][j], ' ', r[i][j]);
end.