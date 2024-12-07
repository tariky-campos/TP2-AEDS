# Nome do executável
TARGET = app

# Coleta todos os arquivos .c no diretório atual
SRCS = $(wildcard *.c)

# Gera os arquivos .o correspondentes
OBJS = $(SRCS:.c=.o)

# Compilador e flags
CC = gcc
CFLAGS = -Wall -Wextra -g

# Regra padrão: compilar o programa
all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS)

# Regra para compilar cada arquivo .c em .o
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Limpeza dos arquivos gerados
clean:
	rm -f $(OBJS) $(TARGET)

# Regra de limpeza completa (útil para remover arquivos temporários)
distclean: clean

# Regra para rodar o programa
run: $(TARGET)
	./$(TARGET)
