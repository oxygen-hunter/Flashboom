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


    string bestHand(vector<int>& ranks, vector<char>& suits) {
        static const vector<string> LOOKUP = {"", "High Card", "Pair", "Three of a Kind", "Three of a Kind", "Three of a Kind"};
        if (all_of(cbegin(suits), cend(suits), [&](const auto& x) { return x == suits[0]; })) {
            return "Flush";
        }
        vector<int> cnt(13);
        for (const auto& x : ranks) {
            ++cnt[x - 1];
        }
        return LOOKUP[*max_element(cbegin(cnt), cend(cnt))];
    }


