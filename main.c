#include<stdio.h>
#include <stdlib.h>
#include <string.h>
/**
关于生成的文件的储存
密码本文件 filePath+"passwordbook\"+fileName+".passwordbook"
未压缩的文件 filePath+"codfile\"+fileName+".cod"
压缩文件 filePath+"codzip\"+fileName+".codzip"
解码文件 filePath+"decode\"+fileName
*/
struct Link
{
    char s[100];
    struct Link *next;
};
typedef struct
{
    int weight;
    int parent,left,right;
}HTNode;
typedef struct
{
    char s[128];
}Password;
void choseFile(FILE *fp,int *chNums,struct Link* S,char *path,char *fileName,int *j);
void CreatHuffmanTree(HTNode *HT,int *chNums);
void Select(HTNode *HT,int n,int *s1,int *s2);
void CreatPassword(HTNode *HT,Password *ps);
void hs(int index,HTNode *HT,Password *ps,char *s,int now);
void strClone(char *from,char *to,int n);
void passwordBookStore(int *chNums,Password *ps,char *filePath);
void creatCod(Password *ps,struct Link* S,int n,char *filePath);
void openFile(FILE *fp,int *chNums,struct Link* S,char *filePath);
void codOfZip(struct Link* S,char *filePath,int *n);
void readCodZip(struct Link* S,char *filePath);
void toEightBriny(int ch,char *s);
void readPasswordBook(Password *ps,char *filePath);
void decode(struct Link* S,Password *ps,char *filePath);
int isExistence(char *s,Password *ps,char *c);
int main1()
{
    FILE *readFp;
    FILE *writeFp;
    int chNums[128];/**储存扫描后的各字符数量*/
    for(int i = 0;i<128;i++)
    {
        chNums[i]=0;
    }
    struct Link* S = (struct Link*)malloc(sizeof(struct Link));
    S->next=(struct Link*)malloc(sizeof(struct Link));
    S->next->next=NULL;
    char path[128];
    char fileName[128];
    const char *passwordBook = "passwordbook\\";
    const char *codFile = "codfile\\";
    const char *codZip = "codzip\\";
    const char *decodeCod = "decode\\";
    int n = 0;
    choseFile(readFp,chNums,S,path,fileName,&n);/**打开文件需要输入文件路径*/
    printf("%s %s", path,fileName);
    HTNode HT[256];/**因为ascii码只有128个所以没有动态生成*/

    /**
    for(int i = 0;i<128;i++)
    {
        printf("%c  %d\n",i,chNums[i]);
    }
    */
    CreatHuffmanTree(HT,chNums);/**构造哈夫曼树*/

    Password password[128];

    /**
    printf("i\t\tweight\t\tparent\t\tleft\t\tright\t\t\n");
    for(int i = 1;i<=255;++i)
    {
        printf("%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t\n",i,HT[i].weight,HT[i].parent,HT[i].left,HT[i].right);
    }
    */
    CreatPassword(HT,password);/**根据哈夫曼树生成密码*/
/**
    printf("\n------------------------\n");
    for(int i = 0;i<128;++i)
    {
        printf("%c %s\n",i,password[i].s);
    }
    */

    char filePath[128];

    sprintf(filePath, "%s%s%s.password", path,passwordBook,fileName);
    //printf("%s\n",filePath);
    passwordBookStore(chNums,password,filePath);/**将密码本转入外存*/


    struct Link* codS = (struct Link*)malloc(sizeof(struct Link));
    codS->next=(struct Link*)malloc(sizeof(struct Link));
    codS->next->next=NULL;
    sprintf(filePath, "%s%s%s.codfile", path,codFile,fileName);
    creatCod(password,S,0,filePath);/**进行编码并生成.cod文件*/
    openFile(readFp,chNums,codS,filePath);/**读取.cod文件*/

    //sprintf(filePath, "%s%s%s.codzip", path,codZip,fileName);
    //codOfZip(codS,filePath);/**进行压缩并生成.codzip文件*/

    struct Link* codS2 = (struct Link*)malloc(sizeof(struct Link));
    codS2->next=(struct Link*)malloc(sizeof(struct Link));
    codS2->next->next=NULL;
    openFile(readFp,chNums,codS2,filePath);/**读取.cod文件*/
    //readCodZip(codS2,filePath);/**读取.codzip文件,解压生成字符序列*/

    sprintf(filePath, "%s%s%s.password", path,passwordBook,fileName);
    //printf("%s\n",filePath);



    readPasswordBook(password,filePath);/**读取密码本转入内存*/
/**
    printf("\n------------------------\n");
    for(int i = 0;i<128;++i)
    {
        printf("%c %s\n",i,password[i].s);
    }
*/
    sprintf(filePath, "%s%s%s", path,decodeCod,fileName);
    decode(codS2,password,filePath);
/**
    while(codS2!=NULL)
    {
        for(int j = 0;j<100;j++)
        {
            printf("%c",codS2->s[j]);
        }
        codS2=codS2->next;
    }
*/



}
    /**
D:\\test\from\
hamlet
    */
