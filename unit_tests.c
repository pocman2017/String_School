#include <check.h>
#include "s21_string.h"
#include <string.h>
#include <stdlib.h>
#include <signal.h>
#include <stdio.h>
// c
START_TEST(strlenTest) {
    ck_assert_uint_eq(s21_strlen("abcd"), strlen("abcd"));
    ck_assert_uint_eq(s21_strlen(""), strlen(""));
    ck_assert_uint_eq(s21_strlen("hello!"), strlen("hello!"));
    ck_assert_uint_eq(s21_strlen("hello! \n hi!"), strlen("hello! \n hi!"));
    ck_assert_uint_eq(s21_strlen("hello! \0 hi!"), strlen("hello! "));
}
END_TEST

START_TEST(strchrTest) {
    char str[7]="abcdbc";
    char *empty_str = "";
    ck_assert_ptr_eq(s21_strchr(str, 'b'), strchr(str, 'b'));
    ck_assert_str_eq(s21_strchr(str, 'b'), "bcdbc");
    ck_assert_ptr_eq(s21_strchr(str, 'e'), strchr(str, 'e'));
    ck_assert_ptr_eq(s21_strchr(empty_str, 'b'), strchr(empty_str, 'b'));
    ck_assert_ptr_eq(s21_strchr(str, 0), strchr(str, 0));
    ck_assert_ptr_null(s21_strchr(str, 'e'));
}
END_TEST

START_TEST(strcmpTest) {
    char *s21_mem = malloc(10);
    char *mem = malloc(10);

    memset(s21_mem, 'i', 10);
    memset(mem, 'i', 10);
    mem[9]='\0';
    s21_mem[9]='\0';

    ck_assert_int_eq(s21_strcmp(s21_mem, mem), strcmp(s21_mem, mem));

    mem[4]='y';
    ck_assert_int_eq(s21_strcmp(s21_mem, mem), strcmp(s21_mem, mem));

    mem[4]='a';
    ck_assert_int_eq(s21_strcmp(s21_mem, mem), strcmp(s21_mem, mem));
    ck_assert_int_eq(s21_strcmp(s21_mem, ""), strcmp(s21_mem, ""));
    ck_assert_int_eq(s21_strcmp("", mem), strcmp("", mem));
    free(mem);
    free(s21_mem);
}
END_TEST

START_TEST(strncmpTest) {
    char *s21_mem = malloc(10);
    char *mem = malloc(10);

    memset(s21_mem, 'i', 10);
    memset(mem, 'i', 10);

    ck_assert_int_eq(s21_strncmp(s21_mem, mem, 2), strncmp(s21_mem, mem, 2));
    ck_assert_int_eq(s21_strncmp(s21_mem, mem, 10), strncmp(s21_mem, mem, 10));
    ck_assert_int_eq(s21_strncmp(s21_mem, mem, 0), strncmp(s21_mem, mem, 0));

    mem[4]='y';

    ck_assert_int_eq(s21_strncmp(s21_mem, mem, 2), strncmp(s21_mem, mem, 2));
    ck_assert_int_eq(s21_strncmp(s21_mem, mem, 10), strncmp(s21_mem, mem, 10));
    ck_assert_int_eq(s21_strncmp(s21_mem, "", 10), strncmp(s21_mem, "", 10));
    ck_assert_int_eq(s21_strncmp("", mem, 10), strncmp("", mem, 10));
    free(mem);
    free(s21_mem);
}
END_TEST

START_TEST(strcatTest) {
    char str[10], s21_str[10];
    for (int i = 0; i < 10; i++) {
        str[i] = '\0';
        s21_str[i] = '\0';
    }
    ck_assert_str_eq(s21_strcat(s21_str, ""), strcat(str, ""));
    ck_assert_str_eq(s21_strcat(s21_str, "d"), strcat(str, "d"));
    ck_assert_str_eq(s21_strcat(s21_str, "v"), strcat(str, "v"));
    ck_assert_str_eq(s21_strcat(s21_str, "d"), strcat(str, "d"));
    ck_assert_str_eq(s21_strcat(s21_str, ""), strcat(str, ""));
    ck_assert_str_eq(s21_strcat(s21_str, "12"), strcat(str, "12"));
    ck_assert_str_eq(s21_strcat(s21_str, "1z"), strcat(str, "1z"));
}
END_TEST

