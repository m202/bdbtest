bdb_test:
	g++ -lreadline -ldb_cxx bdb_test.cc -o bdb_test

clean:
	rm -f bdb_test
