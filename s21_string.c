#include "s21_string.h"
#include <stdarg.h>
#include <stdlib.h>
#include <math.h>
#include <stdio.h>

#ifdef __linux__
    #define OS_FOUND 1
    #define STR_ERROR "Unknown error "
    #define S21_SYS_ERRORLIST_CAPACITY 134
    #define MAKERLIST {"Success", \
        "Operation not permitted", \
        "No such file or directory", \
        "No such process", \
        "Interrupted system call", \
        "Input/output error", \
        "No such device or address", \
        "Argument list too long", \
        "Exec format error", \
        "Bad file descriptor", \
        "No child processes", \
        "Resource temporarily unavailable", \
        "Cannot allocate memory", \
        "Permission denied", \
        "Bad address", \
        "Block device required", \
        "Device or resource busy", \
        "File exists", \
        "Invalid cross-device link", \
        "No such device", \
        "Not a directory", \
        "Is a directory", \
        "Invalid argument", \
        "Too many open files in system", \
        "Too many open files", \
        "Inappropriate ioctl for device", \
        "Text file busy", \
        "File too large", \
        "No space left on device", \
        "Illegal seek", \
        "Read-only file system", \
        "Too many links", \
        "Broken pipe", \
        "Numerical argument out of domain", \
        "Numerical result out of range", \
        "Resource deadlock avoided", \
        "File name too long", \
        "No locks available", \
        "Function not implemented", \
        "Directory not empty", \
        "Too many levels of symbolic links", \
        "Unknown error 41", \
        "No message of desired type", \
        "Identifier removed", \
        "Channel number out of range", \
        "Level 2 not synchronized", \
        "Level 3 halted", \
        "Level 3 reset", \
        "Link number out of range", \
        "Protocol driver not attached", \
        "No CSI structure available", \
        "Level 2 halted", \
        "Invalid exchange", \
        "Invalid request descriptor", \
        "Exchange full", \
        "No anode", \
        "Invalid request code", \
        "Invalid slot", \
        "Unknown error 58", \
        "Bad font file format", \
        "Device not a stream", \
        "No data available", \
        "Timer expired", \
        "Out of streams resources", \
        "Machine is not on the network", \
        "Package not installed", \
        "Object is remote", \
        "Link has been severed", \
        "Advertise error", \
        "Srmount error", \
        "Communication error on send", \
        "Protocol error", \
        "Multihop attempted", \
        "RFS specific error", \
        "Bad message", \
        "Value too large for defined data type", \
        "Name not unique on network", \
        "File descriptor in bad state", \
        "Remote address changed", \
        "Can not access a needed shared library", \
        "Accessing a corrupted shared library", \
        ".lib section in a.out corrupted", \
        "Attempting to link in too many shared libraries", \
        "Cannot exec a shared library directly", \
        "Invalid or incomplete multibyte or wide character", \
        "Interrupted system call should be restarted", \
        "Streams pipe error", \
        "Too many users", \
        "Socket operation on non-socket", \
        "Destination address required", \
        "Message too long", \
        "Protocol wrong type for socket", \
        "Protocol not available", \
        "Protocol not supported", \
        "Socket type not supported", \
        "Operation not supported", \
        "Protocol family not supported", \
        "Address family not supported by protocol", \
        "Address already in use", \
        "Cannot assign requested address", \
        "Network is down", \
        "Network is unreachable", \
        "Network dropped connection on reset", \
        "Software caused connection abort", \
        "Connection reset by peer", \
        "No buffer space available", \
        "Transport endpoint is already connected", \
        "Transport endpoint is not connected", \
        "Cannot send after transport endpoint shutdown", \
        "Too many references: cannot splice", \
        "Connection timed out", \
        "Connection refused", \
        "Host is down", \
        "No route to host", \
        "Operation already in progress", \
        "Operation now in progress", \
        "Stale file handle", \
        "Structure needs cleaning", \
        "Not a XENIX named type file", \
        "No XENIX semaphores available", \
        "Is a named type file", \
        "Remote I/O error", \
        "Disk quota exceeded", \
        "No medium found", \
        "Wrong medium type", \
        "Operation canceled", \
        "Required key not available", \
        "Key has expired", \
        "Key has been revoked", \
        "Key was rejected by service", \
        "Owner died", \
        "State not recoverable", \
        "Operation not possible due to RF-kill", \
        "Memory page has hardware error"}
