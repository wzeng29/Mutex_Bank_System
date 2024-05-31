#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define maximumAcc 5
#define maximumClient 5

int accountBalances[maximumAcc] = {0};
pthread_mutex_t accountMutex[maximumAcc];

void deposit(int accountIndex, int amount) {
    pthread_mutex_lock(&accountMutex[accountIndex]);
    accountBalances[accountIndex] += amount;
    pthread_mutex_unlock(&accountMutex[accountIndex]);
}

void withdraw(int accountIndex, int amount) {
    pthread_mutex_lock(&accountMutex[accountIndex]);
    if (accountBalances[accountIndex] >= amount) {
        accountBalances[accountIndex] -= amount;
    }
    pthread_mutex_unlock(&accountMutex[accountIndex]);
}

void* processClient(void* arg) {
    int clientIndex = *((int*)arg);

    if (clientIndex == 0) {
        deposit(1, 1000);
    } 
    if (clientIndex == 1) {
        withdraw(0, 300);
        deposit(3, 200);
    } 
    if (clientIndex == 2) {
        deposit(2, 500);
        withdraw(3, 400);
        withdraw(0, 100);
    }
    if (clientIndex == 3) {
        withdraw(0, 40000);
        withdraw(1, 800);
    }
    if (clientIndex == 4) {
        withdraw(4, 5000);
    }

    return NULL;
}

int main() {
    for (int i = 0; i < maximumAcc; i++) {
        pthread_mutex_init(&accountMutex[i], NULL);
    }

    FILE* inputFile = fopen("assignment_5_input.txt", "r");
    for (int i = 0; i < maximumAcc; i++) {
        char accountName[3];
        int balance;
        fscanf(inputFile, "%2s balance %d", accountName, &balance);
        accountBalances[i] = balance;
    }
    pthread_t clientThreads[maximumClient];
    int clientIndices[maximumClient];
    for (int i = 0; i < maximumClient; i++) {
    clientIndices[i] = i;
    pthread_create(&clientThreads[i], NULL, processClient, &clientIndices[i]);
    pthread_join(clientThreads[i], NULL);
    }
    printf("No.of Accounts: %d\nNo.of Clients: %d\n", maximumAcc, maximumClient);
    for (int i = 0; i < maximumAcc; i++) {
        pthread_mutex_destroy(&accountMutex[i]);
        printf("A%d balance %d\n", i + 1, accountBalances[i]);
    }
    fclose(inputFile);
    return 0;
}