START_TEST(strncatTest) {
    char str[10], s21_str[10];
    for (int i = 0; i < 10; i++) {
        str[i] = '\0';
        s21_str[i] = '\0';
    }
    ck_assert_str_eq(s21_strncat(s21_str, "", 0), strncat(str, "", 0));
    ck_assert_str_eq(s21_strncat(s21_str, "", 1), strncat(str, "", 1));
    ck_assert_str_eq(s21_strncat(s21_str, "d", 1), strncat(str, "d", 1));
    ck_assert_str_eq(s21_strncat(s21_str, "vv", 1), strncat(str, "vv", 1));
    ck_assert_str_eq(s21_strncat(s21_str, "dvd", 1), strncat(str, "dvd", 1));
    ck_assert_str_eq(s21_strncat(s21_str, "", 1), strncat(str, "", 1));
    ck_assert_str_eq(s21_strncat(s21_str, "12", 2), strncat(str, "12", 2));
    ck_assert_str_eq(s21_strncat(s21_str, "1z", 3), strncat(str, "1z", 3));
}
END_TEST

START_TEST(memchrTest) {
    char str[6] = "abcdbc";
    char *empty_str = "";
    ck_assert_ptr_eq(s21_memchr(str, 'b', 3), memchr(str, 'b', 3));
    ck_assert_ptr_eq(s21_memchr(str, 'b', 1), memchr(str, 'b', 1));
    ck_assert_ptr_eq(s21_memchr(str, 'b', 0), memchr(str, 'b', 0));
    ck_assert_ptr_eq(s21_memchr(str, 'b', 6), memchr(str, 'b', 6));
    ck_assert_ptr_eq(s21_memchr(str, 'e', 6), memchr(str, 'e', 6));
    ck_assert_ptr_eq(s21_memchr(str, 'e', 3), memchr(str, 'e', 3));
    ck_assert_ptr_eq(s21_memchr(str, 'e', 0), memchr(str, 'e', 0));
    ck_assert_ptr_eq(s21_memchr(str, 500, 2), memchr(str, 500, 2));
    ck_assert_ptr_eq(s21_memchr(empty_str, 500, 1), memchr(empty_str, 500, 1));
    ck_assert_ptr_eq(s21_memchr(empty_str, 'b', 10), memchr(empty_str, 'b', 10));
    ck_assert_ptr_eq(s21_memchr(str, 0, 1), memchr(str, 0, 1));
    ck_assert_ptr_eq(s21_memchr(empty_str, 0, 10), memchr(empty_str, 0, 10));
}
END_TEST

START_TEST(memcmpTest) {
    void *s21_mem = malloc(10);
    void *mem = malloc(10);

    memset(s21_mem, 'i', 10);
    memset(mem, 'i', 10);

    ck_assert_int_eq(s21_memcmp(s21_mem, mem, 2), memcmp(s21_mem, mem, 2));
    ck_assert_int_eq(s21_memcmp(s21_mem, mem, 10), memcmp(s21_mem, mem, 10));
    ck_assert_int_eq(s21_memcmp(s21_mem, mem, 0), memcmp(s21_mem, mem, 0));

    memset(s21_mem, 'y', 4);

    ck_assert_int_eq(s21_memcmp(s21_mem, mem, 2), memcmp(s21_mem, mem, 2));
    ck_assert_int_eq(s21_memcmp(s21_mem, mem, 10), memcmp(s21_mem, mem, 10));
    ck_assert_int_eq(s21_memcmp(s21_mem, "", 10), memcmp(s21_mem, "", 10));
    free(mem);
    free(s21_mem);
}
END_TEST

