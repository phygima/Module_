CC = gcc
CFLAGS = -Wall
USER_TARGET = user_space
USER_SRC = user_space.c

KERNEL_TARGET = kernel_space
KERNEL_SRC = kernel_space.c
obj-m += $(KERNEL_TARGET).o

all: userapp kernelmodule

userapp: $(USER_TARGET)

$(USER_TARGET): $(USER_TARGET).o
	$(CC) -o $(USER_TARGET) $(USER_TARGET).o

$(USER_TARGET).o: $(USER_SRC)
	$(CC) $(CFLAGS) -c $(USER_SRC)

kernelmodule:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

clean:
	rm -f *.o $(USER_TARGET)
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean

.PHONY: all userapp kernelmodule clean
