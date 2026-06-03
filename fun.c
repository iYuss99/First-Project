#include "head.h"

static struct User akun[MAX_USERS];
static struct Owner info[MAX_USERS];
static int jumlahUser = 0;
static long long atm_cash = 50000000LL;
int H = 1;

void clear_screen(void) { system("cls"); }
void pause_seconds(float s) { sleep(s); }
void clear_buffer(void) {while ((getchar()) != '\n' && getchar() != EOF);}

void banner(void) {
    puts("=============================================");
    puts("=============  BANK KELOMPOK 2  =============");
    puts("=============================================\n");
}

    void chomp(char *s) { size_t l = strlen(s); if (l && s[l-1] == '\n') s[l-1] = '\0'; }

    bool is_digits(const char *s, size_t expected_len) {
        if (strlen(s) != expected_len) return false;
        for (size_t i = 0; i < expected_len; ++i) if (!isdigit((unsigned char)s[i])) return false;
        return true;
    }
    
    void swapLong(long long *xp,long long *yp){
        long long temp = *xp;
        *xp = *yp;
        *yp = temp;
    }

    void swapChar(char (*xp)[],char (*yp)[], int length){
        char temp[length];
        strcpy(temp, *xp);
        strcpy(*xp, *yp);
        strcpy(*yp, temp);
    }

    void loadingDot() {
        clear_screen(); 
        banner();
        printf("\n\n               Mohon Tunggu"), 
        printf("."); 
        pause_seconds(1);
        printf("."); 
        pause_seconds(1);
        printf("."); 
        system("cls");
    }

    void intro() {
        clear_screen();
        banner();
        printf("  Selamat datang di Mesin ATM Kelompok 2!");
        pause_seconds(2);
        clear_screen();
        banner();
    }

    int containsLetter(const char str[]) {
        for (int i = 0; str[i] != '\0'; i++) {
            if (isalpha(str[i])) {
                return 1;
            }
        }
        return 0;
    }

    //Bubble Sort
    void bubbleSort(struct User arr[], int n){
        int i, j;
        bool swapped;
        for (i = 0; i < n - 1; i++) {
            swapped = false;
            for (j = 0; j < n - i - 1; j++) {
                if (arr[j].balance < arr[j + 1].balance) {
                    swapLong(&arr[j].balance,&arr[j + 1].balance);
                    swapChar(&arr[j].norek, &arr[j + 1].norek, REK_LEN);
                    swapped = true;
                }
            }
        if (swapped == false)
                break;
        }
    }

    void bubbleSortString(struct Owner arr[], int n){
        int i, j;
        bool swapped;
        for (i = 0; i < n - 1; i++) {
            swapped = false;
            for (j = 0; j < n - i - 1; j++) {
                if (strcmp(arr[j].nama, arr[j + 1].nama)  > 0) {
                    swapChar(&arr[j].nama, &arr[j + 1].nama, NAME_LEN);
                    swapped = true;
                }
            }
        
        if (swapped == false)
                break;
        }
    }

void create_default_files(void) {
    FILE *f = fopen("AkunUser.txt", "w");
    if (!f) return;

    fprintf(f, "1010101010 0987654321 0 Maintenance false\n");
    fprintf(f, "6969696969 1234512345 0 Manager true\n");
    fprintf(f, "1234567890 100307 1000000 Platinum false\n");
    fprintf(f, "0987654321 100307 1000000 basic false\n");
    fprintf(f, "7878787878 8787878787 123123123 basic true\n");
    fprintf(f, "7676767676 6565656565 6565656565 basic true\n");
    fclose(f);

    f = fopen("InfoUser.txt", "w");
    if (!f) return;

    fprintf(f, "Tukang servis pinggir jalan> 1010101010> Rumah depan upnvj> 081568751073> servis@upn.com>\n");
    fprintf(f, "Evans Adam> 6969696969> Gunung Putri> 081319145075> evans@ex.com>\n");
    fprintf(f, "orang kaya> 1234567890> BSD> 083185960783> orang@kaya.com>\n");
    fprintf(f, "orang kaya juga> 0987654321> Amrik> 084535657686> orangkaya@gmail.com>\n");
    fprintf(f, "Ahyan Nubaid> 7878787878> Rumah> 081234567890> ahyan@email.yan>\n");
    fprintf(f, "Darius anak serius> 7676767676> Depok> 080987654321> darius@darius.darius>\n");
    fclose(f);
}