START_TEST(memsetTest) {
    void *s21_mem = malloc(10);
    void *mem = malloc(10);
    s21_memset(s21_mem, 'y', 10);
    memset(mem, 'y', 10);
    ck_assert_mem_eq(s21_mem, mem, 10);

    s21_memset(s21_mem, '5', 4);
    memset(mem, '5', 4);
    ck_assert_mem_eq(s21_mem, mem, 4);

    s21_memset(s21_mem, '\0', 10);
    memset(mem, '\0', 10);
    ck_assert_mem_eq(s21_mem, mem, 10);

    free(mem);
    free(s21_mem);
}
END_TEST

START_TEST(memcpyTest) {
    void *s21_mem = malloc(10);
    void *mem = malloc(10);
    ck_assert_mem_eq(s21_memcpy(s21_mem, mem, 10), mem, 10);
    free(s21_mem);
    free(mem);
}
END_TEST

START_TEST(memcpy_dest_bigger_srcTest) {
    void *s21_mem = malloc(5);
    void *mem = malloc(10);
    ck_assert_mem_eq(s21_memcpy(s21_mem, mem, 10), mem, 5);
    free(s21_mem);
    free(mem);
}
END_TEST

START_TEST(memcpy_src_bigger_destTest) {
    void *s21_mem = malloc(10);
    void *mem = malloc(5);
    ck_assert_mem_eq(s21_memcpy(s21_mem, mem, 10), mem, 10);
    ck_assert_mem_eq(s21_memcpy(s21_mem, mem, 8), mem, 8);
    free(s21_mem);
    free(mem);
}
END_TEST

START_TEST(memmoveTest) {
    void *s21_mem = malloc(10);
    void *mem = malloc(10);
    ck_assert_mem_eq(s21_memmove(s21_mem, mem, 10), mem, 10);
    free(s21_mem);
    free(mem);
}
END_TEST

START_TEST(strcpyTest) {
    char *s21_str = malloc(10);
    char *str = "1234567890";
    ck_assert_str_eq(s21_strcpy(s21_str, str), str);
    ck_assert_str_eq(s21_strcpy(s21_str, ""), s21_str);
    ck_assert_str_eq(s21_strcpy(s21_str, "123456789000"), "123456789000");
    free(s21_str);
}
END_TEST

START_TEST(strcnpyTest) {
    char *s21_str = malloc(10);
    char *str = malloc(10);

    ck_assert_str_eq(s21_strncpy(s21_str, "01234567890", 10), strncpy(str, "01234567890", 10));
    ck_assert_str_eq(s21_strncpy(s21_str, "012345678", 10), strncpy(str, "012345678", 10));
    ck_assert_str_eq(s21_strncpy(s21_str, "01234567", 0), strncpy(str, "01234567", 0));
    ck_assert_str_eq(s21_strncpy(s21_str, "", 10), strncpy(str, "", 10));
    free(s21_str);
    free(str);
}
END_TEST

START_TEST(strcspnTest) {
    ck_assert_uint_eq(s21_strcspn("aaaOOO", "O"), strcspn("aaaOOO", "O"));
    ck_assert_uint_eq(s21_strcspn("aaaOOOaa", "O"), strcspn("aaaOOOaa", "O"));
    ck_assert_uint_eq(s21_strcspn("aaaOOOoo", "Oo"), strcspn("aaaOOOo", "Oo"));
    ck_assert_uint_eq(s21_strcspn("aaaOOOoo", "Ooo"), strcspn("aaaOOOo", "Ooo"));
    ck_assert_uint_eq(s21_strcspn("", "O"), strcspn("", "O"));
    ck_assert_uint_eq(s21_strcspn("aaaOOOaa", ""), strcspn("aaaOOOaa", ""));
}
END_TEST

START_TEST(strpbrkTest) {
    char *str1 = "aAaxxxx";
    ck_assert_ptr_eq(s21_strpbrk(str1, "ax"), strpbrk(str1, "ax"));
    ck_assert_ptr_eq(s21_strpbrk(str1, "x"), strpbrk(str1, "x"));
    ck_assert_ptr_eq(s21_strpbrk(str1, "xA"), strpbrk(str1, "xA"));
    ck_assert_ptr_eq(s21_strpbrk(str1, "z"), strpbrk(str1, "z"));
    ck_assert_ptr_eq(s21_strpbrk(str1, ""), strpbrk(str1, ""));
    ck_assert_ptr_eq(s21_strpbrk("", "ax"), strpbrk("", "ax"));
}
END_TEST

