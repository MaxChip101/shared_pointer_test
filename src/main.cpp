#include <iostream>     // console
#include <sys/mman.h>   // shared memory
#include <sys/stat.h>   // for system()
#include <fcntl.h>      // for flags
#include <unistd.h>     // linux
#include <cstring>      // c style strings
#include <string>       // string

#define SHM_NAME "/shared_memory"
#define SHM_SIZE 1024  // 1 KB

int create_share_point(std::string name, int size, int oflags, int mode)
{
    int shm_fd = shm_open(name.c_str(), oflags, mode); // creates a share point with specific flags
    if (shm_fd == -1) // check for errors
    {
        perror("Failed to create share point");
        return -1;
    }
    if (ftruncate(shm_fd, size) == -1) // check for errors
    {
        perror("Failed to resize share point");
        close(shm_fd);
        return -1;
    }
    return shm_fd;
}

int get_share_point(std::string name, int oflags, int mode)
{
    int shm_fd = shm_open(name.c_str(), oflags, mode); // creates a share point without resizing
    if (shm_fd == -1) // check for errors
    {
        perror("Failed to create share point");
        return -1;
    }
    return shm_fd;
}

char* create_shared_pointer(int shm, int size, int memory_protection, int flags)
{
    char* ptr = (char*) mmap(NULL, size, memory_protection, flags, shm, 0); // maps an array with a specified size, prots, and flags
    if (ptr == MAP_FAILED) // check for errors
    {
        perror("Failed to create a shared pointer");
        return nullptr;
    }
    return ptr;
}

void send(char* pointer, int size, std::string message)
{
    strncpy(pointer, message.c_str(), size); // sends a message
}

std::string read(char* pointer)
{
    std::string message = std::string(pointer); // turns the pointer into a string and returns it
    return message;
}

void close_share_point(int shm)
{
    close(shm); // closes share point
}

void close_shared_pointer(char* pointer, int size)
{
    munmap(pointer, size); // unmaps pointer
}



int main() {

    int share = create_share_point(SHM_NAME, SHM_SIZE, O_CREAT | O_RDWR, 0666); // create share point
    if (share == -1) return 1; // check for errors
    char *pointer = create_shared_pointer(share, SHM_SIZE, PROT_WRITE | PROT_READ, MAP_SHARED); // create a pointer that is shared
    if (pointer == nullptr) return 1; // check for errors
    send(pointer, SHM_SIZE, "hello, from program 5"); // write a message to pointer
    close_shared_pointer(pointer, SHM_SIZE); // close pointer
    close_share_point(share); // close share point

    system("build/linux2/test"); // run second program

    return 0;
}