void load_accounts(void) {
    FILE *f = fopen("AkunUser.txt", "r");
    if (!f) {
        create_default_files();
        f = fopen("AkunUser.txt", "r");
        if (!f) return;
    }

    jumlahUser = 0;
    while (jumlahUser < MAX_USERS && !feof(f)) {
        char norek[REK_LEN]; char pin[PIN_LEN]; long long bal; char priv[PRIV_LEN]; char adminstr[8];
        int r = fscanf(f, "%10s %19s %lld %19s %7s\n", norek, pin, &bal, priv, adminstr);
        if (r == 5) {
            strncpy(akun[jumlahUser].norek, norek, REK_LEN);
            strncpy(akun[jumlahUser].pin, pin, PIN_LEN);
            akun[jumlahUser].balance = bal;
            strncpy(akun[jumlahUser].privilage, priv, PRIV_LEN);
            akun[jumlahUser].admin = (strcmp(adminstr, "true") == 0);
            jumlahUser++;
        } else {
            break;
        }
    }
    fclose(f);
}

void load_info(void) {
    FILE *f = fopen("InfoUser.txt", "r");
    if (!f) return; // info optional

    int idx = 0;
    char line[512];
    while (idx < MAX_USERS && fgets(line, sizeof(line), f)) {
        chomp(line);
        char *p = line;
        char *tok;
        tok = strtok(p, ">");
        if (!tok) continue; strncpy(info[idx].nama, tok, NAME_LEN);
        tok = strtok(NULL, ">"); if (!tok) continue; strncpy(info[idx].nomorrek, tok+ (tok[0]==' '), REK_LEN);
        tok = strtok(NULL, ">"); if (!tok) continue; strncpy(info[idx].alamat, tok+ (tok[0]==' '), ADDR_LEN);
        tok = strtok(NULL, ">"); if (!tok) continue; strncpy(info[idx].notelp, tok+ (tok[0]==' '), 20);
        tok = strtok(NULL, ">"); if (!tok) continue; strncpy(info[idx].email, tok+ (tok[0]==' '), EMAIL_LEN);
        idx++;
    }
    fclose(f);
}

void save_accounts(void) {
    FILE *f = fopen("AkunUser.txt", "w");
    if (!f) { perror("Gagal menyimpan AkunUser.txt"); return; }
    for (int i = 0; i < jumlahUser; ++i) {
        fprintf(f, "%s %s %lld %s %s\n",
            akun[i].norek,
            akun[i].pin,
            akun[i].balance,
            akun[i].privilage,
            akun[i].admin ? "true" : "false");
    }
    fclose(f);
}

void save_info(void) {
    FILE *f = fopen("InfoUser.txt", "w");
    if (!f) { perror("Gagal menyimpan InfoUser.txt"); return; }
    for (int i = 0; i < jumlahUser; ++i) {
        fprintf(f, "%s> %s> %s> %s> %s>\n",
            info[i].nama,
            info[i].nomorrek,
            info[i].alamat,
            info[i].notelp,
            info[i].email);
    }
    fclose(f);
}
//Linear Search
int find_user_by_rek(const char *norek) {
    for (int i = 0; i < jumlahUser; ++i) if (strcmp(akun[i].norek, norek) == 0) return i;
    return -1;
}

void read_line(char *buf, size_t sz) {
    fgets(buf, sz, stdin);
    chomp(buf);
}

void show_main_menu(int idxUser) {
    banner();
    printf("Halo, %s\n", info[idxUser].nama[0] ? info[idxUser].nama : "User");
    printf("Status: %s\n",
        akun[idxUser].balance >= kaya_pro_max ? "Orang Kaya Pro Max" :
        akun[idxUser].balance >= crazy_kaya   ? "Orang kaya gila" :
        akun[idxUser].balance >= kaya         ? "Orang asli punya duit" :
        akun[idxUser].balance >= normal_pro   ? "Orang Normal berduit" :
        akun[idxUser].balance >= normal       ? "Orang Normal" :
        akun[idxUser].balance >= miskin_pro   ? "Miskin Pro" :
                                                "Miskin"
    );
    printf("Saldo: Rp.%lld\n\n", akun[idxUser].balance);
    puts("Menu");
    puts("    1. Tarik Tunai");
    puts("    2. Transfer");
    puts("    3. Setor Tunai");
    puts("    4. Info Akun");
    puts("    5. Exit");
    if (strcmp(akun[idxUser].privilage, "Maintenance") == 0) puts("    100. Cek isi ATM");
    if (akun[idxUser].admin) puts("    69. Mode Admin");
}