START_TEST(strerrorTest) {
    for (int i = -3; i <= 108; i++) {
        ck_assert_str_eq(s21_strerror(i), strerror(i));
    }
}
END_TEST

START_TEST(strrchrTest) {
    char str[7]="abcdbc";
    char *empty_str = "";
    ck_assert_ptr_eq(s21_strrchr(str, 'b'), strrchr(str, 'b'));
    ck_assert_str_eq(s21_strrchr(str, 'b'), "bc");
    ck_assert_ptr_eq(s21_strrchr(str, 'e'), strrchr(str, 'e'));
    ck_assert_ptr_eq(s21_strrchr(empty_str, 'b'), strrchr(empty_str, 'b'));
    ck_assert_ptr_eq(s21_strrchr(str, 0), strrchr(str, 0));
    ck_assert_ptr_null(s21_strrchr(str, 'e'));
}
END_TEST

START_TEST(strspnTest) {
    ck_assert_uint_eq(s21_strspn("aaaOOO", "O"), strspn("aaaOOO", "O"));
    ck_assert_uint_eq(s21_strspn("aaaOOOaa", "O"), strspn("aaaOOOaa", "O"));
    ck_assert_uint_eq(s21_strspn("", "O"), strspn("", "O"));
    ck_assert_uint_eq(s21_strspn("aaaOOOaa", ""), strspn("aaaOOOaa", ""));
    ck_assert_uint_eq(s21_strspn("aaaOOOaaPPP", "Oa"), strspn("aaaOOOaaPPP", "Oa"));
    ck_assert_uint_eq(s21_strspn("aaaOOOaaPPP", "aO"), strspn("aaaOOOaaPPP", "aO"));
}
END_TEST

START_TEST(strstrTest) {
    char *str = "It is test for test";
    char *empty = "";
    ck_assert_ptr_eq(s21_strstr(str, "It"), strstr(str, "It"));
    ck_assert_ptr_eq(s21_strstr(str, "IT"), strstr(str, "IT"));
    ck_assert_ptr_null(s21_strstr(str, "IT"));
    ck_assert_ptr_eq(s21_strstr(str, " test"), strstr(str, " test"));
    ck_assert_ptr_eq(s21_strstr(str, " "), strstr(str, " "));
    ck_assert_ptr_eq(s21_strstr(str, ""), strstr(str, ""));
    ck_assert_ptr_eq(s21_strstr(empty, ""), strstr(empty, ""));
    ck_assert_ptr_eq(s21_strstr(empty, " test"), strstr(empty, " test"));
}
END_TEST

START_TEST(strtokTest) {
    char str[15] = "12|34*56|78m90";
    char s21_str[15] = "12|34*56|78m90";
    char delim[4] = "*m|";
    char *part = strtok(str, delim);
    char *s21_part = s21_strtok(s21_str, delim);
    ck_assert_str_eq(part, s21_part);

    while (part != NULL) {
      part = strtok(NULL, delim);
      s21_part = s21_strtok(S21_NULL, delim);
      if (part != NULL) {
          ck_assert_str_eq(part, s21_part);
      } else {
          ck_assert_ptr_null(s21_part);
      }
    }
}
END_TEST

START_TEST(to_upperTest) {
    char *upper_str;

    upper_str = s21_to_upper("Hello, 123!");
    ck_assert_str_eq(upper_str, "HELLO, 123!");
    free(upper_str);

    upper_str = s21_to_upper("HELLO, 123!");
    ck_assert_str_eq(upper_str, "HELLO, 123!");
    free(upper_str);

    upper_str = s21_to_upper("");
    ck_assert_str_eq(upper_str, "");
    free(upper_str);

    upper_str = s21_to_upper(S21_NULL);
    ck_assert_ptr_null(upper_str);
    free(upper_str);
}
END_TEST

