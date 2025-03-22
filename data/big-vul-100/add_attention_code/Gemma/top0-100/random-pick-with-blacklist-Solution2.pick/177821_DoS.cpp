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


    int pick() {
        int index = rand() % n_;
        int left = 0, right = blacklist_.size() - 1;
        while (left <= right) {
            auto mid = left + (right - left) / 2;
            if (index + mid < blacklist_[mid]) {
                right = mid - 1;
            } else {
                left = mid + 1;
            }
        }
        return index + left;
    }


