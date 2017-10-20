all:client server
.PHONY: clean

INCLUDES=-I include/

client:tcp/client.c
	gcc $(INCLUDES) tcp/client.c common/tcp.c -o client
server:tcp/server.c
	gcc $(INCLUDES) tcp/server.c common/tcp.c -o server
clean:
	rm -f client server 