START_TEST(to_lowerTest) {
    char *lower_str;

    lower_str = s21_to_lower("Hello, 123!");
    ck_assert_str_eq(lower_str, "hello, 123!");
    free(lower_str);

    lower_str = s21_to_lower("hello, 123!");
    ck_assert_str_eq(lower_str, "hello, 123!");
    free(lower_str);

    lower_str = s21_to_lower("");
    ck_assert_str_eq(lower_str, "");
    free(lower_str);

    lower_str = s21_to_lower(S21_NULL);
    ck_assert_ptr_null(lower_str);
    free(lower_str);
}
END_TEST

START_TEST(insertTest) {
    char *result;

    result = s21_insert("13", "2", 1);
    ck_assert_str_eq(result, "123");
    free(result);

    result = s21_insert("", "2", 2);
    ck_assert_ptr_null(result);
    free(result);

    result = s21_insert("hello", "", 0);
    ck_assert_str_eq(result, "hello");
    free(result);

    result = s21_insert("hello", "", 2);
    ck_assert_str_eq(result, "hello");
    free(result);

    result = s21_insert("hello", "", 6);
    ck_assert_ptr_null(result);
    free(result);
}
END_TEST

START_TEST(trimTest) {
    char *result;
    result = s21_trim(" 1221 ", "");
    ck_assert_str_eq(result, "1221");
    free(result);

    result = s21_trim("", "7");
    ck_assert_str_eq(result, "");
    free(result);

    result = s21_trim(" 1221 ", "1");
    ck_assert_str_eq(result, " 1221 ");
    free(result);

    result = s21_trim(" 1221 ", " 1");
    ck_assert_str_eq(result, "22");
    free(result);

    result = s21_trim(" 1221 ", " 12");
    ck_assert_str_eq(result, "");
    free(result);

    result = s21_trim(" 1221 ", NULL);
    ck_assert_str_eq(result, "1221");
    free(result);
}
END_TEST

START_TEST(printf_cTest) {
    short length = 100;
    char *str1 = calloc(length, sizeof(char));
    char *str2 = calloc(length, sizeof(char));
    int res1 = 0, res2 = 0;
    res1 = s21_sprintf(str1, "%c %c %c", ' ', '#', '@');
    res2 = sprintf(str2, "%c %c %c", ' ', '#', '@');
    ck_assert_str_eq(str1, str2);
    ck_assert_int_eq(res1, res2);
    free(str1);
    free(str2);
}
END_TEST

START_TEST(printf_dTest) {
    short length = 100;
    char *str1 = calloc(length, sizeof(char));
    char *str2 = calloc(length, sizeof(char));
    int res1 = 0, res2 = 0;
    long int n = 3;
    res1 = s21_sprintf(str1, "%ld%*.5d  % d   %+d %*d%-2.d", n, -2, 3, 2, 46,
                        4, -53, 9);
    res2 = sprintf(str2, "%ld%*.5d  % d   %+d %*d%-2.d", n, -2, 3, 2, 46,
                        4, -53, 9);
    ck_assert_str_eq(str1, str2);
    ck_assert_int_eq(res1, res2);
    free(str1);
    free(str2);
}
END_TEST

START_TEST(printf_iTest) {
    short length = 100;
    char *str1 = calloc(length, sizeof(char));
    char *str2 = calloc(length, sizeof(char));
    int res1 = 0, res2 = 0;
    short int n = 11;
    res1 = s21_sprintf(str1, "%hi %.5i %0i", n, -46, 57);
    res2 = sprintf(str2, "%hi %.5i %0i", n, -46, 57);
    ck_assert_str_eq(str1, str2);
    ck_assert_int_eq(res1, res2);
    free(str1);
    free(str2);
}
END_TEST

