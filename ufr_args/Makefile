# sudo apt install gcovr

ufr_test_buffer: ufr_test_buffer.c ufr_buffer.c ufr_buffer.h ufr_test.h
	gcc ufr_test_buffer.c ufr_buffer.c -o ufr_test_buffer --coverage

test: clean ufr_test_buffer
	./ufr_test_buffer
	gcovr
	gcovr --html-details saida.html

clean:
	rm -f 'ufr_test_buffer-ufr_buffer.gcda'  'ufr_test_buffer-ufr_test_buffer.gcda'
