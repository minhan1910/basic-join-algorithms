#include <stdio.h>
#include <stdlib.h>

#define TABLE_SIZE 5

typedef struct record
{
    int key,
        value;
} Record;

Record table1[TABLE_SIZE] = {{1, 10}, {2, 20}, {3, 30}, {4, 40}, {5, 50}};
Record table2[TABLE_SIZE] = {{1, 100}, {3, 300}, {5, 500}, {7, 700}, {9, 900}};

// Nested Loop Joins
void nested_loop_join()
{
    printf("Nested Loop Join:\n");
    for (int i = 0; i < TABLE_SIZE; ++i)
    {
        for (int j = 0; j < TABLE_SIZE; ++j)
        {
            if (table1[i].key == table2[j].key)
            {
                printf("(%d, %d) -> (%d, %d)\n", table1[i].key,
                       table1[i].value,
                       table2[j].key,
                       table2[j].value);
            }
        }
    }
}

// Hash Join
#define HASH_SIZE 10
Record *hash_table[HASH_SIZE] = {NULL};

void build_hash_table()
{
    for (int i = 0; i < TABLE_SIZE; ++i)
    {
        int hash_key = table1[i].key % HASH_SIZE;
        hash_table[hash_key] = &table1[i];
    }
}

void hash_join()
{
    printf("Hash Join:\n");
    build_hash_table();
    for (int i = 0; i < TABLE_SIZE; ++i)
    {
        int hash_key = table2[i].key % HASH_SIZE;
        if (hash_table[hash_key] && hash_table[hash_key]->key == table2[i].key)
        {
            Record *recordInTable1 = hash_table[hash_key];
            printf("(%d, %d) -> (%d, %d)\n", hash_table[hash_key]->key,
                   hash_table[hash_key]->value,
                   table2[i].key,
                   table2[i].value);
        }
    }
}

// Sort-merge join
int comp_record(const void *a, const void *b)
{
    Record *ar = (Record *)a;
    Record *br = (Record *)b;
    return ar->key - br->key;
}

void sort_merge_join()
{
    printf("Sort Merge Join:\n");
    qsort(table1, TABLE_SIZE, sizeof(Record), comp_record);
    qsort(table2, TABLE_SIZE, sizeof(Record), comp_record);
    int i = 0,
        j = 0;
    while (i < TABLE_SIZE && j < TABLE_SIZE)
    {
        if (table1[i].key == table2[j].key)
        {
            printf("(%d, %d) -> (%d, %d)\n", table1[i].key,
                   table1[i].value,
                   table2[j].key,
                   table2[j].value);
            ++i;
            ++j;
        }
        else if (table1[i].key > table2[j].key)
        {
            ++j;
        }
        else
        {
            ++i;
        }
    }
}

void print_table(const Record *table, const int n)
{
    printf("Key\t\t\tValue\n");
    for (int i = 0; i < n; ++i)
    {
        printf("%d\t\t\t%d\n", table[i].key, table[i].value);
    }
}

void print_line()
{
    for (int i = 0; i < 30; ++i)
        printf("-");
    printf("\n");
}

int comp(const void *a, const void *b)
{
    int vA = *(int *)a;
    int vB = *(int *)b;
    return vA - vB;
}

int main()
{
    printf("Table 1: \n");
    print_table(table1, TABLE_SIZE);
    print_line();

    printf("Table 2: \n");
    print_table(table2, TABLE_SIZE);
    print_line();

    nested_loop_join();
    print_line();

    hash_join();
    print_line();

    sort_merge_join();
    print_line();

    return 0;
}