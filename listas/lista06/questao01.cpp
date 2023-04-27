#include <iostream>
using namespace std;

int number_cases(int *w, int m, int q, int l) {
    int ***dp = new int**[m];
    
    for (int i=0; i<=m; i++) {
        dp[i] = new int*[q];
        for (int j=0; j<=q; j++) {
            dp[i][j] = new int[l];
            for (int k=0; k<=l; k++) {
                dp[i][j][k] = 0;
            }
        }
    }

    
}

int main() {
    int k, l, m, q;
    cin >> k;

    for (int i=0; i < k; i++) {

        cin >> l;

        int *precos_v = new int[l];
        int *precos_w = new int[l];

        for (int j=0; j < l; j++) {

            int preco_j;
            cin >> preco_j;

            precos_v[j] = 1;
            precos_w[j] = preco_j;

        }

        cin >> m >> q;

        int retorno = number_cases(precos_w, m, q, l);

        cout << "caso " << i << ": " << retorno << endl;
    }

    return 0;
}