#endif

#ifdef __APPLE__
    #define OS_FOUND 1
    #define STR_ERROR "Unknown error: "
    #define S21_SYS_ERRORLIST_CAPACITY 107
    #define MAKERLIST {"Undefined error: 0", \
        "Operation not permitted", \
        "No such file or directory", \
        "No such process", \
        "Interrupted system call", \
        "Input/output error", \
        "Device not configured", \
        "Argument list too long", \
        "Exec format error", \
        "Bad file descriptor", \
        "No child processes", \
        "Resource deadlock avoided", \
        "Cannot allocate memory", \
        "Permission denied", \
        "Bad address", \
        "Block device required", \
        "Resource busy", \
        "File exists", \
        "Cross-device link", \
        "Operation not supported by device", \
        "Not a directory", \
        "Is a directory", \
        "Invalid argument", \
        "Too many open files in system", \
        "Too many open files", \
        "Inappropriate ioctl for device", \
        "Text file busy", \
        "File too large", \
        "No space left on device", \
        "Illegal seek", \
        "Read-only file system", \
        "Too many links", \
        "Broken pipe", \
        "Numerical argument out of domain", \
        "Result too large", \
        "Resource temporarily unavailable", \
        "Operation now in progress", \
        "Operation already in progress", \
        "Socket operation on non-socket", \
        "Destination address required", \
        "Message too long", \
        "Protocol wrong type for socket", \
        "Protocol not available", \
        "Protocol not supported", \
        "Socket type not supported", \
        "Operation not supported", \
        "Protocol family not supported", \
        "Address family not supported by protocol family", \
        "Address already in use", \
        "Can't assign requested address", \
        "Network is down", \
        "Network is unreachable", \
        "Network dropped connection on reset", \
        "Software caused connection abort", \
        "Connection reset by peer", \
        "No buffer space available", \
        "Socket is already connected", \
        "Socket is not connected", \
        "Can't send after socket shutdown", \
        "Too many references: can't splice", \
        "Operation timed out", \
        "Connection refused", \
        "Too many levels of symbolic links", \
        "File name too long", \
        "Host is down", \
        "No route to host", \
        "Directory not empty", \
        "Too many processes", \
        "Too many users", \
        "Disc quota exceeded", \
        "Stale NFS file handle", \
        "Too many levels of remote in path", \
        "RPC struct is bad", \
        "RPC version wrong", \
        "RPC prog. not avail", \
        "Program version wrong", \
        "Bad procedure for program", \
        "No locks available", \
        "Function not implemented", \
        "Inappropriate file type or format", \
        "Authentication error", \
        "Need authenticator", \
        "Device power is off", \
        "Device error", \
        "Value too large to be stored in data type", \
        "Bad executable (or shared library)", \
        "Bad CPU type in executable", \
        "Shared library version mismatch", \
        "Malformed Mach-o file", \
        "Operation canceled", \
        "Identifier removed", \
        "No message of desired type", \
        "Illegal byte sequence", \
        "Attribute not found", \
        "Bad message", \
        "EMULTIHOP (Reserved)", \
        "No message available on STREAM", \
        "ENOLINK (Reserved)", \
        "No STREAM resources", \
        "Not a STREAM", \
        "Protocol error", \
        "STREAM ioctl timeout", \
        "Operation not supported on socket", \
        "Policy not found", \
        "State not recoverable", \
        "Previous owner died", \
        "Interface output queue is full"}
#endif

#ifndef __linux__
    #ifndef __APPLE__
        #define OS_FOUND 0
        #define S21_SYS_ERRORLIST_CAPACITY 1
        #define MAKERLIST {"No errors for this OS"}
    #endif
#endif

#define fori(n) for (s21_size_t i = 0; i < n; i++)