void do_withdraw(int idxUser) {
    loadingDot();
    banner();
    char option[16]; long long keluar = 0;
    puts("Pilih nominal: \n1). 50000 \n2). 100000 \n3). 250000 \n4). Nominal Lain");
    printf("pilih: "); read_line(option, sizeof(option));
    if (strcmp(option, "1") == 0) keluar = 50000;
    else if (strcmp(option, "2") == 0) 
    keluar = 100000;
    else if (strcmp(option, "3") == 0) 
    keluar = 250000;
    else if (strcmp(option, "4") == 0) {
        char tmp[32]; printf("Masukkan nominal (kelipatan 50000): "); 
        read_line(tmp, sizeof(tmp));
        keluar = atoll(tmp);
        if (keluar <= 0 || keluar % 50000 != 0 || containsLetter(tmp)) { 
            puts("Nominal tidak valid."); 
            pause_seconds(1); 
            return; 
        }
    } else { 
        puts("Pilihan salah."); 
        pause_seconds(1); 
        main_user_loop(idxUser); 
    }

    if (keluar > akun[idxUser].balance || akun[idxUser].balance <= 50000) { 
        puts("Saldo anda tidak mencukupi."); 
        pause_seconds(1); 
        return; 
    } else if (keluar > atm_cash) {
        puts("Saldo mesin ATM tidak cukup."); 
        pause_seconds(1); 
        return; 
    } else {
        akun[idxUser].balance -= keluar; 
        atm_cash -= keluar;
        puts("Transaksi berhasil."); printf("Sisa saldo: %lld\n", akun[idxUser].balance); save_accounts(); pause_seconds(1);
    }
}

void do_deposit(int idxUser) {
    loadingDot();
    banner();
    char tmp[64]; printf("Masukkan nominal setor (kelipatan 50000): "); read_line(tmp, sizeof(tmp));
    long long nominal = atoll(tmp);
    if (nominal <= 0 || nominal % 50000 != 0) { puts("Nominal tidak valid."); pause_seconds(1); return; }
    akun[idxUser].balance += nominal; atm_cash += nominal; save_accounts(); puts("Setor berhasil."); pause_seconds(1);
}

void do_transfer(int idxUser) {
    loadingDot();
    banner();
    char tujuan[REK_LEN]; printf("Masukkan nomor rekening tujuan: "); read_line(tujuan, sizeof(tujuan));
    if (!is_digits(tujuan, 10)) { puts("Nomor rekening tidak valid."); pause_seconds(1); return; }
    int idxTo = find_user_by_rek(tujuan);
    if (idxTo == -1) { puts("Rekening tujuan tidak ditemukan."); pause_seconds(1); return; }
    clear_buffer();
    char tmp[64]; printf("Masukkan nominal transfer: "); read_line(tmp, sizeof(tmp));
    long long transfer = atoll(tmp);
    if (transfer <= 0) { puts("Nominal tidak valid."); pause_seconds(1); return; }
    long long fee = (long long)(transfer * FEE_RATE);
    long long total = transfer + fee;
    if (akun[idxUser].balance <= 50000) { puts("Saldo dalam tabungan tidak dapat digunakan."); pause_seconds(3); return; }
    else if (total > akun[idxUser].balance) { puts("Saldo tidak cukup (termasuk fee)."); pause_seconds(3); return; }

    akun[idxUser].balance -= total;
    akun[idxTo].balance += transfer;
    save_accounts(); puts("Transfer berhasil."); printf("Fee: %lld\n", fee); pause_seconds(1);
}

void do_info(int idxUser) {
    loadingDot();
    banner();
    printf("---Informasi Pengguna---\nNama: %s\nAlamat: %s\nEmail: %s\nNo.Telp: %s\n\n",
           info[idxUser].nama, info[idxUser].alamat, info[idxUser].email, info[idxUser].notelp);
    puts("Tekan Enter untuk kembali."); getchar();
}

