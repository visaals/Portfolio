//
//  PeopleCell.swift
//  washu_course_listings
//
//  Created by William Tong on 3/26/17.
//  Copyright © 2017 William Tong. All rights reserved.
//

import UIKit

class PeopleCell: UITableViewCell {

    @IBOutlet weak var nameLabel: UILabel!
    var name: String?
    
    override func awakeFromNib() {
        super.awakeFromNib()
        // Initialization code
    }
    
    override func layoutSubviews() {
        if let name = name{
            nameLabel.text = "\(name)"
        }
    }

    override func setSelected(_ selected: Bool, animated: Bool) {
        super.setSelected(selected, animated: animated)

        // Configure the view for the selected state
    }

}
