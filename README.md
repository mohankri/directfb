[naulinux-school]
name=NauLinux School
baseurl=http://downloads.naulinux.ru/pub/NauLinux/6.2/$basearch/sites/School/RPMS/
enabled=0
gpgcheck=1
gpgkey=http://downloads.naulinux.ru/pub/NauLinux/RPM-GPG-KEY-linux-ink


sudo yum --enablerepo=naulinux-school install directfb
sudo yum --enablerepo=naulinux-school install directfb-devel