void admin_menu(void) {
    while (1) {
        clear_screen(); banner();
        puts("Menu Admin:");
        puts("  1. Registrasi Rekening");
        puts("  2. Ubah Saldo");
        puts("  3. Cek Isi ATM");
        puts("  4. Cek Saldo Berdasarkan Urutan");
        puts("  5. Daftar Nama Nasabah");
        puts("  6. Kembali ke menu utama");
        printf("Pilih: ");
        char opt[100]; 
        read_line(opt, sizeof(opt));
        if (strcmp(opt, "1") == 0) {
            create_akun();
        } else if (strcmp(opt, "2") == 0) {
            loadingDot();
            banner();
            char norek[REK_LEN]; printf("Masukkan No. Rekening: "); read_line(norek, sizeof(norek));
            int idx = find_user_by_rek(norek);
            if (idx == -1) { 
                puts("Rekening tidak ditemukan."); 
                pause_seconds(1); 
            continue; 
            }
            clear_buffer();
            printf("Saldo Rekening: %d\n", akun[idx].balance);
            char tmp[32]; 
            printf("\n-------------------Warning-------------------\n---   Saldo akan diubah sesuai nominal!   ---\n---------------------------------------------\n\nMasukkan nominal: "); 
            read_line(tmp, sizeof(tmp));
            long long delta = atoll(tmp);
            if (delta >= 0) {
                akun[idx].balance = delta; save_accounts(); puts("Saldo berhasil diubah."); pause_seconds(1);
            } else {
                printf("Input tidak boleh negatif!"); pause_seconds(1);
            }
            
        } else if (strcmp(opt, "3") == 0) {
            loadingDot();
            banner();
            printf("Sisa Uang Tunai dalam ATM: %lld\n", atm_cash); 
            puts("Tekan Enter."); 
            getchar();
        } else if (strcmp(opt, "4") == 0) {
            loadingDot();
            banner(); 
            struct User sortedAkun[MAX_USERS];
            for (int i = 0; i < jumlahUser; i++) {
                sortedAkun[i] = akun[i];            
            }
            bubbleSort(sortedAkun, jumlahUser);
            printf("Daftar Saldo Berdasarkan urutan: \n");
            for (int i = 0; i < jumlahUser; i++) {
                for (int j = 0; j < jumlahUser; j++) {
                    if (strcmp(sortedAkun[i].norek, info[j].nomorrek) == 0) {
                        printf("%d. %s : %lld\n", i + 1, info[j].nama, sortedAkun[i].balance);
                    }
                }
            } 
            puts("Tekan Enter."); 
            getchar();
        } else if (strcmp(opt, "5") == 0) {
            loadingDot();
            banner();
            struct Owner sortedInfo[MAX_USERS];
            for (int i = 0; i < jumlahUser; i++) {
                sortedInfo[i] = info[i];            
            }
            bubbleSortString(sortedInfo, jumlahUser); 
            printf("Daftar Nama Nasabah:\n");
            for (int i = 0; i < jumlahUser; i++) {
                printf("%d. %s\n", i + 1, sortedInfo[i].nama);
            } 
            puts("Tekan Enter."); 
            getchar();
        } else if (strcmp(opt, "6") == 0) break;
        else { puts("Pilihan salah."); pause_seconds(1); }
    }
}

    void create_akun (void) {
            char norek[REK_LEN]; 
            char pin[PIN_LEN]; 
            char balstr[32]; 
            char priv[PRIV_LEN]; 
            char adminstr[8];

            if (jumlahUser >= MAX_USERS) { 
                puts("Kapasitas penuh."); 
                pause_seconds(1); 
                return; 
            }

            clear_screen();
            banner();
            
            printf("Masukkan No. Rekening (10 digit): "); 
            read_line(norek, sizeof(norek));
            
            if (!is_digits(norek, 10) || containsLetter(norek)) { 
                puts("No. Rekening tidak valid."); 
                pause_seconds(1); 
                return; 
            }
            
            if (find_user_by_rek(norek) != -1) { 
                puts("No. rekening sudah terdaftar."); 
                pause_seconds(1); 
                return; 
            }

            clear_buffer();
            printf("Masukkan PIN (hanya angka): "); 
            read_line(pin, sizeof(pin)); 
            
            if (!is_digits(pin, strlen(pin))) { 
                puts("PIN tidak valid."); 
                pause_seconds(1); 
                return; 
            }
            
            printf("Masukkan saldo awal: "); 
            read_line(balstr, sizeof(balstr)); 
            
            if (containsLetter(norek)) { 
                puts("Saldo awal tidak valid."); 
                pause_seconds(1); 
                return;             
            }
            long long bal = atoll(balstr);
            
            printf("Masukkan privilege: "); 
            read_line(priv, sizeof(priv));
            
            printf("Apakah admin? (true/false): "); 
            read_line(adminstr, sizeof(adminstr));

            bool isAdminValid = (strcmp(adminstr, "true") == 0) || (strcmp(adminstr, "false") == 0);
            if (!isAdminValid) { 
                puts("Autorisasi tidak valid"); 
                pause_seconds(1); 
                return;             
            }
            
            strncpy(akun[jumlahUser].norek, norek, REK_LEN);
            strncpy(akun[jumlahUser].pin, pin, PIN_LEN);
            akun[jumlahUser].balance = bal;
            strncpy(akun[jumlahUser].privilage, priv, PRIV_LEN);
            akun[jumlahUser].admin = (strcmp(adminstr, "true") == 0);
            
            printf("Nama pemilik: "); 
            read_line(info[jumlahUser].nama, NAME_LEN);
            strncpy(info[jumlahUser].nomorrek, norek, REK_LEN);
            printf("Alamat pemilik: "); read_line(info[jumlahUser].alamat, ADDR_LEN);
            printf("No.Telp pemilik: "); 
            
            read_line(info[jumlahUser].notelp, sizeof(info[jumlahUser].notelp));
            printf("Email pemilik: "); read_line(info[jumlahUser].email, EMAIL_LEN);
            
            jumlahUser++;
            save_accounts(); 
            save_info();
            puts("Registrasi berhasil.");
            pause_seconds(1);
    }

    // Global Variable for exiting the program
    int handle_exit(const char *inputrek) {
    if (strcmp(inputrek, "exit") == 0) {
        H = 0;
        clear_screen();
        banner();
        puts("                Terima kasih.");
        return 1;
    }

    return 0;
    }
    
    int handle_debug(const char *inputrek) {
        if (strcmp(inputrek, "debug") != 0) return 0;
        FILE *d = fopen("Debugging.txt", "w");
        if (d) {
            for (int i = 0; i < jumlahUser; ++i) {
                fprintf(d, "%s> %s> %s> %s> %s>\n",
                    info[i].nama, info[i].nomorrek, info[i].alamat,
                    info[i].notelp, info[i].email
                );
            }
            fclose(d);
            puts("Debugging.txt dibuat.");
            pause_seconds(1);
        }
        return 1;
    }

    int validate_rekening(const char *inputrek) {
        if (!is_digits(inputrek, 10)) {
            puts("Nomor rekening harus 10 digit angka.");
            pause_seconds(1);
            return -1;
        }

        int idxUser = find_user_by_rek(inputrek);
        if (idxUser == -1) {
            puts("Rekening tidak valid.");
            pause_seconds(1);
            return -1;
        }

        return idxUser;
    }

