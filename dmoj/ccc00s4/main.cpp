#include <iostream>
#define INF 9999999

int strokes[5281];
int clubs[32];

int dist, nClubs;

int main() {
    scanf("%d%d", &dist, &nClubs);
    for (int i = 0; i <= dist; i++)
        strokes[i] = INF;
        
    for (int i = 0; i < nClubs; i++)
        scanf("%d", &clubs[i]);
        
    strokes[0] = 0;
    for (int i = 1; i <= dist; i++) {
        for (int j = 0; j < nClubs; j++) {
            if (i - clubs[j] < 0)
                continue;
            else if (strokes[i-clubs[j]] + 1 < strokes[i]){
                strokes[i] = strokes[i-clubs[j]] + 1;
            }
        }
    }
    
    if (strokes[dist] == INF)
        printf("Roberta acknowledges defeat.");
    else
        printf("Roberta wins in %d strokes.", strokes[dist]);

    return 0;
}