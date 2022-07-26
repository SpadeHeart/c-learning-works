#include "tools.h"

char getch(){
    struct termios tmtemp,tm;
    char c;
    int fd=0;
    if(tcgetattr(fd,&tm) != 0){      /*获取当前的终端属性设置，并保存到tm结构体中*/
        return -1;
    }
    tmtemp=tm;
    cfmakeraw(&tmtemp);     /*将tetemp初始化为终端原始模式的属性设置*/
    if(tcsetattr(fd,TCSANOW,&tmtemp) != 0){     /*将终端设置为原始模式的设置*/
        return -1;
    }
    c=getchar();
    if(tcsetattr(fd,TCSANOW,&tm) != 0){      /*接收字符完毕后将终端设置回原来的属性*/
        return 0;
    }
    return c;
}

void gotoxy(int x, int y){
	// HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	// COORD coord = {x, y};

	// SetConsoleCursorPosition(hOut, coord);
    //
    printf("\033[%d;%dH", (x), (y));
    printf("\033[0m");
    
}

void arr2pnt(char * des,char src[],int len){
    int i=0;
    while(len--){
        //des = src;
        *(des) = *(src+i);
        //src++;
        i++;
        des++;
    }
}

void locRemoveR(char * way){
    int i=0;
    while(1){
        if(way[i]=='\n'){
            way[i]='\0';
            break;
        }
        if(way[i]=='\0'){
            break;
        }
        i++;
    }
}

char **split(const char *source, char flag)
{
    char **pt;
    int j, n = 0;
    int count = 1;
    int len = strlen(source);
    // 动态分配一个 *tmp，静态的话，变量len无法用于下标
    char *tmp = (char*)malloc((len + 1) * sizeof(char));
    tmp[0] = '\0';

    for (int i = 0; i < len; ++i)
    {
        if (source[i] == flag && source[i+1] == '\0')
            continue;
        else if (source[i] == flag && source[i+1] != flag)
            count++;
    }
    // 多分配一个char*，是为了设置结束标志
    pt = (char**)malloc((count+1) * sizeof(char*));

    count = 0;
    for (int i = 0; i < len; ++i)
    {
        if (i == len - 1 && source[i] != flag)
        {
            tmp[n++] = source[i];
            tmp[n] = '\0';  // 字符串末尾添加空字符
            j = strlen(tmp) + 1;
            pt[count] = (char*)malloc(j * sizeof(char));
            strcpy(pt[count++], tmp);
        }
        else if (source[i] == flag)
        {
            j = strlen(tmp);
            if (j != 0)
            {
                tmp[n] = '\0';  // 字符串末尾添加空字符
                pt[count] = (char*)malloc((j+1) * sizeof(char));
                strcpy(pt[count++], tmp);
                // 重置tmp
                n = 0;
                tmp[0] = '\0';
            }
        }
        else
            tmp[n++] = source[i];
    }
    
    // 释放tmp
	free(tmp);
	
    // 设置结束标志
    pt[count] = NULL;

    return pt;
}

void Input(char * res,int type){
    

    char ch; //当前输入字符
    char arr[MAXINPUT]; //存储输入字符串
    char ch_tmp[4]; //一次存一个汉字外加一个\0
    //memset(res,0,MAXINPUT);
    int i=0; //输入长度
    int ch_i = 0; //一个汉字占3个字节,没三个字节显示一次实现让用户看到输入的汉字
    while(1){
        ch = getch();
        if(type == TYPE_NUM){
            if((ch>='0' && ch<='9') || ch=='.'){
                printf("%c",ch);
                InputY++;
                arr[i++]=ch;
            }
        }else if(type==TYPE_CHINESE){
            if(ch<0 || ch>127){
                arr[i++]=ch;
                ch_tmp[ch_i] = ch;
                ch_i++;
                if(ch_i==3){
                    //ch_i++;
                    ch_tmp[ch_i] = '\0';
                    // printf("in ");
                    printf("%s",ch_tmp);
                    InputY+=2;
                    // printf(" out\n");
                    ch_i=0;
                }
            }
        }
        
        if(ch==13){//回车键处理
            // *res = '\0';
            // res++;
            arr[i++]='\0';
            // printf("  %s\n",arr);
            // printf("len = %d\n",i);
            arr2pnt(res,arr,i);
            return;
            //return res;
        }else if(ch==127){//退格键处理
            if (i > 0 && type == TYPE_NUM) {
                printf("\b \b");
                InputY--;
                //fflush(stdout);
                i--;
            }else if(i>0 && type == TYPE_CHINESE){
                int c = 3,b=2;
                while(c--){
                    i--;
                }
                while(b--){
                    printf("\b \b");
                    InputY--;
                }
            }
        }else if(ch==27){//esc键处理
            //按下esc,输入结束,清空数组
            //memset(res,0,MAXINPUT);
            res = NULL;
            return;
        }
    }
}

