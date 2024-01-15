
#include <iostream>
#include <chrono>

#define MaxSeconds 60 * 10
int BenchCounter = 1;

int WorldRenderBenchScores[MaxSeconds];
int AverageWorldRender = 0;

void BenchFunction( void (*MyFunction)() ){
    if (BenchCounter != (MaxSeconds) - 1){
        auto start = std::chrono::high_resolution_clock::now();
        MyFunction();
        auto end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        std::cout << "Bench No. " << BenchCounter << "\n";
        std::cout << "Function execution time: " << duration.count() << " microseconds" << std::endl;
        WorldRenderBenchScores[BenchCounter] = duration.count();

        BenchCounter ++;
    }
    else {
        if (AverageWorldRender == 0){

            int Total = 0;

            for (int i = 0 ; i <= BenchCounter; i ++){
                Total += WorldRenderBenchScores[i];
            }

            AverageWorldRender = (Total / MaxSeconds - 1) / 1000;

        }
    }
}