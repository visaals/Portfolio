//
//  CoursesCell.swift
//  washu_course_listings
//
//  Created by William Tong on 3/25/17.
//  Copyright © 2017 William Tong. All rights reserved.
//

import UIKit

class CoursesCell: UITableViewCell {

    @IBOutlet weak var titleLabel: UILabel!
    @IBOutlet weak var nameLabel: UILabel!
    
    var title: String?
    var name: String?

    
    override func awakeFromNib() {
        super.awakeFromNib()
        // Initialization code
    }
    
    override func layoutSubviews() {
        nameLabel.numberOfLines = 0
        nameLabel.lineBreakMode = NSLineBreakMode.byWordWrapping

        if let title = title{
            titleLabel.text = title
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
