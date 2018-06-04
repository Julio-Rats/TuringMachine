    ;    Detector de palindromos

            
          bloco main 01


	01	 a	 --	 A 			 i  		10



	01	 b	 --	 B 	i 	  20


	10 moveFim 11
	20 moveFim 21
	; leu a
	11 iniEsq 12
	12 a -- A i 30
	12 b -- * i 70
	12 _ -- * d 60

	; leu b
	21 iniEsq 22
	22 a -- * i 70
	22 b -- B i 30
	22 _ -- * d 60

	30 moveIni 31
	31 iniDir 32
	32 _ -- * e 60
	32 * -- * i 01

	60 sim pare
	70 nao pare
fim ; main

; move para ultimo caractere da palavra
bloco moveFim 01
	01 _ -- * e retorne
	01 * -- * d 01
fim ; moveFim

; move para primeiro caractere da palavra
bloco moveIni 01
	01 _ -- * d retorne
	01 * -- * e 01
fim ; moveIni

; recua ate caracetere minusculo ou _
bloco iniEsq 01
	01 _ -- * i retorne
	01 a -- * i retorne
	01 b -- * i retorne
	01 * -- * e 01
fim ; iniEsq

; avanca ate caractere minusculu ou _
bloco iniDir 01
	01 _ -- * i retorne
	01 a -- * i retorne
	01 b -- * i retorne
	01 * -- * d 01
fim ; iniDir

; palavra eh palindromo
bloco sim 01
	01 moveFim 02
	02 * -- * d 03
	03 * -- _ d 04
	04 * -- S d 05
	05 * -- I d 08
	08 * -- M d retorne
fim ; sim

; palavra nao eh palindromo
bloco nao 01
	01 moveFim 02
	02 * -- * d 03
	03 * -- _ d 04
	04 * -- N d 05
	05 * -- A d 06
	06 * -- O d retorne
fim ; nao
