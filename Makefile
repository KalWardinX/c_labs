CC := gcc
CFLAGS := -Wall -lpython3.12
PY_CFLAGS := $(shell python-config --cflags)
PY_LDFLAGS := $(shell python-config --ldflags)
# Path setup
SRC := src
OBJ := obj
OUT := out
INCLUDE := include

TEST := test

# FINAL BUILD
SERVER_PROG := c_labs_server
SERVER_OBJ 	:= $(OBJ)/server.o $(OBJ)/conn_queue.o $(OBJ)/thread_func.o $(OBJ)/threadpool.o $(OBJ)/messages.o $(OBJ)/files.o $(OBJ)/lock.o

CLIENT_PROG := c_labs_client
CLIENT_OBJ := $(OBJ)/client.o $(OBJ)/client_func.o $(OBJ)/prompt.o $(OBJ)/messages.o

CLIENT_PROG2 := c_labs_client2
CLIENT_OBJ2 := $(OBJ)/client2.o $(OBJ)/client_func.o $(OBJ)/prompt.o $(OBJ)/messages.o

all: $(SERVER_PROG) $(CLIENT_PROG) $(CLIENT_PROG2)

# $(SERVER) : $(SRC)/server.c $(OBJ)conn_queue.o
# 	rm -f $(SERVER)
# 	$(CC) -o $(OUT)$(SERVER) $(CFLAGS) $(SRC)server.c -I $(INCLUDE) $(OBJ)conn_queue.o
# 	ln -s $(OUT)$(SERVER) $(SERVER)

# $(OBJ)conn_queue.o: $(SRC)conn_queue.c
# 	$(CC) -c $(CFLAGS) $(SRC)conn_queue.c -I $(INCLUDE) -o $(OBJ)conn_queue.o

$(SERVER_PROG) : $(SERVER_OBJ)
	$(CC) $(CFLAGS) $(PY_LDFLAGS) $^ -o $(OUT)/$@
	ln -sf $(OUT)/$@ $@

$(CLIENT_PROG) : $(CLIENT_OBJ)
	$(CC) $(CFLAGS) $^ -o $(OUT)/$@
	ln -sf $(OUT)/$@ $@

$(CLIENT_PROG2) : $(CLIENT_OBJ2)
	$(CC) $(CFLAGS) $^ -o $(OUT)/$@
	ln -sf $(OUT)/$@ $@

$(OBJ)/%.o : $(SRC)/%.c
	$(CC) -c $(CFLAGS) -I$(INCLUDE) $(PY_CFLAGS) $< -o $@





clean:
	rm -f $(OUT)/* $(OBJ)/* $(SERVER_PROG)