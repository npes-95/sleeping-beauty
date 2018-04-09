//
//  AlarmInfo.swift
//  Smart Alarm
//
//  Created by Erika Bondareva on 08/04/2018.
//  Copyright © 2018 Sleeping Beauty. All rights reserved.
//

import Foundation

struct AlarmInfo: Codable {
    let alarmTime: String?
    let isAlarmSet: String
}

struct SetAlarmInfo: Codable {
    let desiredAlarmTime: String
}

struct SetAlarmResponse: Codable {
    let humanReadableResponse: String
}

