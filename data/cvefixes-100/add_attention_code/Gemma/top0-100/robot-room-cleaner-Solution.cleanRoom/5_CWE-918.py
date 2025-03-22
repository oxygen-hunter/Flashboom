def add_security_headers(resp):
    resp.headers['Content-Security-Policy'] = "default-src 'self'" + ''.join([' '+host for host in config.config_trustedhosts.strip().split(',')]) + " 'unsafe-inline' 'unsafe-eval'; font-src 'self' data:; img-src 'self' data:"
    if request.endpoint == "editbook.edit_book" or config.config_use_google_drive:
        resp.headers['Content-Security-Policy'] += " *"
    elif request.endpoint == "web.read_book":
        resp.headers['Content-Security-Policy'] += " blob:;style-src-elem 'self' blob: 'unsafe-inline';"
    resp.headers['X-Content-Type-Options'] = 'nosniff'
    resp.headers['X-Frame-Options'] = 'SAMEORIGIN'
    resp.headers['X-XSS-Protection'] = '1; mode=block'
    resp.headers['Strict-Transport-Security'] = 'max-age=31536000;'
    return resp

def cleanRoom(self, robot):
    """
    :type robot: Robot
    :rtype: None
    """
    directions = [(0, 1), (1, 0), (0, -1), (-1, 0)]

    def goBack(robot):
        robot.turnLeft()
        robot.turnLeft()
        robot.move()
        robot.turnRight()
        robot.turnRight()

    def dfs(pos, robot, d, lookup):
        robot.clean()
        for _ in directions:
            new_pos = (pos[0]+directions[d][0],
                       pos[1]+directions[d][1])
            if new_pos not in lookup:
                lookup.add(new_pos)
                if robot.move():
                    dfs(new_pos, robot, d, lookup)
                    goBack(robot)
            robot.turnRight()
            d = (d+1) % len(directions)
    
    dfs((0, 0), robot, 0, set())


