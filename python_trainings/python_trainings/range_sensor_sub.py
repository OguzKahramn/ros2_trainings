#!/usr/bin/env python3
import rclpy
from rclpy.node import Node
from tutorial_interfaces.msg import RangeSensor
 
 
class RangeSensorSub(Node): 
    def __init__(self):
        super().__init__("range_sensor_sub") 
        self.subs_ = self.create_subscription(RangeSensor, "RangeSensor", self.callback_message, 10)
    
    def callback_message(self,msg):
        self.get_logger().info('The range sensor value is : "%s"' % str(msg.range))
 
 
def main(args=None):
    rclpy.init(args=args)
    node = RangeSensorSub() 
    rclpy.spin(node)
    rclpy.shutdown()
 
 
if __name__ == "__main__":
    main()