    def benign___setitem__(self, key, value):
        self.dict[_hkey(key)] = [value if isinstance(value, unicode) else
                                 str(value)]