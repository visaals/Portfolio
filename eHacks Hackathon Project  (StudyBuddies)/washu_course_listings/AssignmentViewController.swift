//
//  AssignmentViewController.swift
//  washu_course_listings
//
//  Created by William Tong on 3/25/17.
//  Copyright © 2017 William Tong. All rights reserved.
//

import UIKit

class AssignmentViewController: UIViewController, UITableViewDelegate, UITableViewDataSource {

    @IBOutlet weak var courseInfoLabel: UILabel!
    @IBOutlet weak var assignmentNameLabel: UILabel!
    @IBOutlet weak var locationLabel: UILabel!
    @IBOutlet weak var descriptionLabel: UILabel!
    @IBOutlet weak var tableView: UITableView!
    
    var schoolCode: String?
    var departmentID: Int?
    var courseCode: String?
    var courseName: String?
    var assignmentID: Int?
    var assignmentName: String?
    var assignmentLocation: String?
    var assignmentLat: Float?
    var assignmentLong: Float?
    var assignmentUsers: [String] = []
    
    var assignmentData: NSDictionary = [:]
//    var description: String?
    
    override func viewDidLoad() {
        super.viewDidLoad()
        // Do any additional setup after loading the view.
        courseInfoLabel.text = "\(schoolCode!) \(departmentID!) \(courseCode!)"
        assignmentNameLabel.text = "\(assignmentName!)"
        Client.sharedInstance.requestSingleAssignment(assignment_id: assignmentID!, completion: { (success, result) in
            print(result)
            if success {
                let assignment = result
                    self.assignmentData = assignment
                    self.assignmentLocation = self.assignmentData["location_name"] as? String
                    self.locationLabel.text = self.assignmentLocation
                    self.descriptionLabel.text = self.assignmentData["desc"] as? String
//                    self.assignmentUsers = assignment["users"]
                    self.tableView.reloadData()
                
            }else{
                let alertNote = "There are no current courses for this department"
                let alertTitle = "Error"
                self.alertMessage(message: alertNote, title: alertTitle)
            }

        })
    }

    override func didReceiveMemoryWarning() {
        super.didReceiveMemoryWarning()
        // Dispose of any resources that can be recreated.
    }
    
    func populateUsers(){
        
    }
    
    
    func joinGroup(){
        let title = "Success"
        let message = "Joined Study Group!"
        alertMessage(message: message, title: title)
    }
    
    func leaveGroup(){
        
    }
    
    func alertMessage(message: String, title: String = "") {
        let alertController = UIAlertController(title: title, message: message, preferredStyle: .alert)
        let OKAction = UIAlertAction(title: "OK", style: .default, handler: nil)
        alertController.addAction(OKAction)
        self.present(alertController, animated: true, completion: nil)
    }

    @IBAction func join(_ sender: Any) {
        joinGroup()
    }
    
    func tableView(_ tableView: UITableView, numberOfRowsInSection section: Int) -> Int {
        return assignmentUsers.count
    }
    
    func tableView(_ tableView: UITableView, cellForRowAt indexPath: IndexPath) -> UITableViewCell
    {
        let cell = tableView.dequeueReusableCell(withIdentifier: "peopleCell", for: indexPath as IndexPath) as! PeopleCell
        let assignmentUser = assignmentUsers[indexPath.row]
        cell.name = "\(assignmentUser)"
        return cell
    }
    
    func tableView(_ tableView: UITableView, didSelectRowAt indexPath: IndexPath) {
        
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