void main()
{
    FILE *readFp;
    /**定义一些常量*/
    const char *passwordBook = "passwordbook\\";
    const char *codFile = "codfile\\";
    const char *codZip = "codzip\\";
    const char *decodeCod = "decode\\";
    /**定义全局文件名*/
    char path[128];
    path[0] = -1;//初始化3
    char fileName[128];
    /**用于储存扫描的文字数量，以方便之后编码*/
    int chNums[128];

    for(int i = 0;i<128;i++)//稍后进行一个函数的初始化操作1
    {
        chNums[i]=0;
    }

    /**用于储存文件中的字符*/
    struct Link* S = (struct Link*)malloc(sizeof(struct Link));
    S->next=(struct Link*)malloc(sizeof(struct Link));//初始化2
    S->next->next=NULL;
    /**用于储存哈夫曼树的结构 因为ascii码只有128个所以没有动态生成*/
    HTNode HT[256];
    HT[1].weight = -1;//初始化4

    /**密码本*/
    Password password[128];

    /**文件全路径*/
    char filePath[128];

    /**用于储存生成的编码文件的结构(即01序列)*/
    struct Link* codS = (struct Link*)malloc(sizeof(struct Link));
    codS->next=(struct Link*)malloc(sizeof(struct Link));
    codS->next->next=NULL;
    struct Link* codS2 = (struct Link*)malloc(sizeof(struct Link));
    codS2->next=(struct Link*)malloc(sizeof(struct Link));
    codS2->next->next=NULL;

    int choose = 0;
    FILE *sde;
    int n = 0;
    int before = 0;
    int after = 0;
    while(choose != -1)
    {
        printf("**********************************************************************");printf("\n");
        printf("*                         哈夫曼编码译码器                           *");printf("\n");
        printf("*    1、选择需要进行编码的文件                                       *");printf("\n");
        printf("*    2、建立哈夫曼树                                                 *");printf("\n");
        printf("*    3、建立密码本并对文件编码                                       *");printf("\n");
        printf("*    4、选择需要进行解码的文件并解码                                 *");printf("\n");
        printf("*    5、按位压缩方式对文件进行压缩                                   *");printf("\n");
        printf("*    6、解压缩                                                       *");printf("\n");
        printf("**********************************************************************");printf("\n");
        printf("请输入数字选择操作:");
        scanf(" %d",&choose);
        if(choose == 1)
        {
            choseFile(readFp,chNums,S,path,fileName,&before);
        }
        else if(choose == 2)
        {
            if(path[0] == -1)
            {
                printf("您还没有选择文件无法构建\n");
            }
            else
            {
                CreatHuffmanTree(HT,chNums);/**构造哈夫曼树*/
                printf("构造完成\n");
            }

        }
        else if(choose == 3)
        {
            if(HT[1].parent==-1)
            {
                printf("还为构造哈夫曼树，请先构建\n");
            }
            else
            {
                CreatPassword(HT,password);/**根据哈夫曼树生成密码*/
                printf("\n------------------------\n");
                for(int i = 0;i<128;++i)
                {
                    printf("%c %s\n",i,password[i].s);
                }
                sprintf(filePath, "%s%s.password", path,fileName);/**拼接生成的密码本文件*/
                passwordBookStore(chNums,password,filePath);/**将密码本转入外存*/
                //printf("密码生成完成\n");
                sprintf(filePath, "%s%s.codfile", path,fileName);
                creatCod(password,S,n,filePath);/**进行编码并生成.cod文件*/
                openFile(readFp,chNums,codS,filePath);/**读取.cod文件并存入内存*/


                //sprintf(filePath, "%sdecode//%s.txt", path, fileName);/**生成的解码文件*/
                //decode(codS,password,filePath);/**解码*/


                printf("完成\n");
            }
        }
        else if(choose == 4)
        {
            printf("请输入需要操作的文件\n");
            char path2[128];
            char fileName2[128];
            scanf("%s",path2);
            scanf("%s",fileName2);
            sprintf(filePath, "%s%s.codfile", path2, fileName2);
            openFile(sde,chNums,codS,filePath);/**读取.codfile文件*/
            printf("文件读取成功\n");
            sprintf(filePath, "%s%s.password", path2, fileName2);
            readPasswordBook(password,filePath);/**读取密码本转入内存*/
            printf("密码读取成功\n");
            sprintf(filePath, "%sdecode//%s.txt", path2, fileName2);/**生成的解码文件*/
            decode(codS,password,filePath);/**解码*/
            printf("解码完成\n");
        }
        else if(choose == 5)
        {
            if(path[0] == -1||HT[1].parent==-1)
            {
                printf("您还没有选择文件无法构建或者还未对文件进行编码\n");
            }
            else
            {
                sprintf(filePath, "%s%s.codfile", path, fileName);/**对.codfile进行压缩*/
                openFile(sde,chNums,codS2,filePath);/**读取.cod文件*/
                sprintf(filePath, "%s%s.codzip", path,fileName);
                codOfZip(codS2,filePath,&after);/**进行压缩并生成.codzip文件*/
                printf("%d %d\n",before,after);
                printf("压缩比%f\n",(float)after/before);
            }

        }
        else if(choose == 6)
        {
            printf("请输入需要操作的文件\n");
            char path2[128];
            char fileName2[128];
            scanf("%s",path2);
            scanf("%s",fileName2);
            sprintf(filePath, "%s%s.codzip", path2, fileName2);
            readCodZip(codS2,filePath);/**读取.codzip文件,解压生成字符序列*/


            sprintf(filePath, "%s%s.password", path,fileName);/**完成解压下面是生成解压将文件解码并储存*/
            readPasswordBook(password,filePath);/**读取密码本转入内存*/
            sprintf(filePath, "%sdecode//%s_decode.txt", path,fileName);
            decode(codS2,password,filePath);
            printf("解压完成\n");
        }
    }
}
void choseFile(FILE *fp,int *chNums,struct Link* S,char *path,char *fileName,int *j)
{

    char filePath[128];
    struct Link* p = S->next;

    printf("请输入需要编码的文件\n");
    scanf("%s",path);
    scanf("%s",fileName);
    //printf("%s%s",path,fileName);
    sprintf(filePath, "%s%s.txt", path, fileName);
    //printf("%s\n", filePath);
    if((fp=fopen(filePath,"r"))==NULL)
    {
        printf("文件打开失败\n");
        return ;
    }
    char ch;
    int i = 0;
    (*j) = 0;
    while((ch=fgetc(fp))!=EOF)
    {
        (*j)++;
        if(i==100)
        {
            p->next = (struct Link*)malloc(sizeof(struct Link));
            p = p->next;
            p->next=NULL;
            i=0;
        }
        p->s[i] = ch;
        //printf(" %d ",ch);
        ++chNums[ch];
        i++;
    }
    //printf("总字数%d\n",j);
    for(;i<100;i++)
    {
        p->s[i]=-1;
    }
    fclose(fp);
    return ;

}
void CreatHuffmanTree(HTNode *HT,int *chNums)
{
    for(int i = 1;i<=255;++i)
    {
        HT[i].parent =0;
        HT[i].left =0;
        HT[i].right =0;
        HT[i].weight = 0;
    }
    for(int i = 1;i<=128;++i)
    {
        HT[i].weight = chNums[i-1];
    }
    for(int i = 128+1;i<=255;++i)
    {
        int s1;
        int s2;

        Select(HT,i-1,&s1,&s2);
        if(s1==-1||s2==-1)
        {
            break;
        }
        HT[s1].parent = i;
        HT[s2].parent = i;
        HT[i].left=s1;
        HT[i].right = s2;
        HT[i].weight =HT[s1].weight + HT[s2].weight;

    }
}
void Select(HTNode *HT,int n,int *s1,int *s2)
{
    (*s1) = -1;//s1 是比较小的
    (*s2) = -1;
    for(int i = 1;i<=n;++i)
    {

        if(HT[i].parent==0&&HT[i].weight!=0)
        {
            if(*s2==-1)
            {
                *s2 = i;
                continue;
            }

            if((*s1)==-1&&HT[i].weight>=HT[*s2].weight)
            {
                *s1 = *s2;
                *s2 = i;
                continue;
            }
            if((*s1)==-1&&HT[i].weight<HT[*s2].weight)
            {
                *s1 = i;
                continue;
            }



            if(HT[i].weight<HT[*s1].weight)
            {
                if((*s1)!=(*s2))
                {
                    *s2 = *s1;
                    *s1 = i;
                    continue;
                }

            }
            else if(HT[i].weight<HT[*s2].weight&&HT[i].weight>HT[*s1].weight)
            {
                *s2 = i;
                continue;
            }
        }
    }
}

