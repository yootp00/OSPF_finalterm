#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main(void)
{

    char buffer[100] = ""; //파일의 한 줄을 문자열로 저장할 공간
    int size; //배열 사이즈
    int i = 0;


    int start, end;//출발,도착 라우터
    FILE* fp = fopen("init.ospf", "r");

    fscanf(fp, "%d", &size);


    int* distance = (int*)malloc(sizeof(int) * size); //동적할당
    int* found = (int*)malloc(sizeof(int) * size); //동적할당


    //초기화
    for (int i = 0; i < size; i++)
    {
        distance[i] = 16;
        found[i] = 0;
    }

    // size만큼 세로 동적할당
    int** arr = (int**)malloc(sizeof(int*) * size);
    // size만큼 가로 동적할당 
    for (int i = 0; i < size; i++) {
        arr[i] = (int*)malloc(sizeof(int) * size);
    }

    //파일에서 입력받기
    while (fgets(buffer, 100, fp) != NULL)
    {
        for (int j = 0; j < size; j++)
        {
            fscanf(fp, "%d", &arr[i][j]);
        }
        i++;

    }

    fclose(fp);



    //사용자로부터 출발,도착 라우터 입력받기
    printf("출발라우터 : ");
    scanf("%d", &start);
    start--;
    printf("도착라우터 : ");
    scanf("%d", &end);
    end--;



    //다익스트라 알고리즘

    for (int i = 0; i < size; i++)
    {
        distance[i] = arr[start][i];
    }
    found[start] = 1;

    int select = start;
    for (int w = 0; w < size - 1; w++)
    {
        int min = 16, min_idx = -1;//최소값

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

    //경로와 비용 출력
    printf("Path : ");
    for (int i = 0; i < size; i++)
    {
        if (found[i] == 1)
            printf("%d ", i + 1);
    }//2-3-5-8
    printf("\n");
    printf("cost : %d", distance[end]); //8

    printf("\n");



    // 메모리 해제
    for (int i = 0; i < size; i++) {
        free(arr[i]);
    }
    free(arr);
    free(distance);
    free(found);

    return 0;
}