void delay()//自定义延迟函数，不可使用sleep
{
    int x=1000;
    int y;
 
    while(x>0)
    {
        y=1000;
        while(y>0)
            y--;
        x--;
    }
}

void timeC(){

    char * weekTransform[7] = {"周日","周一","周二","周三","周四","周五","周六"};

    //int sec = 0;
    char * str; 
    char * res;
    //time_t *clock;

    //struct tm* timeinfo;

    str = (char *)malloc(30);
    res = (char *)malloc(30);
    //clock = (time_t *)malloc(30);
    //system("clear");
    
    while(1){
        gotoxy(18,3);
        //获取时间，保存到time_t结构体中。在time的返回值(sec)里面有全部秒数

        time_t times;
        time(&times);

        //strcpy(str,ctime(&times));


        strftime(str,30,"%Y-%m-%d %H:%M:%S %w",localtime(&times));

        char weekNum = str[strlen(str)-1];
        // struct tm* utcTime = localtime(&times);
        char * weekDay;
        weekDay = (char *)malloc(10);
        strcpy(weekDay,weekTransform[atoi(&weekNum)]);
        // int timeStrLen = sprintf(str, "%04d-%02d-%02d %02d:%02d:%02d %s", 
        //     utcTime->tm_year+1900, utcTime->tm_mon+1, utcTime->tm_mday, 
        //     utcTime->tm_hour, utcTime->tm_min, utcTime->tm_sec,weekDay);
        sprintf(res,"%s\b \b%s",str,weekDay);
        
        //printf("%s<->%c", str,weekNum);
        printf("%s", res);
        //free(timeinfo);
        gotoxy(InputX,InputY);
        usleep(30000);
        //delay();
    }
}

void timeSimple(){ //精确到天

    char * weekTransform[7] = {"周日","周一","周二","周三","周四","周五","周六"};

    //int sec = 0;
    char * str; 
    char * res;
    //time_t *clock;

    //struct tm* timeinfo;

    str = (char *)malloc(30);
    res = (char *)malloc(30);
    //clock = (time_t *)malloc(30);
    //system("clear");
    
    
        gotoxy(18,3);
        //获取时间，保存到time_t结构体中。在time的返回值(sec)里面有全部秒数

        time_t times;
        time(&times);

        //strcpy(str,ctime(&times));


        strftime(str,30,"%Y-%m-%d %w",localtime(&times));

        char weekNum = str[strlen(str)-1];
        // struct tm* utcTime = localtime(&times);
        char * weekDay;
        weekDay = (char *)malloc(10);
        strcpy(weekDay,weekTransform[atoi(&weekNum)]);
        // int timeStrLen = sprintf(str, "%04d-%02d-%02d %02d:%02d:%02d %s", 
        //     utcTime->tm_year+1900, utcTime->tm_mon+1, utcTime->tm_mday, 
        //     utcTime->tm_hour, utcTime->tm_min, utcTime->tm_sec,weekDay);
        sprintf(res,"%s\b \b%s",str,weekDay);
        
        //printf("%s<->%c", str,weekNum);
        printf("%s", res);
        //free(timeinfo);
        gotoxy(InputX,InputY);
        usleep(30000);
        //delay();
    
}

void clearDown(){
    //清空界面下方的提示信息,避免不同输出互相叠加
    gotoxy(20,1);
    printf("                                                            ");
    gotoxy(21,1);
    printf("                                                            ");
    gotoxy(22,1);
    printf("                                                            ");
    gotoxy(23,1);
    printf("                                                            ");
}