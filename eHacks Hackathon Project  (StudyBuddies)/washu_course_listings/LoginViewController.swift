//
//  LoginViewController.swift
//  washu_course_listings
//
//  Created by William Tong on 3/24/17.
//  Copyright © 2017 William Tong. All rights reserved.
//

import UIKit
import GoogleMaps

class LoginViewController: UIViewController, CLLocationManagerDelegate {

    @IBOutlet weak var usernameText: UITextField!
    @IBOutlet weak var passwordText: UITextField!
    
    @IBOutlet weak var incorrectLabel: UILabel!
    
    let locationManager = CLLocationManager()
    
    override func viewDidLoad() {
        super.viewDidLoad()
        // Do any additional setup after loading the view.
        locationManager.delegate = self
        locationManager.requestAlwaysAuthorization()
        print("making test request")
        incorrectLabel.alpha = 0
    }

    override func didReceiveMemoryWarning() {
        super.didReceiveMemoryWarning()
        // Dispose of any resources that can be recreated.
    }
    
    @IBAction func login(_ sender: Any) {
        print("trying to login")
        if let user = usernameText.text {
            if let pass = passwordText.text{
                print("request to server")
                let username = "\(user)"
                let password = "\(pass)"
                Client.sharedInstance.loginWithCompletion(username: username, password: password, completion: { (success, message) in
                    print("Success \(success)")
                    if(success){
                        print(success)
                        print(message)
                        User.currentUser.username = username
                        self.performSegue(withIdentifier: "loginSegue", sender: self)
                    }else{
                        self.incorrectLabel.alpha = 1
                        UIView.animate(withDuration: 0.6, delay: 0.3, options: .curveEaseIn, animations: {
                            self.incorrectLabel.alpha = 0
                        })

                    }
                })
            }
        }
    }

    @IBAction func signUp(_ sender: Any) {
        if let user = usernameText.text {
            if let pass = passwordText.text{
                print("request to server")
                let username = "\(user)"
                let password = "\(pass)"
                Client.sharedInstance.createUserWithCompletion(username: username, password: password, completion: { (success, message) in
                    if(success){
                        print(success)
                        print(message)
                        User.currentUser.username = username
                        self.performSegue(withIdentifier: "loginSegue", sender: self)
                    }else{
                        self.incorrectLabel.alpha = 1
                        UIView.animate(withDuration: 0.6, delay: 0.3, options: .curveEaseIn, animations: {
                            self.incorrectLabel.alpha = 0
                        })
                        
                    }
                    
                })
            }
        }
    }
    
    /*
    // MARK: - Navigation

    // In a storyboard-based application, you will often want to do a little preparation before navigation
    override func prepare(for segue: UIStoryboardSegue, sender: Any?) {
        // Get the new view controller using segue.destinationViewController.
        // Pass the selected object to the new view controller.
    }
    */
    
    override func touchesBegan(_ touches: Set<UITouch>, with event: UIEvent?) {
        view.endEditing(true)
        super.touchesBegan(touches, with: event)
    }
    
    func textFieldShouldReturn(textField: UITextField) -> Bool {
        self.view.endEditing(true)
        return false
    }
    
    func textFieldDidBeginEditing(textField: UITextField) {
        textField.placeholder = nil
    }
    
    func textFieldDidEndEditing(textField: UITextField) {    //delegate method
        if(textField==usernameText){
            textField.placeholder = "Username"
        }else{
            textField.placeholder = "Password"
        }
    }

}
