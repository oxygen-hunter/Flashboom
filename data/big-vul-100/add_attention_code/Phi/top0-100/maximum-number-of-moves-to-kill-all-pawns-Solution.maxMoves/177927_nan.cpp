PHP_FUNCTION(openssl_seal)
{
	zval *pubkeys, *pubkey, *sealdata, *ekeys, *iv = NULL;
	HashTable *pubkeysht;
	EVP_PKEY **pkeys;
	zend_resource ** key_resources;	/* so we know what to cleanup */
	int i, len1, len2, *eksl, nkeys, iv_len;
	unsigned char iv_buf[EVP_MAX_IV_LENGTH + 1], *buf = NULL, **eks;
	char * data;
	size_t data_len;
	char *method =NULL;
	size_t method_len = 0;
	const EVP_CIPHER *cipher;
	EVP_CIPHER_CTX *ctx;

	if (zend_parse_parameters(ZEND_NUM_ARGS(), "sz/z/a/|sz/", &data, &data_len,
				&sealdata, &ekeys, &pubkeys, &method, &method_len, &iv) == FAILURE) {
		return;
	}
	pubkeysht = Z_ARRVAL_P(pubkeys);
	nkeys = pubkeysht ? zend_hash_num_elements(pubkeysht) : 0;
	if (!nkeys) {
		php_error_docref(NULL, E_WARNING, "Fourth argument to openssl_seal() must be a non-empty array");
		RETURN_FALSE;
	}

	PHP_OPENSSL_CHECK_SIZE_T_TO_INT(data_len, data);

	if (method) {
		cipher = EVP_get_cipherbyname(method);
		if (!cipher) {
			php_error_docref(NULL, E_WARNING, "Unknown signature algorithm.");
			RETURN_FALSE;
		}
	} else {
		cipher = EVP_rc4();
	}

	iv_len = EVP_CIPHER_iv_length(cipher);
	if (!iv && iv_len > 0) {
		php_error_docref(NULL, E_WARNING,
				"Cipher algorithm requires an IV to be supplied as a sixth parameter");
		RETURN_FALSE;
	}

	pkeys = safe_emalloc(nkeys, sizeof(*pkeys), 0);
	eksl = safe_emalloc(nkeys, sizeof(*eksl), 0);
	eks = safe_emalloc(nkeys, sizeof(*eks), 0);
	memset(eks, 0, sizeof(*eks) * nkeys);
	key_resources = safe_emalloc(nkeys, sizeof(zend_resource*), 0);
	memset(key_resources, 0, sizeof(zend_resource*) * nkeys);
	memset(pkeys, 0, sizeof(*pkeys) * nkeys);

	/* get the public keys we are using to seal this data */
	i = 0;
	ZEND_HASH_FOREACH_VAL(pubkeysht, pubkey) {
		pkeys[i] = php_openssl_evp_from_zval(pubkey, 1, NULL, 0, 0, &key_resources[i]);
		if (pkeys[i] == NULL) {
			php_error_docref(NULL, E_WARNING, "not a public key (%dth member of pubkeys)", i+1);
			RETVAL_FALSE;
			goto clean_exit;
		}
		eks[i] = emalloc(EVP_PKEY_size(pkeys[i]) + 1);
		i++;
	} ZEND_HASH_FOREACH_END();

	ctx = EVP_CIPHER_CTX_new();
	if (ctx == NULL || !EVP_EncryptInit(ctx,cipher,NULL,NULL)) {
		EVP_CIPHER_CTX_free(ctx);
		RETVAL_FALSE;
		goto clean_exit;
	}

	/* allocate one byte extra to make room for \0 */
        buf = emalloc(data_len + EVP_CIPHER_CTX_block_size(ctx));
        EVP_CIPHER_CTX_cleanup(ctx);
 
       if (!EVP_SealInit(ctx, cipher, eks, eksl, &iv_buf[0], pkeys, nkeys) ||
                        !EVP_SealUpdate(ctx, buf, &len1, (unsigned char *)data, (int)data_len) ||
                        !EVP_SealFinal(ctx, buf + len1, &len2)) {
                RETVAL_FALSE;
		efree(buf);
		EVP_CIPHER_CTX_free(ctx);
		goto clean_exit;
	}

	if (len1 + len2 > 0) {
		zval_dtor(sealdata);
		ZVAL_NEW_STR(sealdata, zend_string_init((char*)buf, len1 + len2, 0));
		efree(buf);

		zval_dtor(ekeys);
		array_init(ekeys);
		for (i=0; i<nkeys; i++) {
			eks[i][eksl[i]] = '\0';
			add_next_index_stringl(ekeys, (const char*)eks[i], eksl[i]);
			efree(eks[i]);
			eks[i] = NULL;
		}

		if (iv) {
			zval_dtor(iv);
			iv_buf[iv_len] = '\0';
			ZVAL_NEW_STR(iv, zend_string_init((char*)iv_buf, iv_len, 0));
		}
	} else {
		efree(buf);
	}
	RETVAL_LONG(len1 + len2);
	EVP_CIPHER_CTX_free(ctx);

clean_exit:
	for (i=0; i<nkeys; i++) {
		if (key_resources[i] == NULL && pkeys[i] != NULL) {
			EVP_PKEY_free(pkeys[i]);
		}
		if (eks[i]) {
			efree(eks[i]);
		}
	}
	efree(eks);
	efree(eksl);
	efree(pkeys);
	efree(key_resources);
}

    int maxMoves(int kx, int ky, vector<vector<int>>& positions) {
        static const int N = 50;
        static const vector<pair<int, int>> DIRECTIONS = {{1, 2}, {-1, 2}, {1, -2}, {-1, -2}, {2, 1}, {-2, 1}, {2, -1}, {-2, -1}};
        static const int POS_INF = numeric_limits<int>::max();
        static const int NEG_INF = numeric_limits<int>::min();

        const auto& bfs = [](int r, int c) {
            vector<vector<int>> dist(N, vector<int>(N, POS_INF));
            dist[r][c] = 0;
            vector<pair<int, int>> q = {{r, c}};
            while (!empty(q)) {
                vector<pair<int, int>> new_q;
                for (const auto& [r, c] : q) {
                    for (const auto& [dr, dc] : DIRECTIONS) {
                        const int nr = r + dr, nc = c + dc;
                        if (!(0 <= nr && nr < N && 0 <= nc && nc < N && dist[nr][nc] == POS_INF)) {
                            continue;
                        }
                        dist[nr][nc] = dist[r][c] + 1;
                        new_q.emplace_back(nr, nc);
                    }
                }
                q = move(new_q);
            }
            return dist;
        };

        const int p = size(positions);
        positions.emplace_back(vector<int>{kx, ky});
        vector<vector<int>> dist(p + 1, vector<int>(p + 1));
        for (int i = 0; i <= p; ++i) {
            const auto& d = bfs(positions[i][0], positions[i][1]);
            for (int j = i + 1; j <= p; ++j) {
                dist[j][i] = dist[i][j] = d[positions[j][0]][positions[j][1]];
            }
        }
        vector<vector<int>> dp(1 << p);
        for (int mask = 1; mask < 1 << p; ++mask) {
            dp[mask].assign(p, __builtin_popcount(mask) & 1 ? POS_INF : NEG_INF);
        }
        dp.back().assign(p, 0);
        for (int mask = (1 << p) - 1; mask >= 1; --mask) {
            const auto& turn = (__builtin_popcount(mask) & 1) ^ 1;
            for (int i = 0; i < p; ++i) {
                if ((mask & (1 << i)) == 0) {
                    continue;
                }
                for (int j = 0; j < p; ++j) {
                    if (j == i || (mask & (1 << j)) == 0) {
                        continue;
                    }
                    dp[mask ^ (1 << i)][j] = turn ? min(dp[mask ^ (1 << i)][j], dp[mask][i] + dist[i][j])
                                                  : max(dp[mask ^ (1 << i)][j], dp[mask][i] + dist[i][j]);
                }
            }
        }
        int result = 0;
        for (int i = 0; i < p; ++i) {
            result = max(result, dp[1 << i][i] + dist[i][p]);
        }
        return result;
    }

