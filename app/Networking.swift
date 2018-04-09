//
//  RequestBuilder.swift
//  Networking
//
//  Created by Vlad Z on 08/04/2018.
//  Copyright © 2018 Vlad Z. All rights reserved.
//

import UIKit

class Networking: NSObject {
    
    static func getRequest(for urlString: String, header: [String: String] = [:]) -> URLRequest? {
        guard let url = URL(string: urlString) else {
            print("Invalid URL: \(urlString)")
            return nil
        }
        var request = URLRequest(url: url)
        request.setValue("application/json", forHTTPHeaderField: "Content-Type")
        
        for (headerField, value) in header {
            request.setValue(value, forHTTPHeaderField: headerField)
        }
        return request
    }
    
    static func postRequest(for url: String, header: [String: String] = [:], postData: Data) -> URLRequest? {
        guard var request = getRequest(for: url, header: header) else {
            return nil
        }
        request.httpMethod = "POST"
        request.httpBody = postData	
        return request
    }
    
    static func networkTask(for request: URLRequest, completion: @escaping (Data)->Void) -> URLSessionDataTask{
        let task = URLSession.shared.dataTask(with: request) { data, response, error in
            guard let data = data, error == nil else {
                print("error=\(String(describing: error))")
                return
            }
            
            if let httpStatus = response as? HTTPURLResponse, httpStatus.statusCode != 200 {
                print("statusCode should be 200, but is \(httpStatus.statusCode)")
            }
            completion(data)
        }
        return task
    }
    
    static func decode<CodableClass: Codable>(for jsonData: Data) -> CodableClass? {
        let decoder = JSONDecoder()
        guard let marsWeather = try? decoder.decode(CodableClass.self, from: jsonData) else {
            print("Failed to decode json: \(String(describing: String(data: jsonData, encoding: .utf8)))")
            return nil
        }
        return marsWeather
    }
}
