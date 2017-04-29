//
//  ListingsCell.swift
//  washu_course_listings
//
//  Created by William Tong on 3/24/17.
//  Copyright © 2017 William Tong. All rights reserved.
//

import UIKit

class ListingsCell: UITableViewCell {

    @IBOutlet weak var titleLabel: UILabel!
    var title: String?
    var courseName: String?
    var assignmentName: String?
    @IBOutlet weak var courseLabel: UILabel!
    @IBOutlet weak var assignmentLabel: UILabel!

    
    override func awakeFromNib() {
        super.awakeFromNib()
        // Initialization code
    }
    
    override func layoutSubviews() {
        if let title = title{
            titleLabel.text = title
        }
        if let courseName = courseName{
            courseLabel.text = "\(courseName)"
        }
        if let assignmentName = assignmentName{
            assignmentLabel.text = "\(assignmentName)"
        }
    }

    override func setSelected(_ selected: Bool, animated: Bool) {
        super.setSelected(selected, animated: animated)

        // Configure the view for the selected state
    }

}
