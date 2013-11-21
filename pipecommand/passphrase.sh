#!/bin/sh
#echo -n `/sbin/ifconfig eth0|grep HWaddr|awk '{ print $5}'`

#PRODUCT_TYPE=$(cat /mcms/ProductType)
PRODUCT_TYPE=SOFT_MCU_MFW

if [[ "$PRODUCT_TYPE" == "SOFT_MCU_MFW" ]]
then
	#ethname=`cat /mcms/Cfg/NetworkCfg_Management.xml |grep "NETWORK_INTERFACE" | awk -F'<|>' '{if(NF>3) {print $3} }'`
	ethname=`cat NetworkCfg_Management.xml |grep "NETWORK_INTERFACE" | awk -F'<|>' '{if(NF>3) {print $3} }'`
    echo -n `/sbin/ifconfig $ethname|grep HWaddr|awk '{ print $5 }'`
else
	echo -n `/sbin/ifconfig eth0|grep HWaddr|awk '{ print $5 }'`
fi

