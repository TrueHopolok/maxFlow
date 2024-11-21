uses
    math, sysutils;
var
    st, s, hl, dhl, r, i, j, n, p, q, sp, sq, dp: longint;
    cur, edges, next: longint;
    l, c: array [1..200, 1..200] of longint;

begin
    n := strtoint(paramstr(1));
    p := strtoint(paramstr(2));
    q := strtoint(paramstr(3));
    dp := strtoint(paramstr(4));

    randseed := n + 237 * p + q + dp * 23947;

    for i := 1 to n do
    begin
        r := random(p + q);
        l[i][i mod n + 1] := r;
        c[i][i mod n + 1] := max(r, p) + random(dp);
    end;

    cur := n + 1;
    for i := 2 to n do  
    begin
        st := random(n) + 1;
        s := st;

        r := random(p + q);
        inc(l[s][s mod n + 1], r);
        inc(c[s][s mod n + 1], max(r, p) + random(dp));

        s := s mod n + 1;
        next := cur;
        for j := 1 to i do
        begin
            r := random(p + q);
            l[s][next] := r;
            c[s][next] := max(r, p) + random(dp);
            s := next;
            inc(cur);
            if j = i - 1 then
                next := st
            else
                next := cur;
        end;
    end;

    dec(cur);
    edges := 0;
    for i := 1 to cur do
        for j := 1 to cur do
            if c[i][j] > 0 then
                inc(edges);
    writeln(cur, ' ', edges);
    for i := 1 to cur do
        for j := 1 to cur do
            if c[i][j] > 0 then
                writeln(i, ' ', j, ' ', l[i][j], ' ', c[i][j]);
end.