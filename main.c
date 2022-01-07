//
//  main.c
//  2048
//
//  Created by 俞越 on 2022/1/7.
//

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
int score = 0;

void drawTable(int score, int step, int table[4][4]){
    system("cls");
    printf("\n2048 game board\n");
    printf("Total score: %d\n", score);
    printf("Total step: %d\n", step);
    printf("+----+----+----+----+\n");
    for(int i = 0; i < 4; i ++){
        for(int j = 0; j < 4; j++){
            if(table[i][j] != -1)
                printf("|%4d", table[i][j]);
            else
                printf("|    ");
        }
        printf("|\n");
        printf("+----+----+----+----+\n");
    }
    printf("\n");
}

int generateNum(int table[4][4]){
    int emptyNum = 0;
    int index[16];
    for(int i = 0; i < 16; i++)
        index[i] = -1;
    for(int i = 0; i < 4; i++)
    {
        for(int j = 0; j < 4; j++)
        {
            if(table[i][j] == -1)
            {
                index[emptyNum] = i * 4 + j;
                emptyNum ++;
            }
        }
    }
    if(emptyNum == 0)
        return 0;
    int randNum, randPos;
    srand((unsigned)time(NULL));
    randNum = 2 * (rand() % 2 + 1);
    score += randNum;
    srand((unsigned)time(NULL));
    randPos = rand() % emptyNum;
    table[index[randPos]/4][index[randPos]%4] = randNum;
    return 1;
}

int gameOver(int table[4][4]){
    for(int i = 0; i < 4; i++)
        for(int j = 0; j < 4; j++)
            if(table[i][j] == -1)
                return 0;
    int new_table[6][6];
    for(int i = 0; i < 6; i++)
    {
        for(int j = 0; j < 6; j++)
        {
            if(i>0 && i<5 && j>0 && j<5)
                new_table[i][j] = table[i-1][j-1];
            else
                new_table[i][j] = 0;
        }
    }
    for(int i = 1; i < 5; i++)
    {
        for(int j = 1; j < 5; j++)
        {
            if(new_table[i][j] == new_table[i-1][j] || new_table[i][j] == new_table[i+1][j] || new_table[i][j] == new_table[i][j-1] || new_table[i][j] == new_table[i][j+1])
                return 0;
        }
    }
    return 1;
}

