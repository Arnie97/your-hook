#include <windows.h>
#include <mmsystem.h>

int main(int argc, char *argv[])
{
    for (int i = 1; i < argc; i++) {
        PlaySound(argv[i], NULL, SND_FILENAME | SND_SYNC);
    }
    return 0;
}
