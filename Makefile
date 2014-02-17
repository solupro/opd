CC = gcc
CFLAGS = -I include/php/ \
			-I include/php/main \
			-I include/php/Zend \
			-I include/php/TSRM \
			-Wall -g
LDFLAGS = -lstdc++ -L/usr/local/lib -lphp5

ALL:
	$(CC) -o opd opd.c $(CFLAGS) $(LDFLAGS)