int userInputW(int table[4][4]){
    int aval = 0;
    int tmp_table[4][4];
    int tmp_score = 0;
    for(int i = 0; i<4; i++)
        for(int j = 0; j<4; j++)
            tmp_table[i][j] = table[i][j];
    for(int j = 0; j < 4; j++)
    {
        int num = 0;
        int tmp[4];
        for(int i = 0; i<4; i++)
        {
            if(tmp_table[i][j]!=-1)
            {
                tmp[num] = tmp_table[i][j];
                num++;
            }
        }
        if(num == 1)
        {
            tmp_table[0][j] = tmp[0];
            for(int i = 1; i<4; i++)
                tmp_table[i][j] = -1;
        }
        else if(num == 2)
        {
            if(tmp[0] == tmp[1])
            {
                tmp_table[0][j] = tmp[0]+tmp[1];
                tmp_score += tmp[0]+tmp[1];
                for(int i = 1; i<4; i++)
                    tmp_table[i][j] = -1;
            }
            else
            {
                tmp_table[0][j] = tmp[0];
                tmp_table[1][j] = tmp[1];
                for(int i = 2; i<4; i++)
                    tmp_table[i][j] = -1;
            }
        }
        else if(num == 3)
        {
            if(tmp[0] == tmp[1])
            {
                tmp_table[0][j] = tmp[0] + tmp[1];
                tmp_score += tmp[0] + tmp[1];
                tmp_table[1][j] = tmp[2];
                for(int i = 2; i<4; i++)
                    tmp_table[i][j] = -1;
            }
            else if(tmp[1] == tmp[2])
            {
                tmp_table[0][j] = tmp[0];
                tmp_table[1][j] = tmp[1] + tmp[2];
                tmp_score += tmp[1] + tmp[2];
                for(int i = 2; i<4; i++)
                    tmp_table[i][j] = -1;
            }
            else
            {
                tmp_table[0][j] = tmp[0];
                tmp_table[1][j] = tmp[1];
                tmp_table[2][j] = tmp[2];
                tmp_table[3][j] = -1;
            }
        }
        else if(num == 4)
        {
            if(tmp[0] == tmp[1] && tmp[2] == tmp[3])
            {
                tmp_table[0][j] = tmp[0] + tmp[1];
                tmp_table[1][j] = tmp[2] + tmp[3];
                tmp_score += tmp[0] + tmp[1];
                tmp_score += tmp[2] + tmp[3];
                for(int i = 2; i<4; i++)
                    tmp_table[i][j] = -1;
            }
            else if(tmp[0] == tmp[1])
            {
                tmp_table[0][j] = tmp[0] + tmp[1];
                tmp_score += tmp[0] + tmp[1];
                tmp_table[1][j] = tmp[2];
                tmp_table[2][j] = tmp[3];
                tmp_table[3][j] = -1;
            }
            else if(tmp[1]==tmp[2])
            {
                tmp_table[0][j] = tmp[0];
                tmp_table[1][j] = tmp[1]+tmp[2];
                tmp_score += tmp[1]+tmp[2];
                tmp_table[2][j] = tmp[3];
                tmp_table[3][j] = -1;
            }
            else if(tmp[2] == tmp[3])
            {
                tmp_table[0][j] = tmp[0];
                tmp_table[1][j] = tmp[1];
                tmp_table[2][j] = tmp[2] + tmp[3];
                tmp_score += tmp[2] + tmp[3];
                tmp_table[3][j] = -1;
            }
        }
    }
    for(int i = 0; i<4; i++)
    {
        for(int j = 0; j<4; j++)
        {
            if(tmp_table[i][j] != table[i][j])
            {
                aval = 1;
                break;
            }
        }
    }
    if(aval == 1)
    {
        score += tmp_score;
        for(int i = 0; i<4; i++)
            for(int j = 0; j<4; j++)
                table[i][j] = tmp_table[i][j];
        return 1;
    }
    return 0;
}

