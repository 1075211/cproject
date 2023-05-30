//===============================
//歌手比赛评分统计程序
//功能：
//      (1) 有n位选手参赛，m（m>2）为评委为选手评分（最高分10分，最低分0分）
//      (2) 打分规则：每个选手的m个得分中，去掉一个最高分和一个最低分，取平均分作为
//    该选手的最后得分。
//      (3) 根据n个选手的最后得分，从高到低输出选手的得分名次表，以确定获奖名单。
//      (4) 根据各位选手的最后得分与各位评委给该选手所评分数的差距，对每个评委评分的
//    准确性和评分水准给出一个定量的评价，从高到低输出各位评委得分的名次表。
//===============================
#include <stdio.h>
#include <math.h>
#define N 40    // 选手数组下标界
#define M 20    // 评委数组下标界

//================================================
// 结构类型（自定义一个表示参赛选手的数据类型）：参赛选手结构
// 结构成员：
//         选手的ID
//         选手的最终得分
//         选手的裁判打分
//================================================
typedef struct
{
    int cID;            // 选手编号
    float finalScore;   // 选手最后得分
    float scores[M]     // 该数组存放M个评委对某位选手的评分
} Contestant;

//================================================
// 结构类型（自定义一个表示评委的数据类型）：评委结构
// 结构成员：
//         评委的ID
//         评委的水平等级
//================================================
typedef struct
{
    int jID;            //评委编号
    float judgeLevel;   //评委评分水准得分
} Judge;


// 函数声明，函数定义放在main函数后面
int menu(void);                   // 显示菜单，显示用户可以选择的功能
int setContestantAmount(void);    //设置参赛人数
int setJudgeAmount(void);         //设置裁判人数

void inputScore(Contestant * p, Judge* q, int i, int m);    //输入某位选手的裁判打分
void countScores(Contestant* p, Judge * q, int n, int m);   //计算所有选手的最终成绩
void contestantSort(Contestant *p, int n);                  //选手排名

void countJudgeScore(Contestant *p, Judge* q, int n,int m); //计算评委水平等级
void judgeRanking(Judge* q, int m);                         //评委排名

// main函数运行功能
int main()
{
    int n=5; //默认选手人数
    int m=5; //默认评委人数
    Contestant contestants[N];   //创建选手数组，选手人数不超重N人
    Judge judges[M];             //创建评委数组，裁判人数不超过M人

    // 可以一直运行，直到用户选择0退出。
    while(1)
    {
        //菜单函数menu()会返回用户的选择，根据用户选择，调用执行相应的函数
        switch(menu())
        {
        case 1:  //设置选手人数
            n = setContestantAmount();
            break;

        case 2:  //设置评委人数
            m = setJudgeAmount();
            break;

        case 3:  //打分，实参传递选手数组、评委数组
            countScores(contestants,judges,n,m);
            break;

        case 4:  //选手排名，实参传递选手数组
            contestantSort(contestants,n);
            break;

        case 5:  //评委等级排名，实参传递评委数组
            judgeRanking(judges,m);
            break;

        case 0:
            printf("Over! Thank you!\n");
            exit(0);
            break;

        default:
            break;
        }
    }

    return 0;
}

//================================================
// 菜单函数，显示可选功能，并返回用户的选项
//================================================
int menu(void)
{
    int itemSelected;
    printf("\n=========Singing competition=========\n");
    printf("              1. Set Contestant Amount\n");
    printf("              2. Set Judge Amount\n");
    printf("              3. Count Scores\n");
    printf("              4. Contestant Sort\n");
    printf("              5. Judge Ranking\n");
    printf("              0. Exit\n");
    printf("======================================\n");

    printf("Your choice: ");
    scanf("%d", &itemSelected);

    return itemSelected;
}

//================================================
// 函数功能：设置参赛人数
// 函数返回值：返回参赛人数
//================================================
int setContestantAmount(void)
{
    int n;
    printf("How many contestants?");
    scanf("%d", &n);
    return n;

}

//================================================
// 函数功能：设置评委人数
// 函数返回值：返回评委人数
//================================================
int setJudgeAmount(void)
{
    int m;
    printf("How many judges?");
    scanf("%d", &m);
    return m;
}


