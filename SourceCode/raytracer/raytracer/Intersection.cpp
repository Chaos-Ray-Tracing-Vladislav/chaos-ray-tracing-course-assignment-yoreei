#include "Intersection.h"

std::string toString(Intersection intersection) {
    switch (intersection) {
    case Intersection::SUCCESS: return "SUCCESS";
    case Intersection::PARALLEL: return "PARALLEL";
    case Intersection::BACKFACE: return "BACKFACE";
    case Intersection::OUT_OF_BOUNDS: return "OUT_OF_BOUNDS";
    case Intersection::BEHIND_RAY_ORIGIN: return "BEHIND_RAY_ORIGIN";
    default: return "UNKNOWN";
    }
}