int request_pin(int idxUser) {
    clear_screen();
    banner();
    clear_buffer();
    printf("Masukkan PIN: ");
    char inputpin[PIN_LEN];
    read_line(inputpin, sizeof(inputpin));
    if (strcmp(inputpin, akun[idxUser].pin) != 0) {
        puts("PIN salah.");
        pause_seconds(1);
        return 0;
    }    
    return 1;
}

void main_user_loop(int idxUser) {
        clear_screen();
        show_main_menu(idxUser);
        printf("Pilih: ");
        char pilihan[100];
        read_line(pilihan, sizeof(pilihan));
        if (strcmp(pilihan, "1") == 0) do_withdraw(idxUser);
        else if (strcmp(pilihan, "2") == 0) do_transfer(idxUser);
        else if (strcmp(pilihan, "3") == 0) do_deposit(idxUser);
        else if (strcmp(pilihan, "4") == 0) do_info(idxUser);
        else if (strcmp(pilihan, "5") == 0) {
            save_accounts();
            save_info();
            return;
        }
        else if (strcmp(pilihan, "100") == 0 && strcmp(akun[idxUser].privilage, "Maintenance") == 0) {
            clear_screen(); 
            banner();
            printf("Sisa Uang Tunai dalam ATM: %lld\n", atm_cash);
            puts("Tekan Enter."); 
            getchar();
        }

        else if (strcmp(pilihan, "69") == 0 && akun[idxUser].admin) {
            admin_menu();
        }
        else {
            puts("Pilihan salah.");
            pause_seconds(1);
            main_user_loop(idxUser);
        }

        main_user_loop(idxUser);

    }