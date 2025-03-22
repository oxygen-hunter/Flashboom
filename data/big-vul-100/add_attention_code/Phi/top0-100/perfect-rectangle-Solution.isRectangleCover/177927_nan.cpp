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

    bool isRectangleCover(vector<vector<int>>& rectangles) {
        enum Location {L = 0, B = 1, R = 2, T = 3};
        int left = numeric_limits<int>::max(), bottom = numeric_limits<int>::max(),
            right = numeric_limits<int>::min(), top = numeric_limits<int>::min();
        for (const auto& rect : rectangles) {
            left = min(left, rect[L]);
            bottom = min(bottom, rect[B]);
            right = max(right, rect[R]);
            top = max(top, rect[T]);
        }

        using P = pair<pair<int, int>, int>;
        enum Corner {LB = 1, RB = 2, LT = 4, RT = 8};
        unordered_map<int, unordered_map<int, int>> corner_count;
        vector<P> corners{{{L, B}, LB}, {{R, B}, RB}, {{L, T}, LT}, {{R, T}, RT}};
        for (const auto& rect : rectangles) {
            for (const auto& corner : corners) {
                const auto x = rect[corner.first.first];
                const auto y = rect[corner.first.second];
                if (corner_count[x][y] & corner.second) {
                    return false;
                }
                corner_count[x][y] |= corner.second;
            }
        }

        bitset<16> is_valid;
        is_valid[LB | RB] = is_valid[LB | LT] = is_valid[RB | RT] = is_valid[LT | RT] = is_valid[LB | RB | LT | RT] = true;
        for (auto itx = corner_count.cbegin(); itx != corner_count.cend(); ++itx) {
            const auto x = itx->first;
            for (auto ity = itx->second.cbegin(); ity != itx->second.cend(); ++ity) {
                const auto y = ity->first;
                const auto mask = ity->second;
                if ((left < x && x < right) || (bottom < y && y < top)) {
                    if (!is_valid[mask]) {
                        return false;
                    }
                }
            }
        }

        return true;
    }

