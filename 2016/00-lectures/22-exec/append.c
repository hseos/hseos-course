int main()
{
    // non-atomic operation
    fd = open("out.txt", O_WRONLY | O_CREAT, 0600);

    lseek(fd, 0, SEEK_END);
    write(fd, "123\n", 4);

    // atomic operation
    fd = open("out.txt", O_WRONLY | O_CREAT | O_APPEND, 0600);
    write(fd, "123\n", 4);
}
