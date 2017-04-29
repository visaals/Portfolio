//
//  CoursesViewController.swift
//  washu_course_listings
//
//  Created by William Tong on 3/25/17.
//  Copyright © 2017 William Tong. All rights reserved.
//

import UIKit

class CoursesViewController: UIViewController, UITableViewDataSource, UITableViewDelegate, UISearchControllerDelegate, UISearchResultsUpdating {
    @IBOutlet weak var tableView: UITableView!

    let searchController = UISearchController(searchResultsController: nil)

    var schoolCode: String?
    var departmentID: Int?
    var courses: [NSDictionary] = []
    var filteredCourses: [NSDictionary] = []
    
    
    override func viewDidLoad() {
        super.viewDidLoad()
        
        print(schoolCode)
        print(departmentID)
        filteredCourses = courses
        // table view setup
        tableView.dataSource = self
        tableView.delegate = self
        tableView.rowHeight = UITableViewAutomaticDimension
        tableView.estimatedRowHeight = 150
        tableView.tableFooterView = UIView()
        
        // search bar setup
        searchController.searchResultsUpdater = self
        searchController.dimsBackgroundDuringPresentation = false
        searchController.hidesNavigationBarDuringPresentation = false
        definesPresentationContext = true
        tableView.tableHeaderView = searchController.searchBar
        
        self.title = "Courses"
        
        Client.sharedInstance.requestCourses(department_id:
            departmentID!, school_code: schoolCode!) { (success, result) in
                print(result)
                if success {
                    print("SUCCESSFUL")
                    if let courses = result["events"] as? [NSDictionary] {
                        self.courses = courses
                        self.filteredCourses = self.courses
                        print("courses")
                        print(courses.count)
                        if(self.courses.count==0){
                            let alertNote = "There are no current courses for this department"
                            let alertTitle = "Error"
                            self.alertMessage(message: alertNote, title: alertTitle)
                        }
                        self.tableView.reloadData()

                    }
                }else{
                    let alertNote = "There are no current courses for this department"
                    let alertTitle = "Error"
                    self.alertMessage(message: alertNote, title: alertTitle)
                }
        }
        
        tableView.reloadData()

    }
    
    func alertMessage(message: String, title: String = "") {
        let alertController = UIAlertController(title: title, message: message, preferredStyle: .alert)
        let OKAction = UIAlertAction(title: "OK", style: .default, handler: nil)
        alertController.addAction(OKAction)
        self.present(alertController, animated: true, completion: nil)
    }
    
    override func didReceiveMemoryWarning() {
        super.didReceiveMemoryWarning()
        // Dispose of any resources that can be recreated.
    }
    
//    func loadData(){
//        Client.sharedInstance.requestDepartments()
//    }
    
    
    func tableView(_ tableView: UITableView, numberOfRowsInSection section: Int) -> Int {
        return filteredCourses.count
    }
    
    func tableView(_ tableView: UITableView, cellForRowAt indexPath: IndexPath) -> UITableViewCell
    {
        let cell = tableView.dequeueReusableCell(withIdentifier: "coursesCell", for: indexPath as IndexPath) as! CoursesCell
        let courseData = filteredCourses[indexPath.row]
        let courseCode = courseData["course_code"] as? String
        let courseName = courseData["name"] as? String
        cell.title = "\(schoolCode!) \(departmentID!) \(courseCode!)"
        cell.name = "\(courseName!)"
        return cell
    }
    
    func tableView(_ tableView: UITableView, didSelectRowAt indexPath: IndexPath) {
//        performSegue(withIdentifier: "listingsSegue", sender: self)
    }
    
    override func prepare(for segue: UIStoryboardSegue, sender: Any?) {
        if segue.identifier == "listingsSegue" {
            let cell = sender as! UITableViewCell
            let indexPath = tableView.indexPath(for: cell)
            let listingsViewController = segue.destination as! ListingsViewController
            
            let sendCourse = filteredCourses[indexPath!.row]
            listingsViewController.schoolCode = schoolCode
            listingsViewController.departmentID = departmentID
            listingsViewController.courseName = sendCourse["name"] as? String
            listingsViewController.courseCode = sendCourse["course_code"] as? String
            
        }
    }
    
    func updateSearchResults(for searchController: UISearchController) {
        if let searchedText = searchController.searchBar.text {
            filterContentForSearchText(searchText: searchedText)
        }
    }
    
    func filterContentForSearchText(searchText: String, scope: String = "All") {
        if searchText != "" {
            filteredCourses = courses.filter { object in
                if let objectName = object["name"] as? String {
                    return objectName.lowercased().contains(searchText.lowercased())
                }else{
                    return false
                }
            }
        }else{
            filteredCourses = courses
        }
        
        tableView.reloadData()
    }
    
    func scrollViewWillBeginDragging(_ scrollView: UIScrollView) {
        searchController.searchBar.endEditing(true)
    }
    
    func searchBarTextDidBeginEditing(searchBar: UISearchBar) {
        searchBar.showsCancelButton = true;
    }
    
    func searchBarTextDidEndEditing(searchBar: UISearchBar) {
        searchBar.showsCancelButton = false;
    }
    
    deinit{
        if let superView = searchController.view.superview
        {
            superView.removeFromSuperview()
        }
    }
}
