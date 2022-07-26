#include "ui.h"
#include "tools.h"
#include "func.h"

int main(){
    //printf("\033[?25l");

    // pthread_t th2;
    // //pthread_create(&th1,NULL,(void *)&handleMain,NULL);
    // pthread_create(&th2,NULL,(void *)&timeC,NULL);
    // pthread_detach(th2);

    char funcBtn;

    while(1){
        clearDown();
        system("clear");
        gotoxy(1,1);
        titleUI();
        funcBtn = getch();
        switch(funcBtn){
            case '1':
                showAll();
                gotoxy(20,1);
                printf("add结束");
                break;
            case '2':
                add();
                break;
            case '3':
                search();
                break;
            case '4':
                update();
                break;
            case '5':
                del();
                break;
            case '6':
                gotoxy(20,1);
                printf("see you\n");
                exit(0);
                break;
            default:
                // do nothing
                break;
        }
    }

    //printf("\033[?25h");

    return 0;
}