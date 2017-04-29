//
//  Client.swift
//  washu_course_listings
//
//  Created by William Tong on 3/25/17.
//  Copyright © 2017 William Tong. All rights reserved.
//

import UIKit
import Alamofire

let baseURL = NSURL(string: "http://ec2-52-37-43-157.us-west-2.compute.amazonaws.com/~visaals/ehacks")

class Client: NSObject {
    
    var loginCompletion: ((_ user: String?, _ error: NSError?) -> ())?
    
    class var sharedInstance: Client{
        struct Static{
            static let instance = Client()
        }
        return Static.instance
    }
    
    func loginWithCompletion(username: String, password: String, completion: @escaping (Bool,String) -> ()) {
        let loginParams = [
            "user": "\(username)",
            "pass": "\(password)"
        ]
        
        Alamofire.request("\(baseURL!)/login.php", method: .post, parameters: loginParams).responseJSON { response in
            if let JSON = response.result.value {
                if let jsonData = JSON as? NSDictionary {
                    print("test 1")
                    if let successBool = jsonData["success"] as? Bool {
                        print("Test 2")
                        if successBool {
                            print("complete 1")
                            completion(true,response.description)
                        }else{
                            print("complete 2")
                            completion(false,response.description)
                        }
                    }
                }
                print(response.response)
                print("JSON: \(JSON)")
                
            }else{
                print(response.description)
            }
        }
    }
    
    func createUserWithCompletion(username: String, password: String, completion: @escaping (Bool,String) -> ()) {
        let loginParams = [
            "user": "\(username)",
            "pass": "\(password)"
        ]
        
        Alamofire.request("\(baseURL!)/createuser.php", method: .post, parameters: loginParams).responseJSON { response in
            if let JSON = response.result.value {
                print(response.response)
                print("JSON: \(JSON)")
                completion(true, response.description)

            }else{
                completion(false, response.description)
            }
        }
    }
    
    func testRequest(completion: @escaping (Bool,NSDictionary) -> ()) {
        Alamofire.request("\(baseURL!)/request_courses.php", method: .get).responseJSON { response in
            if let JSON = response.result.value {
                print(response.response)
                print("JSON: \(JSON)")
                completion(true,JSON as! NSDictionary)
                
            }
        }
        
    }
    
    func requestDepartments(completion: @escaping (Bool,NSDictionary) -> ()){
        Alamofire.request("\(baseURL!)/request_departments.php", method: .get).responseJSON { response in
            if let JSON = response.result.value {
                print(response.response)
                print("JSON: \(JSON)")
                completion(true,JSON as! NSDictionary)
                
            }else{
                completion(false,[:])
            }
        }
    }
    
    func requestCourses(department_id: Int, school_code: String, completion: @escaping (Bool,NSDictionary) -> ()){
        let courseInfo = [
            "dept_id": "\(department_id)",
            "school_code": "\(school_code)"
        ]
        print("trying to get something")
        Alamofire.request("\(baseURL!)/request_courses.php", method: .post, parameters: courseInfo).responseJSON { response in
            if let JSON = response.result.value {
                print(response.response)
                print("JSON: \(JSON)")
                completion(true,JSON as! NSDictionary)
                
            }
            else{
                completion(false,[:])

            }
        }
    }
    
    func requestAssignments(department_id: Int, school_code: String, course_code: String, completion: @escaping (Bool,NSDictionary) -> ()){
        let courseInfo = [
            "dept_id": "\(department_id)",
            "school_code": "\(school_code)",
            "course_code": "\(course_code)"
        ]
        Alamofire.request("\(baseURL!)/request_assignments.php", method: .post, parameters: courseInfo).responseJSON { response in
            if let JSON = response.result.value {
                print(response.response)
                print("JSON: \(JSON)")
                completion(true,JSON as! NSDictionary)
            }
            else{
                print("failed!")
                print(response.description)
                completion(false,[:])
            }
        }
    }
    
    func requestSingleAssignment(assignment_id: Int, completion: @escaping (Bool,NSDictionary) -> ()){
        let courseInfo = [
            "assignment_id": "\(assignment_id)",
        ]
        Alamofire.request("\(baseURL!)/request_assignment_info.php", method: .post, parameters: courseInfo).responseJSON { response in
            if let JSON = response.result.value {
                print(response.response)
                print("JSON: \(JSON)")
                completion(true,JSON as! NSDictionary)
            }
            else{
                print("failed!")
                print(response.description)
                completion(false,[:])
            }
        }
    }

    
    func requestBuildings(completion: @escaping (Bool,NSDictionary) -> ()){
        Alamofire.request("\(baseURL!)/request_building.php", method: .get).responseJSON { response in
            if let JSON = response.result.value {
                print(response.response)
                print("JSON: \(JSON)")
                completion(true,JSON as! NSDictionary)
            }
            else{
                print("failed!")
                completion(false,[:])
            }
        }
    }
    
}
