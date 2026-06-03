#ifndef head_h
#define head_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <unistd.h>

#define MAX_USERS 100
#define REK_LEN 11
#define PIN_LEN 20
#define NAME_LEN 50
#define ADDR_LEN 100
#define EMAIL_LEN 50
#define PRIV_LEN 20
#define FEE_RATE 0.01

// Exit Global Variable
extern int H;

void clear_screen(void);
void pause_seconds(float s);
void clear_buffer(void);
void banner(void);

struct User {
    char norek[REK_LEN];  
    char pin[PIN_LEN];    
    long long balance;
    char privilage[PRIV_LEN];
    bool admin;
};

struct Owner {
    char nama[NAME_LEN];
    char nomorrek[REK_LEN];
    char alamat[ADDR_LEN];
    char notelp[20];
    char email[EMAIL_LEN];
};

enum Status {
    miskin = 0,
    miskin_pro = 500000,
    normal = 1000000,
    normal_pro = 5000000,
    kaya = 10000000,
    crazy_kaya = 50000000,
    kaya_pro_max = 1000000000
};

void chomp(char *s);
bool is_digits(const char *s, size_t expected_len);
void swapLong(long long *xp,long long *yp);
void swapChar(char (*xp)[],char (*yp)[], int length);
void loadingDot();
void create_akun (void);
void intro();
int containsLetter(const char str[]);
void bubbleSort(struct User arr[], int n);
void bubbleSortString(struct Owner arr[], int n);
void create_default_files(void);
void load_accounts(void);
void load_info(void);
void save_accounts(void);
void save_info(void);
int find_user_by_rek(const char *norek);
void read_line(char *buf, size_t sz);
void show_main_menu(int idxUser);
void do_withdraw(int idxUser);
void do_deposit(int idxUser);
void do_transfer(int idxUser);
void do_info(int idxUser);
void admin_menu(void);
int handle_exit(const char *inputrek);
int handle_debug(const char *inputrek);
int validate_rekening(const char *inputrek);
int request_pin(int idxUser);
void main_user_loop(int idxUser);

#endif