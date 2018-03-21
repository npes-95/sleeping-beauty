//
//  FirstViewController.swift
//  Smart Alarm
//
//  Created by Erika Bondareva on 26/02/2018.
//  Copyright © 2018 Sleeping Beauty. All rights reserved.
//

import UIKit
import UserNotifications

class FirstViewController: UIViewController {

    override func viewDidLoad() {
        super.viewDidLoad()
        // Do any additional setup after loading the view, typically from a nib.
        
        // Request authorization for notifications
        let center = UNUserNotificationCenter.current()
        let options: UNAuthorizationOptions = [.alert, .sound, .badge]
        center.requestAuthorization(options: options) { (granted, error) in
            if !granted {
                print("Something went wrong: notification authorization not granted")
            }
        }
    }

    override func didReceiveMemoryWarning() {
        super.didReceiveMemoryWarning()
        // Dispose of any resources that can be recreated.
    }
    
}