int userInputS(int table[4][4]){
    int aval = 0;
    int tmp_table[4][4];
    int tmp_score = 0;
    for(int i = 0; i<4; i++)
        for(int j = 0; j<4; j++)
            tmp_table[i][j] = table[i][j];
    for(int j = 0; j < 4; j++)
    {
        int num = 0;
        int tmp[4];
        for(int i = 3; i>=0; i--)
        {
            if(tmp_table[i][j]!=-1)
            {
                tmp[num] = tmp_table[i][j];
                num++;
            }
        }
        if(num == 1)
        {
            tmp_table[3][j] = tmp[0];
            for(int i = 0; i<3; i++)
                tmp_table[i][j] = -1;
        }
        else if(num == 2)
        {
            if(tmp[0] == tmp[1])
            {
                tmp_table[3][j] = tmp[0]+tmp[1];
                tmp_score += tmp[0]+tmp[1];
                for(int i = 0; i<3; i++)
                    tmp_table[i][j] = -1;
            }
            else
            {
                tmp_table[3][j] = tmp[0];
                tmp_table[2][j] = tmp[1];
                for(int i = 0; i<2; i++)
                    tmp_table[i][j] = -1;
            }
        }
        else if(num == 3)
        {
            if(tmp[0] == tmp[1])
            {
                tmp_table[3][j] = tmp[0] + tmp[1];
                tmp_score += tmp[0] + tmp[1];
                tmp_table[2][j] = tmp[2];
                for(int i = 0; i<2; i++)
                    tmp_table[i][j] = -1;
            }
            else if(tmp[1] == tmp[2])
            {
                tmp_table[3][j] = tmp[0];
                tmp_table[2][j] = tmp[1] + tmp[2];
                tmp_score += tmp[1] + tmp[2];
                for(int i = 0; i<2; i++)
                    tmp_table[i][j] = -1;
            }
            else
            {
                tmp_table[3][j] = tmp[0];
                tmp_table[2][j] = tmp[1];
                tmp_table[1][j] = tmp[2];
                tmp_table[0][j] = -1;
            }
        }
        else if(num == 4)
        {
            if(tmp[0] == tmp[1] && tmp[2] == tmp[3])
            {
                tmp_table[3][j] = tmp[0] + tmp[1];
                tmp_table[2][j] = tmp[2] + tmp[3];
                tmp_score += tmp[0] + tmp[1];
                tmp_score += tmp[2] + tmp[3];
                for(int i = 0; i<2; i++)
                    tmp_table[i][j] = -1;
            }
            else if(tmp[0] == tmp[1])
            {
                tmp_table[3][j] = tmp[0] + tmp[1];
                tmp_score += tmp[0] + tmp[1];
                tmp_table[2][j] = tmp[2];
                tmp_table[1][j] = tmp[3];
                tmp_table[0][j] = -1;
            }
            else if(tmp[1]==tmp[2])
            {
                tmp_table[3][j] = tmp[0];
                tmp_table[2][j] = tmp[1]+tmp[2];
                tmp_score += tmp[1]+tmp[2];
                tmp_table[1][j] = tmp[3];
                tmp_table[0][j] = -1;
            }
            else if(tmp[2] == tmp[3])
            {
                tmp_table[3][j] = tmp[0];
                tmp_table[2][j] = tmp[1];
                tmp_table[1][j] = tmp[2] + tmp[3];
                tmp_score += tmp[2] + tmp[3];
                tmp_table[0][j] = -1;
            }
        }
    }
    for(int i = 0; i<4; i++)
    {
        for(int j = 0; j<4; j++)
        {
            if(tmp_table[i][j] != table[i][j])
            {
                aval = 1;
                break;
            }
        }
    }
    if(aval == 1)
    {
        score += tmp_score;
        for(int i = 0; i<4; i++)
            for(int j = 0; j<4; j++)
                table[i][j] = tmp_table[i][j];
        return 1;
    }
    return 0;
}

