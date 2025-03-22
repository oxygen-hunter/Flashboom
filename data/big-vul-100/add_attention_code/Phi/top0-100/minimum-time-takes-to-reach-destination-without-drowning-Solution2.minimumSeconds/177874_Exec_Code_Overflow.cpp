void aes_crypt_ecb( aes_context *ctx,
                    int mode,
                    const unsigned char input[16],
                    unsigned char output[16] )
{
    int i;
    unsigned long *RK, X0, X1, X2, X3, Y0, Y1, Y2, Y3;

#if defined(XYSSL_PADLOCK_C) && defined(XYSSL_HAVE_X86)
    if( padlock_supports( PADLOCK_ACE ) )
    {
        if( padlock_xcryptecb( ctx, mode, input, output ) == 0 )
            return;
     }
 #endif
 
     RK = ctx->rk;
 
     GET_ULONG_LE( X0, input,  0 ); X0 ^= *RK++;

    if( mode == AES_DECRYPT )
    {
        for( i = (ctx->nr >> 1) - 1; i > 0; i-- )
        {
            AES_RROUND( Y0, Y1, Y2, Y3, X0, X1, X2, X3 );
            AES_RROUND( X0, X1, X2, X3, Y0, Y1, Y2, Y3 );
        }

        AES_RROUND( Y0, Y1, Y2, Y3, X0, X1, X2, X3 );

        X0 = *RK++ ^ ( RSb[ ( Y0       ) & 0xFF ]       ) ^
                     ( RSb[ ( Y3 >>  8 ) & 0xFF ] <<  8 ) ^
                     ( RSb[ ( Y2 >> 16 ) & 0xFF ] << 16 ) ^
                     ( ((unsigned int)RSb[ ( Y1 >> 24 ) & 0xFF ]) << 24 );

        X1 = *RK++ ^ ( RSb[ ( Y1       ) & 0xFF ]       ) ^
                     ( RSb[ ( Y0 >>  8 ) & 0xFF ] <<  8 ) ^
                     ( RSb[ ( Y3 >> 16 ) & 0xFF ] << 16 ) ^
                     ( ((unsigned int)RSb[ ( Y2 >> 24 ) & 0xFF ]) << 24 );

        X2 = *RK++ ^ ( RSb[ ( Y2       ) & 0xFF ]       ) ^
                     ( RSb[ ( Y1 >>  8 ) & 0xFF ] <<  8 ) ^
                     ( RSb[ ( Y0 >> 16 ) & 0xFF ] << 16 ) ^
                     ( ((unsigned int)RSb[ ( Y3 >> 24 ) & 0xFF ]) << 24 );

        X3 = *RK++ ^ ( RSb[ ( Y3       ) & 0xFF ]       ) ^
                     ( RSb[ ( Y2 >>  8 ) & 0xFF ] <<  8 ) ^
                     ( RSb[ ( Y1 >> 16 ) & 0xFF ] << 16 ) ^
                     ( ((unsigned int)RSb[ ( Y0 >> 24 ) & 0xFF ]) << 24 );
    }
    else /* AES_ENCRYPT */
    {
        for( i = (ctx->nr >> 1) - 1; i > 0; i-- )
        {
            AES_FROUND( Y0, Y1, Y2, Y3, X0, X1, X2, X3 );
            AES_FROUND( X0, X1, X2, X3, Y0, Y1, Y2, Y3 );
        }

        AES_FROUND( Y0, Y1, Y2, Y3, X0, X1, X2, X3 );

        X0 = *RK++ ^ ( FSb[ ( Y0       ) & 0xFF ]       ) ^
                     ( FSb[ ( Y1 >>  8 ) & 0xFF ] <<  8 ) ^
                     ( FSb[ ( Y2 >> 16 ) & 0xFF ] << 16 ) ^
                     ( ((unsigned int)FSb[ ( Y3 >> 24 ) & 0xFF ]) << 24 );

        X1 = *RK++ ^ ( FSb[ ( Y1       ) & 0xFF ]       ) ^
                     ( FSb[ ( Y2 >>  8 ) & 0xFF ] <<  8 ) ^
                     ( FSb[ ( Y3 >> 16 ) & 0xFF ] << 16 ) ^
                     ( ((unsigned int)FSb[ ( Y0 >> 24 ) & 0xFF ]) << 24 );

        X2 = *RK++ ^ ( FSb[ ( Y2       ) & 0xFF ]       ) ^
                     ( FSb[ ( Y3 >>  8 ) & 0xFF ] <<  8 ) ^
                     ( FSb[ ( Y0 >> 16 ) & 0xFF ] << 16 ) ^
                     ( ((unsigned int)FSb[ ( Y1 >> 24 ) & 0xFF ]) << 24 );

        X3 = *RK++ ^ ( FSb[ ( Y3       ) & 0xFF ]       ) ^
                     ( FSb[ ( Y0 >>  8 ) & 0xFF ] <<  8 ) ^
                     ( FSb[ ( Y1 >> 16 ) & 0xFF ] << 16 ) ^
                     ( ((unsigned int)FSb[ ( Y2 >> 24 ) & 0xFF ]) << 24 );
    }

    PUT_ULONG_LE( X0, output,  0 );
    PUT_ULONG_LE( X1, output,  4 );
    PUT_ULONG_LE( X2, output,  8 );
    PUT_ULONG_LE( X3, output, 12 );
}

    int minimumSeconds(vector<vector<string>>& land) {
        static const vector<pair<int, int>> DIRECTIONS {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};
        vector<vector<int>> lookup1(size(land), vector<int>(size(land[0]), -1));
        vector<vector<int>> lookup2(size(land), vector<int>(size(land[0]), -1));
        vector<pair<int, int>> q1;
        vector<pair<int, int>> q2;
        for (int i = 0; i < size(land); ++i) {
            for (int j = 0; j < size(land[0]); ++j) {
                if (land[i][j] == "*") {
                    q1.emplace_back(i, j);
                    lookup2[i][j] = 0;
                } else if (land[i][j] == "S") {
                    q2.emplace_back(i, j);
                    lookup2[i][j] = 0;
                }
            }
        }
        while (!empty(q1) || !empty(q2)) {
            vector<pair<int, int>> new_q1;
            vector<pair<int, int>> new_q2;
            for (const auto& [i, j] : q1) {
                for (const auto& [di, dj] : DIRECTIONS) {
                    const int ni = i + di, nj = j + dj;
                    if (!(0 <= ni && ni < size(land) && 0 <= nj && nj < size(land[0]) && land[ni][nj] != "X" && land[ni][nj] != "D" && lookup1[ni][nj] == -1)) {
                        continue;
                    }
                    lookup1[ni][nj] = 0;
                    new_q1.emplace_back(ni, nj);
                }
            }
            for (const auto& [i, j] : q2) {
                if (land[i][j] == "D") {
                    return lookup2[i][j];
                }
                for (const auto& [di, dj] : DIRECTIONS) {
                    const int ni = i + di, nj = j + dj;
                    if (!(0 <= ni && ni < size(land) && 0 <= nj && nj < size(land[0]) && land[ni][nj] != "X" && lookup2[ni][nj] == -1 && lookup1[ni][nj] == -1)) {
                        continue;
                    }
                    lookup2[ni][nj] = lookup2[i][j] + 1;
                    new_q2.emplace_back(ni, nj);
                }
            }
            q1 = move(new_q1);
            q2 = move(new_q2);
        }
        return -1;
    }