// FORMAT STRING: SPECIFIERS
# define S21_F_SPEC_CHAR 'c'                 // Character
# define S21_F_SPEC_SIGN_DEC_INT 'd'         // Signed decimal integer
# define S21_F_SPEC_SIGN_INT 'i'             // Signed integer
# define S21_F_SPEC_SCI_N_SMALL 'e'          // Scientific notation (mantissa/exponent) using e character
# define S21_F_SPEC_SCI_N_BIG 'E'            // Scientific notation (mantissa/exponent) using E character
# define S21_F_SPEC_DEC_FLOAT 'f'            // Decimal floating point
# define S21_F_SPEC_SHR_OF_e_f 'g'           // Uses the shorter of %e or %f
# define S21_F_SPEC_SHR_OF_E_F 'G'           // Uses the shorter of %E or %f
# define S21_F_SPEC_USIGN_OCT 'o'            // Unsigned octal
# define S21_F_SPEC_STR 's'                  // String of characters
# define S21_F_SPEC_USIGN_DEC_INT 'u'        // Unsigned decimal integer
# define S21_F_SPEC_USIGN_HEX_INT_SMALL 'x'  // Unsigned hexadecimal integer
# define S21_F_SPEC_USIGN_HEX_INT_BIG 'X'    // Unsigned hexadecimal integer (capital letters)
# define S21_F_SPEC_PTR 'p'                  // Pointer address
# define S21_F_SPEC_COUNT_OF_CHARACTERS 'n'  // Count of characters before %n occurs
# define S21_F_SPEC_PERCENT '%'              // Character %

// FORMAT STRING: FLAGS
typedef enum formatFlag {
    S21_F_FLAG_LEFT_JUSTIFY,
    S21_F_FLAG_SIGN,
    S21_F_FLAG_SPACE_SIGN,
    S21_F_FLAG_DELIMITER,
    S21_F_FLAG_ZERO_PADDING,
    S21_F_COUNT_OF_FLAGS
} s21_FormatFlag;

static char formatFlagSymbols[S21_F_COUNT_OF_FLAGS] = {
    '-',
    '+',
    ' ',
    '#',
    '0'
};

// FORMAT STRING: LENGTH
typedef enum s21_formatLength {
    S21_F_LEN_CHAR,             // "hh"
    S21_F_LEN_SH_INT,           // "h"
    S21_F_LEN_LONG_INT,         // "l"
    S21_F_LEN_LONG_LONG_INT,    // "ll"
    S21_F_LEN_LONG_DOUBLE,      // "L"
    S21_F_LEN_COUNT
} s21_FormatLength;

#define S21_F_LEN_h 'h'
#define S21_F_LEN_l 'l'
#define S21_F_LEN_L 'L'

// STRUCT FORMAT TOKEN
typedef struct formatToken {
    char flags[S21_F_COUNT_OF_FLAGS];
    char widthAst;
    s21_size_t width;
    char precisionAst;
    s21_size_t precision;
    s21_FormatLength length;
    char specifier;
    void *data;
    char *freeSymbols;
    struct formatToken *next;
} FormatToken;

static char* s21_intToStr(int n) {
    char *result = S21_NULL;
    int rank = 0;
    int minus = 0;
    if (n < 0) {
        minus = 1;
        n = -n;
    }
    for (int nn = n; nn > 9; nn /= 10, rank++) {}
    int len = rank + minus + 1;
    result = malloc(sizeof(char) * (len + 1));
    if (result) {
        if (minus) {
            *result = '-';
        }
        int nn = n;
        for (int i = len - 1; i >= minus; i--) {
            result[i] = (nn % 10) + 48;
            nn /= 10;
        }
        result[len] = '\0';
    }
    return result;
}

/*mcarb*/
void *s21_memchr(const void *str, int c, size_t n) {
    char *str_s = (char *) str;
    char ch = (char) c;
    char *find_char = S21_NULL;
    for (s21_size_t i = 0; i < n; i++) {
        if (str_s[i] == ch) {
            find_char = str_s+i;
            break;
        }
    }
    return (void *) find_char;
}

/*mcarb + fcharlin*/
int s21_memcmp(const void *str1, const void *str2, s21_size_t n) {
    unsigned char *str1_s = (unsigned char *) str1;
    unsigned char *str2_s = (unsigned char *) str2;
    int result = 0;
    for (s21_size_t i = 0; i < n && !(result); i++) {
        result = str1_s[i] - str2_s[i];
        if (result != 0) {
            if (i % 2) {
                result = result << 8;
            }
        }
    }
    return result;
}

/*mcarb*/
void *s21_memcpy(void *dest, const void *src, s21_size_t n) {
    char *dest_s = (char *) dest;
    const char *src_s = (char *) src;
    s21_size_t len = 0;
    for (len = 0; len < n; len++) {
        *(dest_s+len) = *(src_s+len);
    }
    return (void *) dest_s;
}

