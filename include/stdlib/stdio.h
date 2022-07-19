#ifndef _STDIO_H_
#define _STDIO_H_

void stdio_init();
void prints(const char *string);
void printc(char c);
void gets(char *buffer, unsigned int length);
char getc();

#endif //_STDIO_H_