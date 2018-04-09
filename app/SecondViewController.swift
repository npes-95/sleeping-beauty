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

    static let headerKey = "auth_token"
    static let authToken = "8ad4a3b3-8d28-47ae-87a1-b2c25ffe916d"
    static let serverUrl = "https://sleeping-beauty-api.herokuapp.com/"
    let getAlarmInfo = "getAlarmInfo"
    let setAlarm = "setAlarm"
    
    override func viewDidLoad() {
        super.viewDidLoad()
        getAlarmDetails()
    }
    
    @IBOutlet weak var chosenAlarmTime: UIDatePicker!
    
    func getAlarmDetails() {
        guard let request = Networking.getRequest(for: SecondViewController.serverUrl + getAlarmInfo, header: [SecondViewController.headerKey:SecondViewController.authToken]) else {
            return
        }
        let task = Networking.networkTask(for: request) {data in
            guard let alarmDetails: AlarmInfo = Networking.decode(for: data) else {
                return
            }
            if alarmDetails.isAlarmSet == "true" {
                let storyBoard = UIStoryboard.init(name: "Main", bundle: Bundle.main)
                let cancelViewController = storyBoard.instantiateViewController(withIdentifier: "cancelAlarm") as! CancelAlarmViewController
                let dateFormatter = DateFormatter()
                dateFormatter.dateFormat = "yyyy-MM-dd'T'HH:mm:ss.SSS'Z'"
                guard let alarmTime = alarmDetails.alarmTime,
                    let date = dateFormatter.date(from: alarmTime) else {
                    return
                }

                dateFormatter.dateFormat = "HH:mm"

                let dateString = dateFormatter.string(from: date)
                let alarmString = "Alarm is set for " + dateString
                cancelViewController.alarmTime = alarmString
                
                DispatchQueue.main.async {
                    self.present(cancelViewController, animated: true, completion: nil)
                }
            }
        }
        task.resume()
    }
    
    func set(alarmDetails: String) {
        
        guard let postData = try? JSONEncoder().encode(SetAlarmInfo(desiredAlarmTime: alarmDetails)),
            let request = Networking.postRequest(for: SecondViewController.serverUrl + setAlarm, header: [SecondViewController.headerKey:SecondViewController.authToken], postData: postData) else {
                return
        }
        let task = Networking.networkTask(for: request) {data in
            guard let alarmResponse: SetAlarmResponse = Networking.decode(for: data) else {
                return
            }
            let storyBoard = UIStoryboard.init(name: "Main", bundle: Bundle.main)
            let cancelViewController = storyBoard.instantiateViewController(withIdentifier: "cancelAlarm") as! CancelAlarmViewController
            cancelViewController.alarmTime = alarmResponse.humanReadableResponse.replacingOccurrences(of: " +00:00", with: "")
            DispatchQueue.main.async {
                self.present(cancelViewController, animated: true, completion: nil)
            }
            
        }
		        
        task.resume()
    }
    
    @IBAction func setAlarmButtonTapped(_ sender: Any) {
        
        let chosenDate = chosenAlarmTime.date
        let dateFormatter = DateFormatter()
        dateFormatter.dateFormat = "yyyy-MM-dd'T'HH:mm:ss"
        let dateString = dateFormatter.string(from: chosenDate)
        set(alarmDetails: dateString)
        return
        
        let alarmDateTimeString = String (dateFormatter.string(from: chosenAlarmTime.date))
        NSLog("Set Alarm Button was tapped : %@", alarmDateTimeString)
        
        

// **************************************************************
// Creating the notification for the alarm
// **************************************************************
        
        // The notification content + sound
        let alarmNotificationContent = UNMutableNotificationContent()
        alarmNotificationContent.title = NSString.localizedUserNotificationString(forKey: "Wake up!",
                                                                                  arguments: nil)
        alarmNotificationContent.body = NSString.localizedUserNotificationString(forKey: "Rise and shine, a beautiful day is ahead of you!",
                                                                                 arguments: nil)
        alarmNotificationContent.sound = UNNotificationSound.default()
            // when want to add my own soundtrack, use:  UNNotificationSound(named: "MySound.aiff")
        
        // Creating the notification actions: stop and snooze (Still part of notification content)
        let snoozeAction = UNNotificationAction(identifier: "Snooze",
                                                title: "Snooze",
                                                options: [])
        let stopAction = UNNotificationAction(identifier: "Stop",
                                              title: "Stop",
                                              options: .destructive)
        let alarmNotificationCategory = UNNotificationCategory(identifier: "alarmCategoryIdentifier",
                                                   actions: [snoozeAction, stopAction],
                                                   intentIdentifiers: [],
                                                   options: [])
    UNUserNotificationCenter.current().setNotificationCategories([alarmNotificationCategory])
        alarmNotificationContent.categoryIdentifier = "alarmCategoryIdentifier"
        
        
        
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
        
        let urlString = URL(string: "https://erikas-alarm-manager.herokuapp.com/getAlarmInfoAlways")
        if let url = urlString {
            let task = URLSession.shared.dataTask(with: url) { (data, response, error) in
                if error != nil {
                    print(error)
                } else {
                    if let data = data {
                        if let json = (try? JSONSerialization.jsonObject(with: data, options: .allowFragments)) as? [String: Any] {
                            if let isAlarmSet = json["isAlarmSet"] as? Bool {
                                print(isAlarmSet)
                            }
                            
                            if let alarmTime = json["alarmTime"] as? String {
                                let dateFormatter = DateFormatter()
                                dateFormatter.locale = Locale(identifier: "en_US_POSIX")
                                dateFormatter.timeZone = TimeZone.autoupdatingCurrent
                                dateFormatter.dateFormat = "yyyy-MM-dd'T'HH:mm:ss.SSSZ"
                                
                                let alarmTimeAsSwiftDate = dateFormatter.date(from: alarmTime)
                                print(alarmTimeAsSwiftDate as Any)
                            }
                        }
                    
                    }
                }
            }
            task.resume()
        }
 
// **************************************************************
// Send the app user into the second alarm view controller
// **************************************************************
        
    }

    override func didReceiveMemoryWarning() {
        super.didReceiveMemoryWarning()
        // Dispose of any resources that can be recreated.
    }



}
