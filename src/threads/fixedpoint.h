#ifndef fp_h
#define fp_h

#define P 17
#define Q 14
#define F (1 << Q)

#define IntToFP(N) (N * F)
#define FPtoInt(X) (X / F)
#define FPtoIntRN(X) (X >= 0) ? ((X + F / 2) / F) : ((X - F / 2) / F)

#define addFPFP(X, Y) (X + Y)
#define subFPFP(X, Y) (X - Y)
#define addFPInt(X, N) (X + N * F)
#define subFPInt(X, N) (X - N * F)

#define mulFPFP(X, Y) ((int64_t) X) * Y / F
#define mulFPInt(X, N) (X * N)
#define divFPFP(X, Y) ((int64_t) X) * F / Y
#define divFPInt(X, N) (X / N)

#endif
