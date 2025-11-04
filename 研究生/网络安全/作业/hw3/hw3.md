# HW3

![image-20251023004512183](assets/image-20251023004512183.png)

## 实验报告

### 实验步骤

- 网卡设置：在工具中设置好网卡

  ![818aebebd9729cede64899231a33bb26](assets/818aebebd9729cede64899231a33bb26-1761151862100-2.png)

- 对不同的虚拟机按照表1对虚拟网络和ip信息配置

  以router为例：

  ![e40d8e034930822dcc6245ddbae0c6e6](assets/e40d8e034930822dcc6245ddbae0c6e6.png)

​		在网络连接中选中对应的网络进行ip设置，以VMnet5为例：

​		![2570abbc98696b26a193d09cc16e1bad](assets/2570abbc98696b26a193d09cc16e1bad.png)

- 后续几步完全依照4.2.3的步骤进行

  包括router、vpnserver、clientA和clientB的设置

- 在clientA上新建连接To-server，输入166.66.66.203，连接到vpn



### 实验结果

-  Client A和Client B的IP地址

  我的学号后三位是241，对170取模然后加20得到91，所以两者IP地址后三位应该是91

  

  在ClientA上输入ipconfig：

  ![bd05bb93696130e8ffc10d3dbc4e81cd](assets/bd05bb93696130e8ffc10d3dbc4e81cd.png)

​		在ClientA上ping  B

​		![2c391ca1f958507f59e626df87283a83](assets/2c391ca1f958507f59e626df87283a83.png)

从上面两张图上可以看出ClientA和B的ip地址后三位已经被设置为91



- 用IPconfig命令分别查看VPN客户机和VPN服务器的虚拟网络接口对应的IP地址

​		vpn客户机：<img src="assets/bd05bb93696130e8ffc10d3dbc4e81cd-1761152565924-8.png" alt="bd05bb93696130e8ffc10d3dbc4e81cd"  />

​		vpn服务器：

![9a47fd68005da6566d5a9bccb7f6fa3d](assets/9a47fd68005da6566d5a9bccb7f6fa3d.png)

- 启动VPN服务器的wireshark抓PPP数据包

  ![b3d8551ffd82c3a11144971ca1e6176c](assets/b3d8551ffd82c3a11144971ca1e6176c.png)