//================================================
// 函数功能：M位裁判为某位选手打分
// 参数p: 选手数组
// 参数q: 评委数组
// 参数n： 选手数目
// 参数m： 评委数目
// 函数返回值：无返回值
//================================================
void inputScore(Contestant * p, Judge* q, int i, int m)
{
    printf("Contestant %d is playing.\n", i+1);
    printf("Please enter his ID: ");
    scanf("%d", &p[i].cID);   // 读入选手编号

    //数组scores[]保存M位评委的打分
    for(int j =0; j< m; j++)
    {
        q[j].jID = j+1;    //评委编号
        printf("Judge %d gives score: ", q[j].jID);
        scanf("%f", &p[i].scores[j]);  //评委为选手i打分
    }

}

//================================================
// 函数功能：统计选手得分
// 参数p: 选手数组
// 参数q: 评委数组
// 参数n： 选手数目
// 参数m： 评委数目
// 函数返回值：无返回值
//================================================
void countScores(Contestant* p, Judge * q, int n, int m)
{
    float max, min;
    for(int i =0; i< n; i++)
    {
        inputScore(p,q,i,m);  //调用打分函数inputScore，完成打分
        p[i].finalScore = p[i].scores[0];
        max = p[i].scores[0];
        min = p[i].scores[0];

        for(int j = 1; j< m; j++)
        {
            if(p[i].scores[j] > max)
            {
                max = p[i].scores[j];
            }
            else if (p[i].scores[j] < min)
            {
                min = p[i].scores[j];
            }
            p[i].finalScore += p[i].scores[j];
        }
        printf("Delete a maximum score: %.1f\n", max);
        printf("Delete a minimum score: %.1f\n", min);
        p[i].finalScore = (p[i].finalScore - max - min )/(m -2);
        printf("The final score of Contestant %d is %.3f\n", p[i].cID, p[i].finalScore);
    }
}

//================================================
// 函数功能：统计评委得分
// 参数p: 选手数组
// 参数q: 评委数组
// 参数n： 选手数目
// 参数m： 评委数目
// 函数返回值：无返回值
//================================================
void countJudgeScore(Contestant *p, Judge* q, int n,int m)
{
    float sum;
    for(int j=0; j<m; j++)
    {
        sum =0;
        // 某位评委的打分，从选手的 scores[]数组中读取
        for(int i =0; i<n; i++)
        {
            sum += (p[i].scores[j] - p[i].finalScore)*(p[i].scores[j]- p[i].finalScore);
        }
        if(n>0)
        {
            q[j].judgeLevel = 10-sqrt(sum/n);
        }
        else
        {
            printf("n=0\n");
            exit(0);
        }
    }
    judgeRanking(q,m);

}

//================================================
// 函数功能：对选手得分排名（冒泡法排序）
// 参数p: 选手数组
// 参数n： 选手数目
// 函数返回值：无返回值
//================================================
void contestantSort(Contestant *p, int n)
{
    printf("Order of contestants: \n");
    printf("Order\tfinal score\tID\n");

    Contestant temp;
    for(int i =0; i< n-1; i++)
    {
        for(int j = 0; j< n-1-i; j++)
        {
            if(p[j].finalScore < p[j+1].finalScore)
            {
                temp = p[j];
                p[j] = p[j+1];
                p[j+1] = temp;
            }
        }
    }

    for(int i = 0; i< n; i++)
    {
        printf("%-5d\t%-11.3f\t%-6d\n", i+1, p[i].finalScore, p[i].cID);
    }
}

//================================================
// 函数功能：评委评分水平定量评估（选择法排序）
// 参数p: 选手数组
// 参数n： 选手数目
// 函数返回值：无返回值
//================================================
void judgeRanking(Judge* q, int m)
{
    printf("Order of judges: \n");
    printf("order\tRanking\tID\n");
    int k;
    Judge temp;
    for(int i = 0; i< m -1; i++)
    {
        k = i;
        for(int j = i+1; j< m; j++ )
        {
            if(q[j].judgeLevel < q[j+1].judgeLevel)
            {
                k = j;
            }
            temp = q[k];
            q[k] = q[i];
            q[i] = temp;
        }
    }
    for(int i = 0; i< m; i++)
    {
        printf("%-5d\t%-11.3f\t%-6d\n", i+1, q[i].judgeLevel, q[i].jID);
    }
}

