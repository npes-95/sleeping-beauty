//
//  SecondViewController.swift
//  Smart Alarm
//
//  Created by Erika Bondareva on 26/02/2018.
//  Copyright © 2018 Sleeping Beauty. All rights reserved.
//

import UIKit
import UserNotifications

class SecondViewController: UIViewController {
 
    override func viewDidLoad() {
        super.viewDidLoad()
        // Do any additional setup after loading the view, typically from a nib.
        NSLog("The alarm window loaded")
    }
    
    @IBOutlet weak var chosenAlarmTime: UIDatePicker!
    
    @IBAction func setAlarmButtonTapped(_ sender: Any) {
        
        let dateFormatter = DateFormatter()
        dateFormatter.dateStyle = .short
        dateFormatter.timeStyle = .short
        
        let alarmDateTimeString = String (dateFormatter.string(from: chosenAlarmTime.date))
        NSLog("Set Alarm Button was tapped : %@", alarmDateTimeString)
        
// Creating the notification for the alarm
        
        // The notification content + sound
        let alarmNotificationContent = UNMutableNotificationContent()
        alarmNotificationContent.title = NSString.localizedUserNotificationString(forKey: "Wake up!",
                                                                                  arguments: nil)
        alarmNotificationContent.body = NSString.localizedUserNotificationString(forKey: "Rise and shine, a beautiful day is ahead of you!",
                                                                                 arguments: nil)
        alarmNotificationContent.sound = UNNotificationSound.default()
            // when want to add my own soundtrack, use:  UNNotificationSound(named: "MySound.aiff")
        
            // Creating the notification actions: stop and snooze (Still part of notification content)
//        let snoozeAction = UNNotificationAction(identifier: "Snooze",
//                                                title: "Snooze",
//                                                options: [])
//        let stopAction = UNNotificationAction(identifier: "Stop",
//                                              title: "Stop",
//                                              options: .destructive)
//        let alarmNotificationCategory = UNNotificationCategory(identifier: "alarmCategoryIdentifier",
//                                                   actions: [snoozeAction, stopAction],
//                                                   intentIdentifiers: [],
//                                                   options: [])
//        UNUserNotificationCenter.current().setNotificationCategories([alarmNotificationCategory])
//        alarmNotificationContent.categoryIdentifier = "alarmCategoryIdentifier"
        
        // The notification trigger
            // First need to convert the Date into Date components
        let alarmDateComponents = Calendar.current.dateComponents([.year,.month,.day,.hour,.minute,.second,],
                                                                  from: chosenAlarmTime.date)
        
        let alarmTrigger = UNCalendarNotificationTrigger(dateMatching: alarmDateComponents,
                                                         repeats: false)
        
        // The alarm notification request object
        let request = UNNotificationRequest(identifier: "alarmNotification",
                                      content: alarmNotificationContent,
                                      trigger: alarmTrigger)
        
        UNUserNotificationCenter.current().add(request)
        
// Send the app user into the second alarm view controller

        
    }

    override func didReceiveMemoryWarning() {
        super.didReceiveMemoryWarning()
        // Dispose of any resources that can be recreated.
    }



}

