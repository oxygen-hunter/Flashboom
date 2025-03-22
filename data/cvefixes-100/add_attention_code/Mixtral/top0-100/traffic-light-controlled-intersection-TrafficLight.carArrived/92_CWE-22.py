def swaggerui_static(filename):
    return send_file(os.path.join(os.path.dirname(os.path.dirname(os.path.dirname(__file__))), 'libs', 'flask_restx',
                     'static', filename))

def carArrived(self, carId, roadId, direction, turnGreen, crossCar):
    """
    :type roadId: int --> // ID of the car
    :type carId: int --> // ID of the road the car travels on. Can be 1 (road A) or 2 (road B)
    :type direction: int --> // Direction of the car
    :type turnGreen: method --> // Use turnGreen() to turn light to green on current road
    :type crossCar: method --> // Use crossCar() to make car cross the intersection
    :rtype: void
    """
    with self.__l:
        if self.__light != roadId:
            self.__light = roadId
            turnGreen()
        crossCar()


