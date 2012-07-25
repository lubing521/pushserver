AUTHOR:ZHANGSHIGUANG 
Email：zzsg2005@126.com 
QQ：87895224
简介：6年桌面软件开发，5年手机软件开发，2年后台软件开发。目前在学习后台和网站架构设计与软件开发；最熟悉C/C++，也熟悉其它多种语言、数据库；欢迎联系我。
2012.7


pushserver

pushserver routine is a service that running on windows server 2003.

推送服务程序
本推送服务程序设计为在windows server 2003上运行的后台服务程序。手机等终端可以通过HTTP协议连接到服务器；
连接协议如下：
客户端：GET http://domainname:port/please?imei=[15个数字的IMEI号码] HTTP/1.1 \r\n
服务器端：【直接下发json格式的结果，不给标准应答格式如header】
 {"statuscode":"1","title":"标题文本","text":"内容","cmd":"[跳转指令字]"}\r\n
 
 手机终端会定期连接后台服务器，后台服务程序检查数据库，看是否有信心给此手机终端；如果没有则下发{"statuscode":"0"}；如果有则按json格式下发信息。
 
 后台服务程序，难点在大并发连接的处理，故本程序采用了完成端口（IOCP）；
 对于恶意连接的处理，采用了一个线程检测每一个socket的连接时间的方式；
 数据库连接采用mysql connector C lib驱动，因为默认采用mysql数据库。
 
 一切尽在代码中，请看代码吧。
 欢迎来信探讨。
 
 