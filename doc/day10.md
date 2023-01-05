# 10일차 STUDY & TASK
* TASK
    > 해시 테이블을 이용한 로그인, 회원가입 프로그램   
    ```cpp
    #define _CRT_SECURE_NO_WARNINGS
    #include <stdio.h>
    #include <stdlib.h>
    #include <Windows.h>
    #include <conio.h>				    //_getch() 사용하기위해 인클루드
    #define MAXSIZE 40
    #define ENCRYPTION_KEY 0x48

    typedef struct st_MAMBER		    //회원정보
    {
        char ID[MAXSIZE];
        char Pass[MAXSIZE];
        char Name[MAXSIZE];
    } MAMBER;

    typedef struct st_NODE			    //더블 링크드리스트로 회원정보 저장
    {
        MAMBER Member;
        struct st_NODE *pNext, *pPrev;
    } NODE;

    typedef struct st_HASH_NODE		    //해시테이블의 싱글 링크드리스트 형식의 자료구조
    {
        NODE *pData;
        struct st_HASH_NODE *pnext;
    } HASH_NODE;

    NODE Head, Tail;				    //회원정보의 헤드테일을 전역으로 선언해놓음
    HASH_NODE HashTable[1000];		    //해시테이블 1000개 배열로 미리저장

    bool Join();					                //가입폼
    bool Encryption(char* data, char* output);	    //암호화
    bool Print();					                //전체회원 출력 함수
    bool Login();					                //로그인 처리 함수
    bool Serch();					                //회원 찾기
    bool Del_Acc();					                //회원 삭제
    bool SerchID(char* ID);			                //중복 ID 검사
    int Hash(char* ID);                             //STRING 해시화 함수
    bool Hash_Enroll(int hash, HASH_NODE* NewHash); //해시 테이블에 데이터 추가

    int main()
    {
        int counter;
        Head.pNext = &Tail;
        Tail.pPrev = &Head;
        for (counter = 0; counter < 1000; counter++)
        {
            HashTable->pnext = NULL;
        }
        int Case;
        while (1)
        {
            printf("회원 관리 프로그램\n");
            printf("1. 회원가입\n");
            printf("2. 로그인\n");
            printf("3. 전체회원 출력\n");
            printf("4. 회원 검색\n");
            printf("5. 탈퇴\n");
            printf("6. 종료\n");
            scanf("%d", &Case);
            switch (Case)
            {
            case 1:
                system("cls");
                Join();
                break;
            case 2:
                system("cls");
                Login();
                break;
            case 3:
                system("cls");
                Print();
                break;
            case 4:
                system("cls");
                Serch();
                break;
            case 5:
                system("cls");
                Del_Acc();
                break;
            case 6:
                printf("종료되었습니다\n");
                return 0;
            }
            system("cls");
        }
    }

    bool Join()
    {
        bool flag = false;							//중복 ID 검사 플래그
        int hash;
        char OriPass[MAXSIZE];
        NODE *pNode = (NODE*)malloc(sizeof(NODE));
        HASH_NODE *NewHash = (HASH_NODE*)malloc(sizeof(HASH_NODE));
        while (flag == false)
        {
            printf("--------회원가입---------\n\n");
            printf("ID : ");
            scanf("%s", pNode->Member.ID);
            printf("PassWord : ");
            scanf("%s", OriPass);
            Encryption(OriPass, pNode->Member.Pass);
            printf("Name : ");
            scanf("%s", pNode->Member.Name);
            flag = SerchID(pNode->Member.ID);			//중복 ID 검사
        }
        pNode->pPrev = &Head;
        pNode->pNext = Head.pNext;
        Head.pNext = pNode;
        pNode->pNext->pPrev = pNode;
        hash = Hash(pNode->Member.ID);					//해시처리
        NewHash->pData = pNode;							//해시 데이터 입력
        Hash_Enroll(hash, NewHash);						//해시테이블에 해시 추가
        printf("가입이 완료되었습니다\n");
        _getch();
        system("cls");
        return true;
    }

    bool Encryption(char *data, char *output)
    {
        int Counter = 0;
        char key = ENCRYPTION_KEY;						//암호화 키값
        while (data[Counter] != '\0')					//글자길이만큼 암호화
        {
            data[Counter] ^= key;
            Counter++;
        }

        memcpy(output,data,sizeof(char[MAXSIZE]));	
        return true;
    }

    bool Login()
    {
        NODE *pNode = Head.pNext;
        char ID[MAXSIZE];
        char Pass[MAXSIZE];
        printf("--------로그인---------\n\n");
        printf("ID : ");
        scanf("%s", ID);
        printf("PassWord : ");
        scanf("%s", Pass);
        Encryption(Pass, Pass);
        while (pNode != &Tail)
        {
            if (0 == strcmp(pNode->Member.ID,ID))		//로그인은 해시테이블 사용 안했음
            {
                break;
            }
            pNode = pNode->pNext;
        }
        if (pNode == &Tail)
        {
            printf("찾을 수 없는 ID 입니다\n");
            _getch();
            system("cls");
            return false;
        }
        if (0 == memcmp(pNode->Member.Pass, Pass, sizeof(char[MAXSIZE])))	//암호화때문에 메모리 비교 사용
        {
            printf("로그인 되었습니다\n");
            _getch();
            system("cls");
            return true;
        }
        else
        {
            printf("틀린 비밀번호 입니다\n");
            _getch();
            system("cls");
            return false;
        }
    }

    bool Print()
    {
        NODE *pNode = Head.pNext;
        printf("--------전체 회원---------\n\n");
        while (pNode != &Tail)							//회원정보 링크드리스트 순회하면서 출력
        {
            printf("ID : %s\n", pNode->Member.ID);
            printf("PassWord : %s\n", pNode->Member.Pass);
            printf("Name : %s\n", pNode->Member.Name);
            printf("\n\n");
            pNode = pNode->pNext;
        }
        _getch();
        system("cls");
        return true;
    }

    bool Serch()
    {
        int index;										//해시테이블 배열의 인덱스 값
        char ID[40];	
        HASH_NODE *pNode;
        printf("--------회원찾기---------\n\n");
        printf("ID : ");
        scanf("%s", ID);
        index = Hash(ID);
        pNode = HashTable[index].pnext;					//헤시테이블을 이용해서 검색없이 바로 접근가능
        while (pNode != NULL)							//헤시테이블이 겹칠시 싱글 링크드리스트를 이용해서 값들을 저장함
        {
            if (0 == strcmp(pNode->pData->Member.ID, ID))	
            {
                printf("ID : %s\n", pNode->pData->Member.ID);
                printf("PassWord : %s\n", pNode->pData->Member.Pass);
                printf("Name : %s\n", pNode->pData->Member.Name);
                printf("\n\n");
                _getch();
                return true;							//찾음
                
            }
            pNode = pNode->pnext;
        }
        printf("찾을 수 없는 ID 입니다\n");				//못찾음
        _getch();
        return false;
    }
    bool Del_Acc()
    {
        char ID[MAXSIZE];
        char Pass[MAXSIZE];
        int index;
        HASH_NODE *pNode, *pPriv;
        printf("-------계정삭제-------\n\n");
        printf("ID : ");
        scanf("%s", ID);
        printf("PassWord : ");
        scanf("%s", Pass);
        Encryption(Pass, Pass);
        index = Hash(ID);
        pNode = HashTable[index].pnext;
        pPriv = &HashTable[index];
        while (pNode != NULL)
        {
            if (0 == strcmp(pNode->pData->Member.ID, ID))
            {
                if (0 == strcmp(pNode->pData->Member.Pass, Pass))
                {
                    pNode->pData->pPrev->pNext = pNode->pData->pNext;			//NODE 앞뒤 연결 후 삭제
                    pNode->pData->pNext->pPrev = pNode->pData->pPrev;
                    free(pNode->pData);
                    pPriv->pnext = pNode->pnext;								//HASH_NODE 뒤에서 다음으로 연결 후 삭제
                    free(pNode);
                    printf("삭제되었습니다\n");
                    _getch();
                    return true;
                }
                printf("비밀번호가 틀렸습니다\n");								//Pass 틀린경우
                _getch();
                return false;
            }
            pPriv = pNode;														//pPriv 는 항상 pNode의 전을 가리키고 있다
            pNode = pNode->pnext;
        }
        printf("없는 ID 입니다\n");												//ID 검색이 안될시
        _getch();
        return false;
    }

    int Hash(char *ID)
    {
        int Hash = 0;
        int counter;
        int L = strlen(ID);
        for (counter = 0; counter <= L; counter++)
        {
            Hash += ID[counter];
        }
        Hash = Hash % 1000;
        return Hash;
    }

    bool Hash_Enroll(int hash, HASH_NODE* NewHash)								//해시 테이블에 데이터 추가
    {
        HASH_NODE *pTemp;
        pTemp = HashTable[hash].pnext;
        if (pTemp == NULL)
        {
            HashTable[hash].pnext = NewHash;
            NewHash->pnext = NULL;
            return true;
        }
        while (pTemp->pnext != NULL)
        {
            pTemp = pTemp->pnext;
        }
        pTemp->pnext = NewHash;
        NewHash->pnext = NULL;
        return true;
    }

    bool SerchID(char*ID)														//가입시 ID 검사
    {
        int index;		//key
        HASH_NODE *pNode;
        index = Hash(ID);
        pNode = HashTable[index].pnext;
        while (pNode != NULL)
        {
            if (0 == strcmp(pNode->pData->Member.ID, ID))
            {
                printf("이미 있는 ID 입니다\n");
                _getch();
                system("cls");
                return false;						//찾음

            }
            pNode = pNode->pnext;
        }
        return true;
    }
    ```
    > 위 코드를 확인하고 실행시켜보기   
    > 디버깅 하는 방법 익히기   

[To main](/README.md)