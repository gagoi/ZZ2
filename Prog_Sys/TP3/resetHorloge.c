#include <time.h>
#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main()
{
    mkfifo(".sec_reset", O_WRONLY);
    mkfifo(".min_reset", O_WRONLY);
    mkfifo(".heu_reset", O_WRONLY);
    
    unlink(".reset");
}