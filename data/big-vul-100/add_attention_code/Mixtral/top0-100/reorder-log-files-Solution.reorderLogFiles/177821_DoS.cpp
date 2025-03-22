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

