import numpy as np
import matplotlib.pyplot as plt

def gen_rand_vec(dim: int) -> np.array:
    vecs = np.random.normal(size=(1, dim))
    return np.squeeze(vecs)

def generate_surface_pts(nopts: int) -> list:
    pts = []
    def inside_sphere() -> np.array:
        while True:
            pt = gen_rand_vec(dim=3)
            if(np.linalg.norm(pt) >= 1): 
                continue
            return pt
    while len(pts) < nopts: 
        v = inside_sphere()
        unit_v = v / np.linalg.norm(v)
        pts.append(unit_v)
    return pts

def main():
    surface_points = generate_surface_pts(300)
    x = np.array(list(map(lambda p: p[0], surface_points)))
    y = np.array(list(map(lambda p: p[1], surface_points)))
    z = np.array(list(map(lambda p: p[2], surface_points)))
    ax = plt.axes(projection ='3d')
    ax.plot(x, y, z, "ob")
    plt.show()

if __name__ == "__main__":
    main()

"""
Turns out that normalizing a given point inside a unit sphere, gives a
points that lies on its surface.
"""
