#include <stdio.h>
#include <stdlib.h>

void  getMovieData(int [], int);   // 读取电影数据
void  sort(int *, int);          // 排序

double average(int *, int);       // 求平均值
double median(int *, int);        // 中位数
int   mode(int *, int);           // 众数

int main()
{
    int *movieData;  //动态数组保存统计的每位学生今年看的电影数目
    int num;         //调研的学生数目
    int mod;         // Mode statistic

    //读入数据
    printf("How many students were surveyed?\n");
    scanf("%d", &num);

    movieData = (int *) malloc(num * sizeof(int));

    // 读取电影调查数据
    getMovieData(movieData, num);

    // 排序
    sort(movieData, num);

    // 输出
    for (int k = 0; k < num; k++)
        printf("%d ", movieData[k]);
    printf("\n");

    // 平均值
    printf("The average number of movies seen is ");
    printf("%lf\n", average(movieData, num));

    // 中位数
    printf("The median of the number of movies seen is ");
    printf("%lf\n", median(movieData, num));

    // 众数
    printf("The mode of the number of movies seen is: ");
    mod = mode(movieData, num);
    if (mod == -1)
        printf("The set has no mode.\n");
    else
        printf("The mode is %d\n", mod);

    // 回收内存
    free(movieData);

    return 0;
}

//读取电影信息
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

//排序
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

// 中位数
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
// 众数
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

//平均值
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

