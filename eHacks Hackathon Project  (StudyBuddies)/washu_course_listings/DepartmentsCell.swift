//
//  DepartmentsCell.swift
//  washu_course_listings
//
//  Created by William Tong on 3/25/17.
//  Copyright © 2017 William Tong. All rights reserved.
//

import UIKit

class DepartmentsCell: UITableViewCell {

    @IBOutlet weak var titleLabel: UILabel!
    @IBOutlet weak var nameLabel: UILabel!
    
    var schoolCode: String?
    var departmentID: Int?
    var name: String?
    
    override func awakeFromNib() {
        super.awakeFromNib()
        // Initialization code
    }
    
    override func layoutSubviews() {
        
        if let schoolCode = schoolCode{
            if let departmentID = departmentID {
                titleLabel.text = "\(schoolCode) \(departmentID)"
            }
        }
        if let name = name{
            nameLabel.text = "\(name)"
        }
    }

    override func setSelected(_ selected: Bool, animated: Bool) {
        super.setSelected(selected, animated: animated)

        // Configure the view for the selected state
    }

}
