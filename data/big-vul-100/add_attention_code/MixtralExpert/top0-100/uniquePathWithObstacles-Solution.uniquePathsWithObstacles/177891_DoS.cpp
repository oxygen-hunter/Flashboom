static RSA_PSS_PARAMS *rsa_pss_decode(const X509_ALGOR *alg,
                                      X509_ALGOR **pmaskHash)
{
    const unsigned char *p;
    int plen;
    RSA_PSS_PARAMS *pss;

    *pmaskHash = NULL;

    if (!alg->parameter || alg->parameter->type != V_ASN1_SEQUENCE)
        return NULL;
    p = alg->parameter->value.sequence->data;
    plen = alg->parameter->value.sequence->length;
    pss = d2i_RSA_PSS_PARAMS(NULL, &p, plen);

    if (!pss)
        return NULL;

     if (pss->maskGenAlgorithm) {
         ASN1_TYPE *param = pss->maskGenAlgorithm->parameter;
         if (OBJ_obj2nid(pss->maskGenAlgorithm->algorithm) == NID_mgf1
            && param->type == V_ASN1_SEQUENCE) {
             p = param->value.sequence->data;
             plen = param->value.sequence->length;
             *pmaskHash = d2i_X509_ALGOR(NULL, &p, plen);
        }
    }

    return pss;
}


        int uniquePathsWithObstacles(vector<vector<int> > &obstacleGrid) {
            const int m = obstacleGrid.size();
            const int n = obstacleGrid[0].size();
            vector<int> v(n, 0);

            v[0] = 1;
            for(int i = 0; i < m; ++i) {
                if(obstacleGrid[i][0] != 0)
                    v[0] = 0;
                for(int j = 1; j < n; ++j) {
                    if(obstacleGrid[i][j] == 0)
                        v[j] += v[j - 1];
                    else
                        v[j] = 0;
                }
            }

            return v[n - 1];
        }


