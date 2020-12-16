#ifndef SERVER_CONTENTS_H
#define SERVER_CONTENTS_H

    void get_filetype(char* filename, char* filetype);
    void server_static(int fd, char* filename, int filesize);
    void server_dynamic(int fd, char* filename, char* cgiargs);

#endif  /* SERVER_CONTENTS_H */
