/*
����������ϰ������λ���ļӷ����������˷���������ȡģ��ϰ
��1���Թ��ܲ˵��ķ�ʽ�����û�ѡ��ִ����������������ϰ��+ - * / %��
��2��ѡ��һ��������ϰ�󣬿�����ϰ�����⣬��ϰ��������������
��3���û��ڴ��������ɴ��Դ�Ļ��ᣬ�����û�д�ԣ��Ѵ���ʾ���û����Դ�Ĵ�����������
��4����¼�û���ԡ������������ڽ���һ��������ϰ����ʾ���û�
*/
#include<stdio.h>
#include <stdlib.h>
#include <time.h>

// �����������������main��������
int menu(void);  // ��ʾ�˵�����ʾ�û�����ѡ��Ĺ���
int arithmeticOp(char op, int amount,int chance);// �������㣬ִ��+ - * / %
int setAmount(void);   //���ô�����
int setChance(void);   //�����Դ����
void stat(int rightNum, int amount);   //�������ͳ��


// main����ִ�й�������
int main()
{
    int rightNum;      // ��Ե�������
    int amount = 5;    // �û���ѡ��һ���������ϰ���������������
    int chance = 3;    // �û��ڴ������󣬿����Դ�Ĵ���

    // ����һֱ���У�ֱ���û�ѡ��0�˳���
    while(1)
    {
        //�˵�����menu()�᷵���û���ѡ�񣬸����û�ѡ��Ĺ��ܣ�������Ӧ�ĺ��������м���
        switch(menu())
        {
        case 1:  //�ӷ�����
            rightNum = arithmeticOp('+',amount,chance);
            stat(rightNum,amount);
            break;
        case 2:  // ��������
            rightNum = arithmeticOp('-',amount,chance);
            stat(rightNum,amount);
            break;
        case 3:  // �˷�����
            rightNum = arithmeticOp('*',amount,chance);
            stat(rightNum,amount);
            break;
        case 4:  // ��������
            rightNum = arithmeticOp('/',amount,chance);
            stat(rightNum,amount);
            break;
        case 5:  // ȡģ����
            rightNum = arithmeticOp('%',amount,chance);
            stat(rightNum,amount);
            break;
        case 6:  // ���ô�����
            amount = setAmount();
            break;
        case 7:  // �����Դ����
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

// �˵���������ʾ��ѡ���ܣ��������û���ѡ��
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

// �������㣬ִ��+ - * / %
// ����op: ���������㣺+ - * / %
// ����amount: ��ϰ���������������
// ����chances�� �û��ڴ������󣬿����Դ�Ĵ���
int arithmeticOp(char op, int amount,int chances)
{
    int a, b; // ������ɵ���������������������
    int answer, result;  // answer��ȷ�ļ�������result�û�����ļ�����
    int rightNum=0;     //��ȷ������

    while(amount)  // �û�����amount����Ŀ
    {
        // �����������ĳ�ʼ������Ҫ����whileѭ���ڣ���Ϊÿһ��ѭ��������һ���µ���Ŀ��
        // �Դ��ܴ����͵�ǰ�Դ���ۼƴ���������Ҫ�ָ�ԭֵ
        int chance=chances;  //�����Դ���ܴ�������ֵchances���β�ֵ
        int count = 0;       //��ǰ�Դ�Ĵ���

        //���������������
        srand(time(NULL));
        a = rand()%100 + 1;
        b = rand()%100 +1;

        //�����β�opֵ��ִ����Ӧ������
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

        //�����û��ļ����������������chance�λ���
        do
        {
            // �����û�������
            printf("%d %c %d = ", a, op,b);
            scanf("%d", &answer);

            //�ж��û��������Ƿ���ȷ
            // �����ȷ��������ȷ���ۼ�1
            // �����һ�δ��⣬������Ŀ��1
            // ������Ŀ��1�������ֳ�����
            //     ����һ����һ�ξʹ���ˣ�count == 0��
            //     �������������Դ���һ�Σ�count > 0�����û����Դ�Ļ��ᣬ������Ŀ��1
            //             ��Ҫ�����û��Դ��������ִ�У��û��������Դ�����ˣ�Ҳ��
            //             �����ն�û�д�ԡ���
            if(answer == result)
            {
                printf("Bingo, you are right.\n");
                rightNum++;    //������ȷ���ۼ�1

                // ������Ŀ��1������һ����һ�ξʹ���ˣ�
                if(count==0)
                    amount--;
            }
            else
            {
                printf("Oopse, It's wrong, try again.\n");
                count++;   //��ǰ�Դ������1
            }
        }
        while(count< chance && result != answer);  // �û�û�д�ԣ�ͬʱ�����Դ����

        // �û��Դ�û�д�ԣ���ʾ�û����մ�
        if(count == chance)
        {
            printf("The answer is: %d\n\n", result);
        }

        // ������Ŀ��1���������������Դ���һ�Σ�
        if(count>0)
            amount--;
    }
    return rightNum;  //���ص�ǰ��һ�ּ������ȷ������
}

//���ô�����Ŀ
int setAmount(void)
{
    int x;
    printf("Set amount: ");
    scanf("%d", &x);
    return x;
}

//���ô����Դ����
int setChance(void)
{
    int x;
    printf("Set chance: ");
    scanf("%d", &x);
    return x;
}

//ͳ�Ƶ�ǰһ���У����������������
//����rightNum����ǰһ�֣���Ե�����
//����amount����ǰһ�֣���Ҫ�����������
void stat(int rightNum, int amount)
{
    //  ������������Ҫ����Ϊ��̬�ͱ����������ۼ�����
    static int score = 0, error = 0;

    score +=rightNum;
    error = error + (amount - rightNum);

    printf("Total score =  %d, error number = %d\n", score, error);
}



