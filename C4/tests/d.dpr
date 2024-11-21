program reactor_cooling;

uses
    math;

const
    maxn = 200;

var
    l, c, f: array [0..maxn + 1, 0..maxn + 1] of longint;
    q: array [0..maxn] of longint;
    h, t: longint;
    u: array [0..maxn + 1] of boolean;
    from, delta: array [0..maxn + 1] of longint;
    a, b: array [1..maxn * maxn] of longint;
    i, j: longint;
    n, m: longint;
    need, flow: longint;

begin
    assign(input, 'cooling.in');
    reset(input);
    assign(output, 'cooling.out');
    rewrite(output);

    read(n, m);
    for i := 1 to m do
    begin
        read(a[i], b[i]);
        read(l[a[i]][b[i]]);
        read(c[a[i]][b[i]]);
    end;

    for i := 1 to n do
    begin
        c[0][i] := 0;
        for j := 1 to n do
            c[0][i] := c[0][i] + l[j][i];
        c[i][n + 1] := 0;
        for j := 1 to n do
            c[i][n + 1] := c[i][n + 1] + l[i][j];
    end;

    need := 0;
    for i := 1 to n do
        for j := 1 to n do
        begin
            need := need + l[i][j];
            c[i][j] := c[i][j] - l[i][j];
        end;

    flow := 0;
    repeat
        h := 0;
        t := 1;
        q[h] := 0;
        fillchar(u, sizeof(u), 0);
        u[0] := true;
        delta[0] := maxlongint;
        while h < t do
        begin
            i := q[h];
            inc(h);
            
            for j := 1 to n + 1 do
                if (not u[j]) and (c[i][j] - f[i][j] > 0) then
                begin
                    q[t] := j;
                    inc(t);
                    delta[j] := min(delta[i], c[i][j] - f[i][j]);
                    u[j] := true;
                    from[j] := i;
                end;
        end;

        if u[n + 1] then
        begin
            flow := flow + delta[n + 1];
            j := n + 1;
            while j <> 0 do
            begin
                inc(f[from[j]][j], delta[n + 1]);
                dec(f[j][from[j]], delta[n + 1]);
                j := from[j];
            end;
        end;
    until not u[n + 1];

    if need = flow then
    begin
        writeln('YES');
        for i := 1 to m do
            writeln(l[a[i]][b[i]]  + f[a[i]][b[i]]);
    end else begin
        writeln('NO');
    end;

    close(input);
    close(output);
end.