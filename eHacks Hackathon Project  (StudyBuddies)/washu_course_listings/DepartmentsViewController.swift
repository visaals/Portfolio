//
//  DepartmentsViewController.swift
//  washu_course_listings
//
//  Created by William Tong on 3/25/17.
//  Copyright © 2017 William Tong. All rights reserved.
//

import UIKit

class DepartmentsViewController: UIViewController, UITableViewDelegate, UITableViewDataSource, UISearchControllerDelegate, UISearchResultsUpdating {
    @IBOutlet weak var tableView: UITableView!
    
    let searchController = UISearchController(searchResultsController: nil)
    
//    var filler = ["hi", "this", "is a test"]
//    var filteredResults: [String]?
    
    var departments: [NSDictionary] = []
    var filteredDepartments: [NSDictionary] = []
    
    
    override func viewDidLoad() {
        super.viewDidLoad()
        print("show departments")
        Client.sharedInstance.requestDepartments { (success,result) in
            print(result)
            if success {
                if let departments = result["events"] as? [NSDictionary] {
                    self.departments = departments
                    self.filteredDepartments = self.departments
                    print("departments")
                    print(self.departments)
                    self.tableView.reloadData()
                
                }
            }
        }
        
//        filteredResults = filler

        // table view setup
        tableView.dataSource = self
        tableView.delegate = self
        tableView.rowHeight = UITableViewAutomaticDimension
        tableView.estimatedRowHeight = 150
//        tableView.tableFooterView = UIView()
        
        // search bar setup
        searchController.searchResultsUpdater = self
        searchController.dimsBackgroundDuringPresentation = false
        searchController.hidesNavigationBarDuringPresentation = false
        definesPresentationContext = true
        tableView.tableHeaderView = searchController.searchBar
        
        self.title = "Departments"
       
        tableView.reloadData()

    }
    
    
    override func didReceiveMemoryWarning() {
        super.didReceiveMemoryWarning()
        // Dispose of any resources that can be recreated.
    }
    
//    func loadData(){
//        Client.sharedInstance.requestDepartments()
//    }
    
    
    func tableView(_ tableView: UITableView, numberOfRowsInSection section: Int) -> Int {
            return filteredDepartments.count

    }
    
    func tableView(_ tableView: UITableView, cellForRowAt indexPath: IndexPath) -> UITableViewCell
    {
        let cell = tableView.dequeueReusableCell(withIdentifier: "departmentsCell", for: indexPath as IndexPath) as! DepartmentsCell
        let departmentData = filteredDepartments[indexPath.row]
        let schoolCode = departmentData["school_code"] as? String
        let departmentID = departmentData["dept_id"] as? Int
        let departmentName = departmentData["dept_name"] as? String
        cell.schoolCode = schoolCode
        cell.departmentID = departmentID
        cell.name = "\(departmentName!)"
        return cell
    }
    
    func tableView(_ tableView: UITableView, didSelectRowAt indexPath: IndexPath) {
        
//        performSegue(withIdentifier: "coursesSegue", sender: indexPath)
    }
    
    override func prepare(for segue: UIStoryboardSegue, sender: Any?) {
        if segue.identifier == "coursesSegue" {
            let cell = sender as! UITableViewCell
            let indexPath = tableView.indexPath(for: cell)
            let coursesViewController = segue.destination as! CoursesViewController
            
            let sendDepartment = filteredDepartments[indexPath!.row]
            coursesViewController.schoolCode = sendDepartment["school_code"] as? String
            coursesViewController.departmentID = sendDepartment["dept_id"] as? Int

        }
    }
    
    
    func updateSearchResults(for searchController: UISearchController) {
        if let searchedText = searchController.searchBar.text {
            filterContentForSearchText(searchText: searchedText)
        }
    }
    
    func filterContentForSearchText(searchText: String, scope: String = "All") {
        if searchText != "" {
            filteredDepartments = departments.filter { object in
                if let objectName = object["dept_name"] as? String {
                    return objectName.lowercased().contains(searchText.lowercased())
                }else{
                    return false
                }
            }
        }else{
            filteredDepartments = departments
        }
        
        tableView.reloadData()
    }
    
    func scrollViewWillBeginDragging(_ scrollView: UIScrollView) {
        searchController.searchBar.endEditing(true)
    }
    
    func searchBarTextDidBeginEditing(searchBar: UISearchBar) {
        searchController.searchBar.endEditing(true)
    }
    
    func searchBarTextDidEndEditing(searchBar: UISearchBar) {
        searchController.searchBar.endEditing(true)
    }

//    override func prepareForSegue(segue: UIStoryboardSegue, sender: AnyObject?) {
//        if segue.identifier == "courseSegue" {
//            
//        }
//        
//    }

}