/*mcarb*/
void *s21_memmove(void *dest, const void *src, s21_size_t n) {
    char *dest_s = (char *) dest;
    const char *src_s = (char *) src;
    if (dest_s > src_s && src_s + n > dest_s) {
        dest_s = dest_s + n -1;
        src_s = src_s + n -1;
        for (s21_size_t i = n; i > 0; i--) {
            *(dest_s+i) = *(src_s+i);
        }
    } else {
        for (s21_size_t i = 0; i< n; i++) {
            *(dest_s+i) = *(src_s+i);
        }
    }
    return (void *) dest_s;
}

/*mcarb*/
void *s21_memset(void *str, int c, s21_size_t n) {
    char *str_s = (char *) str;
    for (s21_size_t i = 0;  i< n; i++) {
        str_s[i] = c;
    }
    return (void *) str_s;
}

/*mcarb*/
char *s21_strcat(char *dest, const char *src) {
    s21_size_t len = 0, len_src = 0;
    for (len = 0; dest[len]; len++) {}
    for (len_src = 0; src[len_src]; len_src++) {
        dest[len+len_src] = (char) src[len_src];
    }
    dest[len+len_src] = '\0';
    return dest;
}

/*mcarb*/
char *s21_strncat(char *dest, const char *src, s21_size_t n) {
    s21_size_t len = 0, len_src = 0;
    for (len = 0; dest[len]; len++) {}
    for (len_src = 0; len_src < n && src[len_src]; len_src++) {
        dest[len+len_src] = (char) src[len_src];
    }
    return dest;
}

/*mcarb*/
char *s21_strchr(const char *str, int c) {
    char *find_str = S21_NULL;
    if (c > 0) {
        for (int i = 0; str[i]; i++) {
            if (str[i] == (char)c) {
                find_str = (char*) str+i;
                break;
            }
       }
    } else {
        find_str = (char *) str +(s21_strlen(str));
    }
    return find_str;
}

/*mcarb*/
int s21_strcmp(const char *str1, const char *str2) {
    int result = 0;
    s21_size_t len;
    for (len = 0; str1[len] && result == 0; len++) {
        if (!str2[len]) {
            result = str1[len];
        } else {
                result = str1[len] - str2[len];
        }
    }
    if (result == 0 && str2[len]) result = -str2[len];
    return result;
}

/*mcarb + fcharlin*/
int s21_strncmp(const char *str1, const char *str2, s21_size_t n) {
    int result = 0;
    for (s21_size_t i = 0; i < n && !(result = str1[i] - str2[i]) && str1[i] != '\0' ; i++) {
    }
    return result;
}

/*jamidala*/
char *s21_strcpy(char *dest, const char *src) {
    s21_size_t i = 0;
    while (src[i] != '\0') {
        dest[i] = src[i];
        i++;
    }
    dest[i] = '\0';
    return dest;
}

/*jamidala + fcharlin*/
char* s21_strncpy(char *dest, const char *src, size_t n) {
    if (n > 0) {
        s21_size_t i = 0;
        for (; i < n && src[i] != '\0'; i++) {
            dest[i] = src[i];
        }
        dest[i] = '\0';
    }
    return dest;
}

/*jamidala + fcharlin + mcarb*/
s21_size_t s21_strcspn(const char *str1, const char *str2) {
    const char *temp = str1;
    for (; s21_strchr(str2, *str1) == S21_NULL; str1++) {
    }
    return (str1 - temp);
}

/*jamidala*/
char *s21_strerror(int errnum) {
    static char s21_errorString[200];
    char *result = s21_errorString;
    if (errnum < 0 || errnum >= S21_SYS_ERRORLIST_CAPACITY) {
        char *str_errnum = s21_intToStr(errnum);
        s21_strcpy(result, STR_ERROR);
        s21_strcat(result, str_errnum);
        free(str_errnum);
    } else {
        char *arr[S21_SYS_ERRORLIST_CAPACITY] = MAKERLIST;
        s21_strcpy(result, arr[errnum]);
    }
    return result;
}

/*mcarb*/
s21_size_t s21_strlen(const char *str) {
    s21_size_t length = 0;
    for (length = 0 ; *(str + length); length++) {}
    return length;
}

