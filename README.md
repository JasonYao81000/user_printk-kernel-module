# user_printk kernel module
A kernel module for calling printk from the user space.

## Kernel Module

### 1. Compile and insert the kernel module
```
$ cd user_printk-kernel-module/
$ make
$ sudo insmod user_printk.ko
```

### 2. Check the inserted kernel module
```
$ lsmod | grep user_printk
user_printk            16384  0
```
```
$ dmesg | tail
[   42.783173] user_printk init
```
```
$ ls -lR /dev/user_printk
crw------- 1 root root 10, 53  三  24 18:50 /dev/user_printk
```

## User Program

### 1. Compile the example user program
```
$ cd user_program/
$ make clean
$ make
```

### 2. Execute the example user program
```
$ make run
```
or
```
$ sudo ./main "Say something to the kernel from the user space."
```

### 3. Check the kernel module works well
```
$ dmesg | tail
[   58.211401] Say something to the kernel from the user space.
```

## Remove kernel module
```
$ sudo rmmod user_printk.ko
$ dmesg | tail
[   68.004246] user_printk cleanup
```
