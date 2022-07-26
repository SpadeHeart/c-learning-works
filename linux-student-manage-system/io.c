#include "io.h"
#include "tools.h"

void addOne(Student * stu){
    //功能2:添加一个学生
    FILE * f;
    char * data;
    sprintf(data,"id=%s,name=%s,age=%s,grade=%s,fee=%s\n",stu->id,stu->name,
        stu->age,stu->grade,stu->fee);
    f = fopen("./data","a");
    fputs(data,f);
    fclose(f);
    //free(f);
}

int getAll(char * allData[]){
    //功能1:显示所有学生
    Student *newStu;
    newStu = (Student *)malloc(100);

    newStu->id = (char *)malloc(20);
    newStu->name = (char *)malloc(20);
    newStu->age = (char *)malloc(20);
    newStu->grade = (char *)malloc(20);
    newStu->fee = (char *)malloc(20);

    int count = 0;

    FILE * f;
    char * data;
    data = (char *)malloc(100);

    char ** vals;
    vals = (char **)malloc(100);
    f = fopen("./data","r");

    while(fgets(data,100,f)!=NULL){
        allData[count] = (char *)malloc(100);

        vals = split(data,',');
        locRemoveR(*(vals+4));

        sscanf(*(vals+0),"id=%s",newStu->id);
        sscanf(*(vals+1),"name=%s",newStu->name);
        sscanf(*(vals+2),"age=%s",newStu->age);
        sscanf(*(vals+3),"grade=%s",newStu->grade);
        sscanf(*(vals+4),"fee=%s",newStu->fee);

        sprintf(data,"[id:%s name:%s age:%s grade:%s fee:%s]",newStu->id,
            newStu->name,newStu->age,newStu->grade,newStu->fee);

        //printf("raw:%s\n",data);
        //data正常获取数据

        //allData[count] = data;
        strcpy(allData[count],data);

        //printf("raw:%d|%s\n",count,allData[count]);
        //*(allData+count)正常读取数据

        count++;
    }
    //printf("%s\n",*allData+4);
    //出了上面的while之后就只能输出最后一条了

    fclose(f);
    return count;
}

void getAllShow(char * allData[],int curp,int total){

    //覆盖旧数据
    int up = 9;
    int down = 12;
    int left = 8;
    int right = 58;

    while(up<=down){
        gotoxy(up,left);
        for(int i=left;i<=right;i++)
            printf(" ");
        up++;
    }

    //显示新数据
    int start = (curp-1)*4;
    int startOffset = 0;
    int startLine = 9;
    while(startOffset<4){
        gotoxy(startLine,8);
        int position = startOffset+start;

        if(position<total)
            printf("%s",allData[position]);

        startOffset++;
        startLine++;
    }
}

void getOne(char * id){
    //功能3.查找
    int flag=0;
    Student *newStu;
    newStu = (Student *)malloc(100);

    newStu->id = (char *)malloc(20);
    newStu->name = (char *)malloc(20);
    newStu->age = (char *)malloc(20);
    newStu->grade = (char *)malloc(20);
    newStu->fee = (char *)malloc(20);

    int startLine = 9;
    int count = 0;

    FILE * f;
    char * data;
    data = (char *)malloc(100);

    char ** vals;
    vals = (char **)malloc(100);
    f = fopen("./data","r");

    while(fgets(data,100,f)!=NULL){
        //gotoxy(startLine,8);

        vals = split(data,',');
        locRemoveR(*(vals+4));

        sscanf(*(vals+0),"id=%s",newStu->id);

        if(strcmp(id,newStu->id)!=0){
            continue;
        }else{
            flag=1;
            sscanf(*(vals+1),"name=%s",newStu->name);
            sscanf(*(vals+2),"age=%s",newStu->age);
            sscanf(*(vals+3),"grade=%s",newStu->grade);
            sscanf(*(vals+4),"fee=%s",newStu->fee);

            sprintf(data,"[id:%s name:%s age:%s grade:%s fee:%s]",newStu->id,
                newStu->name,newStu->age,newStu->grade,newStu->fee);

            printf("%s",data);
        }

    }

    fclose(f);

    if(flag==0){
        printf("找不到学号为%s的学生                            ",id);
    }
}

void delOne(char * id){
    //功能5.删除学生
    int flag = 0;
    Student *newStu;
    newStu = (Student *)malloc(100);

    newStu->id = (char *)malloc(20);
    newStu->name = (char *)malloc(20);
    newStu->age = (char *)malloc(20);
    newStu->grade = (char *)malloc(20);
    newStu->fee = (char *)malloc(20);

    int startLine = 9;
    int count = 0;

    FILE * f;
    FILE *ft;
    char * data;
    data = (char *)malloc(100);

    char ** vals;
    vals = (char **)malloc(100);

    f = fopen("./data","r");
    ft = fopen("./tmp","w");

    while(fgets(data,100,f)!=NULL){

        vals = split(data,',');
        sscanf(*(vals+0),"id=%s",newStu->id);

        if(strcmp(id,newStu->id)!=0){
            fprintf(ft, "%s", data);
        }else{
            flag=1;//找到条目,成功删除
        }

    }

    fclose(f);
    fclose(ft);

    system("rm ./data");
    system("mv ./tmp ./data");

    if(flag==1){
        printf("删除信息成功           ");
    }else{
        printf("找不到对应条目,删除失败");
    }
}

void delAll(){
    FILE * f;
    f = fopen("./data","w");
    fclose(f);
}

int idCheck(char * num){
    Student *newStu;
    newStu = (Student *)malloc(100);

    newStu->id = (char *)malloc(20);
    newStu->name = (char *)malloc(20);
    newStu->age = (char *)malloc(20);
    newStu->grade = (char *)malloc(20);
    newStu->fee = (char *)malloc(20);

    int startLine = 9;
    int count = 0;

    FILE * f;
    char * data;
    data = (char *)malloc(100);

    char ** vals;
    vals = (char **)malloc(100);
    f = fopen("./data","r");

    while(fgets(data,100,f)!=NULL){
        vals = split(data,',');
        locRemoveR(*(vals+4));

        sscanf(*(vals+0),"id=%s",newStu->id);

        if(strcmp(num,newStu->id)==0){
            return 1;
        }
    }
    fclose(f);
    return 0;
}

void updateOne(Student * stu){
    //4.修改学生信息
    //思路: 删除当前学号的学生,再按照修改的信息新建一个
    Student *newStu;
    newStu = (Student *)malloc(100);

    newStu->id = stu->id;
    newStu->name = stu->name;
    newStu->age = stu->age;
    newStu->grade = stu->grade;
    newStu->fee = stu->fee;

    //delOne(stu->id);
    addOne(newStu);
}