/*fcharlin*/
char *s21_strpbrk(const char *str1, const char *str2) {
    const char *pointer = S21_NULL;
    for (; *str1 != '\0' && pointer == S21_NULL; str1++) {
        for (const char *temp = str2; *temp != '\0'; temp++) {
            if (*temp == *str1) {
                pointer = str1;;
                break;
            }
        }
    }
    return (char*)pointer;
}

/*fcharlin*/
char *s21_strrchr(const char *str, int c) {
    const char *pointer = S21_NULL;
    if (c != 0) {
        for (; *str != '\0'; str++) {
            if (*str == (char)c) {
                pointer = str;
            }
        }
    } else {
        pointer = s21_strlen(str) + str;
    }
    return (char*)pointer;
}

/*fcharlin*/
s21_size_t s21_strspn(const char *str1, const char *str2) {
    s21_size_t count = 0;
    for (const char *temp = str2; *str1 != '\0' && *temp != '\0'; str1++) {
        temp = str2;
        for (; *temp != '\0'; temp++) {
            if (*temp == *str1) {
                count++;
                break;
            }
        }
    }
    return count;
}

/*fcharlin*/
char *s21_strstr(const char *haystack, const char *needle) {
    const char *pointer = S21_NULL;
    while (1) {
        const char *temp1 = needle;
        for (const char *temp = haystack; *temp == *temp1 && *temp1 != '\0'; temp++, temp1++) {}
        if (*temp1 == '\0') {
            pointer = haystack;
            break;
        }
        if (*haystack == '\0') {
            break;
        }
        haystack++;
    }
    return (char*)pointer;
}

/*fcharlin*/
char *s21_strtok(char *str, const char *delim) {
    static char *pointer_mem;
    char *pointer;
    if (str == S21_NULL) {
        pointer = pointer_mem;
    } else {
        pointer = str;
    }
    pointer = pointer + s21_strspn(pointer, delim);
    if ((pointer_mem = s21_strpbrk(pointer, delim)) != S21_NULL) {
        *pointer_mem = '\0';
        pointer_mem++;
    } else {
        pointer_mem = pointer + s21_strlen(pointer);
    }
    if (*pointer == '\0') {
        pointer = S21_NULL;
    }
    return pointer;
}

/*fcharlin*/
void *s21_to_upper(const char *str) {
    char *pointer = S21_NULL;
    if (str != S21_NULL) {
        pointer = (char*) calloc(s21_strlen(str) + 1, sizeof(char));
    }
    if (pointer != S21_NULL) {
        for (char *temp = pointer; *str != '\0'; str++, temp++) {
            if (*str >= 'a' && *str <= 'z') {
                *temp = *str + 'A' - 'a';
            } else {
                *temp = *str;
            }
        }
    }
    return pointer;
}

/*fcharlin*/
void *s21_to_lower(const char *str) {
    char *pointer = S21_NULL;
    if (str != S21_NULL) {
        pointer = (char*) calloc(s21_strlen(str) + 1, sizeof(char));
    }
    if (pointer != S21_NULL) {
        for (char *temp = pointer; *str != '\0'; str++, temp++) {
            if (*str >= 'A' && *str <= 'Z') {
                *temp = *str + 'a' - 'A';
            } else {
                *temp = *str;
            }
        }
    }
    return pointer;
}

/*fcharlin*/
void *s21_insert(const char *src, const char *str, s21_size_t start_index) {
    char *pointer = S21_NULL;
    s21_size_t size_src = 0;
    if (src != S21_NULL) {
        size_src = s21_strlen(src);
    }
    if (str != S21_NULL && start_index <= size_src) {
        pointer = (char*) calloc(size_src + s21_strlen(str) + 1, sizeof(char));
    }
    if (pointer != S21_NULL) {
        for (char *temp = pointer; *src != '\0' || *str != '\0'; src++, temp++) {
            if ((temp - pointer) == (long) start_index) {
                for (; *str != '\0'; str++, temp++) {
                    *temp = *str;
                }
            }
            *temp = *src;
            if (*src == '\0' && *str != '\0') {
                src--;
            }
        }
    }
    return pointer;
}

