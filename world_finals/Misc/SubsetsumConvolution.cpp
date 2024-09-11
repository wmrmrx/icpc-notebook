//subset sum convolution fog[s] = sum t in s f(t)*g(s\t)
for(int mask = 0; mask < (1 << N); mask++) {
    fhat[__builtin_popcount(mask)][mask] = f[mask];
    ghat[__builtin_popcount(mask)][mask] = g[mask];
}
for(int i = 0; i < N; i++) {
    for(int j = 0; j < N; j++) {
        for(int mask = 0; mask < (1 << N); mask++) {
            if((mask & (1 << j)) != 0) {
                fhat[i][mask] += fhat[i][mask ^ (1 << j)];
                ghat[i][mask] += ghat[i][mask ^ (1 << j)];
            }
        }
    }
}
for(int mask = 0; mask < (1 << N); mask++) {
    for(int i = 0; i < N; i++) {
        for(int j = 0; j <= i; j++) {
            h[i][mask] += fhat[j][mask] * ghat[i - j][mask];
        } 
    }
}
for(int i = 0; i < N; i++) {
    for(int j = 0; j < N; j++) {
        for(int mask = 0; mask < (1 << N); mask++) {
            if((mask & (1 << j)) != 0) {
                h[i][mask] -= h[i][mask ^ (1 << j)];
            }
        }
    }
}
for(int mask = 0; mask < (1 << N); mask++)  
	fog[mask] = h[__builtin_popcount(mask)][mask];
