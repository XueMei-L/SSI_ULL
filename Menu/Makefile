main: main.o 01_cv.o 02_rc4.o 03_chacha20.o 04_cagps.o 05_snow3gyaes.o 06_aes.o 07_aesEnBloque.o 08_diffie_hellman_elgamal.o 09_rsa.o 10_eliptic.o 11_ffa.o
	g++ -o main main.o 01_cv.o 02_rc4.o 03_chacha20.o 04_cagps.o 05_snow3gyaes.o 06_aes.o 07_aesEnBloque.o 08_diffie_hellman_elgamal.o 09_rsa.o 10_eliptic.o 11_ffa.o

main.o: main.cpp
	g++ -c main.cpp

01_cv.o: 01_cv.cpp
	g++ -c 01_cv.cpp

02_rc4.o: 02_rc4.cpp
	g++ -c 02_rc4.cpp

03_chacha20.o: 03_chacha20.cpp
	g++ -c 03_chacha20.cpp

04_cagps.o: 04_cagps.cpp
	g++ -c 04_cagps.cpp

05_snow3gyaes.o: 05_snow3gyaes.cpp
	g++ -c 05_snow3gyaes.cpp

06_aes.o: 06_aes.cpp
	g++ -c 06_aes.cpp

07_aesEnBloque.o: 07_aesEnBloque.cpp
	g++ -c 07_aesEnBloque.cpp

08_diffie_hellman_elgamal.o: 08_diffie_hellman_elgamal.cpp
	g++ -c 08_diffie_hellman_elgamal.cpp

09_rsa.o: 09_rsa.cpp
	g++ -c 09_rsa.cpp

10_eliptic.o: 10_eliptic.cpp
	g++ -c 10_eliptic.cpp

11_ffa.o: 11_ffa.cpp
	g++ -c 11_ffa.cpp

clean:
	rm *.o main