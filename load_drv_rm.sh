# 移除模块

rmmodule=dev_meng

echo "sudo rm /dev/$rmmodule.ko"
sudo rm /dev/$rmmodule
echo "sudo rmmod $rmmodule.ko"
sudo rmmod $rmmodule #|| exit 1





