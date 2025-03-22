def swaggerui_static(filename):
    return send_file(os.path.join(os.path.dirname(os.path.dirname(os.path.dirname(__file__))), 'libs', 'flask_restx',
                     'static', filename))

def setZeroes(self, matrix):
    first_col = reduce(lambda acc, i: acc or matrix[i][0] == 0, xrange(len(matrix)), False)
    first_row = reduce(lambda acc, j: acc or matrix[0][j] == 0, xrange(len(matrix[0])), False)

    for i in xrange(1, len(matrix)):
        for j in xrange(1, len(matrix[0])):
            if matrix[i][j] == 0:
                matrix[i][0], matrix[0][j] = 0, 0

    for i in xrange(1, len(matrix)):
        for j in xrange(1, len(matrix[0])):
            if matrix[i][0] == 0 or matrix[0][j] == 0:
                matrix[i][j] = 0

    if first_col:
        for i in xrange(len(matrix)):
            matrix[i][0] = 0

    if first_row:
        for j in xrange(len(matrix[0])):
            matrix[0][j] = 0



