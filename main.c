#include<stdio.h>
#include <stdlib.h>
#include <string.h>
/**
�������ɵ��ļ��Ĵ���
���뱾�ļ� filePath+"passwordbook\"+fileName+".passwordbook"
δѹ�����ļ� filePath+"codfile\"+fileName+".cod"
ѹ���ļ� filePath+"codzip\"+fileName+".codzip"
�����ļ� filePath+"decode\"+fileName
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
    int chNums[128];/**����ɨ���ĸ��ַ�����*/
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
    choseFile(readFp,chNums,S,path,fileName,&n);/**���ļ���Ҫ�����ļ�·��*/
    printf("%s %s", path,fileName);
    HTNode HT[256];/**��Ϊascii��ֻ��128������û�ж�̬����*/

    /**
    for(int i = 0;i<128;i++)
    {
        printf("%c  %d\n",i,chNums[i]);
    }
    */
    CreatHuffmanTree(HT,chNums);/**�����������*/

    Password password[128];

    /**
    printf("i\t\tweight\t\tparent\t\tleft\t\tright\t\t\n");
    for(int i = 1;i<=255;++i)
    {
        printf("%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t\n",i,HT[i].weight,HT[i].parent,HT[i].left,HT[i].right);
    }
    */
    CreatPassword(HT,password);/**���ݹ���������������*/
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
    passwordBookStore(chNums,password,filePath);/**�����뱾ת�����*/


    struct Link* codS = (struct Link*)malloc(sizeof(struct Link));
    codS->next=(struct Link*)malloc(sizeof(struct Link));
    codS->next->next=NULL;
    sprintf(filePath, "%s%s%s.codfile", path,codFile,fileName);
    creatCod(password,S,0,filePath);/**���б��벢����.cod�ļ�*/
    openFile(readFp,chNums,codS,filePath);/**��ȡ.cod�ļ�*/

    //sprintf(filePath, "%s%s%s.codzip", path,codZip,fileName);
    //codOfZip(codS,filePath);/**����ѹ��������.codzip�ļ�*/

    struct Link* codS2 = (struct Link*)malloc(sizeof(struct Link));
    codS2->next=(struct Link*)malloc(sizeof(struct Link));
    codS2->next->next=NULL;
    openFile(readFp,chNums,codS2,filePath);/**��ȡ.cod�ļ�*/
    //readCodZip(codS2,filePath);/**��ȡ.codzip�ļ�,��ѹ�����ַ�����*/

    sprintf(filePath, "%s%s%s.password", path,passwordBook,fileName);
    //printf("%s\n",filePath);



    readPasswordBook(password,filePath);/**��ȡ���뱾ת���ڴ�*/
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
    /**����һЩ����*/
    const char *passwordBook = "passwordbook\\";
    const char *codFile = "codfile\\";
    const char *codZip = "codzip\\";
    const char *decodeCod = "decode\\";
    /**����ȫ���ļ���*/
    char path[128];
    path[0] = -1;//��ʼ��3
    char fileName[128];
    /**���ڴ���ɨ��������������Է���֮�����*/
    int chNums[128];

    for(int i = 0;i<128;i++)//�Ժ����һ�������ĳ�ʼ������1
    {
        chNums[i]=0;
    }

    /**���ڴ����ļ��е��ַ�*/
    struct Link* S = (struct Link*)malloc(sizeof(struct Link));
    S->next=(struct Link*)malloc(sizeof(struct Link));//��ʼ��2
    S->next->next=NULL;
    /**���ڴ�����������Ľṹ ��Ϊascii��ֻ��128������û�ж�̬����*/
    HTNode HT[256];
    HT[1].weight = -1;//��ʼ��4

    /**���뱾*/
    Password password[128];

    /**�ļ�ȫ·��*/
    char filePath[128];

    /**���ڴ������ɵı����ļ��Ľṹ(��01����)*/
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
        printf("*                         ����������������                           *");printf("\n");
        printf("*    1��ѡ����Ҫ���б�����ļ�                                       *");printf("\n");
        printf("*    2��������������                                                 *");printf("\n");
        printf("*    3���������뱾�����ļ�����                                       *");printf("\n");
        printf("*    4��ѡ����Ҫ���н�����ļ�������                                 *");printf("\n");
        printf("*    5����λѹ����ʽ���ļ�����ѹ��                                   *");printf("\n");
        printf("*    6����ѹ��                                                       *");printf("\n");
        printf("**********************************************************************");printf("\n");
        printf("����������ѡ�����:");
        scanf(" %d",&choose);
        if(choose == 1)
        {
            choseFile(readFp,chNums,S,path,fileName,&before);
        }
        else if(choose == 2)
        {
            if(path[0] == -1)
            {
                printf("����û��ѡ���ļ��޷�����\n");
            }
            else
            {
                CreatHuffmanTree(HT,chNums);/**�����������*/
                printf("�������\n");
            }

        }
        else if(choose == 3)
        {
            if(HT[1].parent==-1)
            {
                printf("��Ϊ����������������ȹ���\n");
            }
            else
            {
                CreatPassword(HT,password);/**���ݹ���������������*/
                printf("\n------------------------\n");
                for(int i = 0;i<128;++i)
                {
                    printf("%c %s\n",i,password[i].s);
                }
                sprintf(filePath, "%s%s.password", path,fileName);/**ƴ�����ɵ����뱾�ļ�*/
                passwordBookStore(chNums,password,filePath);/**�����뱾ת�����*/
                //printf("�����������\n");
                sprintf(filePath, "%s%s.codfile", path,fileName);
                creatCod(password,S,n,filePath);/**���б��벢����.cod�ļ�*/
                openFile(readFp,chNums,codS,filePath);/**��ȡ.cod�ļ��������ڴ�*/


                //sprintf(filePath, "%sdecode//%s.txt", path, fileName);/**���ɵĽ����ļ�*/
                //decode(codS,password,filePath);/**����*/


                printf("���\n");
            }
        }
        else if(choose == 4)
        {
            printf("��������Ҫ�������ļ�\n");
            char path2[128];
            char fileName2[128];
            scanf("%s",path2);
            scanf("%s",fileName2);
            sprintf(filePath, "%s%s.codfile", path2, fileName2);
            openFile(sde,chNums,codS,filePath);/**��ȡ.codfile�ļ�*/
            printf("�ļ���ȡ�ɹ�\n");
            sprintf(filePath, "%s%s.password", path2, fileName2);
            readPasswordBook(password,filePath);/**��ȡ���뱾ת���ڴ�*/
            printf("�����ȡ�ɹ�\n");
            sprintf(filePath, "%sdecode//%s.txt", path2, fileName2);/**���ɵĽ����ļ�*/
            decode(codS,password,filePath);/**����*/
            printf("�������\n");
        }
        else if(choose == 5)
        {
            if(path[0] == -1||HT[1].parent==-1)
            {
                printf("����û��ѡ���ļ��޷��������߻�δ���ļ����б���\n");
            }
            else
            {
                sprintf(filePath, "%s%s.codfile", path, fileName);/**��.codfile����ѹ��*/
                openFile(sde,chNums,codS2,filePath);/**��ȡ.cod�ļ�*/
                sprintf(filePath, "%s%s.codzip", path,fileName);
                codOfZip(codS2,filePath,&after);/**����ѹ��������.codzip�ļ�*/
                printf("%d %d\n",before,after);
                printf("ѹ����%f\n",(float)after/before);
            }

        }
        else if(choose == 6)
        {
            printf("��������Ҫ�������ļ�\n");
            char path2[128];
            char fileName2[128];
            scanf("%s",path2);
            scanf("%s",fileName2);
            sprintf(filePath, "%s%s.codzip", path2, fileName2);
            readCodZip(codS2,filePath);/**��ȡ.codzip�ļ�,��ѹ�����ַ�����*/


            sprintf(filePath, "%s%s.password", path,fileName);/**��ɽ�ѹ���������ɽ�ѹ���ļ����벢����*/
            readPasswordBook(password,filePath);/**��ȡ���뱾ת���ڴ�*/
            sprintf(filePath, "%sdecode//%s_decode.txt", path,fileName);
            decode(codS2,password,filePath);
            printf("��ѹ���\n");
        }
    }
}
void choseFile(FILE *fp,int *chNums,struct Link* S,char *path,char *fileName,int *j)
{

    char filePath[128];
    struct Link* p = S->next;

    printf("��������Ҫ������ļ�\n");
    scanf("%s",path);
    scanf("%s",fileName);
    //printf("%s%s",path,fileName);
    sprintf(filePath, "%s%s.txt", path, fileName);
    //printf("%s\n", filePath);
    if((fp=fopen(filePath,"r"))==NULL)
    {
        printf("�ļ���ʧ��\n");
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
    //printf("������%d\n",j);
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
    (*s1) = -1;//s1 �ǱȽ�С��
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
    //printf("��һ��now�� %d\n",now);
    FILE *fp;
    int index=0;/**��ʱ������ַ�������*/
    char s[128];
    hs(index,HT,ps,s,now);

}
void hs(int index,HTNode *HT,Password *ps,char *s,int now)/**���ݵݹ麯��*/
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
        printf("�ļ���ʧ��\n");
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
        printf("�ļ���ʧ��\n");
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
    //printf("creatCode:д����%d��\n",count);
    fclose(fp);
}

void openFile(FILE *fps,int *chNums,struct Link* S,char *filePath)
{
    FILE *fp;
    struct Link* p = S->next;
    if((fp=fopen(filePath,"r"))==NULL)
    {
        printf("�ļ���ʧ��\n");
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
    //printf("openfile:������%d\n",j);
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
        printf("�ļ���ʧ��\n");
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
    /**����Ϊ������λ�Ĵ���*/
    for(int p = 0;p<8-k;p++)/**������ĺ��油�㲹����λ*/
    {
        eiehtNum = eiehtNum * 2;
    }
    //printf("k = %d \neightNum = %d\n",k,eiehtNum);
    fputc(eiehtNum,fp);/**�������*/
    fputc(k,fp);/**�����һλ���ȴ������*/
    fclose(fp);
}

void readCodZip(struct Link* S,char *filePath)
{
    FILE *fp;
    if((fp=fopen(filePath,"rb"))==NULL)
    {
        printf("�ļ���ʧ��\n");
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
    /**����λ�Ķ�ȡ����*/
    /**��ȡλ��*/
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
    /**��ȡ����λ����*/
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
        printf("�ļ���ʧ��\n");
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
        printf("2�ļ���ʧ��\n");
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
    //printf("decode:%d������\n",count);
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





