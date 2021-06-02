#include "Random.h"

namespace Sun {

    Vector3D randomPointInUnitSphere() {
        Vector3D p;
        do {
            p = Vector3D(rand48(), rand48(), rand48()) * 2 - Vector3D(1, 1, 1);
        } while (p.dotProduct(p) >= 1.0);
        return p;
    }

    std::vector<Vector3D> randomIntVector3Ds(int x_min, int x_max, int y_min, int y_max, int z_min, int z_max, int n) {
        std::vector<Vector3D> res(n);
        for (int i = 0; i < n; ++i) {
            res[i] = randomIntVector3D(x_min, x_max, y_min, y_max, z_min, z_max);
        }
        return std::move(res);
    }

    std::vector<std::vector<Vector3D>> buildScatterPoints(const Vector3D& start,
        const Vector3D& box, float r, int n)
    {
        std::vector<std::vector<Vector3D>> result;
        randomSeed();
        for (int i = 0; i < n; ++i) {
            Vector3D center = randomVector3D(start.x, start.x + box.x, start.y, start.y + box.y,
                start.z, start.z + box.z);
            std::vector<Vector3D> vec = randomVector3Ds(center.x - r / 2, center.x + r / 2, center.y - r / 2, center.y + r / 2, center.z - r / 2, center.z + r / 2, n);
            //把超出范围的平移到范围内部
            for (int j = 0; j < vec.size(); ++j) {
                if (vec[j].x < start.x)vec[j].x = start.x;
                if (vec[j].y < start.y)vec[j].y = start.y;
                if (vec[j].z < start.z)vec[j].z = start.z;
                if (vec[j].x > start.x + box.x) vec[j].x = start.x + box.x;
                if (vec[j].y > start.y + box.y)vec[j].y = start.y + box.y;
                if (vec[j].z > start.z + box.z)vec[j].z = start.z + box.z;
            }
            result.push_back(vec);
        }
        return result;
    }


}