/*fcharlin*/
s21_size_t s21_strspn_back(const char *str1, const char *str2) {
    s21_size_t count = 0;
    s21_size_t size = s21_strlen(str1);
    if (size != 0) {
        for (const char *temp2 = str2, *temp1 = size + str1 - 1; temp1 >= str1 && *temp2 != '\0'; temp1--) {
            temp2 = str2;
            for (; *temp2 != '\0'; temp2++) {
                if (*temp2 == *temp1) {
                    count++;
                    break;
                }
            }
        }
    }
    return count;
}

/*fcharlin*/
void *s21_trim(const char *src, const char *trim_chars) {
    char *pointer = S21_NULL;
    char *trim_temp = (char*)trim_chars;
    if (trim_chars == S21_NULL || *trim_chars == '\0') {
        static char delimiters[] = {' ', '\t', '\r', '\v', '\f', '\n', '\0'};
        trim_temp = delimiters;
    }
    if (src != S21_NULL) {
        src = src + s21_strspn(src, trim_temp);
        const char *pointer_end = src + s21_strlen(src) - s21_strspn_back(src, trim_temp);
        pointer = (char*) calloc(pointer_end - src + 1, sizeof(char));
        if (pointer != S21_NULL) {
            for (char *pointer_temp = pointer; src != pointer_end; src++, pointer_temp++) {
                *pointer_temp = *src;
            }
        }
    }
    return pointer;
}

static s21_FormatFlag s21_getFormatFlagFromChar(char c) {
    s21_FormatFlag result;
    for (result = 0; result < S21_F_COUNT_OF_FLAGS && formatFlagSymbols[result] != c; result++) {}
    return result;
}

static s21_size_t s21_getLengthFromString(s21_FormatLength *length, char *s) {
    s21_size_t result = 0;

    switch (*s) {
    case S21_F_LEN_h:
        if (*(++s) == S21_F_LEN_h) {
            *length = S21_F_LEN_CHAR;
            result += 2;
        } else {
            *length = S21_F_LEN_SH_INT;
            result++;
        }
        break;
    case S21_F_LEN_l:
        if (*(++s) == S21_F_LEN_l) {
            *length = S21_F_LEN_LONG_LONG_INT;
            result += 2;
        } else {
            *length = S21_F_LEN_LONG_INT;
            result++;
        }
        break;
    case S21_F_LEN_L:
        *length = S21_F_LEN_LONG_DOUBLE;
        result++;
        break;
    default:
        *length = S21_F_LEN_COUNT;
        break;
    }

    return result;
}

static s21_size_t s21_getNumberFromString(s21_size_t *number, char *s) {
    s21_size_t result = 0;
    *number = 0;
    char *c;
    for (c = s; *c > 47 && *c < 58; c++) {
        result++;
    }
    s21_size_t power = 1;
    for (c--; c >= s; c--) {
        *number += (*c - 48) * power;
        power *= 10;
    }
    return result;
}

static s21_size_t s21_formatTokenFromFormatString(FormatToken *token, const char *format) {
    token->precisionAst = 0;
    token->widthAst = 0;
    token->precision = 0;
    token->width = 0;
    for (int i = 0; i < S21_F_COUNT_OF_FLAGS; i++) token->flags[i] = 0;
    char *c = (char *) format;
    if (*c == '%') {
        s21_FormatFlag flag = s21_getFormatFlagFromChar(*++c);
        while (flag != S21_F_COUNT_OF_FLAGS) {
            token->flags[flag] = 1;
            flag = s21_getFormatFlagFromChar(*(++c));
        }
        if (*c == '*') {
            token->widthAst = 1;
            c++;
        } else {
            token->widthAst = 0;
            c += (int) s21_getNumberFromString(&token->width, c);
        }
        if (*c == '.') {
            if (*(++c) == '*') {
                token->precisionAst = 1;
                c++;
            } else {
                token->precisionAst = 0;
                c += (int) s21_getNumberFromString(&token->precision, c);
            }
        }
        c += (int) s21_getLengthFromString(&token->length, c);
        token->specifier = *c++;
    }
    token->freeSymbols = c;
    for (; *c && *c != '%'; c++) {}
    token->next = S21_NULL;
    return c - format;
}

static void s21_formatTokenSetWidthAndPrecision(FormatToken *token, va_list *args) {
    if (token->widthAst) {
            int width = va_arg(*args, int);
            if (width < 0) {
                token->flags[0] = 1;
                width = -width;
            }
            token->width = width;
        }
        if (token->precisionAst) {
            int precision = va_arg(*args, int);
            if (precision < 0) {
                precision = 0;
            }
            token->precision = precision;
        }
}