void CreatPassword(HTNode *HT,Password *ps)
{
    int now = 0;
    for(int i = 129;i<=255;i++)
    {
        if(HT[i].parent==0)
        {
            now = i;
            break;
        }

    }
    //printf("第一个now是 %d\n",now);
    FILE *fp;
    int index=0;/**临时保存的字符串索引*/
    char s[128];
    hs(index,HT,ps,s,now);

}
void hs(int index,HTNode *HT,Password *ps,char *s,int now)/**回溯递归函数*/
{
    if(HT[now].left!=0||HT[now].right!=0)
    {
        if(HT[now].left!=0)
        {
            s[index] = '0';
            hs(index+1,HT,ps,s,HT[now].left);
        }
        if(HT[now].right!=0)
        {
            s[index] = '1';
            hs(index+1,HT,ps,s,HT[now].right);
        }
    }
    else
    {
        s[index]='\0';
        //printf("%d\n",now);
        strClone(s,ps[now-1].s,128);
        return;
    }


}
void strClone(char *from,char *to,int n)
{
    for(int i = 0;i<n;i++)
    {
        to[i]=from[i];
    }
}

void passwordBookStore(int *chNums,Password *ps,char *filePath)
{
    FILE *fp;

    if((fp=fopen(filePath,"w"))==NULL)
    {
        printf("文件打开失败\n");
        return;
    }
    for(int i = 0;i<128;i++)
    {
        if(chNums[i]==0)
        {
            fprintf(fp,"2\n");
        }
        else
        {
            fprintf(fp,"%s\n",ps[i].s);
        }
    }
    fclose(fp);
}

