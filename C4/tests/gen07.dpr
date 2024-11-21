var
    i: longint;

begin
    writeln('200 200');
    for i := 1 to 200 do
    begin
        writeln(i, ' ', i mod 200 + 1, ' ', 99800 - i, ' ', 100000 - i);
    end;
end.