#include "func.h"
#include "ui.h"
#include "tools.h"
#include "io.h"

//  1.学号:
//  2.姓名:
//  3.年龄:
//  4.绩点:
//  5.学费:

void showAll(){
    gotoxy(1,1);
    showAllUI();
    char ch;
    
    int curPage = 1;

    char * all[100];
    //all = (char *)malloc(1000);
    //gotoxy(9,14);
    int count = getAll(all);

    //一页显示4条
    int pages;

    pages = count/4;
    if(count%4!=0){
        pages++;
    }

    int startLine = 9;
    int startOffset = 0;
    int pageStart = 0;

    int pageFirst = 0;
    int position;

    //printf("%s",*(allData+0));
    
    while(1){
        gotoxy(7,4);
        printf("共 %d 条数据,第 %d/%d 页",count,curPage,pages);

        getAllShow(all,curPage,count);

        ch = getch();
        if(ch=='q'){
            break;
        }else if(ch=='n' || ch=='p'){
            //翻页操作
            //n:下一页  p:上一页
            if(ch=='n'){
                if(curPage<pages)
                    curPage++;
            }else if(ch=='p'){
                if(curPage>1)
                    curPage--;
            }

        }
    }
}

void add(){
    int v1,v2,v3,v4,v5;
    v1=v2=v3=v4=v5=0;
    Student *newStu;
    newStu = (Student *)malloc(100);
    char chooseBtn = '1';
    int check = 0;
    while(1){
        gotoxy(1,1);//完成一次输入后重新绘制页面
        addUI();
        chooseBtn = getch();
        switch(chooseBtn){
            case '1':
                gotoxy(10,14);
                InputX = 10;InputY=14;
                char * num;
                num = (char*)malloc(MAXINPUT);
                Input(num,TYPE_NUM);

                //添加学号重复检测模块
                //如果重复就要求重新输入
                int isExisted = idCheck(num);
                if(isExisted==1){
                    //重复
                    memset(num,'\0',MAXINPUT);
                    gotoxy(20,1);
                    printf("当前学号已存在,请重新输入");
                    gotoxy(10,14);
                    free(num);
                    v1=0;
                    sleep(1);
                }else{
                    gotoxy(20,1);
                    printf("you have just inputed id : %s\n",num);
                    v1=1;
                    sleep(1);
                }
                

                break;
            case '2':
                gotoxy(11,14);
                InputX = 11;InputY=14;
                char * name;
                name = (char*)malloc(MAXINPUT);
                Input(name,TYPE_CHINESE);

                gotoxy(20,1);
                printf("you have just inputed name : %s\n",name);
                v2=1;
                sleep(1);
                break;
            case '3':
                gotoxy(12,14);
                InputX = 12;InputY=14;
                char * age;
                age = (char*)malloc(MAXINPUT);
                Input(age,TYPE_NUM);

                gotoxy(20,1);
                printf("you have just inputed age : %s\n",age);
                v3=1;
                sleep(1);
                break;
            case '4':
                gotoxy(13,14);
                InputX = 13;InputY=14;
                char * grade;
                grade = (char*)malloc(MAXINPUT);
                Input(grade,TYPE_NUM);

                gotoxy(20,1);
                printf("you have just inputed grade : %s\n",grade);
                v4=1;
                sleep(1);
                break;
            case '5':
                //showAllUI();
                gotoxy(14,14);
                InputX = 14;InputY=14;
                char * fee;
                fee = (char*)malloc(MAXINPUT);
                Input(fee,TYPE_NUM);

                gotoxy(20,1);
                printf("you have just inputed fee : %s\n",fee);
                v5=1;
                sleep(1);
                break;
            case 'q'://取消添加,直接退回主菜单
                check = -1;
                break;
            case 13: //保存数据,并在页面上提示保存成功,再退回主菜单
                if(v1==1 && v2==1 && v3==1 && v4==1 && v5==1){
                    //所有参数成功输入,可以保存
                    newStu->id = num;
                    newStu->name = name;
                    newStu->age = age;
                    newStu->grade = grade;
                    newStu->fee = fee;
                    // gotoxy(20,1);

                    // printf("id:%s\n",newStu->id);
                    // printf("name:%s\n",newStu->name);
                    // printf("age:%s\n",newStu->age);
                    // printf("grade:%s\n",newStu->grade);
                    // printf("fee:%s\n",newStu->fee);

                    addOne(newStu);

                    printf("保存成功\n");

                    //sleep(3);
                    //sleep(1);
                    system("clear");

                    check = 1;
                    printf("延时结束\n");
                }else{
                    //参数不完整,需要补充
                    printf("参数不完整,请补齐再保存\n");
                    check=0;
                }
                
                break;
            default:
                break;
        }
        gotoxy(20,1);
        if(check!=0){
            printf("添加结束,2s后跳转回主页");
            sleep(2);
            break;
                
        }
    }
}

