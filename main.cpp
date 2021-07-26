#include <iostream>
#include "geom/Point3D.h"
#include "geom/Vector3D.h"

int main() {
    Point3D a(1,2,3);
    a += Vector3D(1,2,4);
    a.println();
}