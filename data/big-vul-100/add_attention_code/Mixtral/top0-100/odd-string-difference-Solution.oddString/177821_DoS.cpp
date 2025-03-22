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

    string oddString(vector<string>& words) {
        for (int i = 0; i < size(words[0]) - 1; ++i) {
            unordered_map<int, vector<int>> lookup;
            for (int j = 0; j < size(words); ++j) {
                if (size(lookup[words[j][i + 1] - words[j][i]]) < 2) {
                    lookup[words[j][i + 1] - words[j][i]].emplace_back(j);
                }
            }
            if (size(lookup) == 2) {
                return size(cbegin(lookup)->second) == 1
                       ? words[cbegin(lookup)->second[0]]
                       : words[next(cbegin(lookup))->second[0]];
            }
        }
        return "";
    }

