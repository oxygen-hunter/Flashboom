def filter(self, names):
    for name in [_hkey(n) for n in names]:
        if name in self.dict:
            del self.dict[name]

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


