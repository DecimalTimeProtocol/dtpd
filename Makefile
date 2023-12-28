dtpd: dtpd.c utils.c
	mkdir build
	clang -fcolor-diagnostics -fansi-escape-codes -g dtpd.c utils.c -o build/dtpd

clean:
	rm -rf build
