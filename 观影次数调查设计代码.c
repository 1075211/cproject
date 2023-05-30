#include <stdio.h>
#include <stdlib.h>

void  getMovieData(int [], int);   // ��ȡ��Ӱ����
void  sort(int *, int);          // ����

double average(int *, int);       // ��ƽ��ֵ
double median(int *, int);        // ��λ��
int   mode(int *, int);           // ����

int main()
{
    int *movieData;  //��̬���鱣��ͳ�Ƶ�ÿλѧ�����꿴�ĵ�Ӱ��Ŀ
    int num;         //���е�ѧ����Ŀ
    int mod;         // Mode statistic

    //��������
    printf("How many students were surveyed?\n");
    scanf("%d", &num);

    movieData = (int *) malloc(num * sizeof(int));

    // ��ȡ��Ӱ��������
    getMovieData(movieData, num);

    // ����
    sort(movieData, num);

    // ���
    for (int k = 0; k < num; k++)
        printf("%d ", movieData[k]);
    printf("\n");

    // ƽ��ֵ
    printf("The average number of movies seen is ");
    printf("%lf\n", average(movieData, num));

    // ��λ��
    printf("The median of the number of movies seen is ");
    printf("%lf\n", median(movieData, num));

    // ����
    printf("The mode of the number of movies seen is: ");
    mod = mode(movieData, num);
    if (mod == -1)
        printf("The set has no mode.\n");
    else
        printf("The mode is %d\n", mod);

    // �����ڴ�
    free(movieData);

    return 0;
}

//��ȡ��Ӱ��Ϣ
void getMovieData(int arr[], int num)
{
    printf("Enter the number of movies each student saw.\n");
    for (int i = 0; i < num; i++)
    {
        printf("Student %d: ", i + 1);
        scanf("%d", &arr[i]);
        //scanf("%d", arr+i);
    }
}

//����
void sort(int * array, int n)
{
    int minPos;
    for (int k = 0; k < n - 1; k++)
    {
        minPos = k;
        for(int pos = k + 1; pos < n; pos++)
        {
            if (*(array+pos) < *(array+minPos))
            {
                minPos = pos;
            }
        }
        int  temp ;
        temp = *(array+k);
        *(array+k) = *(array+minPos);
        *(array+minPos)= temp;
    }
}

// ��λ��
double median(int *arr, int num)
{
    double med;

    if (num % 2 == 0)    // Number of elements even?
    {
        int mid1 = num / 2, mid2 = (num / 2) - 1;
        med = ((*(arr + mid1) + *(arr + mid2)) / 2.0);
    }
    else
        med = *(arr + (num / 2));
    return med;
}
// ����
int mode(int *arr, int num)
{
    int *p = arr;
    int mode = -1;

    int modeFreq = 0;
    int currentFreq = 1;
    p++;

    while (p < arr + num)
    {
        if (*p == *(p-1))
        {
            currentFreq++;
            if (currentFreq > modeFreq)
            {
                mode = *p;
                modeFreq = currentFreq;
            }
        }
        else
        {
            currentFreq = 1;
        }
        p++;
    }
    if (modeFreq == 1)
        return -1;
    else
        return mode;
}

//ƽ��ֵ
double average(int arr[], int num)
{
    int total = 0;
    double ave;

    for (int count = 0; count < num; count++)
    {
        total += arr[count];
    }
    ave = total / (double)num;
    return ave;
}

