//
//  ListingsViewController.swift
//  washu_course_listings
//
//  Created by William Tong on 3/24/17.
//  Copyright © 2017 William Tong. All rights reserved.
//

import UIKit

class ListingsViewController: UIViewController, UITableViewDelegate, UITableViewDataSource, UISearchControllerDelegate, UISearchResultsUpdating {
    @IBOutlet weak var tableView: UITableView!
    
    let searchController = UISearchController(searchResultsController: nil)

    var schoolCode: String?
    var departmentID: Int?
    var courseCode: String?
    var courseName: String?
    var listings: [NSDictionary] = []
    var filteredListings: [NSDictionary] = []

    override func viewDidLoad() {
        super.viewDidLoad()
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
        
        self.title = "Listings"
        
        Client.sharedInstance.requestAssignments(department_id:
        departmentID!, school_code: schoolCode!, course_code:courseCode!) { (success, result) in
            print(result)
            if success {
                if let listings = result["events"] as? [NSDictionary] {
                    self.listings = listings
                    self.filteredListings = self.listings
                    print("listings")
                    print(self.listings)
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
        return filteredListings.count
    }
    
    func tableView(_ tableView: UITableView, cellForRowAt indexPath: IndexPath) -> UITableViewCell
    {
        let cell = tableView.dequeueReusableCell(withIdentifier: "listingsCell", for: indexPath as IndexPath) as! ListingsCell
        let listingsData = filteredListings[indexPath.row]
        let assignmentName = listingsData["name"] as? String
//        let assignmentID = listingsData["assignment_id"] as? Int
        cell.title = "\(schoolCode!) \(departmentID!) \(courseCode!)"
        cell.courseName = "\(courseName!)"
        cell.assignmentName = "\(assignmentName!)"
        return cell
    }
    
    func tableView(_ tableView: UITableView, didSelectRowAt indexPath: IndexPath) {
        
    }
    
    override func prepare(for segue: UIStoryboardSegue, sender: Any?) {
        if segue.identifier == "assignmentSegue" {
            let cell = sender as! UITableViewCell
            let indexPath = tableView.indexPath(for: cell)
            let  assignmentViewController = segue.destination as! AssignmentViewController
            
            let sendAssignment = filteredListings[indexPath!.row]
             assignmentViewController.schoolCode = schoolCode
             assignmentViewController.departmentID = departmentID
             assignmentViewController.courseName = courseName
             assignmentViewController.courseCode = courseCode
             assignmentViewController.assignmentID = sendAssignment["assignment_id"] as? Int
             assignmentViewController.assignmentName = sendAssignment["name"] as? String
        }
    }
    
    func updateSearchResults(for searchController: UISearchController) {
        if let searchedText = searchController.searchBar.text {
            filterContentForSearchText(searchText: searchedText)
        }
    }

    func filterContentForSearchText(searchText: String, scope: String = "All") {
        if searchText != "" {
            filteredListings = listings.filter { object in
                if let objectName = object["name"] as? String {
                    return objectName.lowercased().contains(searchText.lowercased())
                }else{
                    return false
                }
            }
        }else{
            filteredListings = listings
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
