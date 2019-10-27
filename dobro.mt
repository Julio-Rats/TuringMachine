;
; Expressão definida por 0^(N)1^(2N)
;
bloco main 0
	0 _ -- * i 11
	0 * -- * i 1

	1 0 -- x d 2
	1 * -- * i 10

	2 0 -- 0 d 2
	2 1 -- 1 d 2
	2 y -- y e 3
	2 _ -- _ e 3
	2 * -- * i 10

	3 1 -- y e 6
	3 * -- * i 10
	6 1 -- y i 4
	6 * -- * i 10

	4 x -- x d 5
	4 * -- * e 4

	5 y -- * i 11
	5 * -- * i 1

	10 error 	pare
	11 aceita pare
fim

bloco error 1
	1 apaga_fita 3
	3 * -- N d 4
	4 * -- A d 5
	5 * -- O d 6
	6 * -- _ d 7
	7 write_aceita retorne
fim

bloco aceita 1
	1 apaga_fita 3
	3 * -- S d 4
	4 * -- I d 5
	5 * -- M d 6
	6 * -- _ d 7
	7 write_aceita retorne
fim

bloco apaga_fita 1
	1 _ -- * e 2
	1 * -- * d *
	2 _ -- * d retorne
	2 * -- _ e *
fim

bloco write_aceita 1
	1 * -- A d 2
	2 * -- C d 3
	3 * -- E d 4
	4 * -- I d 5
	5 * -- T d 6
	6 * -- A d retorne
fim