static void* s21_formatTokenSetData(FormatToken *token, va_list *args) {
    #define setTokenData(pType, argType) { \
        pType *p = malloc(sizeof(pType)); \
        if (p) { \
            *p = va_arg(*args, argType); \
            token->data = p; \
            result = p; \
        } \
    }
    void *result = S21_NULL;
    char spec = token->specifier;
    s21_FormatLength length = token->length;
    if (spec == S21_F_SPEC_CHAR) {
        setTokenData(char, int);
    }
    if (spec == S21_F_SPEC_SIGN_DEC_INT || spec == S21_F_SPEC_SIGN_INT) {
        setTokenData(int, int);
    }
    if (spec == S21_F_SPEC_SCI_N_SMALL || spec == S21_F_SPEC_SCI_N_BIG
    || (spec == S21_F_SPEC_DEC_FLOAT && length == S21_F_LEN_COUNT)
    || spec == S21_F_SPEC_SHR_OF_e_f || spec == S21_F_SPEC_SHR_OF_E_F) {
        setTokenData(long double, double);
    }
    if (spec == S21_F_SPEC_USIGN_OCT || spec == S21_F_SPEC_USIGN_DEC_INT
    || spec == S21_F_SPEC_USIGN_HEX_INT_SMALL || spec == S21_F_SPEC_USIGN_HEX_INT_BIG) {
        setTokenData(unsigned int, unsigned int);
    }
    if (spec == S21_F_SPEC_PTR) {
        setTokenData(s21_size_t, s21_size_t);
    }
    if (spec == S21_F_SPEC_STR) {
        token->data = va_arg(*args, char*);
    }
    if (spec == S21_F_SPEC_DEC_FLOAT && length == S21_F_LEN_LONG_DOUBLE) {
        setTokenData(long double, long double);
    }

    #undef setTokenData

    return result;
}

static FormatToken* s21_formatParcing(const char *format, va_list *args) {
    FormatToken *result = S21_NULL;

    FormatToken *lastToken = S21_NULL;
    while (*format) {
        FormatToken *token = malloc(sizeof(FormatToken));
        if (token) {
            format += s21_formatTokenFromFormatString(token, format);
            s21_formatTokenSetWidthAndPrecision(token, args);
            s21_formatTokenSetData(token, args);
            if (lastToken) {
                lastToken->next = token;
                lastToken = token;
            } else {
                result = token;
                lastToken = token;
            }
        }
    }

    return result;
}

static char* s21_tokenIntToStr(FormatToken *token) {
    int n = *(int*)(token->data);
    char *result = S21_NULL;
    int sign = 0;
    int rank = 0;
    char signChar = ' ';
    if (token->flags[S21_F_FLAG_SPACE_SIGN]) {
        sign = 1;
        signChar = ' ';
    }
    if (token->flags[S21_F_FLAG_SIGN]) {
        sign = 1;
        signChar = '+';
    }
    if (n < 0) {
        sign = 1;
        signChar = '-';
        n = -n;
    }
    for (int nn = n; nn > 9; nn /= 10, rank++) {}
    int prec = token->precision - rank - 1;
    if (prec < 0) {
        prec = 0;
    }
    int len = token->precision == 0 && n == 0 ? 0 : rank + sign + prec + 1;
    result = malloc(sizeof(char) * (len + 1));
    if (result) {
        if (sign) {
            *result = signChar;
        }
        int nn = n;
        for (int i = len - 1; i >= sign; i--) {
            result[i] = (nn % 10) + 48;
            nn /= 10;
        }
        result[len] = '\0';
    }
    return result;
}

static void reverse(char* str, int len) {
    int i = 0, j = len - 1;
    while (i < j) {
        char temp = str[i];
        str[i] = str[j];
        str[j] = temp;
        i++;
        j--;
    }
}

static int intToStr(int x, char *str, int d) {
    int i = 0;
    while (x) {
        str[i++] = (x % 10) + '0';
        x = x / 10;
    }
    while (i < d) str[i++] = '0';
    reverse(str, i);
    str[i] = '\0';
    return i;
}

