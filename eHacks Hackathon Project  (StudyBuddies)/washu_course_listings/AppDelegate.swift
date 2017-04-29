//
//  AppDelegate.swift
//  washu_course_listings
//
//  Created by William Tong on 3/24/17.
//  Copyright © 2017 William Tong. All rights reserved.
//

import UIKit
import GoogleMaps

@UIApplicationMain
class AppDelegate: UIResponder, UIApplicationDelegate {

    var window: UIWindow?
    private let googleMapsApiKey = "AIzaSyAGiQQj_d9VmKv4VuqGmcakJYvFpbKragA"


    func application(_ application: UIApplication, didFinishLaunchingWithOptions launchOptions: [UIApplicationLaunchOptionsKey: Any]?) -> Bool {
        // Override point for customization after application launch.
        GMSServices.provideAPIKey(googleMapsApiKey)

        return true
    }
    
//    func requestForAccess(completionHandler: (_ accessGranted: Bool) -> Void) {
//         
//        
//        let authorizationStatus = CNContactStore.authorizationStatusForEntityType(CNEntityType.Contacts)
//        
//        switch authorizationStatus {
//        case .Authorized:
//            completionHandler(accessGranted: true)
//            
//        case .Denied, .NotDetermined:
//            self.contactStore.requestAccessForEntityType(CNEntityType.Contacts, completionHandler: { (access, accessError) -> Void in
//                if access {
//                    completionHandler(accessGranted: access)
//                }
//                else {
//                    if authorizationStatus == CNAuthorizationStatus.Denied {
//                        dispatch_async(dispatch_get_main_queue(), { () -> Void in
//                            let message = "\(accessError!.localizedDescription)\n\nPlease allow the app to access your contacts through the Settings."
//                            self.showMessage(message)
//                        })
//                    }
//                }
//            })
//            
//        default:
//            completionHandler(false)
//        }
//    }


    func applicationWillResignActive(_ application: UIApplication) {
        // Sent when the application is about to move from active to inactive state. This can occur for certain types of temporary interruptions (such as an incoming phone call or SMS message) or when the user quits the application and it begins the transition to the background state.
        // Use this method to pause ongoing tasks, disable timers, and invalidate graphics rendering callbacks. Games should use this method to pause the game.
    }

    func applicationDidEnterBackground(_ application: UIApplication) {
        // Use this method to release shared resources, save user data, invalidate timers, and store enough application state information to restore your application to its current state in case it is terminated later.
        // If your application supports background execution, this method is called instead of applicationWillTerminate: when the user quits.
    }

    func applicationWillEnterForeground(_ application: UIApplication) {
        // Called as part of the transition from the background to the active state; here you can undo many of the changes made on entering the background.
    }

    func applicationDidBecomeActive(_ application: UIApplication) {
        // Restart any tasks that were paused (or not yet started) while the application was inactive. If the application was previously in the background, optionally refresh the user interface.
    }

    func applicationWillTerminate(_ application: UIApplication) {
        // Called when the application is about to terminate. Save data if appropriate. See also applicationDidEnterBackground:.
    }


}

