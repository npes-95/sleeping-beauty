//
//  ViewController.swift
//  Smart Alarm
//
//  Created by Erika Bondareva on 07/04/2018.
//  Copyright © 2018 Sleeping Beauty. All rights reserved.
//

import UIKit

class CancelAlarmViewController: UIViewController {
    
    let cancelAlarmKey = "cancelAlarm"
    
    @IBOutlet weak var alarmConfirmation: UILabel!
    public var alarmTime = "Alarm was not set"
    
    override func viewDidLoad() {
        super.viewDidLoad()
        alarmConfirmation.text = alarmTime
        // Do any additional setup after loading the view.
    }

    override func didReceiveMemoryWarning() {
        super.didReceiveMemoryWarning()
        // Dispose of any resources that can be recreated.
    }

    
    @IBAction func cancelAlarm(_ sender: Any) {
        guard let request = Networking.getRequest(for: SecondViewController.serverUrl + cancelAlarmKey, header: [SecondViewController.headerKey: SecondViewController.authToken]) else {
            return
        }
        let task = Networking.networkTask(for: request) {_ in
            self.dismiss(animated: true, completion: nil)
        }
        task.resume()
    }
    
    

    /*
    // MARK: - Navigation

    // In a storyboard-based application, you will often want to do a little preparation before navigation
    override func prepare(for segue: UIStoryboardSegue, sender: Any?) {
        // Get the new view controller using segue.destinationViewController.
        // Pass the selected object to the new view controller.
    }
    */

}
