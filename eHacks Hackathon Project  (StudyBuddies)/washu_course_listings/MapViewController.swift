//
//  MapViewController.swift
//  washu_course_listings
//
//  Created by William Tong on 3/25/17.
//  Copyright © 2017 William Tong. All rights reserved.
//

import UIKit
import GoogleMaps

class MapViewController: UIViewController, CLLocationManagerDelegate {
    
    @IBOutlet weak var containerView: UIView!
    
    let locationManager = CLLocationManager()
    var mapView: GMSMapView!

    var locations: [NSDictionary] = []
    var locationMarkers: [GMSMarker] = []

    let zoomLevel: Float = 13

    let defaultLocation = CLLocation(latitude: -33.869405, longitude: 151.199)

    
    override func viewDidLoad() {
        super.viewDidLoad()

        locationManager.delegate = self
        locationManager.desiredAccuracy = kCLLocationAccuracyBest
        locationManager.requestAlwaysAuthorization()
        locationManager.distanceFilter = 50
        locationManager.startUpdatingLocation()
        
        var mapCenter = defaultLocation
        if let userCoordinates = locationManager.location {
//            mapCenter = userCoordinates
        }
        let camera = GMSCameraPosition.camera(withLatitude: mapCenter.coordinate.latitude,
                                              longitude: mapCenter.coordinate.longitude,
                                              zoom: zoomLevel)
        mapView = GMSMapView.map(withFrame: containerView.bounds, camera: camera)
        mapView.isMyLocationEnabled = true
        mapView.settings.myLocationButton = true
        mapView.autoresizingMask = [.flexibleWidth, .flexibleHeight]
        containerView.addSubview(mapView)
        
        createMarker()
        
        Client.sharedInstance.requestBuildings { (success, result) in
            print(result)
            if success {
                if let buildings = result["events"] as? [NSDictionary] {
                    self.locations = buildings
                    self.setUpMarkers(locations: self.locations)

                }
            }else{
//                let alertNote = "There are no current courses for this department"
//                let alertTitle = "Error"
//                self.alertMessage(message: alertNote, title: alertTitle)
            }
        }

    }

    override func didReceiveMemoryWarning() {
        super.didReceiveMemoryWarning()
        // Dispose of any resources that can be recreated.
    }
    
    func loadMapView(){
        let camera = GMSCameraPosition.camera(withLatitude: -33.86, longitude: 151.20, zoom: 6.0)
        let mapView = GMSMapView.map(withFrame: CGRect.zero, camera: camera)
        
    }
    
    func createMarker(){
        let marker = GMSMarker()
        marker.position = CLLocationCoordinate2D(latitude: -33.86, longitude: 151.20)
        marker.title = "Sydney"
        marker.snippet = "Australia"
        marker.map = mapView
    }
    
    func setUpMarkers(locations: [NSDictionary]) {
        for location in locations {
            print("getting individual location")
            var locationMarker = GMSMarker()
            print(location["lat"])
            print(location["lng"])
            if let lat = location["lat"] as? String, let lng = location["lng"] as? String{
                print("DOUBLES")
                let coordinate = CLLocationCoordinate2D(latitude: Double(lat)!, longitude: Double(lng)!)
                locationMarker = GMSMarker(position: coordinate)
            }
            locationMarker.title = location["name"] as? String
            locationMarker.appearAnimation = kGMSMarkerAnimationPop
            locationMarker.isFlat = false
            locationMarker.snippet = "Time posted"
            locationMarker.map = mapView
            locationMarkers.append(locationMarker)
        }
    }
    
    func locationManager(_ manager: CLLocationManager, didUpdateLocations locations: [CLLocation]) {
        let userLocation:CLLocation = locations[0] 
        let long = userLocation.coordinate.longitude;
        let lat = userLocation.coordinate.latitude;
    }
    
    
    /*
    // MARK: - Navigation

    // In a storyboard-based application, you will often want to do a little preparation before navigation
    override func prepare(for segue: UIStoryboardSegue, sender: Any?) {
        // Get the new view controller using segue.destinationViewController.
        // Pass the selected object to the new view controller.
    }
    */

}
