CC = clang
CFLAGS = -Wall -Wextra

all: tcp_syn_sender clean

tcp_syn_sender: tcp_syn_sender.o
	$(CC) $(CFLAGS) -o $@ $^

tcp_syn_sender.o: main.c
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -f tcp_syn_sender.o