void creatCod(Password *ps,struct Link* S,int n,char *filePath)
{
    FILE *fp;
    if((fp=fopen(filePath,"w"))==NULL)
    {
        printf("文件打开失败\n");
        return;
    }
    int count = 0;
    struct Link* p = S->next;
    while(p!=NULL)
    {
        for(int j = 0;j<100;j++)
        {
            ++count;
            if(p->s[j]>=0)
                fprintf(fp,"%s",ps[p->s[j]].s);
            //p->s[i]
        }
        p=p->next;
    }
    //printf("creatCode:写入了%d个\n",count);
    fclose(fp);
}

void openFile(FILE *fps,int *chNums,struct Link* S,char *filePath)
{
    FILE *fp;
    struct Link* p = S->next;
    if((fp=fopen(filePath,"r"))==NULL)
    {
        printf("文件打开失败\n");
        return;
    }
    char ch;
    int i = 0;
    int j = 0;
    while((ch=fgetc(fp))!=EOF)
    {
        j++;
        if(i==100)
        {
            p->next = (struct Link*)malloc(sizeof(struct Link));
            p = p->next;
            p->next=NULL;
            i=0;
        }
        p->s[i] = ch;
        //printf(" %d ",ch);
        //++chNums[ch];
        i++;
    }
    //printf("openfile:总字数%d\n",j);
    for(;i<100;i++)
    {
        p->s[i]=-1;
    }
    fclose(fp);
    return;

}

