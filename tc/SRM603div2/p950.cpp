    int n = graph.size();
    for (int i = 0; i < n; i++) {
        // 0.0 probability to win in at most zero turns:
        prob[i][0] = 0.0;
    }
    for (int k = 1; k <= MAX_TURNS; k++) {
        for (int i = 0; i < n; i++) {
            prob[i][k] = 0.0;
            for (int j = 0; j < n; j++) {
                if ( graph[i][j] == '1' ) {
                    // can move from i to j.
                    double q = winprob[j] / 100.0 + prob[j][k-1] * (100 - winprob[j] - loseprob[j]) / 100;
                    prob[i][k] = std::max(prob[i][k], q);
                }
            }
        }
    }
     
    return prob[Start][MAX_TURNS];