int userInputA(int table[4][4]){
    int aval = 0;
    int tmp_table[4][4];
    int tmp_score = 0;
    for(int i = 0; i<4; i++)
        for(int j = 0; j<4; j++)
            tmp_table[i][j] = table[i][j];
    for(int i = 0; i < 4; i++)
    {
        int num = 0;
        int tmp[4];
        for(int j = 0; j<4; j++)
        {
            if(tmp_table[i][j]!=-1)
            {
                tmp[num] = tmp_table[i][j];
                num++;
            }
        }
        if(num == 1)
        {
            tmp_table[i][0] = tmp[0];
            for(int j = 1; j<4; j++)
                tmp_table[i][j] = -1;
        }
        else if(num == 2)
        {
            if(tmp[0] == tmp[1])
            {
                tmp_table[i][0] = tmp[0]+tmp[1];
                tmp_score += tmp[0]+tmp[1];
                for(int j = 1; j<4; j++)
                    tmp_table[i][j] = -1;
            }
            else
            {
                tmp_table[i][0] = tmp[0];
                tmp_table[i][1] = tmp[1];
                for(int j = 2; j<4; j++)
                    tmp_table[i][j] = -1;
            }
        }
        else if(num == 3)
        {
            if(tmp[0] == tmp[1])
            {
                tmp_table[i][0] = tmp[0] + tmp[1];
                tmp_score += tmp[0] + tmp[1];
                tmp_table[i][1] = tmp[2];
                for(int j = 2; j<4; j++)
                    tmp_table[i][j] = -1;
            }
            else if(tmp[1] == tmp[2])
            {
                tmp_table[i][0] = tmp[0];
                tmp_table[i][1] = tmp[1] + tmp[2];
                tmp_score += tmp[1] + tmp[2];
                for(int j = 2; j<4; j++)
                    tmp_table[i][j] = -1;
            }
            else
            {
                tmp_table[i][0] = tmp[0];
                tmp_table[i][1] = tmp[1];
                tmp_table[i][2] = tmp[2];
                tmp_table[i][3] = -1;
            }
        }
        else if(num == 4)
        {
            if(tmp[0] == tmp[1] && tmp[2] == tmp[3])
            {
                tmp_table[i][0] = tmp[0] + tmp[1];
                tmp_table[i][1] = tmp[2] + tmp[3];
                tmp_score += tmp[0] + tmp[1];
                tmp_score += tmp[2] + tmp[3];
                for(int j = 2; j<4; j++)
                    tmp_table[i][j] = -1;
            }
            else if(tmp[0] == tmp[1])
            {
                tmp_table[i][0] = tmp[0] + tmp[1];
                tmp_score += tmp[0] + tmp[1];
                tmp_table[i][1] = tmp[2];
                tmp_table[i][2] = tmp[3];
                tmp_table[i][3] = -1;
            }
            else if(tmp[1]==tmp[2])
            {
                tmp_table[i][0] = tmp[0];
                tmp_table[i][1] = tmp[1]+tmp[2];
                tmp_score += tmp[1]+tmp[2];
                tmp_table[i][2] = tmp[3];
                tmp_table[i][3] = -1;
            }
            else if(tmp[2] == tmp[3])
            {
                tmp_table[i][0] = tmp[0];
                tmp_table[i][1] = tmp[1];
                tmp_table[i][2] = tmp[2] + tmp[3];
                tmp_score += tmp[2] + tmp[3];
                tmp_table[i][3] = -1;
            }
        }
    }
    for(int i = 0; i<4; i++)
    {
        for(int j = 0; j<4; j++)
        {
            if(tmp_table[i][j] != table[i][j])
            {
                aval = 1;
                break;
            }
        }
    }
    if(aval == 1)
    {
        score += tmp_score;
        for(int i = 0; i<4; i++)
            for(int j = 0; j<4; j++)
                table[i][j] = tmp_table[i][j];
        return 1;
    }
    return 0;
}

