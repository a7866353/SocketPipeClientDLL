#ifndef INDICATIONGS_H
#define INDICATIONGS_H


extern int SendResult(char *buffer, int length);

#define D_INDICATE_BUFFER_SIZE (4*1024*1024)
extern char gIndicateBuffer[D_INDICATE_BUFFER_SIZE];

#endif // INDICATIONGS_H