# insmod Driver.ko 安装模块

insmodule=dev_meng

echo "sudo insmod $insmodule.ko || exit 1"
sudo insmod $insmodule.ko #|| exit 1
echo "load driver: $insmodule.ko OK!^_^"

# 4.增加自己的模块
# 　　mknod /dev/dev_meng c 239 0    //239为设备号 dev_meng是设备名