START_TEST(printf_fTest) {
    short length = 100;
    char *str1 = calloc(length, sizeof(char));
    char *str2 = calloc(length, sizeof(char));
    int res1 = 0, res2 = 0;
    long double n = -7.0004522;
    res1 = s21_sprintf(str1, "%Lf", n);
    res2 = sprintf(str2,  "%Lf", n);
    ck_assert_str_eq(str1, str2);
    ck_assert_int_eq(res1, res2);
    free(str1);
    free(str2);

    str1 = calloc(length, sizeof(char));
    str2 = calloc(length, sizeof(char));

    double m = -7.000;
    res1 = s21_sprintf(str1, "%f", m);
    res2 = sprintf(str2,  "%f", m);
    ck_assert_str_eq(str1, str2);
    ck_assert_int_eq(res1, res2);

    free(str1);
    free(str2);
}
END_TEST

START_TEST(printf_sTest) {
    short length = 100;
    char *str1 = calloc(length, sizeof(char));
    char *str2 = calloc(length, sizeof(char));
    int res1 = 0, res2 = 0;
    res1 = s21_sprintf(str1, "%.*s %.3s %s", -2, "Hello", " world", "!");
    res2 = sprintf(str2, "%.*s %.3s %s", -2, "Hello", " world", "!");
    ck_assert_str_eq(str1, str2);
    ck_assert_int_eq(res1, res2);
    free(str1);
    free(str2);
}
END_TEST

START_TEST(printf_uTest) {
    short length = 100;
    char *str1 = calloc(length, sizeof(char));
    char *str2 = calloc(length, sizeof(char));
    int res1 = 0, res2 = 0;
    unsigned short n = 2;
    unsigned long m = 33;
    res1 = s21_sprintf(str1, "%hu %lu %u", n, m, (unsigned)58432322);
    res2 = sprintf(str2, "%hu %lu %u", n, m, (unsigned)58432322);
    ck_assert_str_eq(str1, str2);
    ck_assert_int_eq(res1, res2);
    free(str1);
    free(str2);
}
END_TEST

int main(void) {
    Suite *s1 = suite_create("Core");
    TCase *tc1_1 = tcase_create("Core");
    SRunner *sr = srunner_create(s1);
    int nf;

    suite_add_tcase(s1, tc1_1);
    tcase_add_test(tc1_1, strlenTest);
    tcase_add_test(tc1_1, strchrTest);
    tcase_add_test(tc1_1, strcmpTest);
    tcase_add_test(tc1_1, strncmpTest);
    tcase_add_test(tc1_1, strcatTest);
    tcase_add_test(tc1_1, strncatTest);
    tcase_add_test(tc1_1, memchrTest);
    tcase_add_test(tc1_1, memcmpTest);
    tcase_add_test(tc1_1, memsetTest);
    tcase_add_test(tc1_1, memcpyTest);
    tcase_add_test(tc1_1, memcpy_dest_bigger_srcTest);
    tcase_add_test(tc1_1, memcpy_src_bigger_destTest);
    tcase_add_test(tc1_1, memmoveTest);
    tcase_add_test(tc1_1, strcpyTest);
    tcase_add_test(tc1_1, strcnpyTest);
    tcase_add_test(tc1_1, strcspnTest);
    tcase_add_test(tc1_1, strpbrkTest);
    tcase_add_test(tc1_1, strerrorTest);
    tcase_add_test(tc1_1, strrchrTest);
    tcase_add_test(tc1_1, strspnTest);
    tcase_add_test(tc1_1, strstrTest);
    tcase_add_test(tc1_1, strtokTest);
    tcase_add_test(tc1_1, to_upperTest);
    tcase_add_test(tc1_1, to_lowerTest);
    tcase_add_test(tc1_1, insertTest);
    tcase_add_test(tc1_1, trimTest);
    tcase_add_test(tc1_1, printf_cTest);
    tcase_add_test(tc1_1, printf_dTest);
    tcase_add_test(tc1_1, printf_iTest);
    tcase_add_test(tc1_1, printf_fTest);
    tcase_add_test(tc1_1, printf_sTest);
    tcase_add_test(tc1_1, printf_uTest);

    srunner_run_all(sr, CK_ENV);
    nf = srunner_ntests_failed(sr);
    srunner_free(sr);

    return nf == 0 ? 0 : 1;
}
