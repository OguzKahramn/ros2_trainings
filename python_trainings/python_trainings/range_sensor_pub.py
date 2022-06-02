#!/usr/bin/env python3
import rclpy
from rclpy.node import Node
from tutorial_interfaces.msg import RangeSensor
import random
 
 
class RangeSensorPub(Node): 
    def __init__(self):
        super().__init__("Range_Sensor_Pub")
        
        self.publisher_ = self.create_publisher(RangeSensor, "RangeSensor",10)
        self.timer_ = self.create_timer(0.5,self.callback_range_sensor)

    def callback_range_sensor(self):
        msg = RangeSensor()
        msg.range = random.randint(0,100)
        self.publisher_.publish(msg)
 
 
def main(args=None):
    rclpy.init(args=args)
    node = RangeSensorPub()
    rclpy.spin(node)
    rclpy.shutdown()
 
 
if __name__ == "__main__":
    main()