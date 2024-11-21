uses
    testlib, sysutils;

const
    maxn = 300;
    maxm = maxn * maxn;

var
    i, j, k, n, m: longint;
    ja, pa: string;
    c, f, l: array [1..maxn, 1..maxn] of longint;
    e: array [1..maxm] of record
        a, b: longint;
    end;

begin
    n := inf.readlongint;
    m := inf.readlongint;
    for i := 1 to m do
    begin
        e[i].a := inf.readlongint;
        e[i].b := inf.readlongint;
        l[e[i].a][e[i].b] := inf.readlongint;
        c[e[i].a][e[i].b] := inf.readlongint;
    end;

    ja := ans.readstring;
    pa := ouf.readstring;

    if (pa <> 'YES') and (pa <> 'NO') then
        quit(_pe, 'neither "YES" nor "NO"');

    if (ja = 'YES') and (pa = 'NO') then
        quit(_wa, 'answer not found where it exists');

    if pa = 'NO' then
        quit(_ok, 'NO');

    for i := 1 to m do
    begin
        f[e[i].a][e[i].b] := ouf.readlongint;
    end;

    for i := 1 to n do
        for j := 1 to n do
            if (f[i][j] < l[i][j]) or (f[i][j] > c[i][j]) then
                quit(_wa, 'flow through pipe ' + inttostr(i) + '->' + inttostr(j) + ' is invalid');

    for i := 1 to n do
    begin
        k := 0;
        for j := 1 to n do
            k := k + f[i][j];
        for j := 1 to n do
            k := k - f[j][i];
        if k <> 0 then
            quit(_wa, 'not circulation - flow through vertex ' + inttostr(i) + ' is not balanced');
    end;

    if ja = 'NO' then
        quit(_fail, 'solution found where jury thought there was none');

    quit(_ok, '');
end.