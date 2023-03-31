# Palindromy - wariant gry Connect Four

Gra dla dwóch graczy - gracz "1" i "2". Gracze na zmianę wybierają numer kolumny, do której chcą wstawić swój numer, i jeżeli gracz swoim ruchem stworzy na planszy palindrom o określonej długości, wygrywa. 

Istnieje możliwość wyboru rozmiaru planszy oraz długości palindromu:

    gcc -DWIERSZE=8 -DKOLUMNY=8 -DDLUGOSC=5 Palindromy.c -o Palindromy
