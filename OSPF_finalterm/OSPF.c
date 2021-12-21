#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main(void)
{

    char buffer[100] = ""; //������ �� ���� ���ڿ��� ������ ����
    int size; //�迭 ������
    int i = 0;


    int start, end;//���,���� �����
    FILE* fp = fopen("init.ospf", "r");

    fscanf(fp, "%d", &size);


    int* distance = (int*)malloc(sizeof(int) * size); //�����Ҵ�
    int* found = (int*)malloc(sizeof(int) * size); //�����Ҵ�


    //�ʱ�ȭ
    for (int i = 0; i < size; i++)
    {
        distance[i] = 16;
        found[i] = 0;
    }

    // size��ŭ ���� �����Ҵ�
    int** arr = (int**)malloc(sizeof(int*) * size);
    // size��ŭ ���� �����Ҵ� 
    for (int i = 0; i < size; i++) {
        arr[i] = (int*)malloc(sizeof(int) * size);
    }

    //���Ͽ��� �Է¹ޱ�
    while (fgets(buffer, 100, fp) != NULL)
    {
        for (int j = 0; j < size; j++)
        {
            fscanf(fp, "%d", &arr[i][j]);
        }
        i++;

    }

    fclose(fp);



    //����ڷκ��� ���,���� ����� �Է¹ޱ�
    printf("��߶���� : ");
    scanf("%d", &start);
    start--;
    printf("��������� : ");
    scanf("%d", &end);
    end--;



    //���ͽ�Ʈ�� �˰���

    for (int i = 0; i < size; i++)
    {
        distance[i] = arr[start][i];
    }
    found[start] = 1;

    int select = start;
    for (int w = 0; w < size - 1; w++)
    {
        int min = 16, min_idx = -1;//�ּҰ�

        if (arr[select][end] < 16)
        {
            found[end] = 1;
            break;
        }
        for (int j = 0; j < size; j++)
        {

            if (arr[select][j] < 16 && arr[select][j] < min && found[j] != 1)
            {
                min = arr[select][j];
                min_idx = j;
            }

        }

        select = min_idx;
        found[min_idx] = 1;


        for (int i = 0; i < size; i++)
        {
            if (distance[i] > (distance[min_idx] + arr[min_idx][i]) && found[i] != 1)
            {
                distance[i] = distance[min_idx] + arr[min_idx][i];
            }
        }

    }

    printf("\n");

    //��ο� ��� ���
    printf("Path : ");
    for (int i = 0; i < size; i++)
    {
        if (found[i] == 1)
            printf("%d ", i + 1);
    }//2-3-5-8
    printf("\n");
    printf("cost : %d", distance[end]); //8

    printf("\n");



    // �޸� ����
    for (int i = 0; i < size; i++) {
        free(arr[i]);
    }
    free(arr);
    free(distance);
    free(found);

    return 0;
}