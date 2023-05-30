/*
四则运算练习程序：两位数的加法、减法、乘法、除法、取模练习
（1）以功能菜单的方式，让用户选择执行哪种四则运算练习（+ - * / %）
（2）选择一种运算练习后，可以练习若干题，练习的题数可以设置
（3）用户在答错后，有若干次试错的机会，如果都没有答对，把答案显示给用户。试错的次数可以设置
（4）记录用户答对、答错的题数，在结束一种运算练习后，显示给用户
*/
#include<stdio.h>
#include <stdlib.h>
#include <time.h>

// 函数声明，定义放在main函数后面
int menu(void);  // 显示菜单，显示用户可以选择的功能
int arithmeticOp(char op, int amount,int chance);// 四则运算，执行+ - * / %
int setAmount(void);   //设置答题数
int setChance(void);   //设置试错次数
void stat(int rightNum, int amount);   //答题情况统计


// main函数执行功能运行
int main()
{
    int rightNum;      // 答对的总题数
    int amount = 5;    // 用户在选择一种运算后，练习该种运算的总题数
    int chance = 3;    // 用户在答题错误后，可以试错的次数

    // 可以一直运行，直到用户选择0退出。
    while(1)
    {
        //菜单函数menu()会返回用户的选择，根据用户选择的功能，调用相应的函数，进行计算
        switch(menu())
        {
        case 1:  //加法运算
            rightNum = arithmeticOp('+',amount,chance);
            stat(rightNum,amount);
            break;
        case 2:  // 减法运算
            rightNum = arithmeticOp('-',amount,chance);
            stat(rightNum,amount);
            break;
        case 3:  // 乘法运算
            rightNum = arithmeticOp('*',amount,chance);
            stat(rightNum,amount);
            break;
        case 4:  // 除法运算
            rightNum = arithmeticOp('/',amount,chance);
            stat(rightNum,amount);
            break;
        case 5:  // 取模运算
            rightNum = arithmeticOp('%',amount,chance);
            stat(rightNum,amount);
            break;
        case 6:  // 设置答题数
            amount = setAmount();
            break;
        case 7:  // 设置试错次数
            chance = setChance();
            break;
        case 0:
            printf("Game over.\n");
            exit(0);
            break;
        default:
            break;
        }
    }
    return 0;
}

// 菜单函数，显示可选功能，并返回用户的选项
int menu(void)
{
    int itemSelected;
    printf("\n=========Arithmetic exercises=========\n");
    printf("              1. Add\n");
    printf("              2. Subtract\n");
    printf("              3. Multiply\n");
    printf("              4. Divide\n");
    printf("              5. Mode\n");
    printf("              6. SetAmount\n");
    printf("              7. SetChance\n");
    printf("              0. Exit\n");
    printf("======================================\n");

    printf("Your choice: ");
    scanf("%d", &itemSelected);

    return itemSelected;
}

// 四则运算，执行+ - * / %
// 参数op: 所做的运算：+ - * / %
// 参数amount: 练习该种运算的总题数
// 参数chances： 用户在答题错误后，可以试错的次数
int arithmeticOp(char op, int amount,int chances)
{
    int a, b; // 随机生成的两个数，参与四则运算
    int answer, result;  // answer正确的计算结果，result用户输入的计算结果
    int rightNum=0;     //正确答题数

    while(amount)  // 用户将做amount道题目
    {
        // 这两个变量的初始化，需要放在while循环内，因为每一轮循环都是做一道新的题目，
        // 试错总次数和当前试错的累计次数，都需要恢复原值
        int chance=chances;  //可以试错的总次数，右值chances是形参值
        int count = 0;       //当前试错的次数

        //生成运算的两个数
        srand(time(NULL));
        a = rand()%100 + 1;
        b = rand()%100 +1;

        //根据形参op值，执行相应的运算
        switch(op)
        {
        case '+':
            result = a + b;
            break;
        case '-':
            result = a - b;
            break;
        case '*':
            result = a * b;
            break;
        case '/':
            result = a / b;
            break;
        case '%':
            result = a % b;
            break;
        }

        //读入用户的计算结果，如果错误，有chance次机会
        do
        {
            // 读入用户计算结果
            printf("%d %c %d = ", a, op,b);
            scanf("%d", &answer);

            //判断用户计算结果是否正确
            // 如果正确，答题正确数累计1
            // 完成了一次答题，答题数目减1
            // 答题数目减1，分两种场景：
            //     场景一：第一次就答对了（count == 0）
            //     场景二：至少试错了一次（count > 0）。用户有试错的机会，答题数目减1
            //             需要放在用户试错结束后再执行（用户可能在试错后答对了，也可
            //             能最终都没有答对。）
            if(answer == result)
            {
                printf("Bingo, you are right.\n");
                rightNum++;    //答题正确数累计1

                // 答题数目减1：场景一（第一次就答对了）
                if(count==0)
                    amount--;
            }
            else
            {
                printf("Oopse, It's wrong, try again.\n");
                count++;   //当前试错次数加1
            }
        }
        while(count< chance && result != answer);  // 用户没有答对，同时还有试错机会

        // 用户试错都没有答对，提示用户最终答案
        if(count == chance)
        {
            printf("The answer is: %d\n\n", result);
        }

        // 答题数目减1：场景二（至少试错了一次）
        if(count>0)
            amount--;
    }
    return rightNum;  //返回当前这一轮计算的正确答题数
}

//设置答题数目
int setAmount(void)
{
    int x;
    printf("Set amount: ");
    scanf("%d", &x);
    return x;
}

//设置答题试错次数
int setChance(void)
{
    int x;
    printf("Set chance: ");
    scanf("%d", &x);
    return x;
}

//统计当前一轮中，答题对与错的总题数
//参数rightNum：当前一轮，答对的题数
//参数amount：当前一轮，需要答题的总题数
void stat(int rightNum, int amount)
{
    //  这两个变量需要设置为静态型变量，用来累计总数
    static int score = 0, error = 0;

    score +=rightNum;
    error = error + (amount - rightNum);

    printf("Total score =  %d, error number = %d\n", score, error);
}