int userInputD(int table[4][4]){
    int aval = 0;
    int tmp_table[4][4];
    int tmp_score = 0;
    for(int i = 0; i<4; i++)
        for(int j = 0; j<4; j++)
            tmp_table[i][j] = table[i][j];
    for(int i = 0; i < 4; i++)
    {
        int num = 0;
        int tmp[4];
        for(int j = 3; j>=0; j--)
        {
            if(tmp_table[i][j]!=-1)
            {
                tmp[num] = tmp_table[i][j];
                num++;
            }
        }
        if(num == 1)
        {
            tmp_table[i][3] = tmp[0];
            for(int j = 0; j<3; j++)
                tmp_table[i][j] = -1;
        }
        else if(num == 2)
        {
            if(tmp[0] == tmp[1])
            {
                tmp_table[i][3] = tmp[0]+tmp[1];
                tmp_score += tmp[0]+tmp[1];
                for(int j = 0; j<3; j++)
                    tmp_table[i][j] = -1;
            }
            else
            {
                tmp_table[i][3] = tmp[0];
                tmp_table[i][2] = tmp[1];
                for(int j = 0; j<2; j++)
                    tmp_table[i][j] = -1;
            }
        }
        else if(num == 3)
        {
            if(tmp[0] == tmp[1])
            {
                tmp_table[i][3] = tmp[0] + tmp[1];
                tmp_score += tmp[0] + tmp[1];
                tmp_table[i][2] = tmp[2];
                for(int j = 0; j<2; j++)
                    tmp_table[i][j] = -1;
            }
            else if(tmp[1] == tmp[2])
            {
                tmp_table[i][3] = tmp[0];
                tmp_table[i][2] = tmp[1] + tmp[2];
                tmp_score += tmp[1] + tmp[2];
                for(int j = 0; j<2; j++)
                    tmp_table[i][j] = -1;
            }
            else
            {
                tmp_table[i][3] = tmp[0];
                tmp_table[i][2] = tmp[1];
                tmp_table[i][1] = tmp[2];
                tmp_table[i][0] = -1;
            }
        }
        else if(num == 4)
        {
            if(tmp[0] == tmp[1] && tmp[2] == tmp[3])
            {
                tmp_table[i][3] = tmp[0] + tmp[1];
                tmp_table[i][2] = tmp[2] + tmp[3];
                tmp_score += tmp[0] + tmp[1];
                tmp_score += tmp[2] + tmp[3];
                for(int j = 0; j<2; j++)
                    tmp_table[i][j] = -1;
            }
            else if(tmp[0] == tmp[1])
            {
                tmp_table[i][3] = tmp[0] + tmp[1];
                tmp_score += tmp[0] + tmp[1];
                tmp_table[i][2] = tmp[2];
                tmp_table[i][1] = tmp[3];
                tmp_table[i][0] = -1;
            }
            else if(tmp[1]==tmp[2])
            {
                tmp_table[i][3] = tmp[0];
                tmp_table[i][2] = tmp[1]+tmp[2];
                tmp_score += tmp[1]+tmp[2];
                tmp_table[i][1] = tmp[3];
                tmp_table[i][0] = -1;
            }
            else if(tmp[2] == tmp[3])
            {
                tmp_table[i][3] = tmp[0];
                tmp_table[i][2] = tmp[1];
                tmp_table[i][1] = tmp[2] + tmp[3];
                tmp_score += tmp[2] + tmp[3];
                tmp_table[i][0] = -1;
            }
        }
    }
    for(int i = 0; i<4; i++)
    {
        for(int j = 0; j<4; j++)
        {
            if(tmp_table[i][j] != table[i][j])
            {
                aval = 1;
                break;
            }
        }
    }
    if(aval == 1)
    {
        score += tmp_score;
        for(int i = 0; i<4; i++)
            for(int j = 0; j<4; j++)
                table[i][j] = tmp_table[i][j];
        return 1;
    }
    return 0;
}

void userInput(int table[4][4]){
    int c;
    while(1)
    {
        printf("please enter [wsad]: ");
        c = getchar();
        getchar();
        printf("you entered: ");
        putchar(c);
        printf("\n");
        if((c == 'w' && userInputW(table)==1) || (c == 's' && userInputS(table)==1) || (c == 'a' && userInputA(table)==1) || (c == 'd' && userInputD(table)==1))
            break;
        printf("Wrong operation!");
    }
    
}

int main(int argc, const char * argv[]) {
    int table[4][4];
    for(int i = 0; i < 4; i++)
        for(int j = 0; j < 4; j++)
            table[i][j] = -1;

    int step = 0;
    printf("Press 's' to start 2048 game! ['q' to quit]: ");
    int ch;
    
    while(1)
    {
        ch = getchar();
        getchar();
        if(ch == 'q')
        {
            printf("Bye!\n");
            return 0;
        }
        else if(ch == 's')
        {
            while(1)
            {
                if(generateNum(table) == 0)
                    break;
                if(gameOver(table) == 1)
                    break;
                drawTable(score, step, table);
                userInput(table);
                step ++;
            }
            drawTable(score, step, table);
            printf("Game Over!\n");
            printf("Total Step: %d\n", step);
            printf("Total Score: %d\n", score);
        }
        else
        {
            printf("Press 's' to start 2048 game! ['q' to quit]");
        }
    }

    return 0;
}
