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

    vector<string> reorderLogFiles(vector<string>& logs) {
        auto pivot = stable_partition(logs.begin(), logs.end(),
                                      []( const auto& log ) {
                                          return isalpha(log.back());
                                      });
        sort(logs.begin(), pivot,
             [](const auto& a, const auto& b) {
                 int i = a.find_first_of(' '), j = b.find_first_of(' ');
                 return a.substr(i) != b.substr(j) ?
                            a.substr(i) < b.substr(j) :
                            a.substr(0, i) < b.substr(0, j);
             });
        return logs;
    }