void search(){
    gotoxy(1,1);
    searchUI();
    char ch;
    char * id;
    id = (char *)malloc(20);
    while(1){
        ch = getch();
        if(ch=='q'){
            break;
        }else{
            gotoxy(10,14);
            Input(id,TYPE_NUM);
            gotoxy(13,14);
            getOne(id);
        }
    }
}

void update(){
    gotoxy(1,1);
    int v2,v3,v4,v5;
    v2=v3=v4=v5=0;
    updateUI();
    char ch;
    Student *newStu;
    newStu = (Student *)malloc(100);
    char chooseBtn = '1';
    int check = 0;
    int exit = 0;
    while(1){
        gotoxy(1,1);//完成一次输入后重新绘制页面
        updateUI();
        chooseBtn = getch();
        switch(chooseBtn){
            case '1':
                gotoxy(10,14);
                InputX = 10;InputY=14;
                char * num;
                num = (char*)malloc(MAXINPUT);
                Input(num,TYPE_NUM);

                //添加学号重复检测模块
                //如果重复就要求重新输入
                int isExisted = idCheck(num);
                if(isExisted==1){
                    //存在
                    gotoxy(20,1);
                    printf("当前学号存在,请输入其他参数以修改\n");
                    //getOne(num);
                    newStu->id = num;
                    //free(num);
                    check=1;
                    sleep(1);
                }else{
                    gotoxy(20,1);
                    printf("当前学号不存在,请输入存在的学号来修改");
                    check=0;
                    sleep(1);
                }
                break;
            case '2':
                gotoxy(11,14);
                InputX = 11;InputY=14;
                if(check!=1){
                    printf("请先输入学号!");
                    break;
                }

                char * name;
                name = (char*)malloc(MAXINPUT);
                Input(name,TYPE_CHINESE);

                gotoxy(20,1);
                printf("you have just inputed name : %s\n",name);
                v2=1;
                sleep(1);
                break;
            case '3':
                gotoxy(12,14);
                InputX = 12;InputY=14;
                if(check!=1){
                    printf("请先输入学号!");
                    break;
                }
                char * age;
                age = (char*)malloc(MAXINPUT);
                Input(age,TYPE_NUM);

                gotoxy(20,1);
                printf("you have just inputed age : %s\n",age);
                v3=1;
                sleep(1);
                break;
            case '4':
                gotoxy(13,14);
                InputX = 13;InputY=14;
                if(check!=1){
                    printf("请先输入学号!");
                    break;
                }
                char * grade;
                grade = (char*)malloc(MAXINPUT);
                Input(grade,TYPE_NUM);

                gotoxy(20,1);
                printf("you have just inputed grade : %s\n",grade);
                v4=1;
                sleep(1);
                break;
            case '5':
                //showAllUI();
                gotoxy(14,14);
                InputX = 14;InputY=14;
                if(check!=1){
                    printf("请先输入学号!");
                    break;
                }
                char * fee;
                fee = (char*)malloc(MAXINPUT);
                Input(fee,TYPE_NUM);

                gotoxy(20,1);
                printf("you have just inputed fee : %s\n",fee);
                v5=1;
                sleep(1);
                break;
            case 'q'://取消添加,直接退回主菜单
                exit = -1;
                break;
            case 13: //保存数据,并在页面上提示保存成功,再退回主菜单
                if(check==1 && v2==1 && v3==1 && v4==1 && v5==1){
                    //所有参数成功输入,可以保存
                    newStu->id = num;
                    newStu->name = name;
                    newStu->age = age;
                    newStu->grade = grade;
                    newStu->fee = fee;
                    // gotoxy(20,1);

                    // printf("id:%s\n",newStu->id);
                    // printf("name:%s\n",newStu->name);
                    // printf("age:%s\n",newStu->age);
                    // printf("grade:%s\n",newStu->grade);
                    // printf("fee:%s\n",newStu->fee);

                    delOne(newStu->id);
                    addOne(newStu);
                    gotoxy(20,1);
                    printf("保存成功,修改后的数据为:\n");
                    printf("<id:%s name:%s age=%s grade:%s fee:%s>\n",newStu->id,newStu->name,
                        newStu->age,newStu->grade,newStu->fee);

                    sleep(3);
                    system("clear");

                    exit = 1;
                }else{
                    //参数不完整,需要补充
                    printf("参数不完整,请补齐再保存\n");
                    exit=0;
                }
                
                break;
            default:
                break;
        }
        if(exit!=0){
            break;
        }
    }
}

void del(){
    gotoxy(1,1);
    delUI();
    char ch;
    char * id;
    id = (char *)malloc(20);
    while(1){
        ch = getch();
        if(ch=='q'){
            break;
        }else if(ch=='c'){
            delAll();
            gotoxy(13,14);
            printf("所有信息已删除");
        }else{
            gotoxy(10,14);
            Input(id,TYPE_NUM);
            gotoxy(13,14);
            delOne(id);
        }
    }
}