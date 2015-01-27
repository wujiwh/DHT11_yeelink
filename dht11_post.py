#!/usr/bin/python
'''
#=============================================================================
#     FileName: dht11_post.py
#         Desc: 
#       Author: wangheng
#        Email: wujiwh@gmail.com
#     HomePage: http://wangheng.org
#      Version: 0.0.1
#   LastChange: 2015-01-27 22:40:37
#      History:
#=============================================================================
'''

import subprocess
import re
import json
import sys
import time
import datetime
import requests

API_Headers = {'U-ApiKey': 'XXX', 'content-type': 'application/json'}  
API_URL="http://api.yeelink.net/v1.1/device/%s/sensor/%s/datapoints"

device_id="XXX"
hum_sensor_id="XXX"
temp_sensor_id="XXX"

hum_url = API_URL % (device_id, hum_sensor_id)
temp_url = API_URL % (device_id, temp_sensor_id)

# Continuously append data
while(True):
  #to get the humidity and temperature readings!
  output = subprocess.check_output(["./dht11", "1"]);
  #print output
  matches = re.search("Temp=([0-9.]+)C", output)
  if (not matches):
	time.sleep(3)
	continue
  temp = float(matches.group(1))
  
  # search for humidity printout
  matches = re.search("Hum=([0-9.]+)\%", output)
  if (not matches):
	time.sleep(3)
	continue
  humidity = float(matches.group(1))

  print "Temperature: %.1f C" % temp
  print "Humidity:    %.1f %%" % humidity
 
  try:

	#Post temp data
    post_data = {'value': temp}  
    r = requests.post(temp_url, headers=API_Headers, data=json.dumps(post_data))  
	#Post Humidity data
    post_data = {'value': humidity}  
    r = requests.post(hum_url, headers=API_Headers, data=json.dumps(post_data))  

    print "Post to yeelink success!"
  except:
    print "Unable to post data.  Check your connection?"
    sys.exit()

  # Wait seconds before continuing
  time.sleep(15)
