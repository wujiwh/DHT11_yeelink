#!/bin/sh
#=============================================================================
#     FileName: dht11_curl.sh
#         Desc:
#       Author: wangheng
#        Email: wujiwh@gmail.com
#     HomePage: http://wangheng.org
#      Version: 0.0.1
#   LastChange: 2015-01-28 00:30:11
#      History:
#=============================================================================


#填入yeelink的API KEY
yeelink_ApiKey='XXX'
yeelink_URL='http://api.yeelink.net/v1.1/device/XXX/sensor/XXX/datapoints'
temp=$(./dht11 1 |awk '/Hum/' |awk -F '=' '{print $2}'|sed 's/%//')
echo $temp

curl_cmd="curl --request POST --data '{\"value\":$temp}' --header U-ApiKey:$yeelink_ApiKey --verbose $yeelink_URL"
 
echo $curl_cmd|sh
