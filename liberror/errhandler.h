#ifndef ERROR_HANDLER_H
#define ERROR_HANDLER_H

    void unix_error(char* msg);
    void posix_error(int code, char* msg);
    void dns_error(char* msg);
    void app_error(char* msg);

#endif  /* ERROR_HANDLER_H */