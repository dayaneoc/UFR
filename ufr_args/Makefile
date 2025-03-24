# sudo apt install gcovr

ufr_test_buffer: ufr_test_args.c ufr_args.c ufr_args.h ufr_test.h
	gcc ufr_test_args.c ufr_args.c -o ufr_test_args --coverage

test: clean ufr_test_args
	./ufr_test_args
	gcovr
	gcovr --html-details saida.html

clean:
	rm -f 'ufr_test_args-ufr_args.gcda'  'ufr_test_args-ufr_test_args.gcda'
