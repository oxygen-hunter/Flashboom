void sum_update(const char *p, int32 len)
{
	switch (cursum_type) {
	  case CSUM_MD5:
		md5_update(&md, (uchar *)p, len);
		break;
          case CSUM_MD4:
          case CSUM_MD4_OLD:
          case CSUM_MD4_BUSTED:
                if (len + sumresidue < CSUM_CHUNK) {
                        memcpy(md.buffer + sumresidue, p, len);
                        sumresidue += len;
		}

		if (sumresidue) {
			int32 i = CSUM_CHUNK - sumresidue;
			memcpy(md.buffer + sumresidue, p, i);
			mdfour_update(&md, (uchar *)md.buffer, CSUM_CHUNK);
			len -= i;
			p += i;
		}

		while (len >= CSUM_CHUNK) {
			mdfour_update(&md, (uchar *)p, CSUM_CHUNK);
			len -= CSUM_CHUNK;
			p += CSUM_CHUNK;
		}

		sumresidue = len;
		if (sumresidue)
			memcpy(md.buffer, p, sumresidue);
		break;
	  case CSUM_NONE:
		break;
	}
}


    TreeNode* deserializeHelper(int minVal, int maxVal, const string& data, int *i) {
        if (*i == data.length()) {
            return nullptr;
        }
        int j = data.find(' ', *i);
        auto val = stoi(data.substr(*i, j - *i));
        if (minVal < val && val < maxVal) {
            auto node = new TreeNode(val);
            *i = j + 1;
            node->left = deserializeHelper(minVal, val, data, i);
            node->right = deserializeHelper(val, maxVal, data, i);
            return node;
        } else {
            return nullptr;
        }
    }