void codOfZip(struct Link* S,char *filePath,int *n)
{
    FILE *fp;
    (*n)= 0;
    if((fp=fopen(filePath,"wb"))==NULL)
    {
        printf("文件打开失败\n");
        return;
    }
    struct Link* p = S->next;
    int k = 0;
    int eiehtNum = 0;
    while(p!=NULL)
    {
        for(int j = 0;j<100;j++)
        {
            if(k==8)
            {
                (*n)++;
                fputc(eiehtNum,fp);
                //fprintf(fp,"%2x",eiehtNum);
                eiehtNum  = 0;
                k=0;
            }
            if(p->s[j]<0)
            {
                break;
            }
            eiehtNum = eiehtNum*2+(p->s[j] - '0');
            //p->s[i]
            k++;
        }

        p=p->next;
    }
    //printf("k = %d \neightNum = %d\n",k,eiehtNum);
    /**以下为最后不足八位的处理*/
    for(int p = 0;p<8-k;p++)/**将不足的后面补零补到八位*/
    {
        eiehtNum = eiehtNum * 2;
    }
    //printf("k = %d \neightNum = %d\n",k,eiehtNum);
    fputc(eiehtNum,fp);/**存入外存*/
    fputc(k,fp);/**将最后一位长度存入外存*/
    fclose(fp);
}

void readCodZip(struct Link* S,char *filePath)
{
    FILE *fp;
    if((fp=fopen(filePath,"rb"))==NULL)
    {
        printf("文件打开失败\n");
        return;
    }
    struct Link* p = S->next;
    int i = 0;
    int ch;
    struct Link *pre = S;
    while((ch=fgetc(fp))!=EOF)
    {
        char s[8];
        toEightBriny(ch,s);
        for(int l=0;l<8;l++)
        {
            if(i==100)
            {
                p->next = (struct Link*)malloc(sizeof(struct Link));
                pre = p;
                p = p->next;
                p->next=NULL;
                i=0;
            }
            p->s[i] = s[l];
            i++;
        }
    }
    int weight = 1;
    int lastLength = 0;
    /**最后八位的读取处理*/
    /**读取位长*/
    for(int d = 7;d>=0;--d)
    {
        //printf("i = %d,p-s[i - 1] = %c\n",i,p->s[i - 1]);
        if(i==0)
        {
            free(p);
            p = pre;

            i = 100;
        }
        lastLength += (p->s[--i]-'0')*weight;
        p->s[i]=-1;
        weight *= 2;
    }
    //printf("lastLength = %d\n",lastLength);
    /**读取最后八位数据*/
    for(int d = 7;d>=0;--d)
    {
        //printf("i = %d\n",i);
        if(i==0)
        {
            free(p);
            p = pre;

            i = 100;
        }
        if(d>lastLength - 1)
        {
            //printf("%c\n",p->s[i - 1]);
            p->s[--i] = -1;
        }
    }

    for(;i<100;i++)
    {
        p->s[i]=-1;
    }
    fclose(fp);
}

void toEightBriny(int ch,char *s)
{
    int shang;
    int yushu;
    s[8]='\0';
    for(int i=1;i<=8;i++)
    {
        shang = ch/2;
        yushu = ch%2;
        s[8-i]='0'+yushu;
        ch = shang;
    }
    return;
}

void readPasswordBook(Password *ps,char *filePath)
{
    FILE *fp;

    if((fp=fopen(filePath,"r"))==NULL)
    {
        printf("文件打开失败\n");
        return;
    }
    for(int i = 0;i<128;i++)
    {
        fscanf(fp,"%s\n",ps[i].s);
        //printf("%s\n",ps[i].s);
    }
    fclose(fp);
}

void decode(struct Link* S,Password *ps,char *filePath)
{
    FILE *fp;
    if((fp=fopen(filePath,"w"))==NULL)
    {
        printf("2文件打开失败\n");
        return;
    }
    struct Link *p = S->next;
    char s[128];
    int sPoint = 0;
    char c;

    int count = 0;
    while(p!=NULL)
    {
        for(int i = 0;i<100;++i)
        {
            //printf("%c",p->s[i]);
            if(p->s[i]>=0)
            {
                s[sPoint++] = p->s[i];
                s[sPoint] = '\0';
                if(isExistence(s,ps,&c)==1)
                {
                    ++count;

                    fprintf(fp,"%c",c);
                    s[0] = '\0';
                    sPoint = 0;
                }
            }


        }
        p=p->next;
    }
    //printf("decode:%d个文字\n",count);
    fclose(fp);
}
int isExistence(char *s,Password *ps,char *c)
{
    for(int i = 0;i<128;++i)
    {
        if(strcmp(s,ps[i].s) == 0)
        {
            //printf("%s %s\n",ps[i].s,s);
            *c = i;
            return 1;
        }
    }
    return 0;
}





