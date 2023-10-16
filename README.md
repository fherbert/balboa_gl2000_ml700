# balboa_gl2000_ml700

##
`main.c` is a sample program to generate the FB command to send to the GL2000 controller

It assumes a few things:

1. The first byte is a message start byte (FB)
2. The next 3 bytes I'm saying are panel ID - happy to be corrected
3. The next 3 bytes are the actual command bytes
4. the last byte is probably some sort of crc byte - which doesn't appear? to be checked

To compile, get gcc and run `gcc main.c -o main`
To run: ./main and enter the number for the command output

```
❯ ./main
Select a command:
 (0): Empty
 (1): Up
 (2): Down
0
Message: 0xFB 0x06 0x64 0xD4 0x06 0x00 0x00 0xFF 0x40
❯ ./main
Select a command:
 (0): Empty
 (1): Up
 (2): Down
2
Message: 0xFB 0x06 0x64 0xD4 0x06 0x00 0x02 0xFD 0x64 
```
