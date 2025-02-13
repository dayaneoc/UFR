# sudo apt install gcovr

teste_exemplo: exemplo.c ufr_buffer.c ufr_buffer.h ufr_test.h
	gcc exemplo.c ufr_buffer.c -o teste_exemplo --coverage

test: clean teste_exemplo
	./teste_exemplo
	gcovr
	gcovr --html-details saida.html

clean:
	rm -f 'teste_exemplo-exemplo.gcda'  'teste_exemplo-ufr_buffer.gcda'
