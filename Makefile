# sudo apt install gcovr

run: teste
	./teste
	gcovr

teste: exemplo.c ufr_buffer.c ufr_buffer.h ufr_test.h
	gcc exemplo.c ufr_buffer.c -o teste --coverage

clean:
	rm teste-exemplo.gcda  teste-ufr_buffer.gcda teste-exemplo.gcno teste-ufr_buffer.gcno teste
