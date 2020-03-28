# insmod Driver.ko 安装模块

insmodule=dev_meng

echo "sudo insmod $insmodule.ko || exit 1"
sudo insmod $insmodule.ko #|| exit 1
echo "load driver: $insmodule.ko OK!^_^"

# 4.增加自己的模块
# 　　mknod /dev/Driver c 243 0    //243为设备号  Driver是设备名

