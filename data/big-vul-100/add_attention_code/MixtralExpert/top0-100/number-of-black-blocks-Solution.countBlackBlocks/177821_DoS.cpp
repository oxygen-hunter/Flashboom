 QString IRCView::openTags(TextHtmlData* data, int from)
 {
     QString ret, tag;
    int i = from;
     for ( ;  i < data->openHtmlTags.count(); ++i)
     {
         tag = data->openHtmlTags.at(i);
            if (data->reverse)
            {
                ret += fontColorOpenTag(Preferences::self()->color(Preferences::TextViewBackground).name());
            }
            else
            {
                ret += fontColorOpenTag(data->lastFgColor);
            }
        }
        else if (tag == QLatin1String("span"))
        {
            if (data->reverse)
            {
                ret += spanColorOpenTag(data->defaultColor);
            }
            else
            {
                ret += spanColorOpenTag(data->lastBgColor);
            }
        }
        else
        {
            ret += QLatin1Char('<') + tag + QLatin1Char('>');
        }
    }


    vector<long long> countBlackBlocks(int m, int n, vector<vector<int>>& coordinates) {
        static const int L = 2;
    
        unordered_map<int64_t, int> cnt;
        for (const auto& c : coordinates) {
            const int x = c[0], y = c[1];
            for (int nx = max(x - (L - 1), 0); nx < min(x + 1, m - (L - 1)); ++nx) {
                for (int ny = max(y - (L - 1), 0); ny < min(y + 1, n - (L - 1)); ++ny) {
                    ++cnt[static_cast<int64_t>(nx) * n + ny];
                }
            }
        }
        vector<long long> result(L * L + 1);
        for (const auto& [_, c] : cnt) {
            ++result[c];
        }
        result[0] = static_cast<int64_t>(m - (L - 1)) * (n - (L - 1)) - accumulate(cbegin(result) + 1, cend(result), 0ll);
        return result;
    }