static char* s21_tokenFloatToStr(FormatToken *token) {
    long double n = *(long double*)(token->data);
    char *result = S21_NULL;
    int sign = 0;
    int precision = 0;
    char signChar = ' ';
    if (token->precision != 0) {
       precision = token->precision;
    } else {
        precision = 6;
    }
    if (token->flags[S21_F_FLAG_SPACE_SIGN]) {
        sign = 1;
        signChar = ' ';
    }
    if (token->flags[S21_F_FLAG_SIGN]) {
        sign = 1;
        signChar = '+';
    }
    if (n < 0) {
        sign = 1;
        signChar = '-';
        n = -n;
    }
    int ipart = (int) n;
    long double fpart = n - ipart;

    int x = n, i = 0;
    while (x) {
        x = x / 10;
        i++;
    }
    result = malloc(sizeof(char) * (i + precision+2+sign));
    if (sign) {
        result[0] = signChar;
    }
    i = sign+intToStr(ipart, result+sign, 0);
    if (precision != 0) {
        result[i] = '.';
    }
    fpart = fpart * pow(10, precision);
    intToStr((int)fpart, result + i + 1, precision);

    return result;
}

static char* s21_tokenStrToStr(FormatToken *token) {
    char *result = S21_NULL;
    s21_size_t len = s21_strlen(token->data);
    if (token->precision > 0 && token->precision < len) {
        len = token->precision;
    }
    result = malloc(sizeof(char) * (len+1));
    s21_strncpy(result, token->data, len);
    return result;
}

static char* s21_bufferForming(FormatToken *token) {
    char *result = S21_NULL;

    char spec = token->specifier;
    if (spec == S21_F_SPEC_CHAR) {
        result = malloc(sizeof(char) * 2);
        if (result) {
            *result = *(char*)token->data;
            result[1] = '\0';
        }
    }
    if (spec == S21_F_SPEC_SIGN_DEC_INT || spec == S21_F_SPEC_SIGN_INT || spec == S21_F_SPEC_USIGN_DEC_INT) {
        result = s21_tokenIntToStr(token);
    }
    if (spec == S21_F_SPEC_STR) {
        result = s21_tokenStrToStr(token);
    }
    if (spec == S21_F_SPEC_PERCENT) {
        result = malloc(sizeof(char) * 2);
        if (result) {
            result[0] = '%';
            result[1] = '\0';
        }
    }
    if (spec == S21_F_SPEC_DEC_FLOAT) {
        result = s21_tokenFloatToStr(token);
    }

    return result;
}

static int s21_tokenJustify(char *str, char *buf, FormatToken *token) {
    char *c = str;

    s21_size_t bufLen = s21_strlen(buf);

    s21_size_t spacesCount = token->width > bufLen ? token->width - bufLen : 0;
    if (!token->flags[S21_F_FLAG_LEFT_JUSTIFY]) {
        char spaceSymbol = ' ';
        if (token->flags[S21_F_FLAG_ZERO_PADDING]) {
            spaceSymbol = '0';
        }
        fori(spacesCount) {
            *c++ = spaceSymbol;
        }
    }
    fori(bufLen) {
        *c++ = buf[i];
    }
    if (token->flags[S21_F_FLAG_LEFT_JUSTIFY]) {
        fori(spacesCount) {
            *c++ = ' ';
        }
    }
    return c - str;
}

static int s21_fromTokenToString(char *str, FormatToken *token) {
    char *c = str;
    char *buf = s21_bufferForming(token);
    if (buf) {
        c += s21_tokenJustify(c, buf, token);

        char *fs = token->freeSymbols;
        for (; *fs && *fs != '%'; fs++) {
            *c++ = *fs;
        }
        free(buf);
    }
    return c - str;
}

static int s21_stringForming(char *str, FormatToken *tokenList) {
    char *c = str;

    while (tokenList) {
        c += s21_fromTokenToString(c, tokenList);
        if (tokenList->specifier != 's') {
            free(tokenList->data);
        }
        FormatToken *token = tokenList;
        tokenList = token->next;
        free(token);
    }
    *c++ = '\0';

    return c - str;
}

int s21_sprintf(char *str, const char *format, ...) {
    int result = 0;

    va_list args;
    va_start(args, format);
    FormatToken *tokenList = s21_formatParcing(format, &args);
    s21_stringForming(str, tokenList);
    result = s21_strlen(str);
    va_end(args);
    return result;
}
