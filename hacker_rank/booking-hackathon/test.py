import math;

def deg2rad(x):
    return x / 180.0 * 3.14159265359

def dist(lat1, lon1, lat2, lon2):
    a1 = deg2rad(lat1)
    b1 = deg2rad(lon1)
    a2 = deg2rad(lat2)
    b2 = deg2rad(lon2)
    earth = 6372
    return math.acos(
        math.sin(a1) * math.sin(a2) +
        math.cos(a1) * math.cos(a2) * math.cos(b2 - b1)) * earth

lat1 = 52.378281 # pt1
lon1 = 4.900070
lat2 = 52.372995 # pt4
lon2 = 4.893096
x1 = 52.379141
y1 = 4.880590
print dist(lat1, lon1, x1, y1)
print dist(lat2, lon2, x1, y1)
