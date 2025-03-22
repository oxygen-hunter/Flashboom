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


        int minDistance(string word1, string word2) {
            const size_t m = word1.size();
            const size_t n = word2.size();

            if(m < n)
                return minDistance(word2, word1);

            vector<size_t> f(n + 1, 0);
            size_t upper_left;

            for(size_t i = 0; i < n + 1; ++i)
                f[i] = i;

            for(size_t i = 1; i < m + 1; ++i) {
                upper_left = f[0];
                f[0] = i;
                for(size_t j = 1; j < n + 1; ++j) {
                    size_t upper = f[j];
                    if(word1[i - 1] == word2[j - 1])
                        f[j] = upper_left;
                    else {
                        f[j] = 1 + min(upper_left, min(f[j - 1], f[j]));
                    }
                    upper_left = upper;
                }
            }

            return f[n];
        }


