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

    int maxTrailingZeros(vector<vector<int>>& grid) {
        const auto& factor = [](int x) {
            static const array<int, 2> primes = {2, 5};
            array<int, 2> cnt = {0, 0};
            for (int i = 0; i < size(primes); ++i) {
                while (x && x % primes[i] == 0) {
                    x /= primes[i];
                    ++cnt[i];
                }
            }
            return cnt;
        };
        const auto& add = [](const auto& a, const auto& b) {
            return array<int, 2>{a[0] + b[0], a[1] + b[1]};
        };
        const auto& sub = [](const auto& a, const auto& b) {
            return array<int, 2>{a[0] - b[0], a[1] - b[1]};
        };
        const auto& count = [](const auto& a) {
            return min(a[0], a[1]);
        };

        vector<vector<array<int, 2>>> left(size(grid), vector<array<int, 2>>(size(grid[0])));
        for (int i = 0; i < size(grid); ++i) {
            left[i][0] = factor(grid[i][0]);
            for (int j = 1; j < size(grid[0]); ++j) {
                left[i][j] = add(left[i][j - 1], factor(grid[i][j]));
            }
        }
        int result = 0;
        for (int j = 0; j < size(grid[0]); ++j) {
            array<int, 2> total = {0, 0};
            for (int i = 0; i < size(grid); ++i) {
                total = add(total, factor(grid[i][j]));
            }
            array<int, 2> up = {0, 0};
            for (int i = 0; i < size(grid); ++i) {
                const auto& right = j ? sub(left[i].back(), left[i][j - 1]) : left[i].back();
                result = max({result, count(add(left[i][j], up)), count(add(right, up))});
                up = add(up, factor(grid[i][j]));
                const auto& down = sub(total, up);
                result = max({result, count(add(left[i][j], down)), count(add(right, down))});
            }
        }
        return result;
    }

