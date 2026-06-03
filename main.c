#include "head.h"

int main(void) {
    intro();
    load_accounts();
    load_info();
    while (H == 1) {
        clear_screen();
        banner();
        printf("Masukkan No. Rekening: ");
        char inputrek[REK_LEN];
        read_line(inputrek, sizeof(inputrek));
        if (handle_debug(inputrek))
            continue;

        if (handle_exit(inputrek))
            continue;
        int idxUser = validate_rekening(inputrek);
        if (idxUser == -1)
            continue;

        if (!request_pin(idxUser))
            continue;
        loadingDot();
        main_user_loop(idxUser);
    }
    return 0;
}