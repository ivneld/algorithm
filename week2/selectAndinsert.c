// clock()을 통해 시간 측정할때 현재 코드에 쓴 QueryPerformanceFrequency() => ms 단위로측정
// 외에도, nanosec단위로도 셀수있고, window()함수에서가 아닌 다른 환경에서 측정할수있는 방법도
// 임있을 상기하자.
#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <time.h>

int* InPlaceSelectionSort(int* arr, int N);
int* InPlaceInsertionSort(int* arr, int N);
void SwapElement(int* a, int* b);
int* RegularArrangement(int* arr, int N);
int* InverseArrangement(int* arr, int N);

int main()
{
    int N, elem;
    int* arr1 = NULL, * arr2 = NULL;
    LARGE_INTEGER ticksPerSec;
    LARGE_INTEGER start, end, diff;

    srand(time(NULL));
    scanf("%d", &N);
    arr1 = (int*)malloc(sizeof(int) * N);
    arr2 = (int*)malloc(sizeof(int) * N);

    for (int i = 0; i < N; i++)
    {
        elem = rand() % N + 1;	// 그냥 이렇게되면 ,N이 32767이하에 수에서만 랜덤으로
        arr1[i] = elem;			// 입력하기때문에 중복이 많이 발생할 수 있다.
        arr2[i] = elem;
    }

    // 정배열 , 역배열로 전환
    //arr1 = RegularArrangement(arr1,N);
    //arr2 = RegularArrangement(arr2,N);
    //arr1 = InverseArrangement(arr1, N);
    //arr2 = InverseArrangement(arr2, N);

    // 정렬 되었는지 확인용 출력
    /*for (int i = 0; i < N; i++)
        printf(" %d", arr1[i]);
    printf("\n");
    for (int i = 0; i < N; i++)
        printf(" %d", arr2[i]);
    printf("\n");*/

    QueryPerformanceFrequency(&ticksPerSec);
    QueryPerformanceCounter(&start);
    arr1 = InPlaceSelectionSort(arr1, N);
    QueryPerformanceCounter(&end);

    // 측정 값으로부터 실행시간 계산
    diff.QuadPart = end.QuadPart - start.QuadPart;
    printf("선택정렬 : %.9f ms\n", ((double)diff.QuadPart / (double)ticksPerSec.QuadPart) * 1000);

    QueryPerformanceFrequency(&ticksPerSec);
    QueryPerformanceCounter(&start);
    arr2 = InPlaceInsertionSort(arr2, N);
    QueryPerformanceCounter(&end);

    diff.QuadPart = end.QuadPart - start.QuadPart;
    printf("삽입정렬 : %.9f ms\n", ((double)diff.QuadPart / (double)ticksPerSec.QuadPart) * 1000);

    // 선택,삽입정렬결과 출력부분
    /*for (int i = 0; i < N; i++)
        printf(" %d", arr1[i]);
    printf("\n");
    for (int i = 0; i < N; i++)
        printf(" %d", arr2[i]);*/

    free(arr1);
    free(arr2);
    return 0;
}
int* InPlaceSelectionSort(int* arr, int N)	// 제자리 선택정렬
{
    int minLoc, save;
    for (int i = N - 1; i > 0; i--)
    {
        minLoc = i;
        for (int j = i - 1; j >= 0; j--)
        {
            if (arr[j] > arr[minLoc])
                minLoc = j;
        }
        SwapElement(&arr[i], &arr[minLoc]); // 쿼리 퍼포먼스사이 시간측정에 함수를 넣지않고
    }										// 원래의 형태를 넣어주는것이 시간측정에 더 정확
    return arr;
}
int* InPlaceInsertionSort(int* arr, int N)	// 제자리 삽입정렬
{
    int save, j;

    for (int i = 1; i < N; i++)
    {
        save = arr[i];
        j = i - 1;
        while (j >= 0 && arr[j] > save)
        {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = save;
    }
    return arr;
}
void SwapElement(int* a, int* b)
{
    int tmp;

    tmp = *a;
    *a = *b;
    *b = tmp;
}
int* RegularArrangement(int* arr, int N)	// 제자리정렬전에 정배열리스트 만들기 ( by.버블정렬 )
{
    int tmp;
    for (int i = 0; i < N - 1; i++)
    {
        for (int j = 0; j < N - 1; j++)
        {
            if (arr[j] > arr[j + 1])
            {
                tmp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = tmp;
            }
        }
    }
    return arr;
}
int* InverseArrangement(int* arr, int N)	// 제자리정렬전에 역배열리스트 만들기 ( by.버블정렬 )
{
    int tmp;
    for (int i = 0; i < N - 1; i++)
    {
        for (int j = 0; j < N - 1; j++)
        {
            if (arr[j] < arr[j + 1])
            {
                tmp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = tmp;
            }
        }
    }
    return arr;
}