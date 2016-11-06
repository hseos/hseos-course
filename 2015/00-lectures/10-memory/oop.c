struct File;
struct FileOperations
{
    void (*close)(struct File *f);
    ssize_t (*read)(struct File *f, void *buf, size_t size);
    ssize_t (*write)(struct File *f, const void *buf, size_t size);
};

struct File
{
    const struct FileOperations *ops;
};

struct TtyFile
{
    struct File b;
    // extra fields
};

void tty_close(struct File *f);
void tty_read(struct File *f, void *buf, size_t size);
void tty_write(struct File *f, const void *buf, size_t size);

const struct FileOperations tty_file_ops =
{
    tty_close, tty_read, tty_write
};

struct File *create_tty_file()
{
    struct TtyFile *p = alloc(sizeof(*p));
    p->b.ops = tty_file_ops;

    return (struct File*) p;
}

void tty_close(struct File *f)
{
    struct TtyFile *p = (struct TtyFile *) f;
    // ...
}

void main(void)
{
    struct File *pf = ...;


    rsz = pf->ops->read(pf, buf, sizeof(buf));
}
