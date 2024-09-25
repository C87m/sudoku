#include <stdio.h>

/*構造体*/
typedef struct cell1
{
    int number;              /*数字*/
    struct cell1 *row[9];    /*行*/
    struct cell1 *column[9]; /*列*/
    struct cell1 *frame[9];  /*3*3の枠*/
    struct cell1 *next;      /*次の要素*/
} cell;

/*グローバル変数*/
cell list[81]; /*構造体の配列*/
int data[81] = {0, 0, 0, 0, 0, 0, 0, 0, 0,
                0, 0, 0, 0, 0, 0, 0, 0, 0,
                0, 0, 0, 0, 0, 0, 0, 0, 0,
                0, 0, 0, 5, 0, 0, 0, 0, 0,
                0, 0, 0, 0, 0, 0, 0, 0, 0,
                0, 0, 0, 0, 0, 1, 0, 0, 0,
                0, 0, 0, 0, 0, 0, 0, 0, 0,
                0, 0, 0, 0, 0, 0, 0, 0, 0,
                0, 0, 0, 0, 0, 0, 0, 0, 0}; /*問題*/

cell *setting()
{                   /*リスト作成*/
    cell *t = list; /*listを書き換える*/
    int x, y;
    for (y = 0; y < 9; y++)
    {
        for (x = 0; x < 9; x++)
        {
            t->number = data[x + 9 * y]; /*dataの値を代入*/

            int i, j;
            for (i = 0; i < 9; i++)
            {
                t->row[i] = &(list[i + 9 * y]);    /*行*/
                t->column[i] = &(list[x + 9 * i]); /*列*/
            }

            for (i = 0; i < 3; i++)
            {
                for (j = 0; j < 3; j++)
                {
                    t->frame[i + 3 * j] = &(list[(x / 3 * 3 + i) + 9 * (y / 3 * 3 + j)]); /*枠*/
                }
            }

            t++;
        }
    }
    t->next = NULL;

    cell *p = NULL;
    cell *q = NULL;
    for (int i = 80; i >= 0; i--) /*連結*/
    {
        p = list + i;
        p->next = q;
        q = p;
    }
    return p;
}

void printcell() /*行列の出力*/
{
    int x, y;
    for (y = 0; y < 9; y++)
    {
        for (x = 0; x < 9; x++)
        {
            printf("%2d ", list[x + 9 * y].number);
        }
        printf("\n");
    }
}

int checknum(cell *t) /*数字の位置がおかしくないかを判別*/
{
    int count = 0;
    for (int i = 0; i < 9; i++)
    {
        if (t->number == t->row[i]->number)
        {
            count++; /*行内に同じ数字があったらカウント+1*/
        }
        if (t->number == t->column[i]->number)
        {
            count++; /*列内に同じ数字があったらカウント+1*/
        }
        if (t->number == t->frame[i]->number)
        {
            count++; /*枠内に同じ数字があったらカウント+1*/
        }
    }
    return count; /*正常なら3が返す もし数字が被っていたら4~6を返す*/
}

int checkmul(cell *t) /*対角積の判別*/
{
    if (t == &(list[9])) /*虱潰し 合っていたら0間違っていたら1*/
    {
        if (list[1].number * list[9].number == 14)
        {
            return 0;
        }
        return 1;
    }
    else if (t == &(list[11]))
    {
        if (list[3].number * list[11].number == 4)
        {
            return 0;
        }
        return 1;
    }
    else if (t == &(list[15]))
    {
        if (list[5].number * list[15].number == 6)
        {
            return 0;
        }
        return 1;
    }
    else if (t == &(list[17]))
    {
        if (list[7].number * list[17].number == 18)
        {
            return 0;
        }
        return 1;
    }
    else if (t == &(list[27]))
    {
        if (list[19].number * list[27].number == 24)
        {
            return 0;
        }
        return 1;
    }
    else if (t == &(list[29]))
    {
        if (list[21].number * list[29].number == 4)
        {
            return 0;
        }
        return 1;
    }
    else if (t == &(list[33]))
    {
        if (list[23].number * list[33].number == 16)
        {
            return 0;
        }
        return 1;
    }
    else if (t == &(list[35]))
    {
        if (list[25].number * list[35].number == 24)
        {
            return 0;
        }
        return 1;
    }
    else if (t == &(list[55]))
    {
        if (list[45].number * list[55].number == 16)
        {
            return 0;
        }
        return 1;
    }
    else if (t == &(list[57]))
    {
        if (list[47].number * list[57].number == 36)
        {
            return 0;
        }
        return 1;
    }
    else if (t == &(list[59]))
    {
        if (list[51].number * list[59].number == 18)
        {
            return 0;
        }
        return 1;
    }
    else if (t == &(list[61]))
    {
        if (list[53].number * list[61].number == 24)
        {
            return 0;
        }
        return 1;
    }
    else if (t == &(list[73]))
    {
        if (list[63].number * list[73].number == 24)
        {
            return 0;
        }
        return 1;
    }
    else if (t == &(list[75]))
    {
        if (list[65].number * list[75].number == 8)
        {
            return 0;
        }
        return 1;
    }
    else if (t == &(list[77]))
    {
        if (list[69].number * list[77].number == 12)
        {
            return 0;
        }
        return 1;
    }
    else if (t == &(list[79]))
    {
        if (list[71].number * list[79].number == 28)
        {
            return 0;
        }
        return 1;
    }
    return 0; /*対角積と無関係なら0*/
}

int sudoku(cell *t) /*数字を入れる 再帰*/
{
    if (t == NULL) /*終端の場合0 = 終わり*/
    {
        return 0;
    }
    else if (t->number != 0) /*最初から数字が入っている = 固定の数字*/
    {
        if (sudoku(t->next) == 0) /*対角積と次の数字のチェック*/
        {
            return 0; /*問題なければ0*/
        }
    }
    else /*空欄*/
    {
        while (t->number < 9)
        {
            t->number++; /*1~9を順に入れる*/
            if (checkmul(t) == 0 && checknum(t) == 3 && sudoku(t->next) == 0)
            {             /*対角積と数字の重複及び次の数字のチェック*/
                return 0; /*問題なければ0*/
            }
        }
        t->number = 0; /*9まで入れ終わってどの数字も当てはまらなければ一旦リセット→1つ前の数字を+1*/
    }

    return 1;
}

/*メイン関数*/
int main(void)
{
    cell *target = setting();

    printf("Problem\n");
    printcell(); /*問題を表示*/

    if (sudoku(target) == 0) /*解けた*/
    {
        printf("\nResult\n");
        printcell(); /*結果の表示*/
    }
    else /*解けない*/
    {
        printf("\nNo answer\n");
    }

    return 0;
}