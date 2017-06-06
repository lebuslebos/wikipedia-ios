import MapKit

extension Array { // seems you can no longer do extension [CLLocationCoordinate2D] ?
    func wmf_boundingRegion(with boundingMetersPerPoint: Double) -> MKCoordinateRegion {
        var rect: MKMapRect?
        for element in self {
            guard let coordinate = element as? CLLocationCoordinate2D else {
                continue
            }
            let point = MKMapPointForCoordinate(coordinate)
            let mapPointsPerMeter = MKMapPointsPerMeterAtLatitude(coordinate.latitude)
            let dimension = mapPointsPerMeter * boundingMetersPerPoint
            let size = MKMapSize(width: dimension, height: dimension)
            let coordinateRect = MKMapRect(origin: MKMapPointMake(point.x - 0.5*dimension, point.y - 0.5*dimension), size: size)
            guard let currentRect = rect else {
                rect = coordinateRect
                continue
            }
            rect = MKMapRectUnion(currentRect, coordinateRect)
        }
        
        guard let finalRect = rect else {
            return MKCoordinateRegion()
        }
        
        var region = MKCoordinateRegionForMapRect(finalRect)
        let adjustedLatitudeDelta = 1.3*region.span.latitudeDelta
        let adjustedLongitudeDelta = 1.3*region.span.longitudeDelta
        region.span.latitudeDelta = adjustedLatitudeDelta > 0.01 ? adjustedLatitudeDelta : 0.01 //max( is complaining about an extra param for some reason?
        region.span.longitudeDelta = adjustedLongitudeDelta > 0.01 ? adjustedLongitudeDelta : 0.01
        return region
    }
    var wmf_boundingRegion: MKCoordinateRegion {
        let metersPerPoint: Double = count == 1 ? 10000 : 50
        return wmf_boundingRegion(with: metersPerPoint)
    }
}

