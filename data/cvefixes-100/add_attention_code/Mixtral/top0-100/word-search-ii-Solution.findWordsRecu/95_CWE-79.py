def test_custom_field_table_render(self):
    queryset = Location.objects.filter(name=self.location.name)
    location_table = LocationTable(queryset)

    custom_column_expected = {
        "text_field": "bar",
        "number_field": "456",
        "boolean_field": '<span class="text-success"><i class="mdi mdi-check-bold" title="Yes"></i></span>',
        "date_field": "2020-01-02",
        "url_field": '<a href="http://example.com/2">http://example.com/2</a>',
        "choice_field": '<span class="label label-default">Bar</span>',
        "multi_choice_field": (
            '<span class="label label-default">Bar</span> <span class="label label-default">Baz</span> '
        ),
    }

    bound_row = location_table.rows[0]

    for col_name, col_expected_value in custom_column_expected.items():
        internal_col_name = "cf_" + col_name
        custom_column = location_table.base_columns.get(internal_col_name)
        self.assertIsNotNone(custom_column)
        self.assertIsInstance(custom_column, CustomFieldColumn)

        rendered_value = bound_row.get_cell(internal_col_name)
        self.assertEqual(rendered_value, col_expected_value)

def findWordsRecu(self, board, trie, cur, i, j, visited, cur_word, result):
    if not trie or i < 0 or i >= len(board) or j < 0 or j >= len(board[0]) or visited[i][j]:
        return

    if board[i][j] not in trie.leaves:
        return

    cur_word.append(board[i][j])
    next_node = trie.leaves[board[i][j]]
    if next_node.is_string:
        result["".join(cur_word)] = True

    visited[i][j] = True
    self.findWordsRecu(board, next_node, cur + 1, i + 1, j, visited, cur_word, result)
    self.findWordsRecu(board, next_node, cur + 1, i - 1, j, visited, cur_word, result)
    self.findWordsRecu(board, next_node, cur + 1, i, j + 1, visited, cur_word, result)
    self.findWordsRecu(board, next_node, cur + 1, i, j - 1, visited, cur_word, result)
    visited[i][j] = False
    cur_word.pop()


