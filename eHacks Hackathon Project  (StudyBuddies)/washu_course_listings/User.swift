//
//  User.swift
//  washu_course_listings
//
//  Created by William Tong on 3/25/17.
//  Copyright © 2017 William Tong. All rights reserved.
//

import UIKit

class User: NSObject {
    var username: String?
    var userID: Int?
    var latitude: Float?
    var longitude: Float?
    var currentAssignmentID: Int?
    
//    init() {
//    }
    
    class var currentUser: User {
        struct Static {
            static let instance = User()
        }
        return Static.instance
    }
    
}
