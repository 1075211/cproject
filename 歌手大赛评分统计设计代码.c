//===============================
//���ֱ�������ͳ�Ƴ���
//���ܣ�
//      (1) ��nλѡ�ֲ�����m��m>2��Ϊ��ίΪѡ�����֣���߷�10�֣���ͷ�0�֣�
//      (2) ��ֹ���ÿ��ѡ�ֵ�m���÷��У�ȥ��һ����߷ֺ�һ����ͷ֣�ȡƽ������Ϊ
//    ��ѡ�ֵ����÷֡�
//      (3) ����n��ѡ�ֵ����÷֣��Ӹߵ������ѡ�ֵĵ÷����α���ȷ����������
//      (4) ���ݸ�λѡ�ֵ����÷����λ��ί����ѡ�����������Ĳ�࣬��ÿ����ί���ֵ�
//    ׼ȷ�Ժ�����ˮ׼����һ�����������ۣ��Ӹߵ��������λ��ί�÷ֵ����α�
//===============================
#include <stdio.h>
#include <math.h>
#define N 40    // ѡ�������±��
#define M 20    // ��ί�����±��

//================================================
// �ṹ���ͣ��Զ���һ����ʾ����ѡ�ֵ��������ͣ�������ѡ�ֽṹ
// �ṹ��Ա��
//         ѡ�ֵ�ID
//         ѡ�ֵ����յ÷�
//         ѡ�ֵĲ��д��
//================================================
typedef struct
{
    int cID;            // ѡ�ֱ��
    float finalScore;   // ѡ�����÷�
    float scores[M]     // ��������M����ί��ĳλѡ�ֵ�����
} Contestant;

//================================================
// �ṹ���ͣ��Զ���һ����ʾ��ί���������ͣ�����ί�ṹ
// �ṹ��Ա��
//         ��ί��ID
//         ��ί��ˮƽ�ȼ�
//================================================
typedef struct
{
    int jID;            //��ί���
    float judgeLevel;   //��ί����ˮ׼�÷�
} Judge;


// ���������������������main��������
int menu(void);                   // ��ʾ�˵�����ʾ�û�����ѡ��Ĺ���
int setContestantAmount(void);    //���ò�������
int setJudgeAmount(void);         //���ò�������

void inputScore(Contestant * p, Judge* q, int i, int m);    //����ĳλѡ�ֵĲ��д��
void countScores(Contestant* p, Judge * q, int n, int m);   //��������ѡ�ֵ����ճɼ�
void contestantSort(Contestant *p, int n);                  //ѡ������

void countJudgeScore(Contestant *p, Judge* q, int n,int m); //������ίˮƽ�ȼ�
void judgeRanking(Judge* q, int m);                         //��ί����

// main�������й���
int main()
{
    int n=5; //Ĭ��ѡ������
    int m=5; //Ĭ����ί����
    Contestant contestants[N];   //����ѡ�����飬ѡ������������N��
    Judge judges[M];             //������ί���飬��������������M��

    // ����һֱ���У�ֱ���û�ѡ��0�˳���
    while(1)
    {
        //�˵�����menu()�᷵���û���ѡ�񣬸����û�ѡ�񣬵���ִ����Ӧ�ĺ���
        switch(menu())
        {
        case 1:  //����ѡ������
            n = setContestantAmount();
            break;

        case 2:  //������ί����
            m = setJudgeAmount();
            break;

        case 3:  //��֣�ʵ�δ���ѡ�����顢��ί����
            countScores(contestants,judges,n,m);
            break;

        case 4:  //ѡ��������ʵ�δ���ѡ������
            contestantSort(contestants,n);
            break;

        case 5:  //��ί�ȼ�������ʵ�δ�����ί����
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
// �˵���������ʾ��ѡ���ܣ��������û���ѡ��
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
// �������ܣ����ò�������
// ��������ֵ�����ز�������
//================================================
int setContestantAmount(void)
{
    int n;
    printf("How many contestants?");
    scanf("%d", &n);
    return n;

}

//================================================
// �������ܣ�������ί����
// ��������ֵ��������ί����
//================================================
int setJudgeAmount(void)
{
    int m;
    printf("How many judges?");
    scanf("%d", &m);
    return m;
}


//================================================
// �������ܣ�Mλ����Ϊĳλѡ�ִ��
// ����p: ѡ������
// ����q: ��ί����
// ����n�� ѡ����Ŀ
// ����m�� ��ί��Ŀ
// ��������ֵ���޷���ֵ
//================================================
void inputScore(Contestant * p, Judge* q, int i, int m)
{
    printf("Contestant %d is playing.\n", i+1);
    printf("Please enter his ID: ");
    scanf("%d", &p[i].cID);   // ����ѡ�ֱ��

    //����scores[]����Mλ��ί�Ĵ��
    for(int j =0; j< m; j++)
    {
        q[j].jID = j+1;    //��ί���
        printf("Judge %d gives score: ", q[j].jID);
        scanf("%f", &p[i].scores[j]);  //��ίΪѡ��i���
    }

}

//================================================
// �������ܣ�ͳ��ѡ�ֵ÷�
// ����p: ѡ������
// ����q: ��ί����
// ����n�� ѡ����Ŀ
// ����m�� ��ί��Ŀ
// ��������ֵ���޷���ֵ
//================================================
void countScores(Contestant* p, Judge * q, int n, int m)
{
    float max, min;
    for(int i =0; i< n; i++)
    {
        inputScore(p,q,i,m);  //���ô�ֺ���inputScore����ɴ��
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
// �������ܣ�ͳ����ί�÷�
// ����p: ѡ������
// ����q: ��ί����
// ����n�� ѡ����Ŀ
// ����m�� ��ί��Ŀ
// ��������ֵ���޷���ֵ
//================================================
void countJudgeScore(Contestant *p, Judge* q, int n,int m)
{
    float sum;
    for(int j=0; j<m; j++)
    {
        sum =0;
        // ĳλ��ί�Ĵ�֣���ѡ�ֵ� scores[]�����ж�ȡ
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
// �������ܣ���ѡ�ֵ÷�������ð�ݷ�����
// ����p: ѡ������
// ����n�� ѡ����Ŀ
// ��������ֵ���޷���ֵ
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
// �������ܣ���ί����ˮƽ����������ѡ������
// ����p: ѡ������
// ����n�� ѡ����Ŀ
// ��������ֵ���޷���ֵ
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

